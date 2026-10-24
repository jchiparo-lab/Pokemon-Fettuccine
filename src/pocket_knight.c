#include "global.h"
#include "bg.h"
#include "event_data.h"
#include "gpu_regs.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "overworld.h"
#include "palette.h"
#include "pocket_knight.h"
#include "scanline_effect.h"
#include "script.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "task.h"
#include "text.h"
#include "window.h"
#include "constants/rgb.h"
#include "constants/songs.h"

// Pocket Knight Adventures: a small original side-scroller, a homemade
// tribute to Rocket Knight Adventures, hidden in the player's bedroom.
//
// Built in steps:
//   1. Name check and placeholder title screen
//   2. Scrolling level and parallax background
//   3. Player movement: run, jump (hold A to jump higher), B rocket dash
//   4. Obstacles and enemies (todo)
//   5. Win/lose and the Master Ball reward (todo)
//   6. Polish (todo)
//
// Art lives in graphics/pocket_knight/ as indexed 16-color PNGs, and the
// level layout is ASCII art in src/data/pocket_knight_level.h.

#include "data/pocket_knight_level.h"

#define LEVEL_PIXEL_WIDTH (POCKET_KNIGHT_LEVEL_WIDTH * 8)
#define CAMERA_MAX_X      (LEVEL_PIXEL_WIDTH - DISPLAY_WIDTH)

// Player physics. Positions and speeds are in 1/256ths of a pixel.
#define PLAYER_WIDTH      10 // hitbox, smaller than the 16x16 sprite
#define PLAYER_HEIGHT     14
#define WALK_SPEED        0x180
#define WALK_ACCEL        0x30
#define GRAVITY           0x40
#define MAX_FALL_SPEED    0x400
#define JUMP_SPEED        0x480
#define JUMP_CUT_SPEED    0x200 // letting go of A early caps the rise to this
#define DASH_SPEED        0x400
#define DASH_FRAMES       14
#define CAMERA_LEAD       100 // how far from the left edge the camera keeps the player

// The level BG is 64 tiles wide and wraps, so new columns are drawn into it
// as the camera scrolls.
#define LEVEL_MAP_WIDTH   64
#define BG_MAP_WIDTH      32
#define VISIBLE_COLUMNS   (DISPLAY_WIDTH / 8 + 1)

enum {
    BG_TEXT,
    BG_LEVEL,
    BG_SCENERY,
};

enum {
    PAL_TEXT_BACKDROP = 0,
    PAL_LEVEL = 1,
    PAL_SCENERY = 2,
    PAL_TEXT = 15,
};

// Tile numbers in graphics/pocket_knight/level_tiles.png
enum {
    LTILE_EMPTY,
    LTILE_GRASS,
    LTILE_DIRT,
    LTILE_BRICK,
    LTILE_SPIKES,
    LTILE_POLE,
    LTILE_FLAG,
    LTILE_POLE_TOP,
};

// Tile numbers in graphics/pocket_knight/background.png
enum {
    STILE_EMPTY,
    STILE_MOUNTAIN,
    STILE_SLOPE_UP,
    STILE_SLOPE_DOWN,
    STILE_PEAK,
    STILE_CLOUD_LEFT,
    STILE_CLOUD_RIGHT,
};

enum {
    WIN_TITLE,
    WIN_PROMPT,
    WIN_HUD,
};

// Frames in graphics/pocket_knight/knight.png (16x16 each, stacked)
enum {
    KFRAME_STAND,
    KFRAME_RUN1,
    KFRAME_RUN2,
    KFRAME_JUMP,
    KFRAME_BOOST,
};

#define TAG_KNIGHT 0x7100

struct PocketKnight
{
    u16 levelTilemap[LEVEL_MAP_WIDTH * 32];
    u16 sceneryTilemap[BG_MAP_WIDTH * 32];
    s32 cameraX;
    s16 drawnMin; // range of level columns currently in levelTilemap
    s16 drawnMax;
    s32 x; // top-left of the player's hitbox
    s32 y;
    s32 velX;
    s32 velY;
    s32 startX;
    s32 startY;
    u8 spriteId;
    bool8 onGround;
    bool8 facingLeft;
    bool8 canDash;
    u8 dashTimer;
    u8 animTimer;
};

static EWRAM_DATA struct PocketKnight *sPocketKnight = NULL;

static void CB2_InitPocketKnight(void);
static void CB2_PocketKnight(void);
static void VBlankCB_PocketKnight(void);
static void Task_Title_WaitFadeIn(u8 taskId);
static void Task_Title_HandleInput(u8 taskId);
static void Task_Title_FadeToLevel(u8 taskId);
static void Task_Level_WaitFadeIn(u8 taskId);
static void Task_Level_Main(u8 taskId);
static void Task_Exit(u8 taskId);

// Case-sensitive: "JOE F." and "joe f." don't count
static const u8 sSecretName[] = _("Joe F.");

static const u8 sText_TitleTop[] = _("POCKET KNIGHT");
static const u8 sText_TitleBottom[] = _("ADVENTURES");
static const u8 sText_TitlePrompt[] = _("A: START   B: QUIT");
static const u8 sText_Hud[] = _("A: JUMP  B: BOOST  START: QUIT");

static const u32 sLevelTiles_Gfx[] = INCBIN_U32("graphics/pocket_knight/level_tiles.4bpp");
static const u16 sLevelTiles_Pal[] = INCBIN_U16("graphics/pocket_knight/level_tiles.gbapal");
static const u32 sScenery_Gfx[] = INCBIN_U32("graphics/pocket_knight/background.4bpp");
static const u16 sScenery_Pal[] = INCBIN_U16("graphics/pocket_knight/background.gbapal");

static const u32 sKnight_Gfx[] = INCBIN_U32("graphics/pocket_knight/knight.4bpp");
static const u16 sKnight_Pal[] = INCBIN_U16("graphics/pocket_knight/knight.gbapal");

static const struct SpriteSheet sSpriteSheet_Knight = {sKnight_Gfx, sizeof(sKnight_Gfx), TAG_KNIGHT};
static const struct SpritePalette sSpritePalette_Knight = {sKnight_Pal, TAG_KNIGHT};

static const struct OamData sOam_Knight =
{
    .shape = SPRITE_SHAPE(16x16),
    .size = SPRITE_SIZE(16x16),
    .priority = 1,
};

static const struct SpriteTemplate sSpriteTemplate_Knight =
{
    .tileTag = TAG_KNIGHT,
    .paletteTag = TAG_KNIGHT,
    .oam = &sOam_Knight,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const u16 sTitleBackdropColor = RGB(2, 3, 10); // dark navy
static const u16 sSkyColor = RGB(13, 22, 30);

static const u16 sText_Pal[16] =
{
    RGB(2, 3, 10),   // 0: transparent
    RGB_WHITE,       // 1: text
    RGB(8, 8, 14),   // 2: text shadow
    RGB(31, 25, 4),  // 3: title gold
};

static const u8 sTextColors_White[] = {TEXT_COLOR_TRANSPARENT, 1, 2};
static const u8 sTextColors_Gold[] = {TEXT_COLOR_TRANSPARENT, 3, 2};

// Mountain height (in tiles) for each column of the repeating backdrop.
// Neighbors differ by at most 1 so the slopes join up.
static const u8 sMountainHeights[BG_MAP_WIDTH] =
{
    3, 4, 5, 6, 7, 6, 5, 4, 5, 6, 7, 8, 9, 8, 7, 6,
    5, 4, 3, 3, 4, 5, 6, 5, 4, 3, 2, 2, 3, 4, 4, 3,
};

static const struct BgTemplate sBgTemplates[] =
{
    {
        .bg = BG_TEXT,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .priority = 0
    },
    {
        .bg = BG_LEVEL,
        .charBaseIndex = 1,
        .mapBaseIndex = 28,
        .screenSize = 1, // 64x32 tiles
        .priority = 1
    },
    {
        .bg = BG_SCENERY,
        .charBaseIndex = 2,
        .mapBaseIndex = 26,
        .priority = 2
    },
};

static const struct WindowTemplate sWindowTemplates[] =
{
    [WIN_TITLE] = {
        .bg = BG_TEXT,
        .tilemapLeft = 2,
        .tilemapTop = 5,
        .width = 26,
        .height = 4,
        .paletteNum = PAL_TEXT,
        .baseBlock = 1
    },
    [WIN_PROMPT] = {
        .bg = BG_TEXT,
        .tilemapLeft = 2,
        .tilemapTop = 14,
        .width = 26,
        .height = 2,
        .paletteNum = PAL_TEXT,
        .baseBlock = 1 + 26 * 4
    },
    [WIN_HUD] = {
        .bg = BG_TEXT,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 30,
        .height = 2,
        .paletteNum = PAL_TEXT,
        .baseBlock = 1 + 26 * 4 + 26 * 2
    },
    DUMMY_WIN_TEMPLATE
};

void IsPlayerNamedJoeF(void)
{
    gSpecialVar_Result = (StringCompare(gSaveBlock2Ptr->playerName, sSecretName) == 0);
}

void StartPocketKnightAdventures(void)
{
    LockPlayerFieldControls();
    gMain.savedCallback = CB2_ReturnToFieldContinueScript;
    SetMainCallback2(CB2_InitPocketKnight);
}

static void PrintCentered(u8 windowId, const u8 *str, u8 y, const u8 *colors)
{
    u32 x = (sWindowTemplates[windowId].width * 8 - GetStringWidth(FONT_NORMAL, str, 0)) / 2;
    AddTextPrinterParameterized3(windowId, FONT_NORMAL, x, y, colors, TEXT_SKIP_DRAW, str);
}

static void ShowWindow(u8 windowId)
{
    PutWindowTilemap(windowId);
    CopyWindowToVram(windowId, COPYWIN_FULL);
}

static void PrintTitleScreen(void)
{
    FillWindowPixelBuffer(WIN_TITLE, PIXEL_FILL(0));
    PrintCentered(WIN_TITLE, sText_TitleTop, 1, sTextColors_Gold);
    PrintCentered(WIN_TITLE, sText_TitleBottom, 17, sTextColors_Gold);
    ShowWindow(WIN_TITLE);

    FillWindowPixelBuffer(WIN_PROMPT, PIXEL_FILL(0));
    PrintCentered(WIN_PROMPT, sText_TitlePrompt, 1, sTextColors_White);
    ShowWindow(WIN_PROMPT);

    ScheduleBgCopyTilemapToVram(BG_TEXT);
}

static void PrintHud(void)
{
    ClearWindowTilemap(WIN_TITLE);
    ClearWindowTilemap(WIN_PROMPT);
    FillWindowPixelBuffer(WIN_HUD, PIXEL_FILL(0));
    AddTextPrinterParameterized3(WIN_HUD, FONT_NORMAL, 4, 1, sTextColors_White, TEXT_SKIP_DRAW, sText_Hud);
    ShowWindow(WIN_HUD);
    ScheduleBgCopyTilemapToVram(BG_TEXT);
}

// Level drawing

static u8 GetLevelChar(s32 col, s32 row)
{
    if (col < 0 || col >= POCKET_KNIGHT_LEVEL_WIDTH || row < 0 || row >= POCKET_KNIGHT_LEVEL_HEIGHT)
        return '.';
    return sLevelLayout[row][col];
}

static u16 GetLevelTile(s32 col, s32 row)
{
    switch (GetLevelChar(col, row))
    {
    case '#':
        return (GetLevelChar(col, row - 1) == '#') ? LTILE_DIRT : LTILE_GRASS;
    case '=':
        return LTILE_BRICK;
    case '^':
        return LTILE_SPIKES;
    case '|':
        return LTILE_POLE;
    case 'F':
        return LTILE_FLAG;
    case 'P':
        return LTILE_POLE_TOP;
    default:
        return LTILE_EMPTY;
    }
}

static void DrawLevelColumn(s32 col)
{
    s32 row;
    s32 mapCol = col % LEVEL_MAP_WIDTH;
    // A 64-wide BG is stored as two 32x32 blocks (left half, then right half)
    u16 *dest = &sPocketKnight->levelTilemap[(mapCol / 32) * 32 * 32 + (mapCol % 32)];

    for (row = 0; row < POCKET_KNIGHT_LEVEL_HEIGHT; row++)
        dest[row * 32] = GetLevelTile(col, row) | (PAL_LEVEL << 12);
}

// Makes sure every column the camera can see is drawn into the wrapping tilemap.
static void UpdateLevelColumns(void)
{
    s32 first = sPocketKnight->cameraX / 8;
    s32 last = min(first + VISIBLE_COLUMNS, POCKET_KNIGHT_LEVEL_WIDTH - 1);
    bool32 changed = FALSE;

    while (sPocketKnight->drawnMax < last)
    {
        DrawLevelColumn(++sPocketKnight->drawnMax);
        sPocketKnight->drawnMin = max(sPocketKnight->drawnMin, sPocketKnight->drawnMax - (LEVEL_MAP_WIDTH - 1));
        changed = TRUE;
    }
    while (sPocketKnight->drawnMin > first)
    {
        DrawLevelColumn(--sPocketKnight->drawnMin);
        sPocketKnight->drawnMax = min(sPocketKnight->drawnMax, sPocketKnight->drawnMin + (LEVEL_MAP_WIDTH - 1));
        changed = TRUE;
    }
    if (changed)
        ScheduleBgCopyTilemapToVram(BG_LEVEL);
}

static void DrawScenery(void)
{
    s32 col, row, height, top;
    u16 *map = sPocketKnight->sceneryTilemap;

    for (col = 0; col < BG_MAP_WIDTH; col++)
    {
        s32 left = sMountainHeights[(col + BG_MAP_WIDTH - 1) % BG_MAP_WIDTH];
        s32 right = sMountainHeights[(col + 1) % BG_MAP_WIDTH];
        u16 topTile;

        height = sMountainHeights[col];
        top = POCKET_KNIGHT_LEVEL_HEIGHT - height;
        if (height > left && height > right)
            topTile = STILE_PEAK;
        else if (height > left)
            topTile = STILE_SLOPE_UP;
        else if (height > right)
            topTile = STILE_SLOPE_DOWN;
        else
            topTile = STILE_MOUNTAIN;

        map[top * BG_MAP_WIDTH + col] = topTile | (PAL_SCENERY << 12);
        for (row = top + 1; row < POCKET_KNIGHT_LEVEL_HEIGHT; row++)
            map[row * BG_MAP_WIDTH + col] = STILE_MOUNTAIN | (PAL_SCENERY << 12);
    }

    // A few clouds
    map[3 * BG_MAP_WIDTH + 4] = STILE_CLOUD_LEFT | (PAL_SCENERY << 12);
    map[3 * BG_MAP_WIDTH + 5] = STILE_CLOUD_RIGHT | (PAL_SCENERY << 12);
    map[5 * BG_MAP_WIDTH + 15] = STILE_CLOUD_LEFT | (PAL_SCENERY << 12);
    map[5 * BG_MAP_WIDTH + 16] = STILE_CLOUD_RIGHT | (PAL_SCENERY << 12);
    map[2 * BG_MAP_WIDTH + 24] = STILE_CLOUD_LEFT | (PAL_SCENERY << 12);
    map[2 * BG_MAP_WIDTH + 25] = STILE_CLOUD_RIGHT | (PAL_SCENERY << 12);

    ScheduleBgCopyTilemapToVram(BG_SCENERY);
}

static void UpdateScroll(void)
{
    ChangeBgX(BG_LEVEL, (sPocketKnight->cameraX % (LEVEL_MAP_WIDTH * 8)) << 8, BG_COORD_SET);
    ChangeBgX(BG_SCENERY, ((sPocketKnight->cameraX / 4) % (BG_MAP_WIDTH * 8)) << 8, BG_COORD_SET);
}

// Player

static bool32 IsSolidAt(s32 px, s32 py)
{
    s32 col = px >> 3;
    s32 row = py >> 3;

    if (col < 0 || col >= POCKET_KNIGHT_LEVEL_WIDTH)
        return TRUE; // walls at both ends of the level
    if (row < 0 || row >= POCKET_KNIGHT_LEVEL_HEIGHT)
        return FALSE; // open sky above, pits below
    return sLevelLayout[row][col] == '#' || sLevelLayout[row][col] == '=';
}

static void FindPlayerStart(void)
{
    s32 col, row;

    for (row = 0; row < POCKET_KNIGHT_LEVEL_HEIGHT; row++)
    {
        for (col = 0; col < POCKET_KNIGHT_LEVEL_WIDTH; col++)
        {
            if (sLevelLayout[row][col] == 'S')
            {
                // Stand on the bottom of the S tile
                sPocketKnight->startX = (col * 8) << 8;
                sPocketKnight->startY = ((row + 1) * 8 - PLAYER_HEIGHT) << 8;
                return;
            }
        }
    }
}

static void ResetPlayer(void)
{
    sPocketKnight->x = sPocketKnight->startX;
    sPocketKnight->y = sPocketKnight->startY;
    sPocketKnight->velX = 0;
    sPocketKnight->velY = 0;
    sPocketKnight->onGround = FALSE;
    sPocketKnight->facingLeft = FALSE;
    sPocketKnight->canDash = TRUE;
    sPocketKnight->dashTimer = 0;
}

static void MovePlayerX(void)
{
    s32 left, right, top, bottom, middle;

    sPocketKnight->x += sPocketKnight->velX;
    left = sPocketKnight->x >> 8;
    right = left + PLAYER_WIDTH - 1;
    top = sPocketKnight->y >> 8;
    bottom = top + PLAYER_HEIGHT - 1;
    middle = (top + bottom) / 2;

    if (sPocketKnight->velX > 0
     && (IsSolidAt(right, top) || IsSolidAt(right, middle) || IsSolidAt(right, bottom)))
    {
        sPocketKnight->x = (((right >> 3) << 3) - PLAYER_WIDTH) << 8;
        sPocketKnight->velX = 0;
        sPocketKnight->dashTimer = 0;
    }
    else if (sPocketKnight->velX < 0
          && (IsSolidAt(left, top) || IsSolidAt(left, middle) || IsSolidAt(left, bottom)))
    {
        sPocketKnight->x = (((left >> 3) + 1) << 3) << 8;
        sPocketKnight->velX = 0;
        sPocketKnight->dashTimer = 0;
    }
}

static void MovePlayerY(void)
{
    s32 left, right, top, bottom;

    sPocketKnight->onGround = FALSE;
    sPocketKnight->y += sPocketKnight->velY;
    left = sPocketKnight->x >> 8;
    right = left + PLAYER_WIDTH - 1;
    top = sPocketKnight->y >> 8;
    bottom = top + PLAYER_HEIGHT - 1;

    if (sPocketKnight->velY > 0 && (IsSolidAt(left, bottom) || IsSolidAt(right, bottom)))
    {
        sPocketKnight->y = (((bottom >> 3) << 3) - PLAYER_HEIGHT) << 8;
        sPocketKnight->velY = 0;
        sPocketKnight->onGround = TRUE;
        sPocketKnight->canDash = TRUE;
    }
    else if (sPocketKnight->velY < 0 && (IsSolidAt(left, top) || IsSolidAt(right, top)))
    {
        sPocketKnight->y = (((top >> 3) + 1) << 3) << 8;
        sPocketKnight->velY = 0;
    }
    else if (sPocketKnight->velY >= 0 && (IsSolidAt(left, bottom + 1) || IsSolidAt(right, bottom + 1)))
    {
        // Standing still: gravity alone moves less than a pixel, so check just below the feet
        sPocketKnight->y = (top << 8);
        sPocketKnight->velY = 0;
        sPocketKnight->onGround = TRUE;
        sPocketKnight->canDash = TRUE;
    }
}

static void HandlePlayerInput(void)
{
    s32 target = 0;

    if (sPocketKnight->dashTimer)
    {
        // Rocket dash: straight line, no gravity, no steering
        sPocketKnight->dashTimer--;
        sPocketKnight->velX = sPocketKnight->facingLeft ? -DASH_SPEED : DASH_SPEED;
        sPocketKnight->velY = 0;
        return;
    }

    if (JOY_HELD(DPAD_LEFT))
    {
        target = -WALK_SPEED;
        sPocketKnight->facingLeft = TRUE;
    }
    else if (JOY_HELD(DPAD_RIGHT))
    {
        target = WALK_SPEED;
        sPocketKnight->facingLeft = FALSE;
    }

    // Ease toward the target speed (this also slows a dash back down to walking)
    if (sPocketKnight->velX < target)
        sPocketKnight->velX = min(sPocketKnight->velX + WALK_ACCEL, target);
    else if (sPocketKnight->velX > target)
        sPocketKnight->velX = max(sPocketKnight->velX - WALK_ACCEL, target);

    if (JOY_NEW(A_BUTTON) && sPocketKnight->onGround)
    {
        sPocketKnight->velY = -JUMP_SPEED;
        PlaySE(SE_LEDGE);
    }
    else if (!JOY_HELD(A_BUTTON) && sPocketKnight->velY < -JUMP_CUT_SPEED)
    {
        sPocketKnight->velY = -JUMP_CUT_SPEED;
    }

    if (JOY_NEW(B_BUTTON) && sPocketKnight->canDash)
    {
        sPocketKnight->canDash = FALSE;
        sPocketKnight->dashTimer = DASH_FRAMES;
        PlaySE(SE_M_JUMP_KICK);
        return;
    }

    sPocketKnight->velY = min(sPocketKnight->velY + GRAVITY, MAX_FALL_SPEED);
}

static void UpdateCamera(void)
{
    s32 cameraX = (sPocketKnight->x >> 8) - CAMERA_LEAD;

    sPocketKnight->cameraX = max(0, min(cameraX, CAMERA_MAX_X));
}

static void UpdatePlayerSprite(void)
{
    struct Sprite *sprite = &gSprites[sPocketKnight->spriteId];
    u32 frame;

    if (sPocketKnight->dashTimer)
        frame = KFRAME_BOOST;
    else if (!sPocketKnight->onGround)
        frame = KFRAME_JUMP;
    else if (sPocketKnight->velX != 0)
        frame = ((sPocketKnight->animTimer++ / 6) % 2) ? KFRAME_RUN2 : KFRAME_RUN1;
    else
        frame = KFRAME_STAND;

    sprite->oam.tileNum = sprite->sheetTileStart + frame * 4;
    sprite->oam.matrixNum = sPocketKnight->facingLeft ? ST_OAM_HFLIP : 0;

    // The 16x16 sprite is centered on its x/y; the hitbox sits at its bottom middle
    sprite->x = (sPocketKnight->x >> 8) + PLAYER_WIDTH / 2 - sPocketKnight->cameraX;
    sprite->y = (sPocketKnight->y >> 8) + PLAYER_HEIGHT - 8;
}

static void UpdatePlayer(void)
{
    HandlePlayerInput();
    MovePlayerX();
    MovePlayerY();

    // Fell into a pit: back to the start for now
    if ((sPocketKnight->y >> 8) > POCKET_KNIGHT_LEVEL_HEIGHT * 8)
        ResetPlayer();

    UpdateCamera();
    UpdatePlayerSprite();
}

static void LoadLevel(void)
{
    s32 col;

    LoadBgTiles(BG_LEVEL, sLevelTiles_Gfx, sizeof(sLevelTiles_Gfx), 0);
    LoadBgTiles(BG_SCENERY, sScenery_Gfx, sizeof(sScenery_Gfx), 0);
    LoadPalette(sLevelTiles_Pal, BG_PLTT_ID(PAL_LEVEL), PLTT_SIZE_4BPP);
    LoadPalette(sScenery_Pal, BG_PLTT_ID(PAL_SCENERY), PLTT_SIZE_4BPP);
    LoadPalette(&sSkyColor, BG_PLTT_ID(PAL_TEXT_BACKDROP), PLTT_SIZEOF(1));

    LoadSpriteSheet(&sSpriteSheet_Knight);
    LoadSpritePalette(&sSpritePalette_Knight);
    FindPlayerStart();
    ResetPlayer();
    sPocketKnight->spriteId = CreateSprite(&sSpriteTemplate_Knight, 0, 0, 0);

    sPocketKnight->cameraX = 0;
    for (col = 0; col < LEVEL_MAP_WIDTH; col++)
        DrawLevelColumn(col);
    sPocketKnight->drawnMin = 0;
    sPocketKnight->drawnMax = LEVEL_MAP_WIDTH - 1;
    ScheduleBgCopyTilemapToVram(BG_LEVEL);
    DrawScenery();
    UpdateScroll();
    UpdatePlayerSprite();
    PrintHud();
}

// Screen setup

static void CB2_InitPocketKnight(void)
{
    SetVBlankCallback(NULL);
    SetGpuReg(REG_OFFSET_DISPCNT, 0);
    SetGpuReg(REG_OFFSET_BG3CNT, 0);
    SetGpuReg(REG_OFFSET_BG2CNT, 0);
    SetGpuReg(REG_OFFSET_BG1CNT, 0);
    SetGpuReg(REG_OFFSET_BG0CNT, 0);
    ChangeBgX(0, 0, BG_COORD_SET);
    ChangeBgY(0, 0, BG_COORD_SET);
    ChangeBgX(1, 0, BG_COORD_SET);
    ChangeBgY(1, 0, BG_COORD_SET);
    ChangeBgX(2, 0, BG_COORD_SET);
    ChangeBgY(2, 0, BG_COORD_SET);
    ChangeBgX(3, 0, BG_COORD_SET);
    ChangeBgY(3, 0, BG_COORD_SET);
    DmaClearLarge16(3, (void *)VRAM, VRAM_SIZE, 0x1000);
    DmaClear32(3, (void *)OAM, OAM_SIZE);
    DmaClear16(3, (void *)PLTT, PLTT_SIZE);

    ScanlineEffect_Stop();
    ResetTasks();
    ResetSpriteData();
    ResetPaletteFade();
    FreeAllSpritePalettes();
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sBgTemplates, ARRAY_COUNT(sBgTemplates));
    sPocketKnight = AllocZeroed(sizeof(*sPocketKnight));
    SetBgTilemapBuffer(BG_LEVEL, sPocketKnight->levelTilemap);
    SetBgTilemapBuffer(BG_SCENERY, sPocketKnight->sceneryTilemap);
    InitWindows(sWindowTemplates);
    DeactivateAllTextPrinters();
    ClearScheduledBgCopiesToVram();

    LoadPalette(sText_Pal, BG_PLTT_ID(PAL_TEXT), PLTT_SIZE_4BPP);
    LoadPalette(&sTitleBackdropColor, BG_PLTT_ID(PAL_TEXT_BACKDROP), PLTT_SIZEOF(1));
    PrintTitleScreen();

    BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
    EnableInterrupts(INTR_FLAG_VBLANK);
    SetVBlankCallback(VBlankCB_PocketKnight);
    SetMainCallback2(CB2_PocketKnight);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0);
    SetGpuReg(REG_OFFSET_BLDY, 0);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
    ShowBg(BG_TEXT);
    ShowBg(BG_LEVEL);
    ShowBg(BG_SCENERY);
    CreateTask(Task_Title_WaitFadeIn, 0);
}

static void CB2_PocketKnight(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void VBlankCB_PocketKnight(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

// Title screen

static void Task_Title_WaitFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_Title_HandleInput;
}

static void Task_Title_HandleInput(u8 taskId)
{
    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_Title_FadeToLevel;
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_Exit;
    }
}

static void Task_Title_FadeToLevel(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        LoadLevel();
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        gTasks[taskId].func = Task_Level_WaitFadeIn;
    }
}

// Level

static void Task_Level_WaitFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_Level_Main;
}

static void Task_Level_Main(u8 taskId)
{
    if (JOY_NEW(START_BUTTON))
    {
        PlaySE(SE_SELECT);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_Exit;
        return;
    }

    UpdatePlayer();
    UpdateLevelColumns();
    UpdateScroll();
}

static void Task_Exit(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        // No wins yet; the reward check comes in a later step
        gSpecialVar_Result = FALSE;
        FreeAllWindowBuffers();
        UnsetBgTilemapBuffer(BG_LEVEL);
        UnsetBgTilemapBuffer(BG_SCENERY);
        FREE_AND_SET_NULL(sPocketKnight);
        DestroyTask(taskId);
        SetMainCallback2(gMain.savedCallback);
    }
}
