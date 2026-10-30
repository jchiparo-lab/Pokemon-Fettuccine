#include "global.h"
#include "event_data.h"
#include "item.h"
#include "item_menu.h"
#include "list_menu.h"
#include "malloc.h"
#include "mega_stone_case.h"
#include "script_menu.h"
#include "string_util.h"
#include "constants/hold_effects.h"
#include "constants/items.h"

// Fettuccine: the Mega Stone Case. Sam gives it with the Mega Ring, and it
// holds every Mega Stone and never runs out. While the player has it, the bag
// acts as if every Mega Stone is always there (see item.c): giving one to a
// Pokémon takes nothing away, and taking one off a Pokémon puts it back in
// the case instead of the Items pocket. Two Pokémon can hold the same stone.

// Every Mega Stone in the game, in alphabetical order (the case's menu order).
static const u16 sMegaStones[] =
{
    ITEM_ABOMASITE,
    ITEM_ABSOLITE,
    ITEM_AERODACTYLITE,
    ITEM_AGGRONITE,
    ITEM_ALAKAZITE,
    ITEM_ALTARIANITE,
    ITEM_AMPHAROSITE,
    ITEM_AUDINITE,
    ITEM_BANETTITE,
    ITEM_BEEDRILLITE,
    ITEM_BLASTOISINITE,
    ITEM_BLAZIKENITE,
    ITEM_CAMERUPTITE,
    ITEM_CHARIZARDITE_X,
    ITEM_CHARIZARDITE_Y,
    ITEM_DIANCITE,
    ITEM_GALLADITE,
    ITEM_GARCHOMPITE,
    ITEM_GARDEVOIRITE,
    ITEM_GENGARITE,
    ITEM_GLALITITE,
    ITEM_GYARADOSITE,
    ITEM_HERACRONITE,
    ITEM_HOUNDOOMINITE,
    ITEM_KANGASKHANITE,
    ITEM_LATIASITE,
    ITEM_LATIOSITE,
    ITEM_LOPUNNITE,
    ITEM_LUCARIONITE,
    ITEM_MANECTITE,
    ITEM_MAWILITE,
    ITEM_MEDICHAMITE,
    ITEM_METAGROSSITE,
    ITEM_MEWTWONITE_X,
    ITEM_MEWTWONITE_Y,
    ITEM_PIDGEOTITE,
    ITEM_PINSIRITE,
    ITEM_SABLENITE,
    ITEM_SALAMENCITE,
    ITEM_SCEPTILITE,
    ITEM_SCIZORITE,
    ITEM_SHARPEDONITE,
    ITEM_SLOWBRONITE,
    ITEM_STEELIXITE,
    ITEM_SWAMPERTITE,
    ITEM_TYRANITARITE,
    ITEM_VENUSAURITE,
};

// True when this item is a Mega Stone that the case looks after.
bool32 IsItemInMegaStoneCase(enum Item itemId)
{
    if (GetItemHoldEffect(itemId) != HOLD_EFFECT_MEGA_STONE)
        return FALSE;
    return CheckBagHasItem(ITEM_MEGA_STONE_CASE, 1);
}

// Script special: fills the dynamic multichoice with every stone's name.
// The choice ids are indexes into sMegaStones.
void MegaStoneCase_PushChoices(void)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sMegaStones); i++)
    {
        struct ListMenuItem item;
        u8 *name = Alloc(ITEM_NAME_LENGTH + 1);

        StringCopy(name, GetItemName(sMegaStones[i]));
        item.name = name;
        item.id = i;
        MultichoiceDynamic_PushElement(item);
    }
}

// Script special: turns the chosen index (VAR_RESULT) into gSpecialVar_ItemId.
void MegaStoneCase_SetChosenStone(void)
{
    if (gSpecialVar_Result < ARRAY_COUNT(sMegaStones))
        gSpecialVar_ItemId = sMegaStones[gSpecialVar_Result];
    else
        gSpecialVar_ItemId = ITEM_NONE;
}

// Old saves: Mega Stones picked up before the case existed sit in the Items
// pocket. Clear them out once the player has the case.
void MegaStoneCase_ClearBagStones(void)
{
    u32 i;

    for (i = 0; i < ARRAY_COUNT(sMegaStones); i++)
    {
        u16 count = CountTotalItemQuantityInBag(sMegaStones[i]);
        if (count != 0)
            RemoveBagItem_IgnoreMegaStoneCase(sMegaStones[i], count);
    }
}
