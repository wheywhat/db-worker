#include "database.h"
#include <iostream>

Database::Database(const std::string& filePath) {
    if (sqlite3_open(filePath.c_str(), &db) == SQLITE_OK) {
        std::cout << "Успешное подключение к базе данных.\n";
    }
    else {
        std::cerr << "Ошибка подключения к базе данных: " << sqlite3_errmsg(db) << "\n";
        exit(1);
    }
}

Database::~Database() {
    if (db) {
        sqlite3_close(db);
        std::cout << "Отключение от базы данных успешно.\n";
    }
}

sqlite3* Database::getDb() const {
    return db;
}

void Database::createTestTable() {
    const char* sqlCreateTable = R"(
        CREATE TABLE IF NOT EXISTS test (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL,
            birthdate TEXT
        );
    )";

    const char* sqlInsertData[] = {
        "INSERT INTO test (name, birthdate) VALUES ('Дима', '1990-01-01');",
        "INSERT INTO test (name, birthdate) VALUES ('Миша', '1985-05-15');",
        "INSERT INTO test (name, birthdate) VALUES ('Иван', '1978-11-22');"
    };

    char* errMsg = nullptr;

    if (sqlite3_exec(db, sqlCreateTable, nullptr, nullptr, &errMsg) != SQLITE_OK) {
        std::cerr << "Ошибка создания таблицы: " << errMsg << "\n";
        sqlite3_free(errMsg);
    }
    else {
        std::cout << "Тестовая таблица `test` успешно создана! \n";
    }

    for (const char* sql : sqlInsertData) {
        if (sqlite3_exec(db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK) {
            std::cerr << "Ошибка вставки данных: " << errMsg << "\n";
            sqlite3_free(errMsg);
        }
    }

    std::cout << "Тестовая таблица `test` заполнена данными.\n";
}

