#include "sifrpc.h"

//#include <stdlib.h>

void sceSifInitRpc(unsigned int mode)
{
}

int sceSifBindRpc(sceSifClientData* client, unsigned int rpc_number, unsigned int mode)
{
    /// Returns success otherwise program will loop forever
    client->serve = malloc(sizeof(struct _sif_serve_data));
    return 1;
}

int sceSifCheckStatRpc(sceSifRpcData* cd)
{
    /// Returns 0 to avoid program looping forever
    return 0;
}

int sceSifCallRpc(sceSifClientData* client, unsigned int rpc_number, unsigned int mode, void* send, int ssize,
    void* receive, int rsize, sceSifEndFunc end_function, void* end_param)
{
    return 1;
}
