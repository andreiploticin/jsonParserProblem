#ifndef JSONPARSER_H
#define JSONPARSER_H
#include <iostream>
#include "jsonbasevalue.h"
#include <memory>
#include <sstream>

class JsonParser final
{
public:
    JsonParser(std::istream &is);
    JsonParser(const std::string &str);
    JsonValue parse();
    void eatSpaces();
    bool isError() const {return errorOccure;}

private:
    std::string parseString();

    std::shared_ptr<JsonBaseValue> result;
    wchar_t getToken();
    wchar_t getChar();
    std::istream &is;
    std::istringstream iss;
    unsigned p = 0;
    bool errorOccure = false;

};

#endif // JSONPARSER_H
