#include "file_loading.h"
#include <filesystem>
#include <fstream>
#include <string.h>

unsigned char* LoadImgHdFile()
{
    return ReadFullFile("./IMG_HD.BIN");
}

unsigned char *ReadFullFile(const char *filename)
{
    if (!std::filesystem::exists(filename))
    {
        return NULL;
    }

    auto fileSize = std::filesystem::file_size(filename);

    char *buffer = new char[fileSize];
    std::ifstream infile(filename, std::ios::binary);
    infile.read(buffer, fileSize);

    infile.close();

    return (unsigned char*)buffer;
}

void ReadFileInArchive(int sector, int size, int64_t address)
{
    if (!std::filesystem::exists("./IMG_BD.BIN"))
    {
        return;
    }

    std::ifstream infile("./IMG_BD.BIN", std::ios::binary);
    infile.seekg(sector * 0x800, std::ios::beg);
    infile.read((char*)address, size);

    infile.close();
}
