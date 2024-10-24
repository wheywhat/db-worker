#pragma once
#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>


class Database {
public:
    Database(const std::string& filePath);
    ~Database();
    void createTestTable();
    sqlite3* getDb() const; // ��������� ����� ��� ��������� ��������� �� ���� ������

private:
    sqlite3* db;
};


#endif // DATABASE_H


