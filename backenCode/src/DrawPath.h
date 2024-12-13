#ifndef DRAWPATH_H
#define DRAWPATH_H

#include "MatchChecker.h"
#include "GameManager.h"
#include "ImageData.h"

// 在头文件中定义
struct PathNode {
    Position pos;     // 当前位置
    int turns;        // 转折点数
    vector<Position> path;  // 记录路径经过的点
    
    PathNode(Position p, int t, vector<Position> prevPath = {}) : pos(p), turns(t) {
        path = prevPath;
        path.push_back(p);
    }
};

vector<Position> findConnectablePath(GameManager& gameManager, ImageData startImage, ImageData endImage);
vector<Position> findEdgeConnectablePath(GameManager& gameManager, ImageData startImage, ImageData endImage);
vector<Position> findBfsConnectablePath(GameManager& gameManager, ImageData startImage, ImageData endImage);
void eraseImage(GameManager& gameManager, ImageData startImage, ImageData endImage);
#endif