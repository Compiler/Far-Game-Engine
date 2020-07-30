#pragma once
#include <string>
#include <fstream>
#include <streambuf>

#define FAR_INTERNAL(x)         "src/resources/" x
#define FAR_INTERNAL_SHADER(x)  far_INTERNAL("shaders/") x
#define FAR_INTERNAL_TEXTURE(x) far_INTERNAL("textures/") x
#define FAR_INTERNAL_MODEL(x)   far_INTERNAL("models/") x


namespace far {

    void loadTextFromFile(const char fileName[], std::string& dst);
    //rgba default composition
    unsigned char* loadImage(const char name[], int* width, int* height, int* numOfColChannels, int req_comp = 4/*STBI_rgb_alpha = 4*/);
    void free(void* data);
}