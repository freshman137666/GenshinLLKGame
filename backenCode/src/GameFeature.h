#ifndef GAMEFEATURE_H
#define GAMEFEATURE_H

#include "GameManager.h"
#include "ImageData.h"
//提示功能
vector<Position> showHint(GameManager& gameManager);
//炸弹功能
void bomb(GameManager& gameManager);
//交换两个图片
void exchange(GameManager& gameManager, ImageData startImage, ImageData endImage);
//刷新全局
void refreshGrid(GameManager& gameManager);
#endif