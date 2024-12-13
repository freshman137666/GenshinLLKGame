#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

/*
游戏管理器：
根据用户选择的难度读取对应文件信息的函数（矩阵行列数和矩阵元素信息）
读取格式化文件的函数
定义一个矩阵用于存储每个图片的对象


*/
#include <vector>
#include <memory>
#include <fstream>
#include  "ImageData.h"
using namespace std;

        
class GameManager
{
private:
    /* data */
    
    
public:
    vector<vector<ImageData>> grid;//首先定义一个二维数组
    GameManager(string difficulty);//需要从前端获取游戏难度，从而从对应文件查找信息
    ~GameManager();
    void readFileToGrid(string difficulty);//打开路径对应的文件，读取文件信息，初始化矩阵
    void run();//启动游戏
    void printGrid();//打印矩阵
    bool isEmptyGrid();//判断矩阵中是否存在不为零的元素
    void operate();//对矩阵进行操作
    void drawConnectPath(const vector<Position>& path);
    
    
};




#endif
