#include <iostream>
#include "database.h"
#include "command.h"
#include <sys/stat.h>
#include <algorithm> // для std::transform
#include <cctype>    // для std::tolower

bool checkDb(const std::string& filePath) {
    struct stat buffer;
    std::cout << "Проверка существования файла базы данных...\n";
    if (stat(filePath.c_str(), &buffer) == 0) {
        std::cout << "База данных найдена!\n";
        return true;
    }
    else {
        std::cout << "База данных не найдена. Будет создана новая БД\n";
        return false;
    }
}

void sql_commands(sqlite3* db, const std::string& query) {
    char* errMsg = nullptr;
    sqlite3_exec(db, query.c_str(), [](void*, int argc, char** argv, char** colNames) -> int {
        // читаем запрос если он что то вернул
        for (int i = 0; i < argc; i++) {
            std::cout << (argv[i] ? argv[i] : "NULL") << "\t";
        }
        std::cout << "\n";
        return 0;
        }, nullptr, &errMsg);

    if (errMsg) {
        std::cerr << "Ошибка выполнения запроса: " << errMsg << "\n";
        sqlite3_free(errMsg);
    }
}


int main() {
    Command commandProcessor;
    // получение пути к файлу
    std::string dbFilePath = commandProcessor.readerDbFile();

    bool dbExists = checkDb(dbFilePath);

    {
        Database dbHelper(dbFilePath);

        // проверка на существование
        if (!dbExists) {
            dbHelper.createTestTable();
        }

        while (true) {
            std::string userQuery = commandProcessor.readerUserQuery();

            // Преобразуем запрос в нижний регистр
            std::transform(userQuery.begin(), userQuery.end(), userQuery.begin(), ::tolower);

            if (userQuery == "close") {
                break;
            }
            sql_commands(dbHelper.getDb(), userQuery); 
        }
    }

    return 0;
}


