

#include "json_driver.h"

// Maps each map index to a save file name
std::map<int, std::string> indexToFile {
        make_pair(0, "latest_save/save.json"),
        make_pair(1, "level1.json"),
        make_pair(2, "level2.json"),
        make_pair(3, "level3.json"),
        make_pair(4, "level4.json"),
        make_pair(5, "level5.json")
};

// Map enemies to an enum number
enum Enemies {
    ZombieType, ZombieHordeType, MichaelMyersType, DraculaType, BatType
};

void JSON::test() {
    Json::Value root;
    std::ifstream ifs;
    ifs.open("../src/level_files/save.json");
    Json::CharReaderBuilder builder;

    JSONCPP_STRING errs;
    if (!parseFromStream(builder, ifs, &root, &errs)) {
        std::cout << errs << std::endl;
        Json::throwRuntimeError("Couldn't parse json");
    }
    std::cout << root["hello"] << std::endl;
}

LevelMap* JSON::loadLevelMap(int index) {
    auto fileName = indexToFile[index];
    Json::Value root;
    std::ifstream ifs;
    ifs.open("../src/level_files/" + fileName);

    Json::CharReaderBuilder builder;

    JSONCPP_STRING errs;
    if (!parseFromStream(builder, ifs, &root, &errs)) {
        std::cout << errs << std::endl;
        Json::throwRuntimeError("Couldn't parse json");
    }
    auto path = root["enemy_path"];
    if (!path.isArray()) {
        std::cout << "Couldn't find enemy path in level file" << std::endl;
        Json::throwRuntimeError("Couldn't parse enemy path");
    }
    auto width = root["width"].asInt();
    auto height = root["height"].asInt();

    auto coords = std::vector<pair<pair<int, int>, pair<int, int>>>();
    auto pairs = std::vector<pair<int, int>>();
    for (auto e : path) {
        auto x = e["x"];
        auto y = e["y"];
        auto p = make_pair(x.asInt(), y.asInt());
        pairs.push_back(p);
    }
    for (int i = 0; i < pairs.size() - 1; i++) {
        coords.emplace_back(pairs[i], pairs[i + 1]);
    }
    auto levelMap = new LevelMap(width, height, index);
    levelMap->InitializePath(coords);
    return levelMap;
}

std::vector<Wave*> JSON::loadWaves(int index) {
    auto fileName = indexToFile[index];
    Json::Value root;
    std::ifstream ifs;
    ifs.open("../src/level_files/" + fileName);

    Json::CharReaderBuilder builder;

    JSONCPP_STRING errs;
    if (!parseFromStream(builder, ifs, &root, &errs)) {
        std::cout << errs << std::endl;
        Json::throwRuntimeError("Couldn't parse json");
    }
    auto waves = root["waves"];
    if (!waves.isArray()) {
        std::cout << "Couldn't find enemy waves in level file" << std::endl;
        Json::throwRuntimeError("Couldn't parse enemy waves");
    }
    auto newWaves = std::vector<Wave*>();

    for (auto wave: waves ) {
        auto enemies = std::vector<Enemy*>();

        for (auto enemy: wave) {
            auto e = static_cast<Enemies>(enemy.asInt());
            switch (e) {
                case ZombieType:
                    enemies.push_back(new Zombie());
                    break;
                case ZombieHordeType:
                    enemies.push_back(new ZombieHorde());
                    break;
                case MichaelMyersType:
                    enemies.push_back(new MichaelMyers());
                    break;
                case DraculaType:
                    enemies.push_back(new Dracula());
                    break;
                case BatType:
                    enemies.push_back(new Bat());
                    break;
            }
            std::reverse(enemies.begin(), enemies.end());
            newWaves.push_back(new Wave(enemies));
        }
    }
    std::reverse(newWaves.begin(), newWaves.end());

    ifs.close();

    return newWaves;
}


int JSON::getNumberOfLevels() {
    return indexToFile.size() - 1;
}

void JSON::saveCurrentGame(Game* game, int levelNumber) {
    auto fileName = indexToFile[0];
    Json::Value root;
    std::ofstream ofs;
    ofs.open("../src/level_files/" + fileName);

    Json::StyledWriter styledWriter;

    JSONCPP_STRING errs;

    root["index"] = levelNumber;
    root["health"] = game->GetPlayer().GetHealth();
    root["money"] = game->GetPlayer().GetMoney();

    // Save towers and their positions
    auto towerSquares = game->GetMap().GetTowerSquares();
    Json::Value vec(Json::arrayValue);

    for (auto it : towerSquares) {
        Json::Value newTower;
        auto tower = it.second->GetTower();

        newTower["id"] = tower->getType();
        newTower["x"] = it.first.first;
        newTower["y"] = it.first.second;

        vec.append(newTower);
    }
    root["towers"] = vec;

    root["current_wave"] = game->GetWaveNumber();


    ofs << styledWriter.write(root);
    ofs.close();
}

Game* JSON::loadLatestSave() {
    auto fileName = indexToFile[0];
    Json::Value root;
    std::ifstream ifs;
    ifs.open("../src/level_files/" + fileName);

    Json::CharReaderBuilder builder;

    JSONCPP_STRING errs;
    if (!parseFromStream(builder, ifs, &root, &errs)) {
        std::cout << errs << std::endl;
        Json::throwRuntimeError("Couldn't parse json");
    }

    int levelIndex = root["index"].asInt();
    int currentWave = root["current_wave"].asInt();
    int playerHealth = root["health"].asInt();
    float playerMoney = root["money"].asFloat();

    auto lvlMap = loadLevelMap(levelIndex);
    auto waves = loadWaves(levelIndex);


    auto player = new Player(100);
    player->SetMoney(playerMoney);
    player->SetHealth(playerHealth);

    auto game = new Game(*lvlMap, *player, waves);
    game->SetWaveNumber(currentWave);


    // load the placed towers
    for (auto tower : root["towers"]) {
        int x = tower["x"].asInt();
        int y = tower["y"].asInt();
        auto towerType = static_cast<TowerTypes>(tower["id"].asInt());
        Tower* newTower = nullptr;

        switch (towerType) {
            case GunnerType:
                newTower = new Gunner();
                break;
            case MultiGunnerType:
                newTower = new Multigunner();
                break;
            case GunFiendType:
                newTower = new GunFiend();
                break;
            case BomberType:
                newTower = new Bomber();
                break;
            case SuperBomberType:
                newTower = new SuperBomber();
                break;
            case UltraBomberType:
                newTower = new UltraBomber();
                break;
            case Attack3:
                // TODO: Add new attack tower
                newTower = new Gunner();
                break;
            case Attack4:
                // TODO: Add new attack tower
                newTower = new Gunner();
                break;
            case ClockerType:
                newTower = new Clocker();
                break;
            case ClockerBlockerType:
                newTower = new ClockBlocker();
                break;
            case SeerType:
                newTower = new Seer();
                break;
            case MotherBrainType:
                newTower = new MotherBrain();
                break;
            case StereoType:
                newTower = new StereoDude();
                break;
            case DJDudeType:
                newTower = new DJDude();
                break;
            case Support4:
                // TODO: Add new support tower
                newTower = new Clocker();
                break;
            default:
                Json::throwLogicError("Unknown tower id");
        }
        lvlMap->PlaceTower(x, y, newTower);
    }




    ifs.close();

    return game;
}