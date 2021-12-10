#ifndef TOWER_DEFENSE_12_SOUND_DRIVER_H
#define TOWER_DEFENSE_12_SOUND_DRIVER_H


#include "map"
#include "utility"
#include "SFML/Audio.hpp"
#include "iostream"
using std::make_pair;
/*
 * How to add sounds:
 * 1. Add the effect name to the enumerator
 * 2. Add the .wav file in the sound_files folder
 * 3. Add the filename to the initiateSounds() map
 * 4. Call the sound effect by gui_->getSoundDriver()->playSound(enum name)
 */




enum SoundEffects {Hitmarker, VictorySound, SelectSound};




class SoundDriver {
public:
    SoundDriver();
    void playSound(SoundEffects effect, int volume = 100);
    void initiateSounds();


private:
    std::map<SoundEffects, std::string> effectToFile_;
    std::map<SoundEffects, sf::SoundBuffer> effectToBuffer_;
    std::map<SoundEffects, sf::Sound> effectToSound_;
};




#endif //TOWER_DEFENSE_12_SOUND_DRIVER_H
