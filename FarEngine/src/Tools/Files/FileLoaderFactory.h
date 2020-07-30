#pragma once
#include <string>
#include <fstream>
#include <streambuf>

#define FAR_INTERNAL(x)         "src/resources/" x
#define FAR_INTERNAL_SHADER(x)  FAR_INTERNAL("shaders/") x
#define FAR_INTERNAL_TEXTURE(x) FAR_INTERNAL("textures/") x
#define FAR_INTERNAL_MODEL(x)   FAR_INTERNAL("models/") x


namespace far {

    namespace FileLoaderFactory{
        extern void loadTextFromFile(const char fileName[], std::string& dst);
        //rgba default composition
        extern unsigned char* loadImage(const char name[], int* width, int* height, int* numOfColChannels, int req_comp = 4/*STBI_rgb_alpha = 4*/);
        extern void free(void* data);
    }
}