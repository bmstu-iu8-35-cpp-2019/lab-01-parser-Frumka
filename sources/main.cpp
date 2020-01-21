// Copyright 2018 me <me@me.me>

#include <string>
#include <iostream>
#include <exception>
#include <iomanip>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
    json input_json = { { "Si-9.15", "RTS-9.15", "GAZP-9.15" },
                  { 100024, 100027, 100050 },
                  { "Futures contract for USD/RUB",
                               "Futures contract for index RTS",
                               "Futures contract for Gazprom shares" }
    };
    json result;
    size_t i = 0;
    for (size_t index = 0; (index < input_json.size() - 1); index++) {
        if (input_json[i].size() != input_json[i + 1].size()) {
            throw std::logic_error("sizes does not match");
        }
    }

    while (i < input_json.size()) {
        result[i]["ticker"] = input_json[0][i];
        result[i]["id"] = input_json[1][i];
        result[i]["description"] = input_json[2][i];
        i++;
    }

    std::cout <<std::setw(4) << result << std::endl;

    return 0;
}
