#ifndef MIKUPAN_TEXTURE_MANAGER_H
#define MIKUPAN_TEXTURE_MANAGER_H
#include <unordered_map>

extern std::unordered_map<unsigned long long, unsigned char*> texture_atlas;
extern std::unordered_map<unsigned long long, void*> sdl_texture_atlas;
extern bool first_upload_done;

extern "C"
{
    void AddTexture(unsigned long long tbp0, unsigned char* img);
    void AddSDLTexture(unsigned long long tbp0, void* img);
    unsigned char* GetTexture(unsigned long long tbp0);
    void* GetSDLTexture(unsigned long long tbp0);
    void FirstUploadDone();
    bool IsFirstUploadDone();
}


#endif //MIKUPAN_TEXTURE_MANAGER_H