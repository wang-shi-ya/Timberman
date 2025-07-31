#pragma once
#ifndef DATABASE_H//
#define DATABASE_H

#include <mysql.h>
#include <string>
#include<iostream>
#include <vector>
#include <utility> // for std::pair

class Database {
public:
    Database();
	~Database();//析构函数

    bool connect(const std::string& host, const std::string& user,
        const std::string& password, const std::string& database);
    void disconnect();

	bool execute(const std::string& query);//执行查询
	std::vector<std::pair<int, std::string>> getTopScores(int limit = 10);//getTopScores函数
    bool addScore(int score, const std::string& playerName = "WSY");

private:
    MYSQL* connection;
    MYSQL_RES* result;
    MYSQL_ROW row;
};

#endif // DATABASE_H