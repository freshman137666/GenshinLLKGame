#include <iostream>
#include "GameManager.h"
#include "httplib.h"
#include "User.h"
#include "GameFeature.h"
#include <windows.h>
using namespace std;

void connectNet(){
    GameManager gameManager;
    gameManager.connectSQL();

    httplib::Server svr;
    svr.set_default_headers({
        { "Access-Control-Allow-Origin", "*" },  // 允许所有域名的请求
        { "Access-Control-Allow-Methods", "POST, GET, OPTIONS" },  // 允许的 HTTP 方法
        { "Access-Control-Allow-Headers", "Content-Type" },  // 允许的请求头部
});

    svr.Options("/sendUsers", [](const httplib::Request& req, httplib::Response& res) {
    res.set_header("Access-Control-Allow-Methods", "POST, GET, OPTIONS");  // 允许的方法
    res.set_header("Access-Control-Allow-Headers", "Content-Type");  // 允许的请求头
    res.status = 200;  // 返回 200 OK 状态
});


    
    svr.Post("/startEZ",[&gameManager](const httplib::Request &req , httplib::Response &res){
        cout<<"easy"<<endl;
        gameManager.readFileToGrid("easy");
    });

    svr.Post("/startEX",[&gameManager](const httplib::Request &req , httplib::Response &res){
        cout<<"hard"<<endl;
        gameManager.readFileToGrid("difficult");
        
    });

    svr.Post("/selected",[&gameManager](const httplib::Request &req , httplib::Response &res){
        cout<<req.body<<endl;
        stringstream ss(req.body);
        int x1,x2,x3,x4;
        char temp;
        ss>>x1>>temp>>x2>>temp>>x3>>temp>>x4;
        cout<<gameManager.grid[x1][x2].imageType<<"  "<<gameManager.grid[x1][x2].position.cols<<endl;
        string ans=gameManager.run(x1,x2,x3,x4);
        res.set_content(ans,"text/plain");
    });

     svr.Post("/getUsers",[&gameManager](const httplib::Request &req , httplib::Response &res){
        cout<<"send message"<<endl;
        if (gameManager.conn == NULL) {
        std::cerr << "mysql_init failed" << std::endl;
        res.status = 500;  // 返回 500 错误
        res.set_content("Database connection failed", "text/plain");
    }   else{
         json users_json =gameManager.users;
         res.set_content(users_json.dump(), "application/json");
    }
        
    });

    svr.Post("/sendUsers",[&gameManager](const httplib::Request &req , httplib::Response &res){
        cout<<"get message"<<endl;
       json user_json =json::parse(req.body);
        gameManager.newUser=user_json.get<User>();
        std::cout << "Received User Data:" << std::endl;
            std::cout << "Name: " << gameManager.newUser.username << std::endl;
            std::cout << "Level: " << gameManager.newUser.level << std::endl;
            std::cout << "Score: " << gameManager.newUser.score << std::endl;
            std::cout << "Password: " << gameManager.newUser.password << std::endl;
        if (gameManager.conn == NULL) {
        std::cerr << "mysql_init failed" << std::endl;
         res.status = 500;  // 返回 500 错误
        res.set_content("Database connection failed", "text/plain");
    } else{
        gameManager.finishGame();
        res.status = 200;
        res.set_content("User data received and processed", "text/plain");
    }
    });


   svr.Post("/bye",[&gameManager](const httplib::Request &req , httplib::Response &res){
    mysql_close(gameManager.conn);
    exit(0);
   });

   svr.Get("/boom",[&gameManager](const httplib::Request &req, httplib::Response &res){
    bomb(gameManager);
    json users_json =bbvalue;
    cout<<bbvalue.bombValue1<<"   "<<bbvalue.bombValue2<<endl;
    res.set_content(users_json.dump(), "application/json");
   });

   svr.Post("/exchange",[&gameManager](const httplib::Request &req, httplib::Response &res){
    int row1,row2,col1,col2;
    stringstream ss(req.body);
    char temp;
    ss>>row1>>temp>>col1>>temp>>row2>>temp>>col2;
    ImageData startImage =gameManager.grid[row1][col1] ;
    ImageData endImage=gameManager.grid[row2][col2];
    exchange(gameManager,startImage,endImage);
    res.status = 200;
   });

    cout<<"server starting"<<endl;
    svr.listen("localhost",11451);    
}

int main(){
    SetConsoleOutputCP(65001);
    connectNet();
    return 0;
}