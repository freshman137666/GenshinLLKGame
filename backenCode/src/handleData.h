#ifndef HANDLEDATA_H
#define HANDLEDATA_H

#include <iostream>
#include <mysql.h>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
#include "User.h"
// 从数据库中读取用户数据，存储在一个vector数组中
void loadUsersFromDB(MYSQL* conn, std::vector<User>& users);

// 添加新用户并更新数据库
void addNewUserToDB(MYSQL* conn, const User& newUser, std::vector<User>& users);


#endif



