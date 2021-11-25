#include "GlobalObjects.h"

GlobalObjects::GlobalObjects() {
    // Relative path from the cmake executable
    if (!font_.loadFromFile("../src/assets/AtariClassicChunky-PxXP.ttf")) {
        //Error
        std::cout << "Error retrieving font file" << std::endl;
        return;
    }
}