#include "database.h"
#include <tuple> 
#include <iostream>

Database::Database() : connection(nullptr) {
    mysql_init(nullptr);
}

Database::~Database() {
    disconnect();
}

bool Database::connect(const std::string& host, const std::string& user,
    const std::string& password, const std::string& database) {
    connection = mysql_real_connect(mysql_init(nullptr),
        host.c_str(),
        user.c_str(),
        password.c_str(),
        database.c_str(),
        0, nullptr, 0);

    if (connection == nullptr) {
        std::cerr << "Database connection failed: " << mysql_error(connection) << std::endl;
        return false;
    }
    return true;
}

void Database::disconnect() {
    if (connection != nullptr) {
        mysql_close(connection);
        connection = nullptr;
    }
}

bool Database::execute(const std::string& query) {
    if (mysql_query(connection, query.c_str())) {
        std::cerr << "Query failed: " << mysql_error(connection) << std::endl;
        return false;
    }
    return true;
}

std::vector<std::tuple<int, std::string, std::string>> Database::getTopScores(int limit) {
    std::vector<std::tuple<int, std::string, std::string>> scores;

    std::string query = "SELECT score, player_name, DATE_FORMAT(created_at, '%Y-%m-%d %H:%i') "
        "FROM scores ORDER BY score DESC, created_at DESC LIMIT " +
        std::to_string(limit);

    if (mysql_query(connection, query.c_str())) {
        std::cerr << "Query failed: " << mysql_error(connection) << std::endl;
        return scores;
    }

    MYSQL_RES* result = mysql_store_result(connection);
    if (!result) {
        std::cerr << "Failed to store result: " << mysql_error(connection) << std::endl;
        return scores;
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        try {
            int score = std::stoi(row[0]);
            std::string playerName = row[1] ? row[1] : "Anonymous";
            std::string timestamp = row[2] ? row[2] : "Unknown";
            scores.emplace_back(score, playerName, timestamp);
        }
        catch (...) {
            std::cerr << "Error parsing score record" << std::endl;
        }
    }

    mysql_free_result(result);
    return scores;
}

bool Database::addScore(int score, const std::string& playerName) {
    std::string query = "INSERT INTO scores (score, player_name) VALUES (" +
        std::to_string(score) + ", '" + playerName + "')";
    return execute(query);
}