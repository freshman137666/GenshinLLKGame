#ifndef DRAWPATH_H
#define DRAWPATH_H

#include "MatchChecker.h"
#include "GameManager.h"
#include "ImageData.h"

// 在头文件中定义
struct PathNode {
    Position pos;     // 当前位置
    int turns;        // 转折点数
    std::vector<Position> path;  // 记录路径经过的点
    
    PathNode(Position p, int t, std::vector<Position> prevPath = {}) : pos(p), turns(t) {
        path = prevPath;
        path.push_back(p);
    }
};

std::vector<Position> findConnectablePath(GameManager& gameManager, ImageData startImage, ImageData endImage);
std::vector<Position> findEdgeConnectablePath(GameManager& gameManager, ImageData startImage, ImageData endImage);
std::vector<Position> findBfsConnectablePath(GameManager& gameManager, ImageData startImage, ImageData endImage);
void eraseImage(GameManager& gameManager, ImageData startImage, ImageData endImage);
#endif