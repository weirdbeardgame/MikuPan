#include "libcdvd.h"

int sceCdInit(int init_mode)
{
}

int sceCdMmode(int media)
{
}

int sceCdReadClock(sceCdCLOCK* rtc)
{
    return 1;
}

int sceCdStRead(u_int size, u_int* buf, u_int mode, u_int* err)
{
}

int sceCdStStop()
{
}

int sceCdDiskReady(int mode)
{
}

int sceCdStInit(u_int bufmax, u_int bankmax, u_int iop_bufaddr)
{
}

int sceCdSearchFile(sceCdlFILE* fp, const char* name)
{
}

int sceCdStStart(u_int lbn, sceCdRMode* mode)
{
}
