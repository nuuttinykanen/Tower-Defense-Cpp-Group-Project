#include "json_driver.h"

void JSON::test() {
    Json::Value root;
    std::ifstream ifs;
    ifs.open("../src/level_files/test.json");
    Json::CharReaderBuilder builder;

    JSONCPP_STRING errs;
    if (!parseFromStream(builder, ifs, &root, &errs)) {
        std::cout << errs << std::endl;
        return;
    }
    std::cout << root["hello"] << std::endl;
}
