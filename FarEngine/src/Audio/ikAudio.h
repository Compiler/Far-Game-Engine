#pragma once
#include <Audio/AudioContext.h>
#include <Tools/Files/FileLoaderFactory.h>
#include "../outsourced/irrKlang/include/irrKlang.h"
#pragma comment(lib, "irrKlang.lib")

namespace far{


    class ikAudio : public far::AudioContext{
        private:
            irrklang::ISoundEngine* engine;


        public:

            ikAudio();

            void playSound(const char* name)override;
    };


}