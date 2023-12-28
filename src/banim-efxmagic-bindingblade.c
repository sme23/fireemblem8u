#include "global.h"

#include "anime.h"
#include "ekrbattle.h"
#include "efxbattle.h"
#include "efxmagic.h"
#include "hardware.h"
#include "bmlib.h"

//! FE8U = 0x0805CEC4
void nullsub_42(struct Anim * anim)
{
    return;
}

// clang-format off

struct ProcCmd CONST_DATA ProcScr_efxHurtmut[] =
{
    PROC_NAME("efxHurtmut"),
    PROC_REPEAT(sub_805CF04),
    PROC_END,
};

// clang-format on

//! FE8U = 0x0805CEC8
void sub_805CEC8(struct Anim * anim)
{
    struct ProcEfx * proc;

    SpellFx_Begin();
    NewEfxSpellCast();
    SpellFx_ClearBG1Position();

    proc = Proc_Start(ProcScr_efxHurtmut, PROC_TREE_3);
    proc->anim = anim;
    proc->timer = 0;
    proc->hitted = CheckRoundMiss(GetAnimRoundTypeAnotherSide(anim));

    return;
}

//! FE8U = 0x0805CF04
void sub_805CF04(struct ProcEfx * proc)
{
    struct Anim * anim = GetAnimAnotherSide(proc->anim);
    int duration = EfxGetCamMovDuration();

    proc->timer++;

    if (proc->timer == 1)
    {
        NewEfxFarAttackWithDistance(proc->anim, -1);
    }

    if (proc->timer == duration + 1)
    {
        PlaySFX(0x10D, 0x100, anim->xPosition, 1);
        sub_805CFC0(anim);

        NewEfxFlashBgWhite(proc->anim, 6);

        anim->state3 |= (ANIM_BIT3_TAKE_BACK_ENABLE | ANIM_BIT3_HIT_EFFECT_APPLIED);

        StartBattleAnimHitEffectsDefault(anim, proc->hitted);

        if (!proc->hitted)
        {
            EfxPlayHittedSFX(anim);
        }
    }
    else if (proc->timer == duration + 28)
    {
        NewEfxALPHA(anim, 0, 14, 16, 0, 0);
    }
    else if (proc->timer == duration + 50)
    {
        return;
    }
    else if (proc->timer == duration + 55)
    {
        SpellFx_Finish();
        RegisterEfxSpellCastEnd();
        Proc_Break(proc);
    }

    return;
}

// clang-format off

struct ProcCmd CONST_DATA ProcScr_efxHurtmutOBJ[] =
{
    PROC_NAME("efxHurtmutOBJ"),
    PROC_REPEAT(sub_805D030),
    PROC_END,
};

// clang-format on

//! FE8U = 0x0805CFC0
void sub_805CFC0(struct Anim * anim)
{
    struct ProcEfxOBJ * proc;
    u32 * scr;

    gEfxBgSemaphore++;

    proc = Proc_Start(ProcScr_efxHurtmutOBJ, PROC_TREE_3);
    proc->anim = anim;
    proc->timer = 0;
    proc->terminator = 52;

    if (GetAnimPosition(anim) == 0)
    {
        scr = gUnknown_085E067C;
    }
    else
    {
        scr = gUnknown_085E12DC;
    }

    proc->anim2 = EfxCreateFrontAnim(anim, scr, scr, scr, scr);

    SpellFx_RegisterObjPal(gUnknown_085DE964, PLTT_SIZE_4BPP);
    SpellFx_RegisterObjGfx(gUnknown_085DDC64, 32 * 4 * CHR_SIZE);

    return;
}

//! FE8U = 0x0805D030
void sub_805D030(struct ProcEfxOBJ * proc)
{
    proc->timer++;

    if (proc->timer > proc->terminator)
    {
        AnimDelete(proc->anim2);
        gEfxBgSemaphore--;
        Proc_Break(proc);
    }

    return;
}
