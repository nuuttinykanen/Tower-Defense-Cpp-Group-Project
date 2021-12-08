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

    if(!superBomberTexture_.loadFromFile("../src/assets/towers/SuperBomber.png")) {
        std::cout << "Error retrieving super bomber sprite" << std::endl;
        return;
    }

    if(!ultraBomberTexture_.loadFromFile("../src/assets/towers/UltraBomber.png")) {
        std::cout << "Error retrieving ultra bomber sprite" << std::endl;
        return;
    }

    if(!clockerTexture_.loadFromFile("../src/assets/towers/Clocker.png")) {
        std::cout << "Error retrieving clocker sprite" << std::endl;
        return;
    }

    if(!clockBlockerTexture_.loadFromFile("../src/assets/towers/ClockBlocker.png")) {
        std::cout << "Error retrieving clock blockers sprite" << std::endl;
        return;
    }

    if(!seerTexture_.loadFromFile("../src/assets/towers/Seer.png")) {
        std::cout << "Error retrieving seer sprite" << std::endl;
        return;
    }

    if(!motherBrainTexture_.loadFromFile("../src/assets/towers/MotherBrain.png")) {
        std::cout << "Error retrieving mother brain sprite" << std::endl;
        return;
    }

    if(!multigunnerTexture_.loadFromFile("../src/assets/towers/Multigunner.png")) {
        std::cout << "Error retrieving multigunner sprite" << std::endl;
        return;
    }

    if(!gunFiendTexture_.loadFromFile("../src/assets/towers/GunFiend.png")) {
        std::cout << "Error retrieving gun fiend sprite" << std::endl;
        return;
    }

    if(!stereoDudeTexture_.loadFromFile("../src/assets/towers/StereoDude.png")) {
        std::cout << "Error retrieving stereo dude sprite" << std::endl;
        return;
    }

    if(!djDudeTexture_.loadFromFile("../src/assets/towers/DJDude.png")) {
        std::cout << "Error retrieving DJ dude sprite" << std::endl;
        return;
    }

    if(!gunProjecHitTexture_.loadFromFile("../src/assets/projectiles/gunProjecHit.png")) {
        std::cout << "Error retrieving Gun projectile hit sprite" << std::endl;
        return;
    }

    if(!bombProjecHit1Texture_.loadFromFile("../src/assets/projectiles/bombProjecHit1.png")) {
        std::cout << "Error retrieving Bomb projectile hit 1 sprite" << std::endl;
        return;
    }

    if(!bombProjecHit2Texture_.loadFromFile("../src/assets/projectiles/bombProjecHit2.png")) {
        std::cout << "Error retrieving Bomb projectile hit 2 sprite" << std::endl;
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
    superBomberSprite_.setTexture(superBomberTexture_);
    ultraBomberSprite_.setTexture(ultraBomberTexture_);
    clockerSprite_.setTexture(clockerTexture_);
    clockBlockerSprite_.setTexture(clockBlockerTexture_);
    seerSprite_.setTexture(seerTexture_);
    motherBrainSprite_.setTexture(motherBrainTexture_);

    gunnerSprite_.setTexture(gunnerTexture_);
    multigunnerSprite_.setTexture(multigunnerTexture_);
    gunFiendSprite_.setTexture(gunFiendTexture_);

    stereoDudeSprite_.setTexture(stereoDudeTexture_);
    djDudeSprite_.setTexture(djDudeTexture_);


    bombProjecSprite_.setTexture(bombProjecTexture_);
    gunProjecSprite_.setTexture(gunProjecTexture_);

    gunProjecHitSprite_.setTexture(gunProjecHitTexture_);
    bombProjecHit1Sprite_.setTexture(bombProjecHit1Texture_);
    bombProjecHit2Sprite_.setTexture(bombProjecHit2Texture_);
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

sf::Sprite &GlobalObjects::getSuperBomberSprite(float scaledBy) {
    superBomberSprite_.scale(scaledBy, scaledBy);
    return superBomberSprite_;
}

sf::Sprite &GlobalObjects::getUltraBomberSprite(float scaledBy) {
    ultraBomberSprite_.scale(scaledBy, scaledBy);
    return ultraBomberSprite_;
}

sf::Sprite &GlobalObjects::getClockerSprite(float scaledBy) {
    clockerSprite_.scale(scaledBy, scaledBy);
    return clockerSprite_;
}

sf::Sprite &GlobalObjects::getClockBlockerSprite(float scaledBy) {
    clockBlockerSprite_.scale(scaledBy, scaledBy);
    return clockBlockerSprite_;
}

sf::Sprite &GlobalObjects::getSeerSprite(float scaledBy) {
    seerSprite_.scale(scaledBy, scaledBy);
    return seerSprite_;
}

sf::Sprite &GlobalObjects::getMultigunnerSprite(float scaledBy) {
    multigunnerSprite_.scale(scaledBy, scaledBy);
    return multigunnerSprite_;
}

sf::Sprite &GlobalObjects::getMotherBrainSprite(float scaledBy) {
    motherBrainSprite_.scale(scaledBy, scaledBy);
    return motherBrainSprite_;
}

sf::Sprite &GlobalObjects::getGunFiendSprite(float scaledBy) {
    gunFiendSprite_.scale(scaledBy, scaledBy);
    return gunFiendSprite_;
}

sf::Sprite &GlobalObjects::getStereoDudeSprite(float scaledBy) {
    stereoDudeSprite_.scale(scaledBy, scaledBy);
    return stereoDudeSprite_;
}

sf::Sprite &GlobalObjects::getDJDudeSprite(float scaledBy) {
    djDudeSprite_.scale(scaledBy, scaledBy);
    return djDudeSprite_;
}

sf::Sprite &GlobalObjects::getGunProjecHitSprite(float scaledBy) {
    gunProjecHitSprite_.scale(scaledBy, scaledBy);
    return gunProjecHitSprite_;
}

sf::Sprite &GlobalObjects::getBombProjecHit1Sprite(float scaledBy) {
    bombProjecHit1Sprite_.scale(scaledBy, scaledBy);
    return bombProjecHit1Sprite_;
}

sf::Sprite &GlobalObjects::getBombProjecHit2Sprite(float scaledBy) {
    bombProjecHit2Sprite_.scale(scaledBy, scaledBy);
    return bombProjecHit2Sprite_;
}


