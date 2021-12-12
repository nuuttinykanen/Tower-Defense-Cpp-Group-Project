#ifndef TOWER_DEFENSE_12_GUI_H
#define TOWER_DEFENSE_12_GUI_H

#include <SFML/Graphics.hpp>
#include "gui_elements/GlobalObjects.h"
#include "utils/sound_driver.h"


class WindowState;
class MenuState;





class Gui {
public:
    Gui(int width, int height);

    void StartMainLoop();

    void ChangeGameState(WindowState* new_state);


    GlobalObjects* GetGlobalObjects() { return global_objects_; };
    SoundDriver* GetSoundDriver() { return sound_; }

private:
    sf::RenderWindow window_;
    WindowState* current_state_;
    GlobalObjects* global_objects_;
    SoundDriver* sound_;


    int screen_width_;
    int screen_height_;
};

#endif //TOWER_DEFENSE_12_GUI_H