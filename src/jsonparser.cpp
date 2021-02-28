#include "jsonparser.h"
#include <iostream>
#include <stdexcept>

JsonParser::JsonParser(std::istream &value) : is(value) {}

JsonParser::JsonParser(const std::string &str) : is(iss), iss(str) {}

JsonValue JsonParser::parse()
{
    try
    {
        while(true)
        {
            auto t = getToken();

            if(t=='"')
                return parseString();

            if(t=='{')  // get object map
            {
                std::map<std::string, JsonValue> map;   // ~object
                auto ch = getToken(); // " : }
                if(ch=='}')
                    return map;

                while(true)    // get pairs: {name, value}
                {
                    if(ch!='"')
                        throw(std::logic_error("miss opening '\"'"));

                    auto name = parseString();

                    if(getToken()!=':')
                        throw(std::logic_error("miss ':'"));

                    map.insert({std::move(name), parse()});

                    auto ch = getToken(); // , }
                    if(ch=='}')
                        break;
                    if(ch!=',')
                        throw(std::logic_error("miss ',' in object"));
                    ch = getToken();
                }
                return map;
            }

            if(t=='[')
            {
                std::vector<JsonValue> vec; // ~array
                auto ch = getToken();
                if(ch==']')
                    return vec;
                while(true)
                {
                    is.unget();
                    vec.push_back(parse());

                    auto ch = getToken();
                    if(ch==']')
                        break;
                    if(ch!=',')
                        throw(std::logic_error("miss ',' in array"));
                    ch = getToken();
                }
                return vec;
            }
        }
    }
    catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        errorOccure = true;
        return svs.emptyValue;
    }
}

std::string JsonParser::parseString()
{
    std::string ret;

    char ch = getChar();
    std::cout << ch;
    while(ch!='"')
    {
        ret.push_back(ch);
        ch = getChar();
    }
    std::cout << std::endl;
    return ret;  // eat ending "
}

void JsonParser::eatSpaces()
{
    auto ch = getChar();
    while(ch==' ' || ch=='\n' || ch=='\t')
        ch = getChar();
    is.unget();
}

wchar_t JsonParser::getToken()
{
    eatSpaces();
    return getChar();
}

wchar_t JsonParser::getChar()
{
    wchar_t ch = is.get();
    if(is.eof())
        throw std::out_of_range("unexpected eof");
    return ch;
}

