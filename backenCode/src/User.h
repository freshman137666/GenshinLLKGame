#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include "nlohmann/json.hpp"
using json = nlohmann::json;

struct User {
    string username;
    int score = 0;
    int rank =0;
    string password;
    string level;
   // 构造函数
    User(std::string username = "", std::string password = "",std::string level = "") : username(username), password(password),level(level) {}
};

inline void to_json(json& j, const User& user) {
    j = json{
        {"name", user.username},
        {"level", user.level},
        {"score", user.score},
        {"password", user.password},
        
    };
}

inline void from_json(const json& j, User& user) {
    j.at("name").get_to(user.username);
    j.at("level").get_to(user.level);
    j.at("score").get_to(user.score);
    j.at("password").get_to(user.password);
}
#endif