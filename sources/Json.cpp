// Copyright 2018 me <me@me.me>

#include <Json.hpp>

#include <exception>
#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <string>

Json::Json(const std::string &s) {
    size_t i = 0;

    while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n') {
        i++;
    }

    if (s[i] != '{' && s[i] != '[')
        throw std::logic_error("not json object");

    if (s[i] == '{') {
        std::map<std::string, std::any> content;
        while (s[i] != '}') {
            i++;
            while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == ',') {
                i++;
            }
            if (s[i] == '}')
                break;

            std::string key = "";
            if (s[i] == '"') {
                i++;
                while (s[i] != '"') {
                    key += s[i];
                    i++;
                }
            }
            i++;
            while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n') {
                i++;
            }
            if (s[i] == ':')
                i++;

            std::any script;

            while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n') {
                i++;
            }
            if (s[i] == '"') {
                i++;
                std::string value = "";
                while (s[i] != '"') {
                    value += s[i];
                    i++;
                }
                script = value;
            }
            if (s[i] == 't') {
                std::string check = "";
                size_t k = 0;
                while (k != 4) {
                    check += s[i];
                    k++;
                    i++;
                }
                if (check == "true")
                    script = true;
            }
            if (s[i] == 'f') {
                std::string check = "";
                size_t k = 0;
                while (k != 5) {
                    check += s[i];
                    k++;
                    i++;
                }
                if (check == "false")
                    script = false;
            }
            if (s[i] == 'n') {
                std::string check = "";
                size_t k = 0;
                while (k != 4) {
                    check += s[i];
                    k++;
                    i++;
                }
                if (check == "null")
                    script = NULL;
            }
            if ((s[i] >= '0' && s[i] <= '9') || s[i] == '-') {
                bool flag = false;
                std::string check = "";
                while ((s[i] >= '0' && s[i] <= '9') || s[i] == '.') {
                    if (s[i] == '.') { flag = true; }
                    check += s[i];
                    i++;
                }
                if (flag )
                    script = std::atof(check.c_str());

                script = std::atoi(check.c_str());
            }
            if (s[i] == '[') {
                std::string check;
                size_t prov = 1;
                while (prov > 0) {
                    check += s[i];
                    if (s[i + prov] == '[')
                        prov++;

                    if (s[i] == ']')
                        prov--;

                    i++;
                }
                script = Json(check);
            }
            if (s[i] == '{') {
                std::string check;
                size_t prov = 1;
                while (prov > 0) {
                    check += s[i];
                    if (s[i + prov] == '{')
                        prov++;

                    if (s[i] == '}')
                        prov--;

                    i++;
                }
                script = Json(check);
            }
            content.insert(std::make_pair(key, script));
        }
        _data = content;
    } else if (s[i] == '[') {
        std::vector<std::any> scripts_vector;
        while (s[i] != ']') {
            std::any script;
            i++;
            while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n' || s[i] == ',') {
                i++;
            }
            if (s[i] == ']')
                break;

            if (s[i] == '"') {
                i++;
                std::string value = "";
                while (s[i] != '"') {
                    value += s[i];
                    i++;
                }
                script = value;
            }
            if (s[i] == 't') {
                std::string check = "";
                size_t k = 0;
                while (k != 4) {
                    check += s[i];
                    k++;
                    i++;
                }
                if (check == "true")
                    script = true;
            }
            if (s[i] == 'f') {
                std::string check = "";
                size_t k = 0;
                while (k != 5) {
                    check += s[i];
                    k++;
                    i++;
                }
                if (check == "false")
                    script = false;
            }
            if (s[i] == 'n') {
                std::string check = "";
                size_t k = 0;
                while (k != 4) {
                    check += s[i];
                    k++;
                    i++;
                }
                if (check == "null") { script = NULL; }
            }
            if ((s[i] >= '0' && s[i] <= '9') || s[i] == '-') {
                bool flag = false;
                std::string check = "";
                while ((s[i] >= '0' && s[i] <= '9') || s[i] == '.') {
                    if (s[i] == '.') { flag = true; }
                    check += s[i];
                    i++;
                }
                if (flag == true)
                    script = std::atof(check.c_str());

                script = std::atoi(check.c_str());
            }
            if (s[i] == '[') {
                std::string check;
                size_t prov = 1;
                while (prov > 0) {
                    check += s[i];
                    if (s[i + prov] == '[')
                        prov++;

                    if (s[i] == ']')
                        prov--;

                    i++;
                }
                script = Json(check);
            }
            if (s[i] == '{') {
                std::string check;
                size_t advance_right = 1;
                while (advance_right > 0) {
                    check += s[i];
                    if (s[i + advance_right] == '{')
                        advance_right++;

                    if (s[i] == '}')
                        advance_right--;

                    i++;
                }
                script = Json(check);
            }
            scripts_vector.push_back(script);
        }
        _data = scripts_vector;
    }
}

bool Json::is_array() const {
    if (_data.type() == typeid(std::vector<std::any>))
        return true;

    return false;
}

bool Json::is_object() const {
    if (_data.type() == typeid(std::map<std::string, std::any>))
        return true;

    return false;
}

std::any &Json::operator[](const std::string &key) {
    if (!is_object()) {
        throw std::invalid_argument("not an object");
    } else {
        return std::any_cast<std::map<std::string, std::any> &>(_data)[key];
    }
}

std::any &Json::operator[](int index) {
    if (!is_array()) {
        throw std::invalid_argument("not an object");
    } else {
        return std::any_cast<std::vector<std::any> &>(_data)[index];
    }
}

Json Json::parse(const std::string &s) {
    return Json(s);
}

Json Json::parseFile(const std::string &path_to_file) {
    std::string result;

    std::ifstream write_stream(path_to_file);

    if (!write_stream)
        throw std::invalid_argument("given path does not lead to a file");

    while (write_stream) {
        std::string value;
        std::getline(write_stream, value);
        result += value;
    }

    write_stream.close();

    std::cout << result;

    return Json(result);
}
