#include "GlobalObjects.h"

GlobalObjects::GlobalObjects() {
    // Relative path from the cmake executable
    if (!font_.loadFromFile("../src/assets/AtariClassicChunky-PxXP.ttf")) {
        //Error
        std::cout << "Error retrieving font file" << std::endl;
        return;
    }

    if (!enemyTexture_.loadFromFile("../src/assets/enemies/EnemySprite.png")) {
        std::cout << "Error retrieving enemy sprite" << std::endl;
        return;
    }
    if (!purpleEnemyTexture_.loadFromFile("../src/assets/enemies/PurpleEnemy.png")) {
        std::cout << "Error retrieving purple enemy sprite" << std::endl;
        return;
    }
    if(!freeSquareTexture_.loadFromFile("../src/assets/squares/freeSquareSprite.png")) {
        std::cout << "Error retrieving free square sprite" << std::endl;
        return;
    }
    if(!enemySquareTexture_.loadFromFile("../src/assets/squares/EnemySquareSprite.png")) {
        std::cout << "Error retrieving enemy square sprite" << std::endl;
        return;
    }

    if(!towerSquareTexture_.loadFromFile("../src/assets/squares/TowerSquareSprite.png")) {
        std::cout << "Error retrieving tower square sprite" << std::endl;
        return;
    }

    enemySprite_.setTexture(enemyTexture_);
    purpleEnemySprite_.setTexture(purpleEnemyTexture_);
    freeSquareSprite_.setTexture(freeSquareTexture_);
    enemySquareSprite_.setTexture(enemySquareTexture_);
    towerSquareSprite_.setTexture(towerSquareTexture_);
}


sf::Sprite &GlobalObjects::getEnemySprite(float scaledBy) {
    enemySprite_.scale(scaledBy, scaledBy);
    return enemySprite_;
}

sf::Sprite &GlobalObjects::getPurpleEnemySprite(float scaledBy) {
    purpleEnemySprite_.scale(scaledBy, scaledBy);
    return purpleEnemySprite_;
}

sf::Sprite &GlobalObjects::getFreeSquareSprite(float scaledBy) {
    freeSquareSprite_.scale(scaledBy, scaledBy);
    return  freeSquareSprite_;
}

sf::Sprite &GlobalObjects::getEnemySquareSprite(float scaledBy) {
    enemySquareSprite_.scale(scaledBy, scaledBy);
    return  enemySquareSprite_;
}

sf::Sprite &GlobalObjects::getTowerSquareSprite(float scaledBy) {
    towerSquareSprite_.scale(scaledBy, scaledBy);
    return  towerSquareSprite_;
}


