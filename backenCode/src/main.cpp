#include <iostream>
#include "GameManager.h"
#include "httplib.h"
using namespace std;

void connectNet(){
    GameManager gameManager("easy");
    httplib::Server svr;
    svr.set_default_headers({
        { "Access-Control-Allow-Origin" , "*" }
        });

        svr.Post("/startEZ",[&gameManager](const httplib::Request &req , httplib::Response &res){
        gameManager=GameManager("easy");
    });

    svr.Post("/selected",[&gameManager](const httplib::Request &req , httplib::Response &res){
        stringstream ss(req.body);
        int x1,x2,x3,x4;
        char temp;
        ss>>x1>>temp>>x2>>temp>>x3>>temp>>x4;
        
        string ans=gameManager.run(x1,x2,x3,x4);
        res.set_content(ans,"text/plain");
    });



    cout<<"server starting"<<endl;
    svr.listen("localhost",11451);    
}

int main(){
    connectNet();
    
    return 0;
}