#ifndef JsonBaseValue_H
#define JsonBaseValue_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>

class JsonValue;
class JsonBaseValue;

// Класс непосредственных элементов упрощённой грамматики JSON
// с которыми может работать пользователь
class JsonValue
{
public:
    enum ValueType {NONE, STRING, OBJECT, ARRAY};
    JsonValue() = default;
    JsonValue(const JsonValue &other) = default;
    JsonValue(JsonValue &&other) = default;

    JsonValue(const std::string &value);
    JsonValue(std::string &&value);
    JsonValue(const std::map<std::string, JsonValue> &value);
    JsonValue(std::map<std::string, JsonValue> &&value);
    JsonValue(const std::vector<JsonValue> &value);
    JsonValue(std::vector<JsonValue> &&value);
    bool isString() const;
    bool isObject() const;
    bool isArray() const;
    const std::string& stringValue() const;
    const std::map<std::string, JsonValue>& objectValue() const;
    const std::vector<JsonValue>& arrayValue() const;
    const JsonValue& operator[](size_t index) const;
    const JsonValue& operator[](const std::string& name) const;
    inline ValueType getType() const {return m_valueType;}

private:
    std::shared_ptr<JsonBaseValue> m_ptr;
    ValueType m_valueType = NONE;
};

struct EmptyValues
{
    std::string stringValue;
    std::map<std::string, JsonValue> objectValue;
    std::vector<JsonValue> arrayValue;
    JsonValue emptyValue;
};

static const EmptyValues& getEmpties()
{
    static const EmptyValues e;
    return e;
}

//Базовый класс иерархии возможных значений ~= JSON value
class JsonBaseValue
{
    friend class JsonValue;
protected:
    virtual const std::string& strinValue() const;
    virtual const std::map<std::string, JsonValue>& objectValue() const;
    virtual const std::vector<JsonValue>& arrayValue() const;
    virtual ~JsonBaseValue() {}
};

// Класс строк JSON string
class JsonStringValue final : public JsonBaseValue
{
public:
    JsonStringValue(const std::string &value) : m_value(value) {}
    virtual const std::string& strinValue() const override;
private:
    std::string m_value;
};

// Класс объектов (асс. массивов) JSON object
class JsonObjectValue final : public JsonBaseValue
{
public:
    JsonObjectValue(const std::map<std::string, JsonValue> &value) : m_value(value) {}
    virtual const std::map<std::string, JsonValue>& objectValue() const override;
private:
    std::map<std::string, JsonValue> m_value;
};

// Класс массивов JSON array
class JsonArrayValue final : public JsonBaseValue
{
public:
    JsonArrayValue(const std::vector<JsonValue> &value) : m_value(value) {}
    virtual const std::vector<JsonValue>& arrayValue() const override;
private:
    std::vector<JsonValue> m_value;
};


#endif // JsonBaseValue_H
