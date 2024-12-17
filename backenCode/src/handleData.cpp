#include "handleData.h"
#include <mysql.h>
void loadUsersFromDB(MYSQL* conn, std::vector<User>& users) {
    std::string query = "SELECT * FROM players";

    MYSQL_RES* res;
    MYSQL_ROW row;
    if (mysql_query(conn, query.c_str())) {
        std::cerr << "MySQL query error: " << mysql_error(conn) << std::endl;
        return;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        std::cerr << "MySQL store result error: " << mysql_error(conn) << std::endl;
        return;
    }

    // 遍历查询结果并将其添加到users向量
    while ((row = mysql_fetch_row(res))) {
        User newUser;
        newUser.rank = std::stoi(row[0]);
        newUser.username = row[1];
        newUser.level = row[2];
        newUser.score = std::stoi(row[3]);
        newUser.password = row[4];
        users.push_back(newUser);
    }
    mysql_free_result(res);
}

void addNewUserToDB(MYSQL* conn, const User& newUser, std::vector<User>& users) {
    // 首先检查连接是否有效
    if (conn == nullptr) {
        std::cerr << "MySQL connection is null" << std::endl;
        return;
    }

    if (mysql_ping(conn) != 0) {
        std::cerr << "MySQL connection is not alive: " << mysql_error(conn) << std::endl;
        return;
    }

    users.push_back(newUser);
    std::sort(users.begin(), users.end(), [](const User& a, const User& b) {
        return a.score > b.score;
    });

    for (int i = 0; i < users.size(); ++i) {
        users[i].rank = i + 1;
    }

    
    std::string deleteQuery = "DELETE FROM players";
    if (mysql_query(conn, deleteQuery.c_str())) {
        std::cerr << "MySQL delete error: " << mysql_error(conn) << std::endl;
        return;
    }

    // 插入新的用户数据
    for (const auto& user : users) {
        char escapedUsername[255];
        char escapedPassword[255];
        char escapedLevel[255];
        mysql_real_escape_string(conn, escapedUsername, user.username.c_str(), user.username.length());
        mysql_real_escape_string(conn, escapedPassword, user.password.c_str(), user.password.length());
        mysql_real_escape_string(conn, escapedLevel, user.level.c_str(), user.level.length());

        std::string insertQuery = "INSERT INTO players (ranking, username,levels, score, password) VALUES (" +
                                std::to_string(user.rank) + ", '" +
                                escapedUsername + "', '" +
                                escapedLevel + "', " +
                                std::to_string(user.score) + ", '" +
                                escapedPassword + "')";

        if (mysql_query(conn, insertQuery.c_str())) {
            std::cerr << "MySQL insert error: " << mysql_error(conn) << std::endl;
            return;
        }
    }
}

