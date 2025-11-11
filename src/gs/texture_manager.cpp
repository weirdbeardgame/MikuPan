#include "texture_manager.h"

std::unordered_map<unsigned long long, unsigned char*> texture_atlas;
std::unordered_map<unsigned long long, void*> sdl_texture_atlas;
bool first_upload_done = false;

void AddTexture(unsigned long long tbp0, unsigned char *img)
{
    texture_atlas[tbp0] = img;
}

unsigned char * GetTexture(unsigned long long tbp0)
{
    if (!first_upload_done)
    {
        return nullptr;
    }

    if (auto el = texture_atlas.find(tbp0); el != texture_atlas.end())
    {
        return texture_atlas[tbp0];
    }

    return nullptr;
}

void FirstUploadDone()
{
    first_upload_done = true;
}

bool IsFirstUploadDone()
{
    return first_upload_done;
}

void AddSDLTexture(unsigned long long tbp0, void *img)
{
    sdl_texture_atlas[tbp0] = img;
}

void * GetSDLTexture(unsigned long long tbp0)
{
    if (!first_upload_done)
    {
        return nullptr;
    }

    if (auto el = sdl_texture_atlas.find(tbp0); el != sdl_texture_atlas.end())
    {
        return sdl_texture_atlas[tbp0];
    }

    return nullptr;
}