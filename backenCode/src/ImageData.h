#ifndef IMAGEDATA_H
#define IMAGEDATA_H

/*
图片数据：可以用一个结构体来表示
图片类型：对应着相应图片
图片ID：
图的坐标Position(rows,cols)

*/
//图片坐标结构体
#include <iostream>
#include <string>
using namespace std;

struct Position
{
    //图片所在行列
    int rows;
    int cols;
    Position(int rows = 0,int cols=0) : rows(rows),cols(cols) {}
};

struct ImageData
{
    int imageType;//用数字编号来表示图片对应的类型
    Position position;//图片坐标
    bool matched;//图片是否已匹配
    bool selected;//是否被选中
    string imagePath;
    ImageData(int imageType = 0,Position position = Position()) 
        : imageType(imageType),position(position) {}

};


#endif