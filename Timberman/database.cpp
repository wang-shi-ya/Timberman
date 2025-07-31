#include "database.h"
#include <iostream>

Database::Database() : connection(nullptr), result(nullptr) {//��ʼ�����ݿ�����
    mysql_init(nullptr);
}

Database::~Database() {//��������
	disconnect();//ȷ���ڶ�������ʱ�Ͽ����ݿ�����
}

bool Database::connect(const std::string& host, const std::string& user,
    const std::string& password, const std::string& database) {//���ӵ����ݿ�
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
    if (result != nullptr) {
        mysql_free_result(result);
        result = nullptr;
    }
}

bool Database::execute(const std::string& query) {//ִ�в�ѯ
    if (mysql_query(connection, query.c_str())) {
        std::cerr << "Query failed: " << mysql_error(connection) << std::endl;
        return false;
    }
    return true;
}

std::vector<std::pair<int, std::string>> Database::getTopScores(int limit) {
    std::vector<std::pair<int, std::string>> scores;

    std::string query = "SELECT score, player_name FROM scores ORDER BY score DESC LIMIT " + std::to_string(limit);//mysql��ѯ���

	if (mysql_query(connection, query.c_str())) {//ִ�в�ѯ
        std::cerr << "Query failed: " << mysql_error(connection) << std::endl;
        return scores;
    }

    result = mysql_store_result(connection);
    if (result == nullptr) {
        std::cerr << "Failed to store result: " << mysql_error(connection) << std::endl;
        return scores;
    }

    while ((row = mysql_fetch_row(result))) {
        int score = std::stoi(row[0]);
        std::string playerName = row[1] ? row[1] : "Anonymous";
        scores.emplace_back(score, playerName);
    }

    mysql_free_result(result);
    result = nullptr;

    return scores;
}

bool Database::addScore(int score, const std::string& playerName) {//��ӷ��������ݿ�
    std::string query = "INSERT INTO scores (score, player_name) VALUES (" +
        std::to_string(score) + ", '" + playerName + "')";
    return execute(query);
}