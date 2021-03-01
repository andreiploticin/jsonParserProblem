#ifndef JsonAbstractValue_H
#define JsonAbstractValue_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>

class JsonValue;
class JsonBaseValue;

using object = std::map<std::string, JsonValue>;
using array = std::vector<JsonValue>;

class JsonValue
{
public:
    enum ValueType {NONE, STRING, OBJECT, ARRAY};
    JsonValue() = default;
    JsonValue(const JsonValue &other) = default;
    JsonValue(JsonValue &&other) = default;

    JsonValue(const std::string &value);
    JsonValue(std::string &&value);
    JsonValue(const object &value);
    JsonValue(object &&value);
    JsonValue(const array &value);
    JsonValue(array &&value);
    bool isString() const;
    bool isObject() const;
    bool isArray() const;
    std::string stringValue() const;
    object objectValue() const;
    array arrayValue() const;
    inline ValueType getType() const {return m_valueType;}

private:
    std::shared_ptr<JsonBaseValue> m_ptr;
    ValueType m_valueType = NONE;
};

class JsonBaseValue
{
    friend class JsonValue;
protected:
    virtual const std::string& strinValue() const;
    virtual const object& objectValue() const;
    virtual const array& arrayValue() const;
    virtual ~JsonBaseValue() {}
};


struct staticValuesStruct
{
    std::string stringValue;
    object objectValue;
    array arrayValue;
    JsonValue emptyValue;
};

extern staticValuesStruct svs;

class JsonStringValue final : public JsonBaseValue
{
public:
    JsonStringValue(const std::string &value) : m_value(value) {}
    virtual const std::string& strinValue() const override;
private:
    std::string m_value;
};

class JsonObjectValue final : public JsonBaseValue
{
public:
    JsonObjectValue(const object &value) : m_value(value) {}
    virtual const object& objectValue() const override;
private:
    object m_value;
};

class JsonArrayValue final : public JsonBaseValue
{
public:
    JsonArrayValue(const array &value) : m_value(value) {}
    virtual const array& arrayValue() const override;
private:
    array m_value;
};


#endif // JsonAbstractValue_H
