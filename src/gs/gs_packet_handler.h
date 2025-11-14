#ifndef MIKUPAN_GS_PACKET_HANDLER_H
#define MIKUPAN_GS_PACKET_HANDLER_H
#include "typedefs.h"

void ImageLoadPacket(Q_WORDDATA *packet);
void ReadPacket(Q_WORDDATA *packet);
void ReadAllPackets(Q_WORDDATA *packets);

#endif //MIKUPAN_GS_PACKET_HANDLER_H