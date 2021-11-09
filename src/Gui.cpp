
#include "Gui.h"

Gui::Gui(int width, int height)
    : screen_width_(width), screen_height_(height){
    start_main_window();
}

void Gui::start_main_window() const {
    sf::RenderWindow window(sf::VideoMode(screen_width_, screen_height_), "Hello world!");

    sf::CircleShape shape(100.f);

    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
}
