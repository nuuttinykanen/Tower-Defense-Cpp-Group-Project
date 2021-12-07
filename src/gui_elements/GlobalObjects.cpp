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

    if(!rangeTexture_.loadFromFile("../src/assets/squares/RangeSprite.png")) {
        std::cout << "Error retrieving range sprite" << std::endl;
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

    if(!bomberTexture_.loadFromFile("../src/assets/towers/Bomber.png")) {
        std::cout << "Error retrieving bomber sprite" << std::endl;
        return;
    }

    if(!gunnerTexture_.loadFromFile("../src/assets/towers/Gunner.png")) {
        std::cout << "Error retrieving gunner sprite" << std::endl;
        return;
    }

    if(!bombProjecTexture_.loadFromFile("../src/assets/projectiles/bombProjec.png")) {
        std::cout << "Error retrieving bomb projectile sprite" << std::endl;
        return;
    }

    if(!gunProjecTexture_.loadFromFile("../src/assets/projectiles/gunProjec.png")) {
        std::cout << "Error retrieving gun projectile sprite" << std::endl;
        return;
    }

    enemySprite_.setTexture(enemyTexture_);
    purpleEnemySprite_.setTexture(purpleEnemyTexture_);
    freeSquareSprite_.setTexture(freeSquareTexture_);
    enemySquareSprite_.setTexture(enemySquareTexture_);
    towerSquareSprite_.setTexture(towerSquareTexture_);
    rangeSprite_.setTexture(rangeTexture_);
    hordeSprite_.setTexture(hordeTexture_);
    zombieSprite_.setTexture(zombieTexture_);
    draculaSprite_.setTexture(draculaTexture_);
    batSprite_.setTexture(batTexture_);
    michaelSprite_.setTexture(michaelTexture_);
    bomberSprite_.setTexture(bomberTexture_);
    gunnerSprite_.setTexture(gunnerTexture_);
    bombProjecSprite_.setTexture(bombProjecTexture_);
    gunProjecSprite_.setTexture(gunProjecTexture_);
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

sf::Sprite &GlobalObjects::getRangeSprite(float scaledBy) {
    rangeSprite_.scale(scaledBy, scaledBy);
    return  rangeSprite_;
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

sf::Sprite &GlobalObjects::getBomberSprite(float scaledBy) {
    bomberSprite_.scale(scaledBy, scaledBy);
    return bomberSprite_;
}

sf::Sprite &GlobalObjects::getGunnerSprite(float scaledBy) {
    gunnerSprite_.scale(scaledBy, scaledBy);
    return gunnerSprite_;
}

sf::Sprite &GlobalObjects::getBombProjecSprite(float scaledBy) {
    bombProjecSprite_.scale(scaledBy, scaledBy);
    return bombProjecSprite_;
}

sf::Sprite &GlobalObjects::getGunProjecSprite(float scaledBy) {
    gunProjecSprite_.scale(scaledBy, scaledBy);
    return gunProjecSprite_;
}


