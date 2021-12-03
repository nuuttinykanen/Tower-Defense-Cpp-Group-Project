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

    if(!hordeTexture_.loadFromFile("../src/assets/enemies/Horde.png")) {
        std::cout << "Error retrieving Horde sprite" << std::endl;
        return;
    }

    if(!zombieTexture_.loadFromFile("../src/assets/enemies/Zombie.png")) {
        std::cout << "Error retrieving Zombie sprite" << std::endl;
        return;
    }
    if(!draculaTexture_.loadFromFile("../src/assets/enemies/Dracula.png")) {
        std::cout << "Error retrieving Dracula sprite" << std::endl;
        return;
    }
    if(!michaelTexture_.loadFromFile("../src/assets/enemies/Michael.png")) {
        std::cout << "Error retrieving Michael sprite" << std::endl;
        return;
    }
    if(!batTexture_.loadFromFile("../src/assets/enemies/Bat.png")) {
        std::cout << "Error retrieving Bat sprite" << std::endl;
        return;
    }

    if(!projectileTexture_.loadFromFile("../src/assets/projectiles/ProjectileSprite.png")) {
        std::cout << "Error retrieving projectile sprite" << std::endl;
        return;
    }

    enemySprite_.setTexture(enemyTexture_);
    purpleEnemySprite_.setTexture(purpleEnemyTexture_);
    freeSquareSprite_.setTexture(freeSquareTexture_);
    enemySquareSprite_.setTexture(enemySquareTexture_);
    towerSquareSprite_.setTexture(towerSquareTexture_);
    hordeSprite_.setTexture(hordeTexture_);
    zombieSprite_.setTexture(zombieTexture_);
    draculaSprite_.setTexture(draculaTexture_);
    batSprite_.setTexture(batTexture_);
    michaelSprite_.setTexture(michaelTexture_);
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

sf::Sprite &GlobalObjects::getDraculaSprite(float scaledBy) {
    draculaSprite_.scale(scaledBy, scaledBy);
    return  draculaSprite_;
}
sf::Sprite &GlobalObjects::getZombieSprite(float scaledBy) {
    zombieSprite_.scale(scaledBy, scaledBy);
    return  zombieSprite_;
}
sf::Sprite &GlobalObjects::getHordeSprite(float scaledBy) {
    hordeSprite_.scale(scaledBy, scaledBy);
    return  hordeSprite_;
}
sf::Sprite &GlobalObjects::getBatSprite(float scaledBy) {
    batSprite_.scale(scaledBy, scaledBy);
    return  batSprite_;
}

sf::Sprite &GlobalObjects::getMichaelSprite(float scaledBy) {
    michaelSprite_.scale(scaledBy, scaledBy);
    return  michaelSprite_;
}

sf::Sprite &GlobalObjects::getProjectileSprite(float scaledBy) {
    projectileSprite_.scale(scaledBy, scaledBy);
    return  projectileSprite_;
}



