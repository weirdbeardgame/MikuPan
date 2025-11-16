#include "common.h"
#include "btl_menu.h"

STAGE_WRK stage_wrk[20];

void FreeModeMain()
{
}

void FreeModePosSet()
{
}

void BattleModeInit()
{
}

void ClearStageWrk()
{
    /* v0 2 */ int i;

    memset(&stage_wrk, 0, sizeof(stage_wrk));

    for (i = 0; i <= 19; i++)
    {
        stage_wrk[i].best_time = 0x8c64;
    }
}

void BattleModeMain()
{
}

int StageTitleInit()
{
}

int StageTitleLoad()
{
}

void StageGhostLoadReq()
{
}

void StageGhostLoadAfter()
{
}

void SaveStoryWrk()
{
}

void LoadStoryWrk()
{
}
