#include "GameManager.h"
#include "MatchChecker.h"
#include "DrawPath.h"
#include "GameFeature.h"
#include <iomanip>
using namespace std;
string canLink ="";
GameManager::GameManager(string difficulty)
{
    readFileToGrid(difficulty);
}

GameManager::~GameManager()
{
}
void GameManager::readFileToGrid(string difficulty){
    //打开文件进行读取
    ifstream inputFile("../GridDataFile/" + difficulty + ".txt");//../GridDataFile/data.txt
    if(!inputFile.is_open()){
        std::cerr << "无法打开文件进行读取"<<endl;
        return;
    }
    int row ;
    int col;
    inputFile >> row >> col;
   
    grid.resize(row+2,vector<ImageData>(col+2));
    //对矩阵进行初始化
    for(int i =1;i<=row;i++){
        for(int j =1;j<=col;j++){
            int imageType;
            inputFile >> imageType;
            grid[i][j] = ImageData(imageType,Position(i,j));
        }
    }
    inputFile.close();//关闭文件
    
}
void GameManager::printGrid(){
    for(int i = 1;i<=grid.size()-2;i++){
        for(int j =1;j<=grid[0].size()-2;j++){
            cout <<left<<setw(4) << grid[i][j].imageType ;
            
        }
        cout <<endl;
    }
    
    
}
bool GameManager::isEmptyGrid(){
    
    for(int i = 1;i<=grid.size()-2;i++){
        for(int j =1;j<=grid[0].size()-2;j++){
            if(grid[i][j].imageType != 0){
                return false;
            }
        }
        
    }
    cout << "游戏结束"<<endl;
    return true;
}
void GameManager::operate(int r1,int c1,int r2,int c2){
    int row =r1;
    int col =c1;
    cout <<"输入你想消除的两个图片: ";
    ImageData startImage = grid[row][col];
    cout <<startImage.imageType <<endl;
    row=r2;
    col=c2;
    ImageData endImage = grid[row][col];
    cout <<endImage.imageType <<endl;
    if(connectable(*this, startImage, endImage)){
        cout << "两图片可以被消除"<<endl;
        canLink="true";
        cout <<"连接路径："<<endl;
        vector<Position> connectPath = findConnectablePath(*this, startImage, endImage);
        drawConnectPath(connectPath);
        cout << "消除图片："<<endl;
        eraseImage(*this, startImage, endImage);
        cout << "消除成功"<<endl;
        

    }else{
        cout << "两图片不能消除"<<endl;
        canLink="false";
    }
    
}
void GameManager::drawConnectPath(const vector<Position>& path) {
    if (path.empty()) {
        cout << "没有找到连接路径" << endl;
        return;
    }
    
    cout << "连接路径如下：" << endl;
    for (size_t i = 0; i < path.size(); ++i) {
        cout << "(" << path[i].rows << "," << path[i].cols << ")";
        if (i < path.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;
}

string GameManager::run(int r1,int c1,int r2,int c2){
    //在矩阵还有元素不为零的情况下，保持循环
        printGrid();
        operate(r1,c1,r2,c2);
        cout<<canLink<<endl;
        return canLink;
}


