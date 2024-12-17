#include <iostream>
#include "GameManager.h"
#include "httplib.h"
#include "User.h"
using namespace std;

void connectNet(){
    GameManager gameManager;
    gameManager.connectSQL();
   

    httplib::Server svr;
    svr.set_default_headers({
        { "Access-Control-Allow-Origin" , "*" }
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
        
        string ans=gameManager.run(x1,x2,x3,x4);
        res.set_content(ans,"text/plain");
    });

     svr.Post("/getUsers",[&gameManager](const httplib::Request &req , httplib::Response &res){
        cout<<"send message"<<endl;
        if (gameManager.conn == NULL) {
        std::cerr << "mysql_init failed" << std::endl;
    }   else{
         json users_json =gameManager.users;
         res.set_content(users_json.dump(), "application/json");
    }
        
    });

    svr.Post("/sendUsers",[&gameManager](const httplib::Request &req , httplib::Response &res){
        cout<<"get message"<<endl;
        if (gameManager.conn == NULL) {
        std::cerr << "mysql_init failed" << std::endl;
    } else{
        json user_json =json::parse(req.body);
        gameManager.newUser=user_json.get<User>();
        gameManager.finishGame();
    }
    });



    cout<<"server starting"<<endl;
    svr.listen("localhost",11451);    
}

int main(){

    connectNet();
    return 0;
}