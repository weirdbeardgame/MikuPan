#ifndef MIKUPAN_FILE_LOADING_H
#define MIKUPAN_FILE_LOADING_H
#include <cstdint>

extern "C" unsigned char* LoadImgHdFile();
extern "C" unsigned char *ReadFullFile(const char *filename);
extern "C" void ReadFileInArchive(int sector, int size, int64_t address);

#endif //MIKUPAN_FILE_LOADING_H