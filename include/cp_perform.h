#ifndef GUARD_CP_PERFORM_H
#define GUARD_CP_PERFORM_H

// ??? AiTargetCursor_Main(???);
void StartAiTargetCursor(int x, int y, int kind, ProcPtr parent);
// ??? CpPerform_UpdateMapMusic(???);
// ??? CpPerform_MoveCameraOntoUnit(???);
// ??? CpPerform_BeginUnitMovement(???);
void AiRefreshMap(void);
// ??? AiStartCombatAction(???);
// ??? AiStartEscapeAction(???);
// ??? AiStartStealAction(???);
// ??? AiPillageAction(???);
// ??? AiStaffAction(???);
// ??? AiUseItemAction(???);
// ??? AiRefreshAction(???);
// ??? AiTalkAction(???);
// ??? AiRideBallistaAction(???);
// ??? AiExitBallistaAction(???);
// ??? AiDKNightmareAction(???);
// ??? AiDKSummonAction(???);
// ??? AiPickAction(???);
// ??? CpPerform_MoveCameraOntoTarget(???);
// ??? CpPerform_PerformAction(???);
// ??? CpPerform_WaitAction(???);
// ??? CpPerform_Cleanup(???);
// ??? AiDummyAction(???);
// ??? AiEscapeAction(???);
// ??? AiWaitAndClearScreenAction(???);
// ??? CpPerform_EquipBest(???);

extern struct ProcCmd CONST_DATA gProcScr_AiTargetCursor[];
extern struct ProcCmd CONST_DATA gProcScr_CpPerform[];

#endif // GUARD_CP_PERFORM_H
