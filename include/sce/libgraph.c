#include "libgraph.h"

void sceGsSetDefDBuff(sceGsDBuff* dp, short psm, short w, short h, short ztest, short zpsm, short clear)
{
}

void sceGsResetPath()
{
}

void sceGsResetGraph(short mode, short inter, short omode, short ffmode)
{
}

void sceGsPutDispEnv(sceGsDispEnv* disp)
{
}

int sceGsPutDrawEnv(sceGifTag* giftag)
{
}

void sceGsSetHalfOffset(sceGsDrawEnv1* draw, short centerx, short centery, short halfoff)
{
}

int sceGsSyncV(int mode)
{
    return 1;
}

int sceGsSwapDBuff(sceGsDBuff* db, int id)
{
}

int sceGsSetDefStoreImage(sceGsStoreImage* sp, short sbp, short sbw, short spsm, short x, short y, short w, short h)
{
}

int sceGsExecStoreImage(sceGsStoreImage* sp, u_long128* dstaddr)
{
}

int sceGsSyncPath(int mode, u_short timeout)
{
}

int sceGsSetDefLoadImage(sceGsLoadImage* lp, short dbp, short dbw, short dpsm, short x, short y, short w, short h)
{
}

int sceGsExecLoadImage(sceGsLoadImage* lp, u_long128* srcaddr)
{
}

int sceGsSetDefDrawEnv(sceGsDrawEnv1* draw, short psm, short w, short h, short ztest, short zpsm)
{
}

sceGsGParam* sceGsGetGParam()
{
}
