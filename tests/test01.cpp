#include "gtest/gtest.h"
#include "../src/jsonparser.h"
#include <fstream>

TEST(ParserTests, Empty)
{
    JsonParser parser("");
    auto result = parser.parse();
    ASSERT_EQ(result.getType(), JsonValue::NONE);
    ASSERT_TRUE(parser.isError());
}

TEST(ParserTests, EmptyString)
{
    JsonParser parser("\"\"");
    auto result = parser.parse();
    ASSERT_EQ(result.getType(), JsonValue::STRING);
    ASSERT_EQ(result.stringValue(), "");
    ASSERT_FALSE(parser.isError());
}

TEST(ParserTests, ArrayWithEmptyString)
{
    JsonParser parser("[\"\"]");
    auto result = parser.parse();
    ASSERT_EQ(result[0].stringValue(), "");
    ASSERT_FALSE(parser.isError());
}

TEST(ParserTests, EmptyObject)
{
    JsonParser parser("{}");
    auto result = parser.parse();
    ASSERT_EQ(result.getType(), JsonValue::OBJECT);
    ASSERT_FALSE(parser.isError());
}

TEST(ParserTests, OneRecord)
{
    std::string str = "{\"name\":\"value\"}";
    JsonParser parser(str);
    auto result = parser.parse();
    ASSERT_EQ(result.getType(), JsonValue::OBJECT);
    ASSERT_EQ(result.objectValue().size(), 1);
    ASSERT_EQ(result.objectValue().cbegin()->first, "name");
    ASSERT_EQ(result.objectValue().cbegin()->second.getType(), JsonValue::STRING);
    ASSERT_EQ(result.objectValue().cbegin()->second.stringValue(), "value");
    ASSERT_FALSE(parser.isError());
}

TEST(ParserTests, RecordWithoutValue)
{
    std::string str = "{\"name\":}";
    JsonParser parser(str);
    auto result = parser.parse();
    ASSERT_TRUE(parser.isError());
}

TEST(ParserTests, proposedValue)
{
    std::string str =
            "{"
            "   \"firstName\": \"Иван\","
            "   \"lastName\": \" Иванов \","
            "   \"address\": {"
            "       \"streetAddress\": \" Московское ш ., 101, кв . 101\","
            "       \"city\": \"Ленинград\","
            "   },"
            "   \"phoneNumbers\": ["
            "       \"812 123-1234\","
            "       \"916 123-4567\""
            "   ]"
            "}";

    JsonParser parser(str);
    auto result = parser.parse();
    ASSERT_TRUE(parser.isError());
}

TEST(ParserTests, ProposedValueWithoutErrors)
{
    std::string str =
            "{"
            "   \"firstName\": \"Иван\","
            "   \"lastName\": \" Иванов \","
            "   \"address\": {"
            "       \"streetAddress\": \" Московское ш ., 101, кв . 101\","
            "       \"city\": \"Ленинград\""
            "   },"
            "   \"phoneNumbers\": ["
            "       \"812 123-1234\","
            "       \"916 123-4567\""
            "   ]"
            "}";

    JsonParser parser(str);
    auto result = parser.parse();
    ASSERT_FALSE(parser.isError());
}


TEST(ParserTests, Empties)
{
    std::string str = "[[[[{},{}],{},{},[[[]]]]]]";
    JsonParser parser(str);
    auto result = parser.parse();
    ASSERT_FALSE(parser.isError());
}



TEST(ParserTests, IndexOperatorOfArrayValue)
{
    std::string str = "[\"name1\", \"name2\", \"name3\"]";
    JsonParser parser(str);
    auto result = parser.parse();
    ASSERT_EQ(result[2].stringValue(), "name3");
}


TEST(ParserTests, ReadFromFile)
{
    std::ifstream ifs("test.json", std::ios::in);
    ASSERT_TRUE(ifs.is_open());
    JsonParser parser(ifs);
    auto result = parser.parse();
    ASSERT_FALSE(parser.isError());
}

