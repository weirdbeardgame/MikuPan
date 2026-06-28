#ifndef MIKUPAN_MIKUPAN_ARGS_C_H
#define MIKUPAN_MIKUPAN_ARGS_C_H
#include "typedefs.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

bool MikuPan_IsArg(char* arg);
void MikuPan_InitArgs();
bool MikuPan_ParseArgs(int argc, char *argv[]);

#endif//MIKUPAN_MIKUPAN_ARGS_C_H