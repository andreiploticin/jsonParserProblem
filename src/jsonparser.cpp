#include "jsonparser.h"

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
                auto ch = getToken(); // one of: " : }
                if(ch=='}')
                    return map;

                while(true)    // get pairs  name:value,
                {
                    if(ch!='"')
                        throw(std::string("missing opening '\"'"));

                    auto name = parseString();

                    if(getToken()!=':')
                        throw(std::string("missing ':'"));

                    map.insert({name, parse()});

                    ch = getToken(); // one of:  , }
                    if(ch=='}')
                        break;
                    if(ch!=',')
                        throw(std::string("missing ',' in object"));
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

                    ch = getToken();
                    if(ch==']')
                        break;
                    if(ch!=',')
                        throw(std::string("miss ',' in array"));
                    ch = getToken();
                }
                return vec;
            }
        }
    }
    catch (std::string &e)
    {
        std::cout << e << std::endl;
        errorOccure = true;
        return getEmpties().emptyValue;
    }
}

std::string JsonParser::parseString()
{
    std::string ret;

    char ch = getChar();
    while(ch!='"')
    {
        ret.push_back(ch);
        ch = getChar();
    }
    return ret;
}

void JsonParser::eatSpaces()
{
    auto ch = getChar();
    while(ch==' ' || ch=='\t' || ch=='\n' || ch=='\r')
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
        throw std::string("unexpected eof");
    return ch;
}

