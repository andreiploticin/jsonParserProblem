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
