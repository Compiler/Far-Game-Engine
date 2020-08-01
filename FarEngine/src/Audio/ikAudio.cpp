#include "ikAudio.h"



far::ikAudio::ikAudio(){  engine = irrklang::createIrrKlangDevice(); }

void far::ikAudio::playSound(const char* name){
     engine->play2D(name,true);
}