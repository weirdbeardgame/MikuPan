#ifndef OUTGAME_BTL_MODE_BTL_MENU_H
#define OUTGAME_BTL_MODE_BTL_MENU_H

#include "typedefs.h"

typedef struct { // 0x10
  /* 0x0 */ u_char rank;
  /* 0x2 */ u_short best_time;
  /* 0x8 */ long int best_shot;
} STAGE_WRK;

// extern MSN_LOAD_DAT stage_load_dat0[0];
// extern MSN_LOAD_DAT stage_load_dat1[0];
// extern MSN_LOAD_DAT stage_load_dat2[0];
// extern MSN_LOAD_DAT stage_load_dat3[0];
// extern MSN_LOAD_DAT stage_load_dat4[0];
// extern MSN_LOAD_DAT *stage_load_dat[0];
// extern FREE_DAT free_dat[0];
// extern BTL_SAVE_STR btl_save_str[0];
// extern u_long btl_save_str_num;

extern STAGE_WRK stage_wrk[20];


void FreeModeMain();
void FreeModePosSet();
void BattleModeInit();
void ClearStageWrk();
void BattleModeMain();
int StageTitleInit();
int StageTitleLoad();
void StageGhostLoadReq();
void StageGhostLoadAfter();
void SaveStoryWrk();
void LoadStoryWrk();

#endif // OUTGAME_BTL_MODE_BTL_MENU_H
