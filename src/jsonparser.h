#ifndef JSONPARSER_H
#define JSONPARSER_H
#include <iostream>
#include "jsonbasevalue.h"
#include <memory>
#include <sstream>

class JsonParser final
{
public:
    // Констркутор для потока (файл и пользовательский ввод)
    JsonParser(std::istream &is);
    // Конструктор для строки
    JsonParser(const std::string &str);
    // Выполнить разбор
    JsonValue parse();
    // Проверка ошибок при разборе
    bool isError() const {return errorOccure;}

private:
    std::string parseString();
    void eatSpaces();
    wchar_t getToken();
    wchar_t getChar();

    std::istream &is;
    std::istringstream iss;
    bool errorOccure = false;

};

#endif // JSONPARSER_H
