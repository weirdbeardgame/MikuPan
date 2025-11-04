#include "common.h"

#ifdef MATCHING_DECOMP
#define INCLUDING_FROM_CAMERA_C
#include "mdlwork.h"
#undef INCLUDING_FROM_CAMERA_C
#else
#include "camera.h"
#endif
