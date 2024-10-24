#pragma once
#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include <string>

class Command {
public:
    Command();
    std::string readerDbFile();
    std::string readerUserQuery();
};

#endif // COMMANDPROCESSOR_H


