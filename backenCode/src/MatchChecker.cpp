#include "MatchChecker.h"

#include <cmath>

//计算两个坐标之间的距离
double distance(Position startPosition,Position endPosition2){
    return std::sqrt(pow(endPosition2.rows - startPosition.rows,2) + pow(endPosition2.cols - startPosition.cols,2));
}
bool checkImagesEmpty(ImageData startImage,ImageData endImage){
    return startImage.imageType != 0 && endImage.imageType != 0;
}
bool connectable(GameManager& gameManager, ImageData startImage, ImageData endImage) {
    if(startImage.imageType == 0 || endImage.imageType == 0){
        cerr << "图片未加载" << endl;
        return false;

    }
    if (startImage.imageType != endImage.imageType) {
        cerr << "图片类型不相同" << endl;
        return false;
    }else if (distance(startImage.position, endImage.position) <= 1) {
        return true; // 相邻图片可以直接连接
    }else if (edgeConnectable(gameManager, startImage, endImage)) {
        return true; // 边界上的图片可连接
    }else if (rowConnectable(gameManager, startImage, endImage) || colConnectable(gameManager, startImage, endImage)) {
        return true; // 同一行或列可连接
    }else if(bfsConnectable(gameManager, startImage, endImage)){
        return true;
    }
    

    return false; // 其他情况不可连接
}

bool rowConnectable(GameManager& gameManager, ImageData startImage, ImageData endImage) {
    if (startImage.position.rows != endImage.position.rows) {
        return false; // 不同的行不可连接
    }

    int start = std::min(startImage.position.cols, endImage.position.cols);
    int end = std::max(startImage.position.cols, endImage.position.cols);


    for (int j = start + 1; j < end; j++) {
        if (gameManager.grid[startImage.position.rows][j].imageType != 0) {
            return false; // 发现阻塞图片，立即返回
        }
    }
    return true; // 所有检查通过
}

bool colConnectable(GameManager& gameManager, ImageData startImage, ImageData endImage) {
    // 如果两图片不在同一列，直接返回不可连接
    if (startImage.position.cols != endImage.position.cols) {
        return false;
    }

    // 确定行的起始和结束位置
    int start = std::min(startImage.position.rows, endImage.position.rows);
    int end = std::max(startImage.position.rows, endImage.position.rows);

    // 检查两图片之间的垂直路径是否被阻塞
    for (int i = start + 1; i < end; i++) {  // 避免检查 start 和 end 行本身，因为已经检查过
        if (gameManager.grid[i][startImage.position.cols].imageType != 0) {
            return false;  // 遇到阻挡物，立即返回不可连接
        }
    }

    return true;  // 没有阻挡物，返回可连接
}

//对于在边上的相同图片，允许连接
bool edgeConnectable(GameManager& gameManager,ImageData startImage,ImageData endImage){
   bool isEdgeConnectable = false;
   int start,end;
   //若两个图片位于列边界
    if(startImage.position.cols == endImage.position.cols && startImage.position.cols == gameManager.grid.size()-2){
        int col = startImage.position.cols +1;
        start = min(startImage.position.rows , endImage.position.rows);
        end = max(startImage.position.rows , endImage.position.rows);

        for(int i =start;i<end;i++){
            if(gameManager.grid[i][col ].imageType != 0){
                isEdgeConnectable = false;
            }else{
                 isEdgeConnectable = true;
            }
        }

    }else if(startImage.position.rows == endImage.position.rows && startImage.position.rows == gameManager.grid.size()-2){
        int row = startImage.position.rows+1;
        start = min(startImage.position.cols , endImage.position.cols);
        end = max(startImage.position.cols , endImage.position.cols);

        for(int i = start;i<end;i++){
            if(gameManager.grid[i][row ].imageType != 0){
                isEdgeConnectable = false;
            }else{
                 isEdgeConnectable = true;
            }
        }
    }
    // 判断左边列边界 (col == 0)
    else if (startImage.position.cols == 1 && endImage.position.cols == 1) {
        int col = startImage.position.cols -1;
        start = min(startImage.position.rows , endImage.position.rows);
        end = max(startImage.position.rows , endImage.position.rows);

        for (int i = start; i < end; i++) {
            if(gameManager.grid[i][col ].imageType != 0){
                isEdgeConnectable = false;
            }else{
                 isEdgeConnectable = true;
            }
        }
    }
    // 判断上边行边界 (row == 0)
    else if (startImage.position.rows == 1 && endImage.position.rows == 1) {
        int row = startImage.position.rows - 1;
        start = min(startImage.position.cols , endImage.position.cols);
        end = max(startImage.position.cols , endImage.position.cols);

        for (int i = start; i < end; i++) {
            if(gameManager.grid[i][row ].imageType != 0){
                isEdgeConnectable = false;
            }else{
                 isEdgeConnectable = true;
            }
        }
    }
    
    return isEdgeConnectable;
   
}
bool bfsConnectable(GameManager& gameManager, ImageData startImage, ImageData endImage) {
    // 定义方向数组，用于搜索四个相邻方向
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    
    // 网格大小
    int rows = gameManager.grid.size();
    int cols = gameManager.grid[0].size();
    
    // 用于标记是否访问过的二维数组
    vector<vector<bool>> visited(rows, vector<bool>(cols, false));
    
    // 用于存储搜索路径的队列
    queue<pair<Position, int>> q;
    
    // 初始化起始位置，0表示转折点数
    q.push({startImage.position, 0});
    visited[startImage.position.rows][startImage.position.cols] = true;
    
    // BFS搜索
    while (!q.empty()) {
        auto [current, turns] = q.front();
        q.pop();
        
        // 如果超过两个转折点，则跳过
        if (turns > 100) continue;
        
        // 搜索四个方向
        for (int k = 0; k < 4; k++) {
            int newRow = current.rows + dx[k];
            int newCol = current.cols + dy[k];
            
            // 检查新位置是否在网格内
            if (newRow > 0 && newRow < rows-1 && newCol > 0 && newCol < cols-1) {
                // 判断是否到达目标图像
                if (newRow == endImage.position.rows && newCol == endImage.position.cols) {
                    return true;
                }
                
                // 如果该位置为空，且未被访问
                if (gameManager.grid[newRow][newCol].imageType == 0 && !visited[newRow][newCol]) {
                    // 判断转折点数
                    int newTurns = turns;
                    q.push({{newRow, newCol}, newTurns + 1});
                    visited[newRow][newCol] = true;
                }
            }
        }
    }
    
    return false;
}
  