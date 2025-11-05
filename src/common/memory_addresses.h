#ifndef MIKUPAN_MEMORY_ADDRESSES_H
#define MIKUPAN_MEMORY_ADDRESSES_H

//#define FontTextAddress     0x01e30000
extern void* FontTextAddress; /// PK2 font texture pack

// #define ImgHdAddress        0x012f0000
extern void* ImgHdAddress; /// IMG_HD.BIN

// #define IG_MSG_OBJ_ADDRESS  0x0084a000
extern void* IG_MSG_OBJ_ADDRESS; ///

// #define EFFECT_ADDRESS      0x01e90000
extern void* EFFECT_ADDRESS; ///

// #define PBUF_ADDRESS        0x00720000
extern void* PBUF_ADDRESS; /// Packet buffer

#define VNBufferAddress     0x00420000
#define CachedBuffer        0x20000000
#define UnCachedBuffer      0x30000000
#define VU0_ADDRESS         0x11000000



#endif //MIKUPAN_MEMORY_ADDRESSES_H