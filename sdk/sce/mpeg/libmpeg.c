#include "libmpeg.h"

int sceMpegReset(sceMpeg* mp)
{
}

int sceMpegCreate(sceMpeg* mp, u_char* work_area, int work_area_size)
{
}

int sceMpegDelete(sceMpeg* mp)
{
}

int sceMpegGetPicture(sceMpeg* mp, sceIpuRGB32* rgb32, int mbcount)
{
}

int sceMpegIsEnd(sceMpeg* mp)
{
}

int sceMpegIsRefBuffEmpty(sceMpeg* mp)
{
}

void sceMpegSetDecodeMode(sceMpeg* mp, int ni, int np, int nb)
{
}

sceMpegCallback sceMpegAddCallback(sceMpeg* mp, sceMpegCbType type, sceMpegCallback callback, void* anyData)
{
}

sceMpegCallback sceMpegAddStrCallback(sceMpeg* mp, sceMpegStrType strType, int ch, sceMpegCallback callback,
    void* anyData)
{
}
