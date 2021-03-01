#ifndef JsonParser_H
#define JsonParser_H
#include <memory>
#include <iostream>
#include <sstream>

#include "jsonbasevalue.h"

class JsonParser final
{
public:
    // Констркутор для потока (файл и пользовательский ввод)
    JsonParser(std::istream &is);
    // Конструктор для строки
    JsonParser(const std::string &str);
    // Выполнить разбор
    JsonValue parse();
    // Наличие ошибок при разборе
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

#endif // JsonParser_H
