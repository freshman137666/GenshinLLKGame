#include "GameFeature.h"
#include "matchChecker.h"
#include "DrawPath.h"
#include <random> 
#include <algorithm>
#include <bits/this_thread_sleep.h>
using namespace std;

bombValue bbvalue;

vector<Position> showHint(GameManager& gameManager) {
    vector<Position> hintPath; // 用于存储提示路径
    vector<vector<ImageData>> grid = gameManager.grid;
    // 遍历整个网格，寻找可以连接的图片对
    for (int i = 1; i <= grid.size() - 2; ++i) {
        for (int j = 1; j <= grid[0].size() - 2; ++j) {
            auto& cell1 = grid[i][j]; // 使用引用减少拷贝
            // 跳过空格
            if (cell1.imageType == 0) {
                continue;
            }
            // 找到当前位置的图片
            ImageData startImage = cell1;
             cout<<"pic1:"<<startImage.position.rows<<"-"<<startImage.position.cols<<endl;

            // 再次遍历寻找可以连接的图片
            for (int k = i; k <= grid.size() - 2; ++k) {
                for (int l = (k == i ? j + 1 : 1); l <= grid[0].size() - 2; ++l) {
                    // 跳过空格
                    auto& cell = grid[k][l]; // 使用引用减少拷贝
                    if (cell.imageType == 0) {
                        continue;
                    }

                    // 找到另一张图片
                    ImageData endImage = cell;
                    cout<<"pic2:"<<endImage.position.rows<<"-"<<endImage.position.cols<<endl;

                    // 判断这两个图片是否可以连接
                    if (startImage.imageType == endImage.imageType && connectable(gameManager, startImage, endImage)) {
                        // 如果可以连接，加入提示路径
                        hintPath.push_back(startImage.position);
                        hintPath.push_back(endImage.position);
                        cout << "可以连接的图片对 (" << startImage.position.rows << "," << startImage.position.cols
                             << ") 和 (" << endImage.position.rows << "," << endImage.position.cols << ")" << endl;
                        
                        return hintPath;  // 找到一对连接的图片后返回
                    }
                }
            }      
        }
    }

    cout << "没有找到可以连接的图片对。" << endl;
    return hintPath;  // 如果没有找到，返回空的路径
}
void bomb(GameManager& gameManager){
    vector<Position> hintPath = showHint(gameManager);
    if(hintPath.size()<1){
    bbvalue.bombValue1="false";
    return;
    }
    
    ImageData startImage, endImage;
    
    startImage = gameManager.grid[hintPath[0].rows][hintPath[0].cols];
    endImage = gameManager.grid[hintPath[1].rows][hintPath[1].cols];
    bbvalue.bombValue1=to_string(hintPath[0].rows)+"-"+to_string(hintPath[0].cols);
    bbvalue.bombValue2=to_string(hintPath[1].rows)+"-"+to_string(hintPath[1].cols);
    cout <<"boom!hahaha"<<endl;

    eraseImage(gameManager, startImage, endImage );

}

void exchange(GameManager& gameManager, ImageData startImage, ImageData endImage){
    if(checkImagesEmpty(startImage, endImage)){
        cout << "交换图片" << endl;
        ImageData temp = startImage;
        gameManager.grid[startImage.position.rows][startImage.position.cols].imageType = endImage.imageType;
        gameManager.grid[endImage.position.rows][endImage.position.cols].imageType = temp.imageType;
        gameManager.printGrid();
    }

}
void refreshGrid(GameManager& gameManager) {
    int rows = gameManager.grid.size() - 2;  // 去除边界
    int cols = gameManager.grid[0].size() - 2;  // 去除边界

    // 收集所有非空的图片
    vector<ImageData> remainingImages;
    for (int row = 1; row <= rows; ++row) {
        for (int col = 1; col <= cols; ++col) {
            if (gameManager.grid[row][col].imageType != 0) {
                remainingImages.push_back(gameManager.grid[row][col]);
            }
        }
    }

    // 随机排列剩余图片
    random_device rd;
    mt19937 g(rd());
    shuffle(remainingImages.begin(), remainingImages.end(), g);
                                                                                                                                                                                                                                                                                                                                                                        
    // 按原位置重新填充图片
    int index = 0;
    for (int row = 1; row <= rows; ++row) {
        for (int col = 1; col <= cols; ++col) {
            if (gameManager.grid[row][col].imageType != 0) { // 仅对原有图片位置进行填充
                gameManager.grid[row][col] = remainingImages[index++];
            }
        }
    }
}
