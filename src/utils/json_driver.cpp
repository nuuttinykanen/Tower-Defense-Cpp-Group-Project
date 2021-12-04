#include "json_driver.h"
std::map<int, std::string> indexToFile {
        make_pair(0, "latest_save/test.json"),
        make_pair(1, "level1.json"),
        make_pair(2, "level2.json")
};


void JSON::test() {
    Json::Value root;
    std::ifstream ifs;
    ifs.open("../src/level_files/test.json");
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
    auto levelMap = new LevelMap(width, height);
    levelMap->InitializePath(coords);
    return levelMap;
}
