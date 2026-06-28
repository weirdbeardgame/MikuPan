#include "mikupan_args.h"
#include "mikupan/mikupan_logging.h"
#include <algorithm>
#include <cstring>

std::vector<std::string> args;


bool MikuPan_IsArg(char* arg)
{
    return std::find(args.begin(), args.end(), arg) != args.end();
}

void MikuPan_InitArgs()
{
    args.push_back("Hello");
    args.push_back("data_dir");
}


bool MikuPan_ParseArgs(int argc, char *argv[])
{
    if (argc == 0)
    {
        info_log("No Args");
        return 0;
    }

    for (int i = 1; i < argc; i++)
    {
        if (MikuPan_IsArg(argv[i]))
        {
            if (strncmp(argv[i], "Hello", std::strlen(argv[i])))
            {
                info_log("World");
                break;
            }
        }
    }
    return true;
}