// Copyright 2019 TurboFen <TurboFenix@yandex.ru>

#include <gtest/gtest.h>

#include "Json.hpp"

TEST(Json, Init) {
    std::string test_from_task_string =
            "{\n"
            "\"lastname\" : \"Ivanov\",\n"
            "\"firstname\" : \"Ivan\",\n"
            "\"age\" : 25,\n"
            "\"islegal\" : false,\n"
            "\"marks\" : [\n"
            "\t 4, 5, 5, 5, 2, 3\n"
            "],\n"
            "\"address\" : {\n"
            "\"city\" : \"Moscow\",\n"
            "\"street\" : \"Vozdvijenka\"\n"
            "}\n"
            "}";

    Json object = Json::parse(test_from_task_string);

    EXPECT_EQ(std::any_cast<std::string>(object["lastname"]), "Ivanov");
    EXPECT_EQ(std::any_cast<bool>(object["islegal"]), false);
    EXPECT_EQ(std::any_cast<int>(object["age"]), 25);

    auto marks = std::any_cast<Json>(object["marks"]);
    EXPECT_EQ(std::any_cast<int>(marks[0]), 4);
    EXPECT_EQ(std::any_cast<int>(marks[1]), 5);

    auto address = std::any_cast<Json>(object["address"]);
    EXPECT_EQ(std::any_cast<std::string>(address["city"]), "Moscow");
    EXPECT_EQ(std::any_cast<std::string>(address["street"]), "Vozdvijenka");
}