#include "jsonbasevalue.h"
#include <memory>

staticValuesStruct svs;

const std::string   &JsonBaseValue::strinValue() const  { return svs.stringValue; }
const object        &JsonBaseValue::objectValue() const { return svs.objectValue; }
const array         &JsonBaseValue::arrayValue() const { return svs.arrayValue; }

const std::string   &JsonStringValue::strinValue()  const { return m_value; }
const object        &JsonObjectValue::objectValue() const { return m_value; }
const array         &JsonArrayValue::arrayValue() const { return m_value; }

JsonValue::JsonValue(const std::string &value)  : m_ptr(std::make_shared<JsonStringValue>(value)), m_valueType(STRING) {}
JsonValue::JsonValue(const object &value)       : m_ptr(std::make_shared<JsonObjectValue>(value)), m_valueType(OBJECT) {}
JsonValue::JsonValue(const array &value)        : m_ptr(std::make_shared<JsonArrayValue>(value)), m_valueType(ARRAY) {}
JsonValue::JsonValue(std::string &&value)       : m_ptr(std::make_shared<JsonStringValue>(std::move(value))), m_valueType(STRING) {}
JsonValue::JsonValue(object &&value)            : m_ptr(std::make_shared<JsonObjectValue>(std::move(value))), m_valueType(OBJECT) {}
JsonValue::JsonValue(array &&value)             : m_ptr(std::make_shared<JsonArrayValue>(std::move(value))), m_valueType(ARRAY) {}

bool JsonValue::isString() const    {return m_valueType == STRING;}
bool JsonValue::isObject() const    {return m_valueType == OBJECT;}
bool JsonValue::isArray() const     {return m_valueType == ARRAY;}

std::string JsonValue::stringValue() const  { return m_ptr->strinValue(); }
object      JsonValue::objectValue() const  { return m_ptr->objectValue(); }
array       JsonValue::arrayValue() const   { return m_ptr->arrayValue(); }

void print(std::ostream &os, const JsonValue &value, size_t tabs)
{
    if(value.isString())
        os << "\"" << value.stringValue() << "\"";

    else if(value.isObject())
    {
        os << "{" << std::endl;

        auto map = value.objectValue();
        for(const auto& pair : map)
        {
            for(size_t i=0; i<(tabs+1); ++i) std::cout << " ";
            os << pair.first << ":";
            print(os, pair.second, tabs+1);
        }

        os << std::endl;
        for(size_t i=0; i<tabs; ++i) std::cout << " ";
        os << "}";
    }
    else if(value.isArray())
    {
        os << "[" << std::endl;

        auto vec = value.arrayValue();
        for(auto it = vec.cbegin(); it!=vec.cend(); ++it)
        {
            for(size_t i=0; i<tabs; ++i) std::cout << "  ";
            print(os, *(it), tabs+1); os << ((it != vec.cend()-1) ? ",\n" : "");
        }

        os << std::endl;
        for(size_t i=0; i<tabs; ++i) std::cout << " ";
        os  << "]";
    }
}
