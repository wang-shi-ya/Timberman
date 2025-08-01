#ifndef DATABASE_H
#define DATABASE_H

#include <mysql.h>
#include <string>
#include <vector>
#include <tuple>  // 添加这行
#include <ctime>

class Database {
public:
    Database();
    ~Database();

    bool connect(const std::string& host, const std::string& user,
                const std::string& password, const std::string& database);
    void disconnect();
    bool execute(const std::string& query);
    std::vector<std::tuple<int, std::string, std::string>> getTopScores(int limit = 10);
    bool addScore(int score, const std::string& playerName = "WSY");//添加排名

private:
    MYSQL* connection;
};

#endif // DATABASE_H