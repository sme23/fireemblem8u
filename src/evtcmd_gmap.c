#include "global.h"

#include "hardware.h"
#include "bm.h"
#include "chapterdata.h"
#include "bmmap.h"
#include "bmudisp.h"
#include "bmtrick.h"
#include "bksel.h"
#include "bmunit.h"
#include "prepscreen.h"
#include "ekrbattle.h"
#include "bmlib.h"
#include "worldmap.h"
#include "face.h"
#include "scene.h"

#include "event.h"

//! FE8U = 0x0800B910
void sub_800B910(u8 bg1, u8 bg2, u8 c)
{
    CpuFastCopy(
        (void *)(0x6000000 + GetBackgroundTileDataOffset(bg1)),
        (void *)(0x6000000 + GetBackgroundTileDataOffset(bg2)), c * 0x800);
    return;
}

extern int gUnknown_080D792C[4];

//! FE8U = 0x0800B954
void sub_800B954(u8 a, u8 bg, u8 c)
{
    int hack[4];
    memcpy(hack, gUnknown_080D792C, 16);

    CpuFastCopy((void *)hack[a], (void *)hack[bg], c * 0x800);
    BG_EnableSyncByMask(1 << bg);

    return;
}

//! FE8U = 0x0800B994
void sub_800B994(u8 a, u8 b, u8 c)
{
    CpuFastCopy(a * 0x10 + gPaletteBuffer, b * 0x10 + gPaletteBuffer, c * 0x20);
    EnablePaletteSync();

    return;
}

//! FE8U = 0x0800B9B8
void sub_800B9B8(u8 bg, u8 b)
{
    u16 i;

    u16 * buf = BG_GetMapBuffer(bg);

    for (i = 0; i < 0x400; i++)
    {
        int tmp = *buf;
        u8 a = (tmp >> 0xc);
        a += b;

        *buf &= 0xfff;
        *buf |= ((a) << 0xc);
        buf++;
    }

    BG_EnableSyncByMask(1 << bg);

    return;
}

extern u16 end[];

//! FE8U = 0x0800BA04
void sub_800BA04(u8 a, u8 b)
{
    u16 * palPtr = gPaletteBuffer + a * 0x10;

    u16 * ptr = end;
    *ptr++ = a;
    *ptr++ = b;

    CpuFastCopy(palPtr, end + 2, b * 0x20);

    return;
}

//! FE8U = 0x0800BA34
void sub_800BA34(void)
{
    u16 * ptr = end;

    int b = *ptr++;
    int c = *ptr++;

    CpuFastCopy(ptr, gPaletteBuffer + b * 0x10, c * 0x20);
    EnablePaletteSync();
    return;
}

void StoreAdjustedCameraPositions(int xIn, int yIn, int * xOut, int * yOut);

//! FE8U = 0x0800BA5C
void SetSomeRealCamPos(int x, int y, s8 unk)
{
    int xOut;
    int yOut;

    if (unk == 1)
    {
        StoreAdjustedCameraPositions(x, y, &xOut, &yOut);
        gBmSt.camera.x = xOut * 16;
        gBmSt.camera.y = yOut * 16;
    }
    else
    {
        gBmSt.camera.x = GetCameraAdjustedX(x * 16);
        gBmSt.camera.y = GetCameraAdjustedY(y * 16);
    }

    return;
}

//! FE8U = 0x0800BAA8
void sub_800BAA8(s16 visionRange, s8 flag, ProcPtr parent)
{
    if (visionRange < 0)
    {
        visionRange = GetROMChapterStruct(gPlaySt.chapterIndex)->initialFogLevel;
    }

    if (flag == 1)
    {
        RenderBmMapOnBg2();
    }

    gPlaySt.chapterVisionRange = visionRange;

    RefreshEntityBmMaps();
    RefreshUnitSprites();
    RenderBmMap();

    if (flag == 1)
    {
        MakeNew6CBMXFADE2(1, parent);
    }

    return;
}

//! FE8U = 0x0800BAF8
void TriggerMapChanges(u16 id, s8 flag, ProcPtr parent)
{
    if (IsMapChangeEnabled(id))
    {
        return;
    }

    if (flag == 1)
    {
        RenderBmMapOnBg2();
    }

    ApplyMapChangesById(id);
    EnableMapChange(id);

    RefreshTerrainBmMap();
    UpdateRoofedUnits();
    RenderBmMap();

    if (flag == 1)
    {
        MakeNew6CBMXFADE2(1, parent);
    }

    return;
}

//! FE8U = 0x0800BB48
void sub_800BB48(u16 id, s8 flag, ProcPtr parent)
{
    if (IsMapChangeEnabled(id) != 1)
    {
        return;
    }
    if (flag == 1)
    {
        RenderBmMapOnBg2();
    }

    RevertMapChange(id);
    DisableMapChange(id);

    RefreshTerrainBmMap();
    UpdateRoofedUnits();
    RenderBmMap();

    if (flag == 1)
    {
        MakeNew6CBMXFADE2(1, parent);
    }

    return;
}

//! FE8U = 0x0800BB98
void sub_800BB98(void)
{
    int found = (int)Proc_Find(gProcScr_BKSEL);

    if ((-found | found) < 0)
    {
        InitBattleForecastFramePalettes();
    }

    return;
}

//! FE8U = 0x0800BBB4
s8 sub_800BBB4(u16 pid)
{
    int i;

    for (i = FACTION_BLUE + 1; i < FACTION_GREEN; i++)
    {
        struct Unit * unit = GetUnit(i);

        if (!UNIT_IS_VALID(unit))
        {
            continue;
        }

        if (unit->pCharacterData->number != pid)
        {
            continue;
        }

        return 1;
    }

    return 0;
}

//! FE8U = 0x0800BBE4
u16 sub_800BBE4(void)
{
    int i;

    u16 count = 0;

    for (i = FACTION_BLUE + 1; i < FACTION_GREEN; i++)
    {
        struct Unit * unit = GetUnit(i);

        if (!UNIT_IS_VALID(unit))
        {
            continue;
        }

        if (unit->state & US_DEAD)
        {
            continue;
        }

        count++;
    }

    return count;
}

//! FE8U = 0x0800BC1C
void HideAllUnits(void)
{
    int i;

    for (i = FACTION_BLUE + 1; i < FACTION_GREEN; i++)
    {
        struct Unit * unit = GetUnit(i);

        if (!UNIT_IS_VALID(unit))
        {
            continue;
        }

        if (unit->state & US_DEAD)
        {
            continue;
        }

        unit->state |= US_HIDDEN;
    }

    return;
}

//! FE8U = 0x0800BC50
struct Unit * GetUnitStructFromEventParameter(s16 pid)
{
    if (pid < -3)
    {
        return NULL;
    }

    switch (pid)
    {
        case -3:
            pid = (u16)gEventSlots[2];
            break;

        case -2:
            if (gBmMapUnit[((u16 *)(gEventSlots + 0xB))[1]][((u16 *)(gEventSlots + 0xB))[0]] != 0)
            {
                return GetUnit(gBmMapUnit[((u16 *)(gEventSlots + 0xB))[1]][((u16 *)(gEventSlots + 0xB))[0]]);
            }
            else
            {
                asm(""); // :/
                return NULL;
            }

        case -1:
            return gActiveUnit;

        case 0:
            pid = GetPlayerLeaderUnitId();
            break;
    }

    return GetUnitFromCharId(pid);
}

extern u16 unit_icon_pal_npc[];
extern u16 gPal_MapSpriteSepia[];
extern u16 unit_icon_pal_enemy[];
extern u16 gPal_MapSprite[];

//! FE8U = 0x0800BCDC
void sub_800BCDC(u16 palId)
{
    if (IsBattleDeamonActive())
    {
        return;
    }

    SetupMapSpritesPalettes();

    switch (palId & 0xf)
    {
        case 2:
            ApplyPalette(unit_icon_pal_enemy, 0x1C);
            break;

        case 3:
            ApplyPalette(unit_icon_pal_npc, 0x1C);
            break;

        case 4:
            ApplyPalette(gPal_MapSpriteSepia, 0x1C);
            break;
    }

    switch ((palId >> 4) & 0xf)
    {
        case 1:
            ApplyPalette(gPal_MapSprite, 0x1D);
            break;

        case 3:
            ApplyPalette(unit_icon_pal_npc, 0x1D);
            break;

        case 4:
            ApplyPalette(gPal_MapSpriteSepia, 0x1D);
            break;
    }

    switch ((palId >> 8) & 0xf)
    {
        case 1:
            ApplyPalette(gPal_MapSprite, 0x1E);
            break;

        case 2:
            ApplyPalette(unit_icon_pal_enemy, 0x1E);
            break;

        case 4:
            ApplyPalette(gPal_MapSpriteSepia, 0x1E);
            break;
    }

    return;
}

//! FE8U = 0x0800BDCC
u8 Event80_(struct EventEngineProc * proc)
{
    int a = EVT_CMD_ARG32_LE(proc->pEventCurrent);

    sub_80BA008(a);
    nullsub_5(a);

    return EVC_ADVANCE_YIELD;
}

//! FE8U = 0x0800BDE8
u8 Event81_(struct EventEngineProc * proc)
{
    if (EVENT_IS_SKIPPING(proc))
    {
        SetDispEnable(0, 0, 0, 0, 0);
        return EVC_ADVANCE_CONTINUE;
    }

    StartSlowLockingFadeToBlack(proc);
    return EVC_ADVANCE_YIELD;
}

//! FE8U = 0x0800BE2C
u8 Event82_EndWM(struct EventEngineProc * proc)
{
    EndWM(proc);
    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800BE38
u8 Event83_WM_SETCAM(struct EventEngineProc * proc)
{
    u16 x = EVT_CMD_ARGV(proc->pEventCurrent)[1];
    u16 y = EVT_CMD_ARGV(proc->pEventCurrent)[2];

    gGMData.xCamera = x;
    gGMData.yCamera = y;

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800BE4C
u8 Event84_WM_SETCAMONLOC(struct EventEngineProc * proc)
{
    u16 x;
    u16 y;

    int nodeId = EVT_CMD_ARG32_LE(proc->pEventCurrent);

    GetWMCenteredCameraPosition(nodeId[gWMNodeData].x, nodeId[gWMNodeData].y, &x, &y);

    gGMData.xCamera = x;
    gGMData.yCamera = y;

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800BE8C
u8 Event85_WM_SETCAMONSPRITE(struct EventEngineProc * proc)
{
    u16 x;
    u16 y;

    int unitId = EVT_CMD_ARG32_LE(proc->pEventCurrent);

    GetWMCenteredCameraPosition(
        gGMData.units[unitId].location[gWMNodeData].x, gGMData.units[unitId].location[gWMNodeData].y, &x, &y);

    gGMData.xCamera = x;
    gGMData.yCamera = y;

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800BED4
u8 Event86_WM_MOVECAM(struct EventEngineProc * proc)
{
    s16 xStart = EVT_CMD_ARGV(proc->pEventCurrent)[1];
    s16 yStart = EVT_CMD_ARGV(proc->pEventCurrent)[2];

    s16 xEnd = EVT_CMD_ARGV(proc->pEventCurrent)[3];
    s16 yEnd = EVT_CMD_ARGV(proc->pEventCurrent)[4];

    s16 speed = EVT_CMD_ARGV(proc->pEventCurrent)[5];
    s16 delay = EVT_CMD_ARGV(proc->pEventCurrent)[6];

    if (EVENT_IS_SKIPPING(proc) || (speed == 0 && delay == 0))
    {
        gGMData.xCamera = xEnd;
        gGMData.yCamera = yEnd;

        return EVC_ADVANCE_CONTINUE;
    }

    sub_80BF404(xStart, yStart, xEnd, yEnd, speed, delay);

    return EVC_ADVANCE_YIELD;
}

//! FE8U = 0x0800BF38
u8 Event87_(struct EventEngineProc * proc)
{
    s16 xEnd;
    s16 yEnd;

    s16 xStart = EVT_CMD_ARGV(proc->pEventCurrent)[1];
    s16 yStart = EVT_CMD_ARGV(proc->pEventCurrent)[2];

    u16 nodeId = EVT_CMD_ARGV(proc->pEventCurrent)[3];

    s16 speed = EVT_CMD_ARGV(proc->pEventCurrent)[4];
    s16 delay = EVT_CMD_ARGV(proc->pEventCurrent)[5];

    GetWMCenteredCameraPosition(nodeId[gWMNodeData].x, nodeId[gWMNodeData].y, &xEnd, &yEnd);

    if (EVENT_IS_SKIPPING(proc) || (speed == 0 && delay == 0))
    {
        gGMData.xCamera = xEnd;
        gGMData.yCamera = yEnd;

        return EVC_ADVANCE_CONTINUE;
    }

    sub_80BF404(xStart, yStart, xEnd, yEnd, speed, delay);

    return EVC_ADVANCE_YIELD;
}

//! FE8U = 0x0800BFD8
u8 Event88_(struct EventEngineProc * proc)
{
    s16 xEnd;
    s16 yEnd;

    s16 xStart = EVT_CMD_ARGV(proc->pEventCurrent)[1];
    s16 yStart = EVT_CMD_ARGV(proc->pEventCurrent)[2];

    u16 unitId = EVT_CMD_ARGV(proc->pEventCurrent)[3];

    s16 speed = EVT_CMD_ARGV(proc->pEventCurrent)[4];
    s16 delay = EVT_CMD_ARGV(proc->pEventCurrent)[5];

    GetWMCenteredCameraPosition(
        gGMData.units[unitId].location[gWMNodeData].x, gGMData.units[unitId].location[gWMNodeData].y, &xEnd, &yEnd);

    if (EVENT_IS_SKIPPING(proc) || (speed == 0 && delay == 0))
    {
        gGMData.xCamera = xEnd;
        gGMData.yCamera = yEnd;

        return EVC_ADVANCE_CONTINUE;
    }

    sub_80BF404(xStart, yStart, xEnd, yEnd, speed, delay);

    return EVC_ADVANCE_YIELD;
}

//! FE8U = 0x0800C084
u8 Event89_(struct EventEngineProc * proc)
{
    if (EVENT_IS_SKIPPING(proc))
    {
        if (sub_80BF3F4())
        {
            sub_80BF4A8();
        }

        return EVC_ADVANCE_CONTINUE;
    }

    if (!sub_80BF3F4())
    {
        return EVC_ADVANCE_YIELD;
    }

    return EVC_STOP_YIELD;
}

//! FE8U = 0x0800C0B8
u8 Event8A_(struct EventEngineProc * proc)
{
    gGMData.unk01 = 1;
    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800C0C8
void Event8B_(void)
{
    gGMData.unk01 = 0;
    return;
}

//! FE8U = 0x0800C0D4
u8 Event8C_(struct EventEngineProc * proc)
{
    s16 x = EVT_CMD_ARGV(proc->pEventCurrent)[1];
    s16 y = EVT_CMD_ARGV(proc->pEventCurrent)[2];

    gGMData.unk08 = x << 8;
    gGMData.unk0C = y << 8;

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800C0F0
u8 Event8D_(struct EventEngineProc * proc)
{
    if (EVENT_IS_SKIPPING(proc))
    {
        return EVC_ADVANCE_CONTINUE;
    }

    return EVC_ADVANCE_YIELD;
}

//! FE8U = 0x0800C108
u8 Event8E_(struct EventEngineProc * proc)
{
    if (EVENT_IS_SKIPPING(proc))
    {
        return EVC_ADVANCE_CONTINUE;
    }

    return EVC_ADVANCE_YIELD;
}

//! FE8U = 0x0800C120
u8 Event8F_(struct EventEngineProc * proc)
{
    if (EVENT_IS_SKIPPING(proc))
    {
        return EVC_ADVANCE_CONTINUE;
    }

    return EVC_ADVANCE_YIELD;
}

//! FE8U = 0x0800C138
u8 Event90_WM_DRAWPATH(struct EventEngineProc * proc)
{
    int pathId = EVT_CMD_ARG32_LE(proc->pEventCurrent);

    if (EVENT_IS_SKIPPING(proc))
    {
        WM_DrawPath(pathId, 0);
        return EVC_ADVANCE_CONTINUE;
    }

    WM_DrawPath(pathId, 0x1e);
    return EVC_ADVANCE_YIELD;
}

//! FE8U = 0x0800C164
u8 Event91_WM_DRAWPATH_Silent(struct EventEngineProc * proc)
{
    struct WorldMapMainProc * worldMapProc;

    int pathId = EVT_CMD_ARG32_LE(proc->pEventCurrent);

    AddGmPath(&gGMData, &gGMData.openPaths, pathId);

    worldMapProc = Proc_Find(gProcScr_WorldMapMain);
    worldMapProc->unk_44->unk_4c->flags |= 3;

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800C198
u8 Event92_REMOVEPATH(struct EventEngineProc * proc)
{
    struct WorldMapMainProc * worldMapProc;

    int pathId = EVT_CMD_ARG32_LE(proc->pEventCurrent);

    RemoveGmPath(&gGMData, &gGMData.openPaths, pathId);

    worldMapProc = Proc_Find(gProcScr_WorldMapMain);
    worldMapProc->unk_44->unk_4c->flags |= 3;

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800C1CC
u8 Event93_(struct EventEngineProc * proc)
{
    int nodeId = EVT_CMD_ARG32_LE(proc->pEventCurrent);
    gGMData.nodes[nodeId].state |= 1;
    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800C1E8
u8 Event94_(struct EventEngineProc * proc)
{
    int nodeId = EVT_CMD_ARG32_LE(proc->pEventCurrent);
    gGMData.nodes[nodeId].state &= ~1;
    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800C204
u8 Event95_(struct EventEngineProc * proc)
{
    int nodeId = EVT_CMD_ARG32_LE(proc->pEventCurrent);

    if (EVENT_IS_SKIPPING(proc))
    {
        gGMData.nodes[nodeId].state |= 1;
        return EVC_ADVANCE_CONTINUE;
    }

    if (!(gGMData.nodes[nodeId].state & 1))
    {
        sub_80BFAEC(nodeId, 0, 0);
    }

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800C254
u8 Event96_(struct EventEngineProc * proc)
{
    int nodeId;
    int i;

    int pathId = EVT_CMD_ARG32_LE(proc->pEventCurrent);

    for (i = 0; i < 2; i++)
    {
        nodeId = (pathId)[gWMPathData].node[i];

        if (!(gGMData.nodes[nodeId].state & 1))
        {
            break;
        }
    }

    if (i >= 2)
    {
        return EVC_ADVANCE_CONTINUE;
    }

    if (EVENT_IS_SKIPPING(proc))
    {
        gGMData.nodes[nodeId].state |= 1;
    }
    else
    {
        sub_80BFAEC(nodeId, 0, 0);
    }

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800C2DC
u8 Event97_(struct EventEngineProc * proc)
{
    struct WorldMapMainProc * worldMapProc;

    int nodeId = WMLoc_GetNextLocId(gGMData.unk_c8);

    if (nodeId < 0)
    {
        return EVC_ADVANCE_CONTINUE;
    }

    if (EVENT_IS_SKIPPING(proc))
    {
        sub_80BCFB4();
        gGMData.nodes[nodeId].state |= 1;
        gGMData.nodes[nodeId].state |= 2;

        worldMapProc = Proc_Find(gProcScr_WorldMapMain);
        worldMapProc->unk_48->nodeId = nodeId;

        worldMapProc = Proc_Find(gProcScr_WorldMapMain);
        worldMapProc->unk_48->unk_32_1 = 1;
    }
    else
    {
        if (!(gGMData.nodes[nodeId].state & 1))
        {
            sub_80BFAEC(nodeId, 0, 0);
            sub_80BCFB4();
            gGMData.nodes[nodeId].state |= 2;
        }
    }

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800C36C
u8 Event98_(struct EventEngineProc * proc)
{
    int nodeId;
    int i;
    struct WorldMapMainProc * worldMapProc;

    int pathId = EVT_CMD_ARG32_LE(proc->pEventCurrent);

    for (i = 0; i < 2; i++)
    {
        nodeId = pathId[gWMPathData].node[i];
        if (!(gGMData.nodes[nodeId].state & 1))
        {
            break;
        }
    }

    if (i >= 2)
    {
        return EVC_ADVANCE_CONTINUE;
    }

    if (EVENT_IS_SKIPPING(proc))
    {
        gGMData.nodes[nodeId].state |= 1;
        gGMData.nodes[nodeId].state |= 2;

        worldMapProc = Proc_Find(gProcScr_WorldMapMain);
        worldMapProc->unk_48->nodeId = nodeId;

        worldMapProc = Proc_Find(gProcScr_WorldMapMain);
        worldMapProc->unk_48->unk_32_1 = 1;
    }
    else
    {
        sub_80BFAEC(nodeId, 0, 0);
        sub_80BCFB4();
        gGMData.nodes[nodeId].state |= 2;
    }

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800C434
u8 Event99_(struct EventEngineProc * proc)
{
    if (EVENT_IS_SKIPPING(proc))
    {
        if (sub_80BFB34())
        {
            sub_80BFB24();
        }

        return EVC_ADVANCE_CONTINUE;
    }

    if (!sub_80BFB34())
    {
        return EVC_ADVANCE_YIELD;
    }

    return EVC_STOP_YIELD;
}

//! FE8U = 0x0800C468
u8 Event9A_(struct EventEngineProc * proc)
{
    struct WorldMapMainProc * worldMapProc;

    int nodeId = EVT_CMD_ARG32_LE(proc->pEventCurrent);

    gGMData.nodes[nodeId].state |= 2;

    worldMapProc = Proc_Find(gProcScr_WorldMapMain);
    worldMapProc->unk_48->nodeId = nodeId;

    worldMapProc = Proc_Find(gProcScr_WorldMapMain);
    worldMapProc->unk_48->unk_32_1 = 1;

    if (EVENT_IS_SKIPPING(proc))
    {
        return EVC_ADVANCE_CONTINUE;
    }

    return EVC_ADVANCE_YIELD;
}

//! FE8U = 0x0800C4C8
u8 Event9B_(struct EventEngineProc * proc)
{
    int nodeId = EVT_CMD_ARG32_LE(proc->pEventCurrent);
    gGMData.nodes[nodeId].state |= 2;

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800C4E4
u8 Event9C_(struct EventEngineProc * proc)
{
    struct WorldMapMainProc * worldMapProc;

    int nodeId = WMLoc_GetNextLocId(gGMData.unk_c8);

    if (nodeId >= 0)
    {
        sub_80BCFB4();

        gGMData.nodes[nodeId].state |= 2;

        worldMapProc = Proc_Find(gProcScr_WorldMapMain);
        worldMapProc->unk_48->nodeId = nodeId;
    }

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800C528
u8 Event9D_(struct EventEngineProc * proc)
{
    int nodeId = EVT_CMD_ARG32_LE(proc->pEventCurrent);

    gGMData.nodes[nodeId].state &= ~2;

    if (EVENT_IS_SKIPPING(proc))
    {
        return EVC_ADVANCE_CONTINUE;
    }

    return EVC_ADVANCE_YIELD;
}

//! FE8U = 0x0800C55C
u8 Event9E_PUTSPRITE(struct EventEngineProc * proc)
{
    u16 muId = EVT_CMD_ARGV(proc->pEventCurrent)[1];
    u16 jid = EVT_CMD_ARGV(proc->pEventCurrent)[2];
    u16 allegiance = EVT_CMD_ARGV(proc->pEventCurrent)[3];
    u16 nodeId = EVT_CMD_ARGV(proc->pEventCurrent)[4];

    WM_PutClassSprite(muId, jid, allegiance, nodeId);

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800C574
u8 Event9F_(struct EventEngineProc * proc)
{
    u16 muId = EVT_CMD_ARGV(proc->pEventCurrent)[1];
    u16 pid = EVT_CMD_ARGV(proc->pEventCurrent)[2];
    u16 allegiance = EVT_CMD_ARGV(proc->pEventCurrent)[3];
    u16 nodeId = EVT_CMD_ARGV(proc->pEventCurrent)[4];

    WM_PutCharSprite(muId, pid, allegiance, nodeId);

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800C58C
u8 EventA0_REMSPRITE(struct EventEngineProc * proc)
{
    int muId = EVT_CMD_ARG32_LE(proc->pEventCurrent);

    WM_RemoveUnit(muId);
    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800C59C
u8 EventA1_(struct EventEngineProc * proc)
{
    int a = EVT_CMD_ARG32_LE(proc->pEventCurrent);

    sub_80BF554(a);
    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800C5AC
u8 EventA2_(struct EventEngineProc * proc)
{
    int a = EVT_CMD_ARG32_LE(proc->pEventCurrent);

    sub_80BF570(a);
    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800C5BC
u8 EventA3_(struct EventEngineProc * proc)
{
    struct WorldMapMainProc * worldMapProc;

    u16 a = EVT_CMD_ARGV(proc->pEventCurrent)[1];
    s16 b = EVT_CMD_ARGV(proc->pEventCurrent)[2];

    if (EVENT_IS_SKIPPING(proc))
    {
        sub_80BF554(a);
        return EVC_ADVANCE_CONTINUE;
    }

    worldMapProc = Proc_Find(gProcScr_WorldMapMain);
    sub_80BE40C(worldMapProc->unk_54, a, b);

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800C5F8
u8 EventA4_(struct EventEngineProc * proc)
{
    struct WorldMapMainProc * worldMapProc;

    u16 a = EVT_CMD_ARGV(proc->pEventCurrent)[1];
    s16 b = EVT_CMD_ARGV(proc->pEventCurrent)[2];

    if (EVENT_IS_SKIPPING(proc))
    {
        sub_80BF570(a);
        return EVC_ADVANCE_CONTINUE;
    }

    worldMapProc = Proc_Find(gProcScr_WorldMapMain);
    sub_80BE42C(worldMapProc->unk_54, a, b);

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800C634
u8 EventA5_(struct EventEngineProc * proc)
{
    if (EVENT_IS_SKIPPING(proc))
    {
        EndGmapUnitFade();
    }

    if (!sub_80BE44C())
    {
        return EVC_ADVANCE_YIELD;
    }

    return EVC_STOP_YIELD;
}

//! FE8U = 0x0800C65C
u8 EventA6_(struct EventEngineProc * proc)
{
    struct WorldMapMainProc * worldMapProc;

    u16 unitId = EVT_CMD_ARGV(proc->pEventCurrent)[1];
    u16 nodeId = EVT_CMD_ARGV(proc->pEventCurrent)[2];

    gGMData.units[unitId].location = nodeId;

    worldMapProc = Proc_Find(gProcScr_WorldMapMain);
    sub_80BE3C8(worldMapProc->unk_54, unitId, nodeId);

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800C68C
u8 EventA7_(struct EventEngineProc * proc)
{
    struct WorldMapMainProc * worldMapProc;

    s16 a = EVT_CMD_ARGV(proc->pEventCurrent)[1];
    s16 b = EVT_CMD_ARGV(proc->pEventCurrent)[3];
    s16 c = EVT_CMD_ARGV(proc->pEventCurrent)[4];

    worldMapProc = Proc_Find(gProcScr_WorldMapMain);
    sub_80BE35C(worldMapProc->unk_54, a, b, c);

    return EVC_ADVANCE_CONTINUE;
}

struct Sub80C33D4
{
    /* 00 */ u8 unk_00;
    /* 01 */ u8 unk_01;
    /* 02 */ u8 unk_02;
    /* 04 */ u16 unk_04;
    /* 06 */ u16 unk_06;
    /* 08 */ u16 unk_08;
    /* 0A */ u16 unk_0a;
    /* 0C */ u16 unk_0c;
    /* 0E */ u16 unk_0e;
    /* 10 */ int unk_10;
};

//! FE8U = 0x0800C6C0
u8 EventA8_(struct EventEngineProc * proc)
{
    struct WorldMapMainProc * worldMapProc;
    struct Sub80C33D4 local;

    // Order needed to match
    u16 r4;
    u16 r8;
    u16 r9;

    s16 r5 = EVT_CMD_ARGV(proc->pEventCurrent)[1];
    u16 r2 = EVT_CMD_ARGV(proc->pEventCurrent)[2];
    u16 r3 = EVT_CMD_ARGV(proc->pEventCurrent)[3];
    u16 ip = EVT_CMD_ARGV(proc->pEventCurrent)[4];
    u16 r6 = EVT_CMD_ARGV(proc->pEventCurrent)[5];
    u16 r7 = EVT_CMD_ARGV(proc->pEventCurrent)[6];

    r9 = EVT_CMD_ARGV(proc->pEventCurrent)[7];
    r4 = EVT_CMD_ARGV(proc->pEventCurrent)[8];
    r8 = EVT_CMD_ARGV(proc->pEventCurrent)[9];

    if (EVENT_IS_SKIPPING(proc))
    {
        worldMapProc = Proc_Find(gProcScr_WorldMapMain);
        sub_80BE35C(worldMapProc->unk_54, r5, r6, r7);

        if ((r4 & 2) != 0)
        {
            sub_80BF570(r5);
        }
    }
    else
    {
        local.unk_00 = r5;
        local.unk_01 = r2;
        local.unk_02 = 0;
        local.unk_06 = r3;
        local.unk_08 = ip;
        local.unk_0a = r6;
        local.unk_0c = r7;
        local.unk_10 = r9;
        local.unk_0e = r8;
        sub_80C33D4(&local, r4, 0);
    }

    return EVC_ADVANCE_CONTINUE;
}

struct Sub80C3378
{
    /* 00 */ u8 unk_00;
    /* 01 */ u8 unk_01;
    /* 02 */ u8 unk_02;
    /* 04 */ u16 unk_04;
    /* 06 */ u16 unk_06;
    /* 08 */ u16 unk_08;
    /* 0A */ u16 unk_0a;
    /* 0C */ int unk_0c;
};

//! FE8U = 0x0800C754
u8 EventA9_(struct EventEngineProc * proc)
{
    struct Sub80C3378 local;

    s16 r3 = EVT_CMD_ARGV(proc->pEventCurrent)[1];
    u16 r2 = EVT_CMD_ARGV(proc->pEventCurrent)[2];
    u16 r5 = EVT_CMD_ARGV(proc->pEventCurrent)[3];
    u16 r4 = EVT_CMD_ARGV(proc->pEventCurrent)[4];
    u16 r6 = EVT_CMD_ARGV(proc->pEventCurrent)[5];
    u16 r7 = EVT_CMD_ARGV(proc->pEventCurrent)[6];

    if (EVENT_IS_SKIPPING(proc))
    {
        gGMData.units[r3].location = r4;

        if ((r2 & 2) != 0)
        {
            sub_80BF570(r3);
        }
    }
    else
    {
        local.unk_00 = r3;
        local.unk_01 = 0;
        local.unk_06 = r5;
        local.unk_08 = r4;
        local.unk_0c = r6;
        local.unk_0a = r7;
        sub_80C3378(&local, r2, 0);
    }

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800C7B4
u8 EventAA_(struct EventEngineProc * proc)
{
    struct WorldMapMainProc * worldMapProc;

    s16 a = EVT_CMD_ARGV(proc->pEventCurrent)[1];

    if (!EVENT_IS_SKIPPING(proc))
    {
        worldMapProc = Proc_Find(gProcScr_WorldMapMain);
        sub_80BE054(worldMapProc->unk_54, a);
    }

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800C7E4
u8 EventAB_(struct EventEngineProc * proc)
{
    struct WorldMapMainProc * worldMapProc;

    s16 a = EVT_CMD_ARGV(proc->pEventCurrent)[1];

    if (!EVENT_IS_SKIPPING(proc))
    {
        worldMapProc = Proc_Find(gProcScr_WorldMapMain);
        sub_80BE068(worldMapProc->unk_54, a);
    }

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800C814
u8 EventAC_(struct EventEngineProc * proc)
{
    s16 a = EVT_CMD_ARGV(proc->pEventCurrent)[1];

    if (EVENT_IS_SKIPPING(proc))
    {
        if (sub_80C3484(a))
        {
            sub_80C343C(a);
        }

        return EVC_ADVANCE_CONTINUE;
    }

    if (!sub_80C3484(a))
    {
        return EVC_ADVANCE_YIELD;
    }

    return EVC_STOP_YIELD;
}

//! FE8U = 0x0800C85C
u8 EventAD_(struct EventEngineProc * proc)
{
    int a = EVT_CMD_ARG32_LE(proc->pEventCurrent);

    if (EVENT_IS_SKIPPING(proc))
    {
        sub_80BF788(0, 0);
        return EVC_ADVANCE_CONTINUE;
    }

    sub_80BF788(0, a);
    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800C884
u8 EventAE_(struct EventEngineProc * proc)
{
    if (EVENT_IS_SKIPPING(proc))
    {
        sub_80BF748();
        return EVC_ADVANCE_CONTINUE;
    }

    if (!sub_80BF730())
    {
        return EVC_ADVANCE_YIELD;
    }

    return EVC_STOP_YIELD;
}

//! FE8U = 0x0800C8B0
u8 EventAF_(struct EventEngineProc * proc)
{
    u16 a = EVT_CMD_ARGV(proc->pEventCurrent)[1];
    u16 b = EVT_CMD_ARGV(proc->pEventCurrent)[2];

    if (!EVENT_IS_SKIPPING(proc))
    {
        sub_80C0240(a, b);
    }

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800C8D4
u8 EventB0_(struct EventEngineProc * proc)
{
    u16 a = EVT_CMD_ARGV(proc->pEventCurrent)[1];
    u16 b = EVT_CMD_ARGV(proc->pEventCurrent)[2];

    if (!EVENT_IS_SKIPPING(proc))
    {
        sub_80C02A4(a, b);
    }

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800C8F8
u8 EventB1_(struct EventEngineProc * proc)
{
    if (EVENT_IS_SKIPPING(proc))
    {
        sub_80C0200();
        return EVC_ADVANCE_CONTINUE;
    }

    if (!sub_80C0228())
    {
        return EVC_ADVANCE_YIELD;
    }

    return EVC_STOP_YIELD;
}

//! FE8U = 0x0800C924
u8 EventB2_(struct EventEngineProc * proc)
{
    int a = EVT_CMD_ARG32_LE(proc->pEventCurrent);

    sub_80C04F4(a, 0);

    return EVC_ADVANCE_YIELD;
}

//! FE8U = 0x0800C938
u8 EventB3_(struct EventEngineProc * proc)
{
    if (!sub_80C0530())
    {
        return EVC_ADVANCE_YIELD;
    }

    return EVC_STOP_YIELD;
}

//! FE8U = 0x0800C950
u8 EventB4_(struct EventEngineProc * proc)
{
    u16 a = EVT_CMD_ARGV(proc->pEventCurrent)[1];
    u16 b = EVT_CMD_ARGV(proc->pEventCurrent)[2];
    int c = EVT_CMD_ARG32_LE(proc->pEventCurrent + 2);

    if (!EVENT_IS_SKIPPING(proc))
    {
        Make6C_Gmap_RM(a, b, c, 0);
    }

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800C980
u8 EventB5_(struct EventEngineProc * proc)
{
    if (EVENT_IS_SKIPPING(proc))
    {
        sub_80C24F8();
        return EVC_ADVANCE_CONTINUE;
    }

    sub_80C24D8();
    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800C9A0
u8 EventB6_(struct EventEngineProc * proc)
{
    u16 r1 = EVT_CMD_ARGV(proc->pEventCurrent)[1];
    u16 r2 = EVT_CMD_ARGV(proc->pEventCurrent)[2];
    u16 r3 = EVT_CMD_ARGV(proc->pEventCurrent)[3];
    u16 r4 = EVT_CMD_ARGV(proc->pEventCurrent)[4];
    u16 r6 = EVT_CMD_ARGV(proc->pEventCurrent)[5];
    u16 r7 = EVT_CMD_ARGV(proc->pEventCurrent)[6];

    if (!EVENT_IS_SKIPPING(proc))
    {
        sub_80C1F18(r1, r2, r3, r4, r6, r7, 0);
    }

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800C9F0
u8 EventB7_(struct EventEngineProc * proc)
{
    if (EVENT_IS_SKIPPING(proc))
    {
        sub_80C24F8();
        return EVC_ADVANCE_CONTINUE;
    }

    if (sub_80C2470())
    {
        return EVC_STOP_YIELD;
    }

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800CA18
u8 EventB8_(struct EventEngineProc * proc)
{
    int a = EVT_CMD_ARG32_LE(proc->pEventCurrent);

    if (!EVENT_IS_SKIPPING(proc))
    {
        sub_80C2AD4(a, 0);
    }

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800CA38
u8 EventB9_(struct EventEngineProc * proc)
{
    int a = EVT_CMD_ARG32_LE(proc->pEventCurrent);

    if (EVENT_IS_SKIPPING(proc))
    {
        sub_80C2B7C(-1);

        return EVC_ADVANCE_CONTINUE;
    }

    sub_80C2C10(a);

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800CA60
u8 EventBA_(struct EventEngineProc * proc)
{
    int a = EVT_CMD_ARG32_LE(proc->pEventCurrent);

    if (EVENT_IS_SKIPPING(proc))
    {
        if (sub_80C2BC4(a))
        {
            sub_80C2B7C(a);
        }

        return EVC_ADVANCE_CONTINUE;
    }

    if (!sub_80C2BC4(a))
    {
        return EVC_ADVANCE_YIELD;
    }

    return EVC_STOP_YIELD;
}

//! FE8U = 0x0800CA9C
u8 EventBB_(struct EventEngineProc * proc)
{
    u16 a = EVT_CMD_ARGV(proc->pEventCurrent)[1];
    u16 b = EVT_CMD_ARGV(proc->pEventCurrent)[2];
    u16 c = EVT_CMD_ARGV(proc->pEventCurrent)[3];
    u16 d = EVT_CMD_ARGV(proc->pEventCurrent)[4];
    int e = EVT_CMD_ARG32_LE(proc->pEventCurrent + 4);

    if (!EVENT_IS_SKIPPING(proc))
    {
        sub_80C2FC0(a, b, c, d, e, 0);
    }

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800CADC
u8 EventBC_(struct EventEngineProc * proc)
{
    u16 a = EVT_CMD_ARGV(proc->pEventCurrent)[1];
    u16 b = EVT_CMD_ARGV(proc->pEventCurrent)[2];
    s16 nodeId = EVT_CMD_ARGV(proc->pEventCurrent)[3];
    s16 d = EVT_CMD_ARGV(proc->pEventCurrent)[4];

    if (!EVENT_IS_SKIPPING(proc))
    {
        s16 x;
        s16 y;
        *&x = nodeId[gWMNodeData].x;
        *&y = nodeId[gWMNodeData].y;
        sub_80C2FC0(a, b, x / 2, y / 2, d, 0);
    }

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800CB48
u8 EventBD_(struct EventEngineProc * proc)
{
    int a = EVT_CMD_ARG32_LE(proc->pEventCurrent);

    if (EVENT_IS_SKIPPING(proc))
    {
        sub_80C304C(-1);

        return EVC_ADVANCE_CONTINUE;
    }

    sub_80C30E0(a);

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800CB70
u8 EventBE_(struct EventEngineProc * proc)
{
    int a = EVT_CMD_ARG32_LE(proc->pEventCurrent);

    if (EVENT_IS_SKIPPING(proc))
    {
        if (sub_80C3094(a))
        {
            sub_80C304C(a);
        }

        return EVC_ADVANCE_CONTINUE;
    }

    if (!sub_80C3094(a))
    {
        return EVC_ADVANCE_YIELD;
    }

    return EVC_STOP_YIELD;
}

//! FE8U = 0x0800CBAC
u8 EventBF_(struct EventEngineProc * proc)
{
    sub_80B9FD4(Proc_Find(gProcScr_WorldMapMain));
    sub_80B9810(Proc_Find(gProcScr_WorldMapMain));
    Make6C_savemenu2(proc);

    return EVC_ADVANCE_YIELD;
}

//! FE8U = 0x0800CBD8
u8 EventC0_(struct EventEngineProc * proc)
{
    sub_80B9154(Proc_Find(gProcScr_WorldMapMain));
    return EVC_ADVANCE_YIELD;
}

//! FE8U = 0x0800CBF0
u8 EventC1_SKIPWM(struct EventEngineProc * proc)
{
    gGMData.state.bits.state_6 = 1;
    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800CC04
u8 EventC2_(struct EventEngineProc * proc)
{
    gGMData.state.bits.state_7 = 1;
    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800CC18
u8 EventC3_(struct EventEngineProc * proc)
{
    u16 unitId = EVT_CMD_ARGV(proc->pEventCurrent)[1];
    u16 pid = EVT_CMD_ARGV(proc->pEventCurrent)[2];
    int nodeId = EVT_CMD_ARG32_LE(proc->pEventCurrent + 2);

    if (!(gGMData.units[unitId].state & 2))
    {
        if (gGMData.units[unitId].id == pid)
        {
            return EVC_ADVANCE_CONTINUE;
        }
    }
    else if (pid == 0)
    {
        return EVC_ADVANCE_CONTINUE;
    }

    WM_PutCharSprite(unitId, pid, -1, nodeId);

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800CC5C
u8 EventCE_(struct EventEngineProc * proc)
{
    if (EVENT_IS_SKIPPING(proc))
    {
        return EVC_ADVANCE_CONTINUE;
    }

    return EVC_ADVANCE_YIELD;
}

//! FE8U = 0x0800CC74
u8 EventCF_(struct EventEngineProc * proc)
{
    if (EVENT_IS_SKIPPING(proc))
    {
        return EVC_ADVANCE_CONTINUE;
    }

    return EVC_ADVANCE_YIELD;
}

//! FE8U = 0x0800CC8C
u8 EventC4_(struct EventEngineProc * proc)
{
    s16 a = EVT_CMD_ARGV(proc->pEventCurrent)[1];
    s16 b = EVT_CMD_ARGV(proc->pEventCurrent)[2];
    s16 c = EVT_CMD_ARGV(proc->pEventCurrent)[3];
    s16 d = EVT_CMD_ARGV(proc->pEventCurrent)[4];

    if (EVENT_IS_SKIPPING(proc))
    {
        return EVC_ADVANCE_CONTINUE;
    }

    if (d)
    {
        sub_80BA0B4(d, 6, a, b, 0, 0, c);
    }
    else
    {
        sub_80B86CC(a, b, c);
    }

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800CCE8
void sub_800CCE8(void)
{
    return;
}

//! FE8U = 0x0800CCEC
void nullsub_32(void)
{
    return;
}

#if NONMATCHING

//! FE8U = 0x0800CCF0
u8 EventC5_(struct EventEngineProc * proc)
{

    u16 a = EVT_CMD_ARGV(proc->pEventCurrent)[0];
    u16 b = EVT_CMD_ARGV(proc->pEventCurrent)[1];
    u16 c = EVT_CMD_ARGV(proc->pEventCurrent)[2];

    if (EVENT_IS_SKIPPING(proc))
    {
        EndFaceById(a);
        return EVC_ADVANCE_CONTINUE;
    }

    if (c)
    {
        sub_80BA0B4(c, 7, a, 0, 0, 0, b);
    }
    else
    {
        sub_80B8844(a, b);
    }

    return EVC_ADVANCE_CONTINUE;
}

#else

NAKEDFUNC
u8 EventC5_(struct EventEngineProc * proc)
{
    asm("\n\
        .syntax unified\n\
        push {r4, lr}\n\
        sub sp, #0xc\n\
        ldr r1, [r0, #0x38]\n\
        ldrh r2, [r1, #2]\n\
        ldrh r4, [r1, #4]\n\
        ldrh r3, [r1, #6]\n\
        ldrh r0, [r0, #0x3c]\n\
        lsrs r1, r0, #2\n\
        movs r0, #1\n\
        ands r1, r0\n\
        cmp r1, #0\n\
        beq _0800CD10\n\
        adds r0, r2, #0\n\
        bl EndFaceById\n\
        b _0800CD2E\n\
    _0800CD10:\n\
        cmp r3, #0\n\
        beq _0800CD26\n\
        str r1, [sp]\n\
        str r1, [sp, #4]\n\
        str r4, [sp, #8]\n\
        adds r0, r3, #0\n\
        movs r1, #7\n\
        movs r3, #0\n\
        bl sub_80BA0B4\n\
        b _0800CD2E\n\
    _0800CD26:\n\
        adds r1, r4, #0\n\
        adds r0, r2, #0\n\
        bl sub_80B8844\n\
    _0800CD2E:\n\
        movs r0, #0\n\
        add sp, #0xc\n\
        pop {r4}\n\
        pop {r1}\n\
        bx r1\n\
        .syntax divided\n\
    ");
}

#endif

struct Proc8591C68
{
    /* 00 */ PROC_HEADER;
    /* 2A */ s16 faceSlot;
};

//! FE8U = 0x0800CD38
void sub_800CD38(struct Proc8591C68 * proc)
{
    return;
}

//! FE8U = 0x0800CD3C
void nullsub_34(struct Proc8591C68 * proc)
{
    return;
}

//! FE8U = 0x0800CD40
void sub_800CD40(struct Proc8591C68 * proc)
{
    EndFaceById(proc->faceSlot);
    return;
}

//! FE8U = 0x0800CD50
u8 EventC6_(struct EventEngineProc * proc)
{
    u16 a;
    u16 b;

    if (EVENT_IS_SKIPPING(proc))
    {
        return EVC_ADVANCE_CONTINUE;
    }

    a = EVT_CMD_ARGV(proc->pEventCurrent)[1];
    b = EVT_CMD_ARGV(proc->pEventCurrent)[2];

    sub_80C36A0(a | b);

    if (proc->evStateBits & EV_STATE_0020)
    {
        SetTalkFlag(TALK_FLAG_NOSKIP);
    }

    return EVC_ADVANCE_YIELD;
}

//! FE8U = 0x0800CD88
u8 EventC7_(struct EventEngineProc * proc)
{
    if (EVENT_IS_SKIPPING(proc))
    {
        return EVC_ADVANCE_CONTINUE;
    }

    sub_80C3624(1);

    return EVC_ADVANCE_YIELD;
}

//! FE8U = 0x0800CDA8
u8 EventC8_(struct EventEngineProc * proc)
{
    if (EVENT_IS_SKIPPING(proc))
    {
        return EVC_ADVANCE_CONTINUE;
    }

    sub_80C3624(0);

    return EVC_ADVANCE_YIELD;
}

//! FE8U = 0x0800CDC8
u8 EventC9_(struct EventEngineProc * proc)
{
    if (EVENT_IS_SKIPPING(proc))
    {
        sub_80C3660();
        return EVC_ADVANCE_CONTINUE;
    }

    sub_80C3660();

    return EVC_ADVANCE_YIELD;
}

//! FE8U = 0x0800CDE8
void sub_800CDE8(void)
{
    return;
}

//! FE8U = 0x0800CDEC
void sub_800CDEC(void)
{
    return;
}

//! FE8U = 0x0800CDF0
u8 EventCA_(struct EventEngineProc * proc)
{
    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800CDF4
u8 EventCB_(struct EventEngineProc * proc)
{
    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800CDF8
u8 EventCC_(struct EventEngineProc * proc)
{
    s16 a = EVT_CMD_ARGV(proc->pEventCurrent)[0];
    s16 b = EVT_CMD_ARGV(proc->pEventCurrent)[1];
    s16 c = EVT_CMD_ARGV(proc->pEventCurrent)[2];

    if (!EVENT_IS_SKIPPING(proc))
    {
        sub_80B8188(b, c, a);
    }

    return EVC_ADVANCE_CONTINUE;
}

//! FE8U = 0x0800CE28
u8 EventCD_(struct EventEngineProc * proc)
{
    if (!EVENT_IS_SKIPPING(proc))
    {
        nullsub_7();
    }

    return EVC_ADVANCE_CONTINUE;
}
