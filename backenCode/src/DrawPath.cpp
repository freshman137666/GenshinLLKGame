#include "DrawPath.h"
using namespace std;
vector<Position> findConnectablePath(GameManager& gameManager, ImageData startImage, ImageData endImage) {
    if (!edgeConnectable(gameManager,startImage,endImage)||rowConnectable(gameManager,startImage,endImage)||colConnectable(gameManager,startImage,endImage))
    {
           return findBfsConnectablePath(gameManager,startImage,endImage);
    }else
    {
            
            return findEdgeConnectablePath(gameManager,startImage,endImage);
    }
    
    
}

vector<Position> findBfsConnectablePath(GameManager& gameManager, ImageData startImage, ImageData endImage) {
    // 定义方向数组：上、下、左、右
    int dx[] = {0, 0, 1, -1};
    int dy[] = {1, -1, 0, 0};
    
    // 网格大小
    int rows = gameManager.grid.size();
    int cols = gameManager.grid[0].size();
    
    // 用于标记是否访问过的二维数组和转折点数的数组
    vector<vector<vector<bool>>> visited(rows, 
        vector<vector<bool>>(cols, 
            vector<bool>(3, false)  // 增加一个维度记录转折点数
        )
    );
    
    // 用于存储搜索路径的队列
    queue<PathNode> q;
    
    // 初始化起始位置，0表示转折点数
    q.push(PathNode(startImage.position, 0));
    visited[startImage.position.rows][startImage.position.cols][0] = true;
    
    // BFS搜索
    while (!q.empty()) {
        PathNode current = q.front();
        q.pop();
        
        // 如果超过两个转折点，则跳过
        if (current.turns > 100) continue;
        
        // 搜索四个方向
        for (int k = 0; k < 4; k++) {
            int newRow = current.pos.rows + dx[k];
            int newCol = current.pos.cols + dy[k];
            
            // 检查新位置是否在网格内
            if (newRow > 0 && newRow < rows-1 && newCol > 0 && newCol < cols-1) {
                // 判断是否到达目标图像
                if (newRow == endImage.position.rows && newCol == endImage.position.cols) {
                    // 创建最终路径，包含起始和目标位置
                    vector<Position> finalPath = current.path;
                    finalPath.push_back(Position(newRow, newCol));
                    return finalPath;
                }
                
                // 如果该位置为空，且未被访问
                if (gameManager.grid[newRow][newCol].imageType == 0) {
                    // 判断是否需要增加转折点
                    int newTurns = current.turns;
                    if (newRow != current.pos.rows && newCol != current.pos.cols) {
                        newTurns++;
                    }
                    
                    // 检查是否已访问，防止重复搜索
                    if (!visited[newRow][newCol][newTurns]) {
                        // 创建新的路径节点
                        PathNode newNode(
                            Position(newRow, newCol), 
                            newTurns, 
                            current.path
                        );
                        
                        q.push(newNode);
                        visited[newRow][newCol][newTurns] = true;
                    }
                }
            }
        }
    }
    
    // 没有找到路径，返回空路径
    return {};
}

vector<Position> findEdgeConnectablePath(GameManager& gameManager, ImageData startImage, ImageData endImage) {
    vector<Position> connectPath;
    int start, end;
    
    // 标记是否找到可连接路径
    bool foundPath = false;
    
    // 若两个图片位于右边列边界
    if (startImage.position.cols == endImage.position.cols && 
        startImage.position.cols == gameManager.grid.size() - 2) {
        int col = startImage.position.cols + 1;
        start = min(startImage.position.rows, endImage.position.rows);
        end = max(startImage.position.rows, endImage.position.rows);
        
        // 检查路径上是否全为空白
        for (int i = start; i <= end; i++) {
            if (gameManager.grid[i][col].imageType == 0) {
                connectPath.push_back(Position(i, col));
                foundPath = true;
            } else {
                foundPath = false;
                break;
            }
        }
    }
    // 若两个图片位于同一行且靠近右边行边界
    else if (startImage.position.rows == endImage.position.rows && 
             startImage.position.rows == gameManager.grid.size() - 2) {
        int row = startImage.position.rows + 1;
        start = min(startImage.position.cols, endImage.position.cols);
        end = max(startImage.position.cols, endImage.position.cols);
        
        // 检查路径上是否全为空白
        for (int i = start; i <= end; i++) {
            if (gameManager.grid[row][i].imageType == 0) {
                connectPath.push_back(Position(row, i));
                foundPath = true;
            } else {
                foundPath = false;
                break;
            }
        }
    }
    // 判断左边列边界
    else if (startImage.position.cols == 1 && endImage.position.cols == 1) {
        int col = startImage.position.cols - 1;
        start = min(startImage.position.rows, endImage.position.rows);
        end = max(startImage.position.rows, endImage.position.rows);
        
        // 检查路径上是否全为空白
        for (int i = start; i <= end; i++) {
            if (gameManager.grid[i][col].imageType == 0) {
                connectPath.push_back(Position(i, col));
                foundPath = true;
            } else {
                foundPath = false;
                break;
            }
        }
    }
    // 判断上边行边界
    else if (startImage.position.rows == 1 && endImage.position.rows == 1) {
        int row = startImage.position.rows - 1;
        start = min(startImage.position.cols, endImage.position.cols);
        end = max(startImage.position.cols, endImage.position.cols);
        
        // 检查路径上是否全为空白
        for (int i = start; i <= end; i++) {
            if (gameManager.grid[row][i].imageType == 0) {
                connectPath.push_back(Position(row, i));
                foundPath = true;
            } else {
                foundPath = false;
                break;
            }
        }
    }
    
    // 如果找到路径，在起始和结束图片位置也加入路径
    if (foundPath) {
        connectPath.insert(connectPath.begin(), startImage.position);
        connectPath.push_back(endImage.position);
    }
    
    return connectPath;
}
void eraseImage(GameManager& gameManager, ImageData startImage, ImageData endImage){
    gameManager.grid[startImage.position.rows][startImage.position.cols].imageType = 0;
    gameManager.grid[endImage.position.rows][endImage.position.cols].imageType = 0;
}