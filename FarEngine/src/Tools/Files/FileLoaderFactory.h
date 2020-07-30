#pragma once
#include <string>
#include <fstream>
#include <streambuf>

#define FAR_INTERNAL(x)         "src/Resources/" x
#define FAR_INTERNAL_SHADER(x)  FAR_INTERNAL("Shaders/") x
#define FAR_INTERNAL_TEXTURE(x) FAR_INTERNAL("Textures/") x
#define FAR_INTERNAL_MODEL(x)   FAR_INTERNAL("Models/") x


namespace far {

    namespace FileLoaderFactory{
        extern void loadTextFromFile(const char fileName[], std::string& dst);
        //rgba default composition
        extern unsigned char* loadImage(const char name[], int* width, int* height, int* numOfColChannels, int req_comp = 4/*STBI_rgb_alpha = 4*/);
        extern void free(void* data);
    }
}