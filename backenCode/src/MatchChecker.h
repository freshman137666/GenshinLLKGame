#ifndef MATCHCHECKER_H
#define MATCHCHECKER_H


#include "GameManager.h"
#include "ImageData.h"
#include <queue>
#include <set>
//计算两个坐标之间的距离
double distance(Position startPosition,Position endPosition2);
    
//判断两个图像是否可以进行连接
bool connectable(GameManager& gameManager,ImageData startImage,ImageData endImage);
bool rowConnectable(GameManager& gameManager,ImageData startImage,ImageData endImage);
bool colConnectable(GameManager& gameManager,ImageData startImage,ImageData endImage);
bool edgeConnectable(GameManager& gameManager,ImageData startImage,ImageData endImage);

//使用BFS算法判断两个图像是否可以进行连接
bool bfsConnectable(GameManager& gameManager,ImageData startImage,ImageData endImage);

//检查传入的两个图像是否为空
bool checkImagesEmpty(ImageData startImage,ImageData endImage);
#endif
