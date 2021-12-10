
#include "sound_driver.h"



void SoundDriver::initiateSounds() {
    // Maps each map sound effect to a file name
    // Note, only .wav or .ogg supported!
    effectToFile_[Hitmarker] = "hitmarker.wav";
    effectToFile_[VictorySound] = "victory_sound.wav";


    for (const auto& e : effectToFile_) {
        sf::SoundBuffer newSoundBuffer;
        if (!newSoundBuffer.loadFromFile("../src/assets/sound_files/" + e.second)) {
            std::cout << "Error in opening sound file" + e.second << std::endl;
            return;
        }
        effectToBuffer_[e.first] = newSoundBuffer;
    }
    for (const auto& b : effectToBuffer_) {
        sf::Sound newSound;
        newSound.setBuffer(b.second);
        effectToSound_[b.first] = newSound;
    }
}

void SoundDriver::playSound(SoundEffects effect, int volume) {
    auto& e = effectToSound_[effect];
    e.setVolume(volume);
    e.play();
}

SoundDriver::SoundDriver() {
    initiateSounds();
}
