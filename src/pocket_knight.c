#include "global.h"
#include "bg.h"
#include "event_data.h"
#include "gpu_regs.h"
#include "main.h"
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
// tribute to Rocket Knight Adventures. Step 1: name check and a placeholder
// title screen that returns to the bedroom.

enum {
    WIN_TITLE,
    WIN_PROMPT,
};

static void CB2_InitPocketKnight(void);
static void CB2_PocketKnight(void);
static void VBlankCB_PocketKnight(void);
static void Task_PocketKnight_WaitFadeIn(u8 taskId);
static void Task_PocketKnight_HandleInput(u8 taskId);
static void Task_PocketKnight_Exit(u8 taskId);

// Case-sensitive: "JOE F." and "joe f." don't count
static const u8 sSecretName[] = _("Joe F.");

static const u8 sText_TitleTop[] = _("POCKET KNIGHT");
static const u8 sText_TitleBottom[] = _("ADVENTURES");
static const u8 sText_Placeholder[] = _("Coming soon! Press A to quit.");

static const u16 sPocketKnight_Pal[16] =
{
    RGB(2, 3, 10),   // 0: background (dark navy)
    RGB_WHITE,       // 1: text
    RGB(8, 8, 14),   // 2: text shadow
    RGB(31, 25, 4),  // 3: title gold
};

static const u8 sTextColors_White[] = {TEXT_COLOR_TRANSPARENT, 1, 2};
static const u8 sTextColors_Gold[] = {TEXT_COLOR_TRANSPARENT, 3, 2};

static const struct BgTemplate sBgTemplates[] =
{
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .priority = 0
    },
};

static const struct WindowTemplate sWindowTemplates[] =
{
    [WIN_TITLE] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 5,
        .width = 26,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 1
    },
    [WIN_PROMPT] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 14,
        .width = 26,
        .height = 2,
        .paletteNum = 15,
        .baseBlock = 1 + 26 * 4
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

static void PrintTitleScreen(void)
{
    FillWindowPixelBuffer(WIN_TITLE, PIXEL_FILL(0));
    PrintCentered(WIN_TITLE, sText_TitleTop, 1, sTextColors_Gold);
    PrintCentered(WIN_TITLE, sText_TitleBottom, 17, sTextColors_Gold);
    PutWindowTilemap(WIN_TITLE);
    CopyWindowToVram(WIN_TITLE, COPYWIN_FULL);

    FillWindowPixelBuffer(WIN_PROMPT, PIXEL_FILL(0));
    PrintCentered(WIN_PROMPT, sText_Placeholder, 1, sTextColors_White);
    PutWindowTilemap(WIN_PROMPT);
    CopyWindowToVram(WIN_PROMPT, COPYWIN_FULL);

    ScheduleBgCopyTilemapToVram(0);
}

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
    InitWindows(sWindowTemplates);
    DeactivateAllTextPrinters();
    ClearScheduledBgCopiesToVram();

    LoadPalette(sPocketKnight_Pal, BG_PLTT_ID(0), PLTT_SIZE_4BPP);
    LoadPalette(sPocketKnight_Pal, BG_PLTT_ID(15), PLTT_SIZE_4BPP);
    PrintTitleScreen();

    BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
    EnableInterrupts(INTR_FLAG_VBLANK);
    SetVBlankCallback(VBlankCB_PocketKnight);
    SetMainCallback2(CB2_PocketKnight);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0);
    SetGpuReg(REG_OFFSET_BLDY, 0);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON);
    ShowBg(0);
    CreateTask(Task_PocketKnight_WaitFadeIn, 0);
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

static void Task_PocketKnight_WaitFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_PocketKnight_HandleInput;
}

static void Task_PocketKnight_HandleInput(u8 taskId)
{
    if (JOY_NEW(A_BUTTON | B_BUTTON))
    {
        PlaySE(SE_SELECT);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_PocketKnight_Exit;
    }
}

static void Task_PocketKnight_Exit(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        // Placeholder never counts as a win; the reward check comes in a later step
        gSpecialVar_Result = FALSE;
        FreeAllWindowBuffers();
        DestroyTask(taskId);
        SetMainCallback2(gMain.savedCallback);
    }
}
