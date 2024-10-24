#include "Command.h"
#include <iostream>
#include <algorithm>

Command::Command() {
    setlocale(LC_ALL, "ru");
}

std::string Command::readerDbFile() {
    std::string dbFilePath;
    std::cout << "¬ведите путь к файлу базы данных : ";
    std::getline(std::cin, dbFilePath);
    return dbFilePath;
}

std::string Command::readerUserQuery() {
    std::string userQuery;
    std::cout << "¬ведите ваш SQL-запрос (или введите 'close' дл€ завершени€): ";
    std::getline(std::cin, userQuery);
    std::transform(userQuery.begin(), userQuery.end(), userQuery.begin(), ::tolower);
    return userQuery;
}
