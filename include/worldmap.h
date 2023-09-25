#ifndef GUARD_WORLDMAP_H
#define GUARD_WORLDMAP_H

struct GmRouteProc
{
    /* 00 */ PROC_HEADER;

    /* 2C */ u32 chr;
    /* 30 */ u8 pal;
    /* 31 */ u8 flags;
    /* 32 */ u8 unk_32;
    /* 33 */ u8 unk_33;
    /* 34 */ u8 bgA;
    /* 35 */ u8 bgB;
    /* 36 */ s8 x1;
    /* 37 */ s8 y1;
    /* 38 */ s8 x2;
    /* 39 */ s8 y2;
    /* 3A */ u8 bgPriority;
    /* 3C */ s16 unk_3c;
    /* 3E */ s16 unk_3e;
    /* 40 */ struct OpenPaths * pOpenPaths;
};

struct Unknown_3001DA8
{
    /* 00 */ s8 unk_00;
    /* 01 */ s8 unk_01;
    /* 02 */ s8 unk_02;
    /* 03 */ s8 unk_03;
    /* 04 */ s8 unk_04;
    /* 05 */ s8 unk_05;
};

struct GMapScreenVSyncProc
{
    /* 00 */ PROC_HEADER;
    /* 2C */ u8 * unk_2c;
    /* 30 */ u16 * unk_30;
    /* 34 */ u8 * unk_34;
    /* 38 */ s16 unk_38;
    /* 3C */ struct Unknown_3001DA8 * unk_3c;
    /* 40 */ u16 unk_40;
    /* 44 */ void * unk_44;
};

struct GmScreenProc
{
    /* 00 */ PROC_HEADER;
    /* 29 */ u8 unk_29_0 : 1;
    /* 2A */ u8 unk_2a;
    /* 2B */ s8 unk_2b;
    /* 2C */ s8 unk_2c;
    /* 2D */ s8 unk_2d;
    /* 2E */ s8 unk_2e;
    /* 2F */ u8 unk_2f;
    /* 30 */ u8 unk_30;
    /* 31 */ u8 unk_31;
    /* 32 */ u8 unk_32;
    /* 33 */ u8 unk_33;
    /* 34 */ s16 unk_34;
    /* 36 */ s16 unk_36;
    /* 38 */ u16 unk_38;
    /* 3A */ u16 unk_3a;
    /* 3C */ u8 * unk_3c;
    /* 40 */ u16 * unk_40;
    /* 44 */ u8 * unk_44;
    /* 48 */ struct GMapScreenVSyncProc * unk_48;
    /* 4C */ struct GmRouteProc * unk_4c;
};

struct GmNodeIconDisplayProc
{
    /* 00 */ PROC_HEADER;
    /* 2C */ u32 chr;
    /* 30 */ u8 pal;
    /* 31 */ u8 unk_31;
    /* 32 */ u8 unk_32_0 : 1;
    /* 32 */ u8 unk_32_1 : 1;
    /* 33 */ u8 nodeId;
    /* 34 */ u32 unk_34[1];
    /* 38 */ struct APHandle * ap;
    /* 3C */ struct GmScreenProc * pScreenProc;
};

enum
{
    GMAPUNIT_FLAG_DISPLAY   = (1 << 0),
    GMAPUNIT_FLAG_BLEND     = (1 << 1),
    GMAPUNIT_FLAG_UPDATEGFX = (1 << 2),
};

struct GMapUnitProc
{
    /* 00 */ PROC_HEADER;
    /* 2A */ u16 flags;
    /* 2C */ u16 unk_2c; // AP obj priority node
    /* 2E */ u16 unk_2e;
    /* 30 */ int unk_30; // base tile index for SMS gfx?
    /* 34 */ s8 index; // within container proc
    /* 35 */ u8 faction;
    /* 36 */ u8 pal;
    /* 37 */ s8 animId;
    /* 38 */ u16 unk_38; // class initially
    /* 3A */ u16 unk_3a; // class initially
    /* 3C */ u16 x;
    /* 3E */ u16 y;
    /* 40 */ struct APHandle * ap;
};

struct GMapUnitContainerProc
{
    /* 00 */ PROC_HEADER;
    /* 2C */ int unk_2c;
    /* 30 */ u8 unk_30;
    /* 34 */ struct GMapUnitProc * pMapUnitProcs[7];
};

struct WorldMapMainProc
{
    /* 00 */ PROC_HEADER;

    /* 29 */ u8 unk_29_0 : 1;
    /* 29 */ u8 unk_29_1 : 1;
    /* 29 */ u8 unk_29_2 : 1;
    /* 29 */ u8 unk_29_3 : 1;
    /* 29 */ u8 unk_29_4 : 1;
    /* 29 */ u8 unk_29_5 : 1;
    /* 29 */ u8 unk_29_6 : 1;
    /* 29 */ u8 unk_29_7 : 1;

    /* 2A */ u8 unk_2a;
    /* 2C */ int unk_2c;
    /* 30 */ STRUCT_PAD(0x30, 0x3a);

    /* 3A */ u16 unk_3a;
    /* 3C */ u16 unk_3c; // pad?
    /* 3E */ u8 unk_3e;
    /* 3F */ u8 unk_3f;
    /* 40 */ s8 unk_40;
    /* 41 */ s8 unk_41;
    /* 44 */ struct GmScreenProc * unk_44; // GmapScreen
    /* 48 */ struct GmNodeIconDisplayProc * unk_48; // GmNodeIconDisplay
    /* 4C */ struct GMapUnitContainerProc * unk_4c; // Gmap Unit Container
    /* 50 */ ProcPtr unk_50; // Gmap Cursor
    /* 54 */ ProcPtr unk_54; // Gmap MU
};

struct GMapMovementPathData
{
    /* 00 */ int elapsedTime;
    /* 04 */ s16 x;
    /* 06 */ s16 y;
};

struct GMapPathData
{
    /* 00 */ u8 * gfxData;
    /* 04 */ s8 node[2];
    /* 08 */ const struct GMapMovementPathData * movementPath;
};

extern const struct GMapPathData gWMPathData[];

enum
{
    GMAP_NODE_PLACEMENT_PROGRESSION  = 0,
    GMAP_NODE_PLACEMENT_FRELIA       = 1,
    GMAP_NODE_PLACEMENT_MONSTERSPAWN = 2,
    GMAP_NODE_PLACEMENT_DUNGEON      = 3,
};

enum
{
    GMAP_ENCOUNTERS_NONE      = 1,
    GMAP_ENCOUNTERS_MONSTERS  = 2,
    GMAP_ENCOUNTERS_DUNGEON   = 3,
};

struct GMapNodeData
{
    /* 00 */ u8 placementFlag;
    /* 01 */ s8 encounters;
    /* 02 */ u8 iconPreClear;
    /* 03 */ u8 iconPostClear;
    /* 04 */ u8 unk_04;  // chapter ID start
    /* 05 */ u8 unk_05;  // chapter ID end
    /* 06 */ s16 unk_06; // event condition flag
    /* 08 */ s8 unk_08[4]; // next destination id
    /* 0C */ u16 * armory;
    /* 10 */ u16 * vendor;
    /* 14 */ u16 * secretShop;
    /* 18 */ s16 x;
    /* 1A */ s16 y;
    /* 1C */ u16 nameTextId;
    /* 1E */ u8 shipTravelFlag;
    /* 1F */ STRUCT_PAD(0x1F, 0x20);
};

extern const struct GMapNodeData gWMNodeData[];

struct NodeIcon
{
    /* 00 */ u16 sheetTileId;
    /* 02 */ STRUCT_PAD(0x2, 0x4);
    /* 04 */ u16 * pSpriteData;
    /* 08 */ s8 xCenter;
    /* 09 */ s8 yCenter;
    /* 0A */ s8 width;
    /* 0B */ s8 height;
    /* 0C */ s8 xFlagOrigin;
    /* 0D */ s8 yFlagOrigin;
    /* 0E */ STRUCT_PAD(0xe, 0xf);
};

extern const struct NodeIcon gWMNodeIconData[];

extern struct ProcCmd gProcScr_WorldMapMain[];

// ??? WorldMapFaceHolder_Init(???);
// ??? WMFaceCtrl_Init(???);
// ??? sub_80B826C(???);
// ??? GetWMFaceBg(???);
// ??? GetWMFaceVramOffset(???);
// ??? sub_80B82C8(???);
// ??? HandleWMFaceFade(???);
// ??? sub_80B843C(???);
// ??? WMFaceCtrl_Loop(???);
// ??? nullsub_57(???);
ProcPtr StartWMFaceCtrl(ProcPtr parent);
void EndWMFaceCtrl(void);
// ??? GetWMFaceBlendAmt(???);
void sub_80B86CC(int faceSlot, int faceId, u16 config);
void sub_80B8844(int faceSlot, u16 config);
void sub_80B895C(void);
// ??? WorldMap_Destruct(???);
// ??? sub_80B8A7C(???);
// ??? sub_80B8B3C(???);
// ??? sub_80B8B60(???);
// ??? sub_80B8BA4(???);
// ??? SetupGraphicSystemsForWorldMap(???);
// ??? sub_80B8E14(???);
// ??? sub_80B8E60(???);
// ??? DeployEveryUnit(???);
void nullsub_22(void);
// ??? sub_80B8FD4(???);
// ??? sub_80B8FEC(???);
// ??? sub_80B9028(???);
// ??? sub_80B90CC(???);
// ??? sub_80B9114(???);
void sub_80B9154(struct WorldMapMainProc * proc);
void sub_80B9218(ProcPtr);
s8 sub_80B92D0(struct WorldMapMainProc *, int);
int sub_80B93E0(ProcPtr);
// ??? sub_80B955C(???);
int sub_80B95B0(void);
// ??? sub_80B961C(???);
// ??? sub_80B96DC(???);
// ??? sub_80B96F8(???);
// ??? sub_80B97F8(???);
// ??? sub_80B9804(???);
void sub_80B9810(ProcPtr);
// ??? sub_80B9820(???);
// ??? sub_80B982C(???);
// ??? sub_80B987C(???);
// ??? sub_80B989C(???);
// ??? sub_80B98A8(???);
// ??? sub_80B98F8(???);
// ??? sub_80B9918(???);
// ??? sub_80B9924(???);
// ??? sub_80B9974(???);
// ??? sub_80B9994(???);
// ??? sub_80B99A0(???);
// ??? sub_80B99F0(???);
// ??? WorldMap_HideEverything(???);
// ??? sub_80B9A34(???);
// ??? sub_80B9A58(???);
// ??? sub_80B9A94(???);
// ??? sub_80B9AB0(???);
// ??? sub_80B9AEC(???);
// ??? WorldMap_InitChapterTransition(???);
// ??? sub_80B9BA4(???);
// ??? WorldMap_WaitForChapterIntroEvents(???);
// ??? sub_80B9D04(???);
// ??? sub_80B9D14(???);
// ??? sub_80B9DB8(???);
// ??? sub_80B9DC4(???);
// ??? sub_80B9DE0(???);
// ??? sub_80B9E40(???);
// ??? sub_80B9E64(???);
// ??? sub_80B9EA4(???);
// ??? DoNothing(???);
// ??? sub_80B9F14(???);
// ??? sub_80B9F24(???);
// ??? sub_80B9F34(???);
// ??? sub_80B9F44(???);
// ??? sub_80B9F54(???);
void sub_80B9FC0(void);
void sub_80B9FD4(ProcPtr);
void sub_80BA008(int);
void EndWM(ProcPtr);
s8 sub_80BA054(void); // gmap something
// ??? sub_80BA06C(???);
void sub_80BA0B4(int timerMaybe, u8 b, int faceSlot, int fid, int e, int f, int config);
// ??? sub_80BA100(???);
// ??? sub_80BA198(???);
// ??? sub_80BA1F4(???);
// ??? sub_80BA288(???);
// ??? NewWorldMap(???);
// ??? WorldMap_SetupChapterStuff(???);
void CallChapterWMIntroEvents(ProcPtr);
void sub_80BA424(void); // gmap something
// ??? sub_80BA458(???);
// ??? sub_80BA490(???);
// ??? sub_80BA4D0(???);
// ??? GMScreenVSync_Init(???);
// ??? GMScreenVSync_Loop(???);
// ??? sub_80BA6DC(???);
// ??? NewMapScreenVSync(???);
// ??? MapScreen_OnDelete(???);
// ??? MapScreen_Init(???);
// ??? sub_80BA818(???);
// ??? sub_80BA8A0(???);
// ??? sub_80BAB00(???);
// ??? sub_80BAB0C(???);
ProcPtr NewMapScreen(ProcPtr);
// ??? MMS_GetGfx(???);
// ??? MMS_GetROMTCS2(???);
// ??? GetMapUnitMMSGfxBuffer(???);
// ??? GmapUnit_Destruct(???);
// ??? GmapUnit_Init(???);
// ??? GmapUnit_Loop(???);
// ??? GetPaletteIdForAllegience(???);
// ??? NewMapUnit(???);
// ??? MapUnitC_DeleteGmapUnit(???);
// ??? MapUnitC_SetPosition(???);
// ??? MapUnitC_GetPosition(???);
// ??? sub_80BAF58(???);
// ??? MapUnitC_GetAnimId(???);
// ??? MapUnitC_SetAnimId(???);
// ??? MapUnitC_SetDisplayEnabled(???);
// ??? MapUnitC_IsBlendEnabled(???);
// ??? MapUnitC_SetBlendEnabled(???);
// ??? MapUnitC_GetLayer(???);
// ??? MapUnitC_SetLayer(???);
// ??? MapUnitC_GetFaction(???);
// ??? MapUnitC_SetFaction(???);
// ??? MapUnitC_SetPalette(???);
void MapUnitC_SetGfxNeedsUpdate(struct GMapUnitContainerProc * container, int index);
// ??? sub_80BB0E0(???);
// ??? sub_80BB188(???);
// ??? sub_80BB194(???);
// ??? GmapUnitContainer_Destruct(???);
// ??? GmapUnitContainer_Init(???);
ProcPtr NewGmapUnitContainer(ProcPtr, int, int);
// ??? GmapUnitFade_Destruct(???);
// ??? GmapUnitFade_Init(???);
// ??? sub_80BB26C(???);
// ??? GmapUnitFade_Loop(???);
// ??? StartGmapUnitFade(???);
void EndGmapUnitFade(void);
// ??? GetGmapUnitFade(???);
// ??? sub_80BB49C(???);
// ??? sub_80BB4C0(???);
// ??? sub_80BB538(???);
int WMLoc_GetChapterId(int);
int WMLoc_GetNextLocId(int idx);
int sub_80BB628(void * unused, int arg1, int arg2, int arg3, int arg4);
// ??? sub_80BB6FC(???);
// ??? sub_80BB708(???);
// ??? GmapScreen2_Destruct(???);
// ??? GmapScreen2_Init(???);
// ??? sub_80BB744(???);
// ??? GmapScreen2_Loop(???);
ProcPtr sub_80BB9A4(ProcPtr, int, int, int, ProcPtr);
const char* GetWorldMapNodeName(u32);
int sub_80BBA4C(int nodeId);
// ??? nullsub_59(???);
// ??? GmapCursor_Init(???);
// ??? GmapCursor_Loop(???);
ProcPtr NewGmapCursor(ProcPtr, int, int, ProcPtr);
// ??? sub_80BBBF4(???);
// ??? sub_80BBC54(???);
// ??? sub_80BBCC8(???);
// ??? sub_80BBDA4(???);
// ??? nullsub_38(???);
// ??? sub_80BBEB8(???);
// ??? sub_80BBF1C(???);
// ??? sub_80BBF60(???);
// ??? MapRoute_StartTransition(???);
// ??? sub_80BC0F4(???);
// ??? MapRoute_EnableBGSyncs(???);
// ??? MapRoute_TransitionLoop(???);
// ??? MapRoute_TransitionEnd(???);
// ??? MapRoute_BeginRouteTransition(???);
void MapRoute_80BC2DC(struct GmRouteProc * proc);
ProcPtr StartGMapRoute(ProcPtr parent, struct OpenPaths * pPaths, int c, int d);
// ??? sub_80BC3D4(???);
// ??? sub_80BC404(???);
// ??? sub_80BC428(???);
// ??? StartWMGeneralMenu(???);
// ??? WMGeneralMenu_OnInit(???);
// ??? WMGeneralMenu_OnEnd(???);
// ??? WMGeneralMenu_OnCancel(???);
// ??? WMMenu_OnUnitSelected(???);
// ??? WMMenu_OnStatusSelected(???);
// ??? WMMenu_OnGuideDraw(???);
// ??? WMMenu_OnGuideSelected(???);
// ??? WMMenu_OnOptionsSelected(???);
// ??? WMMenu_OnSaveSelected(???);
// ??? StartWMNodeMenu(???);
// ??? WMNodeMenu_OnInit(???);
// ??? WMNodeMenu_OnEnd(???);
// ??? WMNodeMenu_OnCancel(???);
// ??? WMMenu_IsArmoryAvailable(???);
// ??? WMMenu_IsVendorAvailable(???);
// ??? WMMenu_IsSecretShopAvailable(???);
// ??? sub_80BC72C(???);
// ??? sub_80BC754(???);
// ??? WMMenu_OnArmorySelected(???);
// ??? WMMenu_OnVendorSelected(???);
// ??? WMMenu_OnSecretShopSelected(???);
// ??? WMMenu_OnManageItemsSelected(???);
void GmDataInit(void);
// ??? GmPathsInit(???);
bool AddGmPath(struct GMapData*, struct OpenPaths*, int);
bool RemoveGmPath(struct GMapData * pGMapData, struct OpenPaths * pPaths, int idx);
// ??? sub_80BC970(???);
void sub_80BCA0C(struct GMapData*);
int sub_80BCA1C(int);
// ??? sub_80BCA54(???);
// ??? sub_80BCA90(???);
// ??? sub_80BCAB8(???);
// ??? sub_80BCBAC(???);
s8 sub_80BCCFC(s8, s8, int);
// ??? sub_80BCDE4(???);
// ??? sub_80BCE34(???);
void sub_80BCFB4(void); // GM_ClearAllStoryLocations
int sub_80BCFDC(int);
int sub_80BD014(struct GMapData*); // Get next WM Destination?
unsigned int sub_80BD048(void);
unsigned int GetChapterThing(void);
int sub_80BD20C(int);
int sub_80BD224(struct GMapData*);
void sub_80BD260(struct GMapData*, void*);
void sub_80BD270(struct GMapData*, void*);
// ??? sub_80BD284(???);
int sub_80BD28C(int);
int sub_80BD29C(void);
// ??? nullsub_37(???);
// ??? GetCharacterClassId(???);
// ??? MapMUPrim_MakeUnitForChar(???);
// ??? MapMUPrim_MakeUnitForClass(???);
// ??? MapMUPrim_RemoveLinkedMapUnit(???);
// ??? sub_80BD410(???);
// ??? nullsub_70(???);
// ??? sub_80BD41C(???);
// ??? sub_80BD444(???);
// ??? sub_80BD5B8(???);
// ??? sub_80BD660(???);
// ??? sub_80BD6A8(???);
// ??? sub_80BD740(???);
// ??? sub_80BD830(???);
// ??? sub_80BD9D8(???);
// ??? sub_80BDA78(???);
// ??? nullsub_49(???);
// ??? MapMU_FillPrim(???);
ProcPtr NewMapMU(ProcPtr);
// ??? MapMU_SetUnit(???);
void MapMU_RemoveUnit(ProcPtr, int);
// ??? sub_80BDD94(???);
void sub_80BDDC4(ProcPtr, int);
// ??? sub_80BDE3C(???);
// ??? sub_80BDEB4(???);
// ??? sub_80BDFA4(???);
void sub_80BE054(ProcPtr, int); // GmMu_PauseMovement
void sub_80BE068(ProcPtr, int); // GmMu_ResumeMovement
// ??? sub_80BE080(???);
void sub_80BE0A4(ProcPtr, int, s16*, s16*);
// ??? sub_80BE0C8(???);
// ??? MapMU_SetUnitTCSOAMIndex(???);
void MapMU_80BE108(ProcPtr, int, int);
s8 sub_80BE12C(ProcPtr, int);
// ??? sub_80BE194(???);
// ??? sub_80BE330(???);
void sub_80BE35C(ProcPtr, int, s16, s16); // GmMu_SetPosition
void sub_80BE3A0(ProcPtr, int, s16*, s16*);
void sub_80BE3C8(ProcPtr, int, int); // GmMu_SetNode
// ??? sub_80BE3E8(???);
void sub_80BE40C(ProcPtr, int, int); // GmMu_StartFadeIn
void sub_80BE42C(ProcPtr, int, int); // GmMu_StartFadeOut
s8 sub_80BE44C(void); // GmUnitFadeExists
// ??? sub_80BE45C(???);
void MapMU_SetUnitClass(ProcPtr, int, int, int, int);
void MapMU_SetUnitChar(ProcPtr, int, int, int, int);
// ??? sub_80BE56C(???);
int sub_80BE594(int, int);
void sub_80BE5B4(int, int);
// ??? sub_80BE5F8(???);
// ??? sub_80BE638(???);
// ??? sub_80BE65C(???);
// ??? sub_80BE82C(???);
// ??? PutGMapPINodeName(???);
// ??? PutGMapPICharName(???);
// ??? PutGMapPIFace(???);
// ??? PutGMapPIClassName(???);
// ??? sub_80BE9D8(???);
// ??? sub_80BEA78(???);
// ??? sub_80BEB2C(???);
// ??? sub_80BEBD4(???);
// ??? GMapPI_ShowLoop(???);
// ??? sub_80BECB8(???);
// ??? sub_80BEDCC(???);
// ??? GMapPI_HideLoop(???);
// ??? GMapPI_GetGMapUnitIndexAndFaction(???);
// ??? InitGMapPIInterfaceKind(???);
// ??? sub_80BEF20(???);
// ??? sub_80BEF6C(???);
// ??? GMapPI_Init(???);
// ??? StartWorldMapPlayerInterface(???);
// ??? sub_80BF13C(???);
void sub_80BF15C(void);
// ??? sub_80BF180(???);
// ??? sub_80BF190(???);
// ??? sub_80BF198(???);
// ??? sub_80BF210(???);
// ??? sub_80BF294(???);
// ??? sub_80BF2AC(???);
// ??? sub_80BF2D0(???);
// ??? sub_80BF2D8(???);
// ??? sub_80BF370(???);
s8 sub_80BF3F4(void);
void sub_80BF404(int, int, int, int, s16, int);
// ??? sub_80BF490(???);
void sub_80BF4A8(void);
void WM_PutClassSprite(int, int, int, int);
void WM_PutCharSprite(int, int, int, int);
void WM_RemoveUnit(int);
void sub_80BF554(int); // ShowGmUnit
void sub_80BF570(int); // HideGmUnit
void WM_DrawPath(int, int);
// ??? nullsub_50(???);
// ??? sub_80BF5C4(???);
// ??? sub_80BF5DC(???);
// ??? sub_80BF6C0(???);
s8 sub_80BF730(void); // GmPalFadeActive
void sub_80BF748(void); // EndGmPalFade
void sub_80BF788(int, int); // StartGmPalFade_
// ??? sub_80BF7B4(???);
// ??? sub_80BF7DC(???);
// ??? sub_80BF804(???);
// ??? sub_80BF890(???);
// ??? sub_80BF8CC(???);
// ??? sub_80BF988(???);
// ??? sub_80BFA1C(???);
void sub_80BFAEC(int, int, int); // StartWMapBaseEntry
void sub_80BFB24(void); // EndGmBaseEntry
s8 sub_80BFB34(void); // GmBaseEntryExists
// ??? sub_80BFB4C(???);
// ??? sub_80BFB90(???);
// ??? sub_80BFBCC(???);
// ??? sub_80BFC44(???);
// ??? sub_80BFCC8(???);
// ??? sub_80BFD00(???);
// ??? sub_80BFD10(???);
// ??? sub_80BFD28(???);
// ??? nullsub_48(???);
// ??? sub_80BFD80(???);
// ??? sub_80BFDA0(???);
// ??? sub_80BFEF8(???);
// ??? sub_80BFFD0(???);
// ??? sub_80C0080(???);
// ??? sub_80C0144(???);
void NewMapMuEntry(int);
void sub_80C0200(void);
// ??? sub_80C0210(???);
s8 sub_80C0228(void);
void sub_80C0240(int, int); // GmMuEntryStartShow
void sub_80C02A4(int, int); // GmMuEntryStartHide
// ??? sub_80C0308(???);
// ??? sub_80C0358(???);
// ??? sub_80C040C(???);
// ??? sub_80C04CC(???);
void sub_80C04F4(int, int); // StartGmapLineFade
// ??? sub_80C0520(???);
s8 sub_80C0530(void);
// ??? nullsub_47(???);
// ??? sub_80C054C(???);
// ??? sub_80C05AC(???);
// ??? sub_80C05C4(???);
// ??? sub_80C05F8(???);
// ??? sub_80C0610(???);
// ??? sub_80C06F0(???);
// ??? sub_80C07B8(???);
void sub_80C07D4(int, int, ProcPtr);
// ??? sub_80C080C(???);
s8 sub_80C081C(void);
int sub_80C0834(int, int, s16, s16, int);
void GetWMCenteredCameraPosition(int, int, s16*, s16*);
int sub_80C089C(int, int, int, int);
int sub_80C0960(int chIndex);
// ??? sub_80C09B8(???);
// ??? sub_80C09EC(???);
// ??? sub_80C0A10(???);
// ??? sub_80C0A44(???);
// ??? sub_80C0A64(???);
// ??? sub_80C0A9C(???);
// ??? sub_80C0C28(???);
// ??? sub_80C0C44(???);
// ??? sub_80C0CF4(???);
// ??? sub_80C0DF0(???);
// ??? sub_80C0E4C(???);
// ??? sub_80C0E58(???);
// ??? sub_80C0EBC(???);
// ??? sub_80C0F00(???);
// ??? sub_80C0FA4(???);
// ??? sub_80C0FB0(???);
// ??? sub_80C0FE8(???);
// ??? sub_80C10B8(???);
// ??? sub_80C119C(???);
// ??? sub_80C128C(???);
// ??? sub_80C12AC(???);
// ??? sub_80C1324(???);
// ??? sub_80C1370(???);
// ??? sub_80C13CC(???);
// ??? sub_80C13D8(???);
// ??? sub_80C13E8(???);
// ??? sub_80C1470(???);
// ??? sub_80C1480(???);
// ??? sub_80C1524(???);
// ??? sub_80C1624(???);
void sub_80C168C(int, int);
s8 sub_80C16DC(void);
// ??? sub_80C16F4(???);
// ??? sub_80C1724(???);
// ??? sub_80C1774(???);
// ??? nullsub_72(???);
// ??? sub_80C18EC(???);
// ??? sub_80C1920(???);
// ??? sub_80C1A58(???);
void sub_80C1A74(int, int*);
void sub_80C1AB0(void);
void sub_80C1ADC(void);
void sub_80C1AF8(void);
s8 sub_80C1BE0(void);
// ??? sub_80C1BF8(???);
void sub_80C1D00(void);
void sub_80C1D70(void);
// ??? sub_80C1DA0(???);
// ??? sub_80C1DC8(???);
// ??? sub_80C1DD8(???);
// ??? sub_80C1DE8(???);
// ??? sub_80C1DFC(???);
// ??? sub_80C1E14(???);
// ??? sub_80C1E2C(???);
// ??? sub_80C1E40(???);
// ??? sub_80C1E54(???);
// ??? sub_80C1E70(???);
// ??? sub_80C1E8C(???);
void sub_80C1F18(s16, s16, s16, s16, s16, s16, s8); // StartGmapRMUpdate2
void sub_80C1F5C(void);
// ??? sub_80C1F6C(???);
// ??? sub_80C1FDC(???);
// ??? sub_80C1FE0(???);
// ??? sub_80C205C(???);
// ??? sub_80C2078(???);
// ??? sub_80C2094(???);
// ??? sub_80C20B0(???);
// ??? sub_80C210C(???);
// ??? sub_80C214C(???);
// ??? sub_80C224C(???);
// ??? sub_80C2290(???);
// ??? sub_80C22FC(???);
// ??? sub_80C2320(???);
// ??? sub_80C2398(???);
void Make6C_Gmap_RM(s16, s16, int, int);
void sub_80C2460(void);
int sub_80C2470(void);
// ??? sub_80C2488(???);
// ??? GetWMDisplayPosition(???);
void sub_80C24D8(void);
void sub_80C24F8(void);
// ??? sub_80C2598(???);
// ??? sub_80C25B8(???);
// ??? sub_80C25F8(???);
// ??? sub_80C2658(???);
// ??? sub_80C26BC(???);
// ??? sub_80C26E0(???);
// ??? sub_80C26F0(???);
// ??? sub_80C2708(???);
// ??? sub_80C2728(???);
// ??? sub_80C2750(???);
// ??? sub_80C27A8(???);
// ??? sub_80C2804(???);
// ??? sub_80C28C4(???);
// ??? sub_80C28DC(???);
// ??? sub_80C2964(???);
// ??? sub_80C298C(???);
// ??? sub_80C29F8(???);
// ??? sub_80C2A1C(???);
// ??? sub_80C2A40(???);
// ??? sub_80C2AAC(???);
void sub_80C2AD4(int, int); // FEBuilder: "Display place name of world map"
void sub_80C2B7C(int);
int sub_80C2BC4(int);
void sub_80C2C10(int);
// ??? sub_80C2C54(???);
// ??? sub_80C2C58(???);
// ??? sub_80C2C80(???);
// ??? sub_80C2D44(???);
// ??? sub_80C2DA4(???);
// ??? sub_80C2E04(???);
// ??? sub_80C2E28(???);
// ??? sub_80C2E38(???);
// ??? sub_80C2E50(???);
// ??? sub_80C2E70(???);
// ??? sub_80C2EA4(???);
// ??? sub_80C2EF0(???);
// ??? sub_80C2F7C(???);
// ??? sub_80C2F9C(???);
void sub_80C2FC0(s16, s16, s16, s16, int, s8); // StartGmapRMBorder
void sub_80C304C(int);
int sub_80C3094(int);
void sub_80C30E0(int);
// ??? sub_80C3124(???);
// ??? sub_80C31A8(???);
// ??? sub_80C31C4(???);
// ??? sub_80C31E0(???);
// ??? sub_80C31FC(???);
// ??? sub_80C3220(???);
// ??? sub_80C3244(???);
// ??? sub_80C3264(???);
// ??? sub_80C3280(???);
// ??? sub_80C32E4(???);
// ??? sub_80C3350(???);
void sub_80C3378(void *, int, int); // StartGmapAutoMu_1
void sub_80C33D4(void *, int, int); // StartGmapAutoMu_2
void sub_80C343C(int); // EndGmAutoMuFor
s8 sub_80C3484(int); // GmAutoMuActiveFor
// ??? sub_80C34D0(???);
// ??? sub_80C3590(???);
// ??? sub_80C35C4(???);
// ??? sub_80C35EC(???);
void sub_80C3624(int);
void sub_80C3660(void);
void sub_80C368C(ProcPtr);
void sub_80C36A0(int);
// ??? sub_80C36E8(???);
// ??? sub_80C3770(???);
// ??? sub_80C380C(???);
// ??? sub_80C38BC(???);
// ??? sub_80C3A28(???);
// ??? sub_80C3A64(???);
// ??? sub_80C3A8C(???);
// ??? sub_80C3AB8(???);
// ??? sub_80C3B40(???);
// ??? sub_80C3BE4(???);
// ??? sub_80C3D24(???);
// ??? sub_80C3D5C(???);
// ??? sub_80C3D9C(???);
// ??? sub_80C3DAC(???);
// ??? sub_80C3E80(???);
void sub_80C3E94(void);
// ??? nullsub_71(???);
// ??? sub_80C3EC8(???);
// ??? sub_80C3EDC(???);
// ??? sub_80C3F04(???);
// ??? sub_80C3F24(???);
// ??? sub_80C3F88(???);
// ??? sub_80C3FB4(???);
// ??? sub_80C3FE0(???);
void sub_80C400C(int, ProcPtr);
// ??? sub_80C4038(???);
// ??? sub_80C4048(???);
// ??? sub_80C4058(???);
int sub_80C4070(void);
int sub_80C4088();
void sub_80C409C(int);

#endif // GUARD_WORLDMAP_H
