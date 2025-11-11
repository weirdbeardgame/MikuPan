#ifndef MIKUPAN_TEXTURE_MANAGER_C_H
#define MIKUPAN_TEXTURE_MANAGER_C_H

void AddTexture(unsigned long long tbp0, unsigned char* img);
void AddSDLTexture(unsigned long long tbp0, void* img);
unsigned char* GetTexture(unsigned long long tbp0);
void* GetSDLTexture(unsigned long long tbp0);
void FirstUploadDone();
bool IsFirstUploadDone();

#endif //MIKUPAN_TEXTURE_MANAGER_C_H