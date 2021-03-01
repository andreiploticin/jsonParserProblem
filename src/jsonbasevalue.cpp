#include "jsonbasevalue.h"
#include <memory>

EmptyValues emptyValues;

const std::string                       &JsonBaseValue::strinValue() const  { return emptyValues.stringValue; }
const std::map<std::string, JsonValue>  &JsonBaseValue::objectValue() const { return emptyValues.objectValue; }
const std::vector<JsonValue>            &JsonBaseValue::arrayValue() const  { return emptyValues.arrayValue; }

const std::string                       &JsonStringValue::strinValue()  const { return m_value; }
const std::map<std::string, JsonValue>  &JsonObjectValue::objectValue() const { return m_value; }
const std::vector<JsonValue>            &JsonArrayValue::arrayValue() const   { return m_value; }

JsonValue::JsonValue(const std::string &value)                      : m_ptr(std::make_shared<JsonStringValue>(value)), m_valueType(STRING) {}
JsonValue::JsonValue(const std::map<std::string, JsonValue> &value) : m_ptr(std::make_shared<JsonObjectValue>(value)), m_valueType(OBJECT) {}
JsonValue::JsonValue(const std::vector<JsonValue> &value)           : m_ptr(std::make_shared<JsonArrayValue>(value)), m_valueType(ARRAY) {}

JsonValue::JsonValue(std::string &&value)                           : m_ptr(std::make_shared<JsonStringValue>(std::move(value))), m_valueType(STRING) {}
JsonValue::JsonValue(std::map<std::string, JsonValue> &&value)      : m_ptr(std::make_shared<JsonObjectValue>(std::move(value))), m_valueType(OBJECT) {}
JsonValue::JsonValue(std::vector<JsonValue> &&value)                : m_ptr(std::make_shared<JsonArrayValue>(std::move(value))), m_valueType(ARRAY) {}

bool JsonValue::isString() const    {return m_valueType == STRING;}
bool JsonValue::isObject() const    {return m_valueType == OBJECT;}
bool JsonValue::isArray() const     {return m_valueType == ARRAY;}

const std::string                         JsonValue::stringValue() const  { return m_ptr->strinValue(); }
const std::map<std::string, JsonValue>    JsonValue::objectValue() const  { return m_ptr->objectValue(); }
const std::vector<JsonValue>              JsonValue::arrayValue() const   { return m_ptr->arrayValue(); }
