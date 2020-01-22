// Copyright 2018 me <me@me.me>
// Created by atrum on 20.01.20.
//

#ifndef INCLUDE_JSON_HPP_
#define INCLUDE_JSON_HPP_

#include <string>
#include <any>

class Json {
private:
    std::any _data;

public:
    explicit Json(const std::string& s);
    bool is_array() const;
    bool is_object() const;
    std::any& operator[](const std::string& key);
    std::any& operator[](int index);
    static Json parse(const std::string& s);
    static Json parseFile(const std::string& path_to_file);
};

#endif // INCLUDE_JSON_HPP_
