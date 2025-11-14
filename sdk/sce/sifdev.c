#include "sifdev.h"

int sceOpen(const char* filename, int flag, ...)
{
}

int sceClose(int fd)
{
}

int sceRead(int fd, void* buf, int nbyte)
{
}

int sceWrite(int fd, const void* buf, int nbyte)
{
}

int sceLseek(int fd, int offset, int where)
{
}

int sceFsReset()
{
}

int sceSifInitIopHeap()
{
}

int sceSifFreeIopHeap(void*)
{
}

void* sceSifAllocIopHeap(unsigned int)
{
}

int sceSifRebootIop(const char* img)
{
    return 1;
}

int sceSifSyncIop()
{
    return 1;
}

int sceSifLoadModule(const char* filename, int args, const char* argp)
{
    return 1;
}
