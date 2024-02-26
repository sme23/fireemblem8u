#ifndef GUARD_FUNCTIONS_H
#define GUARD_FUNCTIONS_H

#include "gba/types.h"
#include "proc.h"
#include "types.h"

// ??? RomHeaderNintendoLogo(???);
// ??? crt0(???);
void IrqMain(void);
// ??? ARMCodeToCopy_Start(???);
// ??? ColorFadeTick(???);
// ??? ClearOam(???);
// ??? Checksum32(???);
// ??? TmFillRect(???);
// ??? sub_80003E0(???);
// ??? sub_800043C(???);
// ??? PutOamHi(???);
// ??? PutOamLo(???);
// ??? DrawGlyph(???);
// ??? sub_8000620(???);
// ??? DecodeString(???);
// ??? MapFloodCoreStep(???);
// ??? MapFloodCore(???);
// ??? ARMCodeToCopy_End(???);
// ??? AgbMain(???);
// ??? sub_8000B10(???);
// ??? StoreIRQToIRAM(???);
// ??? DummyIRQRoutine(???);
void SetIRQHandler(int index, void *irq);

void EnableKeyComboResetEN();
void DisableKeyComboResetEN();
int CheckCanKeyComboReset(void);
u32 GetGameClock(void);
void SetGameTime(int newTime);
void IncrementGameClock(void);
u8 FormatTime(u32 frameTotal, u16 * hours, u16 * minutes, u16 * seconds);

void StoreRoutinesToIRAM();
void DrawGlyphRam();
void CallARM_DecompText(const char *, char *);
void CallARM_PushToSecondaryOAM(int a, int b, const u16 *c, int d);
void CallARM_PushToPrimaryOAM(int x, int y, const u16* data, int oam2base);
// ??? CallARM_Func5(???);
void CallARM_FillMovementMap(void);
// ??? ResetIconGraphics_(???);
// ??? ResetIconGraphics(???);
// ??? LoadIconPalettes(???);
// ??? LoadIconPalette(???);
// ??? sub_80035EC(???);
// ??? GetIconGfxTileIndex(???);
// ??? GetIconGfxIndex(???);
// ??? GetIconTileIndex(???);
// ??? DrawIcon(???);
// ??? ClearIconGfx(???);
// ??? LoadIconObjectGraphics(???);
// ??? sub_8008FB4(???);
// ??? nullsub_15(???);
// ??? sub_800903C(???);
// ??? sub_800904C(???);
// ??? sub_8009100(???);
void sub_800915C(int, int, int, int, int, int, int, ProcPtr);

const char * GetStrPrefix(s8 * str, bool capital);
void InsertPrefix(char * str, const char * prefix, bool capital);
void SetMsgTerminator(signed char * str);
char *GetStringFromIndex(int index);
char *GetStringFromIndexInBuffer(int index, char *buffer);
char *StringInsertSpecialPrefixByCtrl(void);
char* StrInsertTact(void);

// ??? ReputConvoBg_unused(???);
void ResetDialogueScreen(void);
// ??? EventShinningCursorAdvance(???);
void ShinningEventCursor(int lo, int hi, int cur);

void ChangeUnitAi(struct Unit *, u8, u8, u8);
void ChangeAiForCharacter(u8, u8, u8, u8);
// ??? ChangeAiForPositions(???);
// ??? EvtBattleGenerateRealInternal(???);
// ??? EvtBattleGenerateReal(???);
// ??? EvtBattleGenerateBallistaReal(???);
// ??? StartScriptBattleAnim(???);
void StartEventBattle(struct Unit *, struct Unit *, u8, s8, u16, struct BattleHit *, s8);
void EventBattleReloadBmStatus(void);
void EventPromoteUnitExt(struct Unit *, u8, u8);
void sub_8012324(void);
int GetChapterAllyUnitCount();
void InitPlayerUnitPositionsForPrepScreen(void);
void sub_801240C();
void sub_801247C(struct Unit *);
// ??? sub_8012578(???);
void sub_80125C0(struct UnitDefinition*);
void StoreUnitWordStructs(void);
void LoadUnitWordStructs(void);

int GetSomeFacingDirection(int, int, int, int);
// ??? Make6CMOVEUNITForUnitBeingRescued(???);
// ??? Loop6C_KOIDO(???);
void Make6CKOIDO(struct Unit*, int, int, ProcPtr);
void Make6CKOIDOAMM(struct Unit*, int);
// ??? bmxfade_init(???);
// ??? bmxfade_loop(???);
// ??? Destruct6CBMXFADE(???);
void NewBMXFADE(s8 strongLock);
void MakeNew6CBMXFADE2(s8 lock_game, ProcPtr parent);
bool8 DoesBMXFADEExist(void);
// ??? GetPlayerStartCursorPosition(???);
// ??? GetEnemyStartCursorPosition(???);
// ??? ProcFun_ResetCursorPosition(???);
// ??? ADJUSTFROMXI_MoveCameraOnSomeUnit(???);
int ConvoyMenuProc_StarMenu(ProcPtr proc);
int ConvoyMenuProc_MenuEnd(ProcPtr proc);
int ConvoyMenuProc_MaybeStartSelectConvoyItem(ProcPtr proc);
int ConvoyMenuProc_SendToConvoyReal(ProcPtr proc);
void ConvoyMenuProc_SetupActiveUnit(ProcPtr proc);
void ConvoyMenuProc_ExecBootlegPopup(ProcPtr proc);
void HandleNewItemGetFromDrop(struct Unit * unit, int item, ProcPtr parent);
// ??? SendToConvoyMenu_Draw(???);
// ??? MenuCommand_DrawExtraItem(???);
// ??? SendToConvoyMenu_NormalEffect(???);
// ??? sub_801E1DC(???);
// ??? sub_801E1FC(???);
// ??? sub_801E250(???);
// ??? sub_801E294(???);
void UpdateMapViewWithFog(int vision_range);
// ??? FastUpdateMapViewWithFog(???);
void FillWarpRangeMap(struct Unit* caster, struct Unit* target);

// ??? PrepUnitSwapProc_Init(???);
// ??? PrepUnitSwapProc_MainLoop(???);
// ??? PrepUnitSwapProc_OnEnd(???);
void StartPrepUnitSwap(ProcPtr parent, struct Unit *unit, int x_dest, int y_dest);
int PrepUnitSwapProcExits();
// ??? PhaseIntroVMatchHi(???);
// ??? PhaseIntroVMatchMid(???);
// ??? PhaseIntroVMatchLo(???);
// ??? PhaseIntroText_PutText(???);
// ??? PhaseIntroInitText(???);
// ??? PhaseIntroText_InLoop(???);
// ??? PhaseIntroText_OutLoop(???);
// ??? PhaseIntroClearText(???);
// ??? PhaseIntroUnk_Init(???);
// ??? PhaseIntroUnk_Loop(???);
// ??? PhaseIntroSquares_Init(???);
// ??? PhaseIntroSquares_InLoop(???);
// ??? PhaseIntroSquares_OutLoop(???);
// ??? PhaseIntroBlendBox_Init(???);
// ??? PhaseIntroBlendBox_InLoop(???);
// ??? PhaseIntroBlendBox_OutLoop(???);
// ??? PhaseIntro_EndIfNoUnits(???);
// ??? PhaseIntro_InitGraphics(???);
// ??? PhaseIntro_InitDisp(???);
// ??? PhaseIntro_WaitForEnd(???);
void ChangeActiveUnitFacing(int xLook, int yLook);
// ??? GasTrapSpriteAnim_Init(???);
// ??? StartGasTrapAnim(???);
// ??? FireTrapSpriteAnim_Init(???);
void StartFireTrapAnim(ProcPtr, int, int);
void StartFireTrapAnim2(ProcPtr, int, int);
// ??? ProcUnkTrapAnimFunc(???);
// ??? StartUnkTrapAnim(???);
// ??? ArrowTrapSpriteAnim_Init(???);
// ??? StartArrowTrapAnim(???);
// ??? ProcShowMapChange_MoveCamera(???);
// ??? ProcShowMapChange_UpdateGame(???);
// ??? StartShowMapChangeAnim(???);
// ??? PikeTrapSpriteAnim_Init(???);
// ??? sub_801F978(???);
// ??? ProcPopup2_Init(???);
// ??? ProcPopup2_Loop(???);
// ??? NewPopup2_PlanA(???);
// ??? NewPopup2_PlanB(???);
// ??? NewPopup2_PlanC(???);
// ??? NewPopup2_PlanD(???);
void NewPopup2_DropItem(ProcPtr, int);
void NewPopup2_SendItem(ProcPtr, int);
void PutScreenFogEffect(void);
void PutScreenFogEffectOverlayed(void);
// ??? GameOverScreen_RandomScroll_Init(???);
// ??? GameOverScreen_RandomScroll_Loop(???);
// ??? GameOverScreenHBlank(???);
// ??? GameOverScreen_Init(???);
// ??? GameOverScreen_LoopFadeIn(???);
// ??? GameOverScreen_BeginIdle(???);
// ??? GameOverScreen_LoopIdle(???);
// ??? GameOverScreen_BeginFadeOut(???);
// ??? GameOverScreen_LoopFadeOut(???);
// ??? GameOverScreen_End(???);
void StartGameOverScreen(ProcPtr parent);
// ??? ProcLightRuneAnim_Init(???);
// ??? ProcLightRuneAnim_Loop(???);
// ??? ProcBmFx_CommonEnd(???);
void StartLightRuneAnim(ProcPtr parent, int x, int y);
// ??? ProcLightRuneAnim2_Init(???);
// ??? ProcLightRuneAnim2_Loop(???);
// ??? ProcLightRuneAnim2_End(???);
void StartLightRuneAnim2(ProcPtr parent, int x, int y);
// ??? ProcLightRuneAnim3_Init(???);
// ??? ProcLightRuneAnim3_Loop(???);
// ??? ProcLightRuneAnim3_End(???);
void StartLightRuneAnim3(ProcPtr parent, int x, int y);
// ??? ProcDanceAnim_Init(???);
// ??? ProcDanceAnim_Loop(???);
// ??? ProcDanceAnim_ResetTimer(???);
// ??? ProcDanceAnim_Loop_Blend(???);
void StartDanceringAnim(ProcPtr parent);
// ??? ProcEventWrapAnim_Init(???);
// ??? ProcEventWrapAnim_Loop(???);
// ??? ProcEventWrapAnim_End(???);
// ??? StartEventWarpAnim(???);
// ??? StartEventWarpAnim_unused(???);
// ??? EventWarpAnimExists(???);
// ??? ProcWhiteCircleFx_Loop(???);
// ??? ProcWhiteCircleFx_End(???);
// ??? StartCircularFadeAnim(???);
// ??? ProcEmitSingleStar_Init(???);
// ??? ProcEmitSingleStar_Loop(???);
// ??? Calcs_Interpolate(???);
// ??? LetsEmitStars(???);
// ??? StarsBlinking(???);
// ??? StartEmitStarsAnim(???);
// ??? ClearEmitedStars(???);
// ??? EndEmitStars(???);
// ??? ProcMineFxFunc(???);
// ??? StartMineAnim(???);
// ??? ChapterIntroTitle_InitBgImg(???);
// ??? ChapterIntroTitle_ResetBg(???);
// ??? ChapterIntroTitle_End(???);
// ??? GetPhaseAbleUnitCount(???);
u32 GetPartyGoldAmount(void);
void SetPartyGoldAmount(s32);
void sub_8024E20(u32);
struct Proc* StartTradeMenu(struct Unit* lUnit, struct Unit* rUnit, int unused);
void InitPlayConfig(int isDifficult, s8);
char* GetTacticianName(void);
void SetTacticianName(const char* newName);
void InitUnitStack(void* buff);
void PushUnit(struct Unit* unit);
void LoadPlayerUnitsFromUnitStack();
void LoadPlayerUnitsFromUnitStack2();
// ??? sub_8032E28(???);
// ??? sub_80330D4(???);
// ??? sub_803318C(???);
// ??? CanUnitUseVisit(???);
// ??? CanUnitUseSeize(???);
// ??? CanUnitUseAttack(???);
// ??? CanActiveUnitUseRescue(???);
// ??? CanActiveUnitUseTrade(???);
// ??? GetUnitCommandUseFlags(???);
// ??? sub_80344E8(???);
// ??? sub_8034514(???);
// ??? sub_8034550(???);

// ??? sub_8084880(???);
// ??? sub_80848E0(???);
// ??? sub_8084940(???);
// ??? sub_80849A0(???);
// ??? sub_80849D8(???);
// ??? sub_8084A10(???);
// ??? sub_8084A48(???);
// ??? sub_8084A68(???);
// ??? sub_8084A80(???);
// ??? sub_8084A84(???);
// ??? sub_8084A88(???);
// ??? sub_8084A8C(???);
// ??? sub_8084A90(???);
// ??? sub_8084A94(???);
// ??? sub_8084A98(???);
// ??? sub_8084A9C(???);
// ??? sub_8084AA0(???);
// ??? sub_8084AA4(???);
// ??? sub_8084AA8(???);
// ??? sub_8084AAC(???);
// ??? sub_8084AB0(???);
// ??? sub_8084AB4(???);
// ??? sub_8084AB8(???);
// ??? sub_8084ABC(???);
// ??? sub_8084AC0(???);
// ??? sub_8084AC4(???);
// ??? sub_8084AC8(???);
// ??? sub_8084ACC(???);
// ??? sub_8084AD0(???);
// ??? sub_8084AD4(???);
// ??? sub_8084AD8(???);
// ??? sub_8084ADC(???);
// ??? sub_8084AF4(???);
// ??? sub_8084B0C(???);
// ??? sub_8084B34(???);
// ??? sub_8084B40(???);
// ??? sub_8084B60(???);
// ??? sub_8084B6C(???);
// ??? sub_8084B8C(???);
// ??? sub_8084B98(???);
// ??? sub_8084BB0(???);
// ??? sub_8084BCC(???);
// ??? sub_8084C38(???);
// ??? sub_8084C4C(???);
// ??? sub_8084C8C(???);
// ??? sub_8084C9C(???);
// ??? sub_8084CAC(???);
// ??? sub_8084CE8(???);
// ??? sub_8084CF8(???);
// ??? sub_8084D08(???);
// ??? sub_8084D18(???);
// ??? sub_8084D28(???);
// ??? sub_8084D38(???);
// ??? sub_8084D48(???);
// ??? sub_8084D58(???);
// ??? sub_8084D68(???);
// ??? sub_8084D78(???);
// ??? sub_8084D88(???);
// ??? sub_8084D98(???);
// ??? sub_8084DA8(???);
// ??? sub_8084DB8(???);
// ??? sub_8084DC8(???);
// ??? sub_8084DD8(???);
// ??? sub_8084DE8(???);
// ??? sub_8084DF8(???);
// ??? sub_8084E08(???);
// ??? sub_8084E18(???);
// ??? sub_8084E28(???);
// ??? sub_8084E38(???);
// ??? sub_8084E48(???);
// ??? sub_8084E58(???);
// ??? sub_8084E68(???);
// ??? sub_8084E78(???);
// ??? sub_8084E88(???);
// ??? sub_8084EB8(???);
// ??? sub_8084EC8(???);
// ??? sub_8084ED8(???);
int AreAnyEnemyUnitDead(void);
// ??? GetDeadEnemyAmount(???);
// ??? sub_8084F54(???);
// ??? IsCharDeadAsNonPlayerUnit(???);
// ??? sub_8084FA8(???);
// ??? sub_8084FE4(???);
// ??? sub_8085018(???);
// ??? sub_8085028(???);
// ??? sub_8085038(???);
// ??? sub_8085048(???);
// ??? sub_8085058(???);
// ??? sub_8085068(???);
// ??? sub_8085078(???);
// ??? sub_8085088(???);
// ??? sub_8085098(???);
// ??? sub_80850A8(???);
// ??? sub_80850B8(???);
// ??? sub_80850C8(???);
// ??? sub_80850D8(???);
// ??? sub_80850E8(???);
// ??? sub_80850F8(???);
// ??? sub_8085108(???);
// ??? sub_8085118(???);
// ??? sub_8085128(???);
// ??? sub_808513C(???);
// ??? sub_8085150(???);
// ??? sub_8085164(???);
// ??? sub_8085178(???);
// ??? sub_808518C(???);
// ??? sub_80851A0(???);
// ??? sub_80851E4(???);
// ??? sub_8085220(???);
// ??? sub_8085238(???);
// ??? sub_8085250(???);
// ??? sub_8085268(???);
// ??? sub_8085280(???);
// ??? sub_8085298(???);
// ??? sub_80852B4(???);
// ??? sub_80852D0(???);
// ??? sub_80852EC(???);
// ??? sub_8085308(???);
// ??? sub_8085324(???);
// ??? sub_8085338(???);
// ??? sub_8085350(???);
// ??? sub_8085354(???);
// ??? sub_8085370(???);

// void AutoGenerateUnitdef(u8 a, int b, int c, int d, int e, int f);
void sub_808679C(void);
// ??? sub_808683C(???);
// ??? sub_8086928(???);
void sub_8086934(u8 *buf, int a2, int a3);
void sub_8086960(u8 *buf, int a2, int a3);
void sub_8086984(u8 *buf, int a2, int a3);
void sub_80869AC(u8 *buf, int a2, int a3);
void sub_80869D8(u8 *buf, int a2, int a3);
void sub_8086A08(u8 *buf, int a2, int a3);
void sub_8086A24(u8 *buf, int a2, int a3);
void sub_8086A40(int a1, int a2, int a3, int a4, int a5, int a6);
void DrawStatBarGfx(int arg0, int arg1, u16* tilemap, int arg3, int arg4, int arg5, int arg6);
// ??? BackgroundSlide_Init(???);
// ??? BackgroundSlide_Loop(???);
ProcPtr StartMuralBackground(ProcPtr, void*, int);
ProcPtr StartMuralBackgroundAlt(ProcPtr parent, void * vram, int pal, u8 flag);
ProcPtr StartMuralBackgroundExt(ProcPtr, void*, int, int, int);
void EndMuralBackground(void);

void sub_80895B4(int, int);
void sub_8089624(int, u32);
void sub_808966C(int, int);
void sub_8089678(int);
void sub_80896A8(int chr);
void sub_80896D8(u16 bg[], int);
void sub_80896FC(u16 *, int, int);
void sub_8089720(u16 * tm, int pal);
void sub_8089744(u16 * tm, int pal);
int sub_8089768(struct PlaySt *);
int sub_808979C(struct PlaySt *);

u8 CanPrepScreenSave();
int sub_8095024();
int sub_8095094(int, int);
int sub_80950C4(int);
void sub_80950E8(int, int);
// ??? sub_8095138(???);
void PrepScreenMenu_OnPickUnits(struct ProcAtMenu* proc);
void PrepScreenMenu_OnItems(struct ProcAtMenu* proc);
void PrepScreenMenu_OnSupport(struct ProcAtMenu* proc);
void PrepScreenMenu_OnSave(struct ProcAtMenu* proc);
int PrepScreenMenu_OnStartPress(struct ProcAtMenu* proc);
int Prep_HasUnitDeployed();
void sub_8095284(ProcPtr proc);
int PrepScreenMenu_OnBPress(struct ProcAtMenu* proc);
void PrepScreenMenu_OnCheckMap(struct ProcAtMenu* proc);
// ??? sub_80952CC(???);
// ??? __malloc_unlock_1(???);
void ResetSioPidPool();
void RegisterSioPid(u8 val);
void RemoveSioPid(u8 val);

// ??? WmSell_DrawSupplyDialogueSpriteText(???);
// ??? sub_809FDD4(???);
// ??? sub_809FE1C(???);
// ??? WmSell_Init(???);
// ??? sub_809FE68(???);
// ??? WmSell_DrawSellOptionSpriteText(???);
// ??? WmSell_DrawValueSpriteText(???);
// ??? WmSell_DrawItemGoldValue(???);
// ??? WmSell_DrawPartyFunds(???);
// ??? WmSell_PutSupplyFaceAndText(???);
// ??? WmSell_Setup(???);
// ??? WmSell_MainLoop_HandleDpadKeys(???);
// ??? sub_80A03C4(???);
// ??? WmSell_OnLoop_MainKeyHandler(???);
// ??? sub_80A0570(???);
// ??? WmSell_ConfirmSellItem(???);
// ??? WmSell_OnLoop_ConfirmSellKeyHandler(???);
// ??? WmSell_OnEnd(???);
// ??? StartWorldMapSellScreen(???);
// ??? sub_80A0724(???);
// ??? FortuneSubMenu_Init_Null(???);
// ??? __malloc_unlock_2(???);
// ??? FortuneSubMenu_Unused_SetAvailableOptions(???);
// ??? FortuneSubMenu_Unused_SetupText(???);
// ??? FortuneSubMenu_Unused_KeyHandler(???);
// ??? FortuneSubMenu_OnOptionSelected(???);
// ??? FortuneSubMenu_HandleOptionSwitch(???);
void StartFortuneSubMenu(int, ProcPtr);
bool sub_80A095C(int);
// ??? GetChapterDivinationTextIdHectorStory(???);
// ??? GetChapterDivinationTextIdBeginning(???);
// ??? GetChapterDivinationTextIdEnding(???);
// ??? GetChapterDivinationFee(???);
// ??? GetChapterDivinationPortrait(???);
// ??? sub_80A0A18(???);
// ??? sub_80A0A34(???);
// ??? sub_80A0A5C(???);
// ??? sub_80A0A70(???);
// ??? sub_80A0A74(???);

// ??? sub_80A6544(???);

// ??? sub_80AC6AC(???);
// ??? sub_80AC784(???);
void sub_80AC844(u16 *, int, int, int, int, int, int, int);
// ??? UiCursorHand_Init(???);
// ??? UiCursorHand_Loop(???);
ProcPtr StartUiCursorHand(ProcPtr);
void SetUiCursorHandConfig(int, int, int, u8);
void UiCursorHand_80ACA4C(int, int, int, int, int);
void sub_80ACA84(u32 a);
void sub_80ACAA4(void);
void BlockUiCursorHand(void);
void UnblockUiCursorHand(void);
void EndUiCursorHand(void);
// ??? UiSpinningArrows_Init(???);
// ??? UiSpinningArrows_Loop(???);
ProcPtr StartUiSpinningArrows(ProcPtr);
ProcPtr LoadUiSpinningArrowGfx(int, int, int);
void SetUiSpinningArrowConfig(int mask);
void SetUiSpinningArrowPositions(int, int, int, int);
void SetUiSpinningArrowFastMaybe(int);
void EndUiSpinningArrows(void);

// ??? sub_80AE86C(???);
// ??? sub_80AE930(???);
// ??? sub_80AE938(???);
// ??? sub_80AE964(???);
// ??? sub_80AE99C(???);
ProcPtr StartSpriteAnimfx(const u8 * gfx, const u16 * pal, const void * apDef, int x, int y, int animId, int palId, int palCount, u16 chr, int aObjNode);
int GetBgXOffset(int);
// ??? GetBgYOffset(???);
char* AppendTextBuffer_80AEABC(const char*, char*);
char* AppendCharAndTerminate(int, char*);
// ??? sub_80AEAE8(???);
// ??? sub_80AEB1C(???);
// ??? sub_80AEB28(???);
// ??? sub_80AEB44(???);
// ??? BonusClaimHelp_Init(???);
// ??? BonusClaimHelp_Loop(???);
void StartBonusClaimHelpBox(int, int, int, ProcPtr);
int CountDigits(int number);
// ??? sub_80AEC04(???);
// ??? sub_80AEC54(???);
// ??? sub_80AEC68(???);

// ??? sub_80B0458(???);
// ??? sub_80B04BC(???);
// ??? sub_80B04F8(???);
// ??? nullsub_66(???);
// ??? sub_80B05C4(???);
// ??? sub_80B060C(???);
// ??? sub_80B0620(???);
// ??? sub_80B169C(???);
// ??? sub_80B24DC(???);
// ??? nullsub_67(???);
// ??? sub_80B251C(???);
// ??? sub_80B2608(???);
void NewColFadeOut(int, int, int, ProcPtr);
void NewColFadeIn(int, int, int, ProcPtr);
// ??? sub_80B5730(???);
void StartArenaScreen(void);
void StartArenaResultsScreen(void);
// ??? ArenaUi_Init(???);
// ??? sub_80B5970(???);
// ??? ArenaUi_WelcomeDialogue(???);
// ??? ArenaUi_WagerGoldDialogue(???);
// ??? ArenaUi_CheckConfirmation(???);
// ??? ArenaUi_ConfirmWager(???);
// ??? ArenaUi_InstructionsDialogue(???);
// ??? ArenaUi_GoodLuckDialogue(???);
// ??? ArenaUi_FadeOutBgm(???);
// ??? ArenaUi_StartArenaBattle(???);
// ??? sub_80B5B00(???);
// ??? sub_80B5B0C(???);
// ??? ArenaUi_ResultsDialogue(???);
// ??? ArenaUi_ShowGoldBoxOnVictoryOrDraw(???);
// ??? ArenaUi_OnEnd(???);
// ??? StartArenaDialogue(???);
// ??? DrawArenaOpponentDetailsText(???);
// ??? Arena_PlayResultSong(???);
// ??? Arena_PlayArenaSong(???);
void sub_80B5D3C(void);
// ??? sub_80B5D48(???);
void WriteSuspandPlaterIdle(void);
int GetGameTacticsRank();
int GetGameSurvivalRank();
int GetGameExpRank();
int GetGameCombatRank();
int GetGameFundsRank();
int GetOverallRank(int, int, int, int, int);
// ??? sub_80B60C8(???);
// ??? sub_80B6104(???);
// ??? GetChapterTacticsRank(???);
// ??? GetChapterSurvivalRank(???);
// ??? sub_80B61FC(???);
// ??? GetGameDeathCount(???);
// ??? GetGameWinPerc(???);
// ??? GetChapterDeathCount(???);
// ??? sub_80B62D8(???);
// ??? GetChapterFundsRank(???);
// ??? GetChapterWinPerc(???);
// ??? GetChapterCombatRank(???);
// ??? GetChapterExpRank(???);
void ComputeChapterRankings(void);
// ??? GetCG(???);
// ??? sub_80B65F4(???);
void DisplayCGfx(u16* buf, int offset, int, int, int);
void sub_80B8188(int, int, int);
void nullsub_7(void);
// ??? sub_80B8190(???);
void nullsub_5(int unused);
// ??? sub_80B8200(???);

// ??? sub_80C40B0(???);
// ??? sub_80C40B8(???);
// ??? sub_80C412C(???);
// ??? sub_80C4158(???);
// ??? sub_80C4184(???);
// ??? sub_80C41E4(???);
// ??? sub_80C41F4(???);
// ??? sub_80C4210(???);
// ??? sub_80C4228(???);
// ??? sub_80C4238(???);
// ??? sub_80C43B4(???);
// ??? sub_80C4460(???);
// ??? sub_80C45E0(???);
// ??? sub_80C4664(???);
// ??? sub_80C46E4(???);
// ??? sub_80C46F0(???);
// ??? sub_80C4738(???);
// ??? sub_80C47B0(???);
// ??? sub_80C47F4(???);
void sub_80C4878(ProcPtr);
// ??? sub_80C488C(???);
// ??? sub_80C48F0(???);
// ??? OpSubtitle_HandleStartPress(???);
// ??? OpSubtitle_Init(???);
// ??? Subtitle_LightFlareFx_Init(???);
// ??? Subtitle_LightFlareFx_Loop(???);
// ??? Subtitle_LightFlareFx_End(???);
// ??? sub_80C4BB4(???);
// ??? OpSubtitle_AwaitTimer2a(???);
// ??? sub_80C4C60(???);
// ??? sub_80C4CD0(???);
// ??? sub_80C4D54(???);
// ??? sub_80C4DA0(???);
// ??? sub_80C4E18(???);
// ??? sub_80C4EC4(???);
// ??? sub_80C4F60(???);
// ??? sub_80C501C(???);
// ??? sub_80C50A0(???);
// ??? sub_80C5104(???);
// ??? sub_80C51A8(???);
// ??? OpSubtitle_SetupBackgrounds(???);
// ??? sub_80C5218(???);
// ??? sub_80C5328(???);
// ??? sub_80C5370(???);
// ??? sub_80C538C(???);
// ??? sub_80C5400(???);
// ??? sub_80C540C(???);
void StartIntroMonologue(ProcPtr);
// ??? DrawTitleSprites_Init(???);
// ??? DrawTitleSprites_Loop(???);
void sub_80C5548(int);
// ??? SkipTitleFx_Loop_KeyListener(???);
// ??? Title_StartSkipFxListener(???);
// ??? Title_EndSkipFxListener(???);
// ??? Title_Init(???);
// ??? Title_SetupMainGraphics(???);
// ??? TitleScreenTryJumpIntroAnim(???);
// ??? sub_80C5870(???);
// ??? Title_SetupSpecialEffectGraphics(???);
// ??? sub_80C5A44(???);
// ??? Title_Loop_DrawRotatingBlueLights(???);
// ??? sub_80C5BD4(???);
// ??? Title_Loop_DrawRedBlueOrbs(???);
// ??? Title_PrepareMainScreenWithExtendedBgm(???);
// ??? Title_Loop_RevealGreenDragonFlashFx(???);
// ??? Title_Loop_FlashFxExpand(???);
// ??? Title_LoadDemonKingOnBg2(???);
// ??? Title_ShowBg2(???);
// ??? sub_80C5FB4(???);
// ??? Title_PrepareMainLogoZoom(???);
// ??? Title_Loop_MainLogoZoom(???);
// ??? sub_80C60CC(???);
// ??? nullsub_23(???);
// ??? sub_80C6104(???);
// ??? DrawTitleLightBubbleSprites(???);
// ??? Title_Loop_LightExplosionFx(???);
// ??? sub_80C62DC(???);
// ??? Title_IDLE(???);
// ??? Title_EndAllProcChildren(???);
// ??? Title_RestartProc(???);
void StartTitleScreen_WithMusic(ProcPtr);
void StartTitleScreen_FlagFalse(ProcPtr);
void StartTitleScreen_FlagTrue(ProcPtr);

// ??? umul3232H32(???);
// ??? SoundMain(???);
// ??? SoundMainRAM(???);
// ??? sub_80CF6E4(???);
// ??? RealClearChain(???);
// ??? ply_fine(???);
// ??? MPlayJumpTableCopy(???);
// ??? ldrb_r3_r2(???);
// ??? ld_r3_tp_adr_i(???);
// ??? ply_patt(???);
// ??? sub_80CF9D4(???);
// ??? sub_80CF9E8(???);
// ??? sub_80CFA18(???);
// ??? sub_80CFA24(???);
// ??? sub_80CFA38(???);
// ??? sub_80CFA4C(???);
// ??? sub_80CFA7C(???);
// ??? sub_80CFA90(???);
// ??? sub_80CFAA4(???);
// ??? sub_80CFAB8(???);
// ??? sub_80CFACC(???);
// ??? sub_80CFAD8(???);
// ??? sub_80CFAF0(???);
// ??? sub_80CFB04(???);
// ??? m4aSoundVSync(???);
// ??? sub_80CFDC0(???);
// ??? TrackStop(???);
// ??? sub_80CFE14(???);
// ??? ply_note(???);
// ??? ply_endtie(???);
// ??? sub_80D0084(???);
// ??? sub_80D00A0(???);
// ??? ply_lfos(???);
// ??? ply_mod(???);
// ??? MidiKeyToFreq(???);
// ??? MPlayContinue(???);
// ??? MPlayFadeOut(???);
void m4aSoundInit();
// ??? m4aSoundMain(???);
void m4aSongNumStart(u16);
// ??? m4aSongNumStop(???);
// ??? m4aMPlayFadeOut(???);
// ??? m4aMPlayFadeOutTemporarily(???);
// ??? m4aMPlayFadeIn(???);
// ??? m4aMPlayImmInit(???);
// ??? MPlayExtender(???);
// ??? ClearChain(???);
// ??? Clear64byte(???);
// ??? SoundInit(???);
// ??? SampleFreqSet(???);
// ??? m4aSoundMode(???);
// ??? m4aSoundVSyncOff(???);
// ??? m4aSoundVSyncOn(???);
// ??? MPlayOpen(???);
// ??? MPlayStart(???);
// ??? m4aMPlayStop(???);
// ??? FadeOutBody(???);
// ??? TrkVolPitSet(???);
// ??? MidiKeyToCgbFreq(???);
// ??? CgbOscOff(???);
// ??? CgbModVol(???);
// ??? CgbSound(???);
// ??? m4aMPlayVolumeControl(???);
// ??? m4aMPlayPanpotControl(???);
// ??? ClearModM(???);
// ??? ply_memacc(???);
// ??? ply_xcmd(???);
// ??? ply_xxx(???);
// ??? ply_xwave(???);
// ??? ply_xtype(???);
// ??? ply_xatta(???);
// ??? ply_xdeca(???);
// ??? ply_xsust(???);
// ??? ply_xrele(???);
// ??? ply_xiecv(???);
// ??? ply_xiecl(???);
// ??? ply_xleng(???);
// ??? ply_xswee(???);

void ClearOAMBuffer(void * buf, int count);
void TileMap_FillRect(u16 *dest, int width, int height, int fillValue);
void CALLARM_ColorFadeTick();
void TileMap_CopyRect(u16* src, u16* dst, int width, int height);
void CallARM_FillTileRect(u16* tilemap, const void* tsa, int tileref);
u32 ComputeChecksum32(const u32 * buf, int size);

#endif  // GUARD_FUNCTIONS_H
