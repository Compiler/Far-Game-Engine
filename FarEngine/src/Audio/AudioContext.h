#include "../outsourced/FMOD/inc/fmod.h"
#include "../outsourced/FMOD/inc/fmod_common.h"

#include <string>
#include <map>
#include <vector>
#include <math.h>
#include <iostream>

namespace far{
using namespace std;

    struct Implementation {
        Implementation();
        ~Implementation();

        void Update();

        FMOD::Studio::System* mpStudioSystem;
        FMOD::System* mpSystem;

        int mnNextChannelId;

        typedef map<string, FMOD::Sound*> soundMap;
        typedef map<int, FMOD::Channel*> channelMap;
        typedef map<string, FMOD::Studio::EventInstance*> eventMap;
        typedef map<string, FMOD::Studio::Bank*> bankMap;

        BankMap mBanks;
        EventMap mEvents;
        SoundMap mSounds;
        ChannelMap mChannels;
    };


}