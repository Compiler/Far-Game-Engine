#include "TextLoader.h"



void far::loadTextFromFile(const char fileName[], std::string& dst){
    std::ifstream t(fileName);
    std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
    dst = str;
}