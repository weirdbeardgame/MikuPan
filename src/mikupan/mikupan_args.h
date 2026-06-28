#ifndef MIKUPAN_MIKUPAN_ARGS_H
#define MIKUPAN_MIKUPAN_ARGS_H

#include <typedefs.h>
#include <string>
#include <vector>

extern std::vector<std::string> args;

extern "C" {
    bool MikuPan_IsArg(char* arg);
    void MikuPan_InitArgs();
    bool MikuPan_ParseArgs(int argc, char *argv[]);
}
#endif//MIKUPAN_MIKUPAN_ARGS_H