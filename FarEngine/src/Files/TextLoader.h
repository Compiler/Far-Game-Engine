#pragma once
#include <string>
#include <fstream>
#include <streambuf>

//#pragma warning (disable : 4996)
namespace far {

	void loadTextFromFile(const char fileName[], std::string& dst){

		std::ifstream t(fileName);
        std::string str((std::istreambuf_iterator<char>(t)), std::istreambuf_iterator<char>());
        dst = str;
    }

}