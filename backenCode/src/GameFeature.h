#ifndef GAMEFEATURE_H
#define GAMEFEATURE_H

#include "GameManager.h"
#include "ImageData.h"
#include "nlohmann/json.hpp"
//提示功能
std::vector<Position> showHint(GameManager& gameManager);
//炸弹功能
void bomb(GameManager& gameManager);
//交换两个图片
void exchange(GameManager& gameManager, ImageData startImage, ImageData endImage);
//刷新全局
void refreshGrid(GameManager& gameManager);



struct bombValue
{
   public:
   std::string bombValue1;
   std::string bombValue2;
   bombValue() : bombValue1(""), bombValue2(""){};
};

extern bombValue bbvalue;

inline void to_json(json& j, const bombValue& user) {
    j = json{
        {"v1", user.bombValue1},
        {"v2", user.bombValue2}
    };
}

inline void from_json(const json& j, bombValue& user) {
    j.at("v1").get_to(user.bombValue1);
    j.at("v2").get_to(user.bombValue2);
}

#endif