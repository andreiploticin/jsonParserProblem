#include "../src/jsonparser.h"
#include "../src/jsonbasevalue.h"

void print(std::ostream &os, const JsonValue &value, size_t tabs=0)
{
    if(value.isString())
        os << "\"" << value.stringValue() << "\"";

    else if(value.isObject())
    {

        auto map = value.objectValue();
        os << "{";
        if(map.size()>0) os << std::endl;

        auto itBefEnd = --map.end();
        for(auto it = map.cbegin(); it!=map.cend(); ++it)
        {
            for(size_t i=0; i<(tabs+1); ++i) std::cout << " ";
            os << it->first << ":";
            print(os, it->second, tabs+1);
            os << ((it != itBefEnd) ? ",\n" : "");
        }

        os << std::endl;
        for(size_t i=0; i<tabs; ++i) std::cout << " ";
        os << "}";
    }
    else if(value.isArray())
    {
        os << "[";

        auto vec = value.arrayValue();
        if(vec.size()>0) os << std::endl;
        for(auto it = vec.cbegin(); it!=vec.cend(); ++it)
        {
            for(size_t i=0; i<tabs+1; ++i) std::cout << " ";
            print(os, *(it), tabs+1); os << ((it != vec.cend()-1) ? ",\n" : "");
        }

        os << std::endl;
        for(size_t i=0; i<tabs; ++i) std::cout << " ";
        os  << "]";
    }
}

int main()
{
    JsonParser parser1("{\"name\\1\":\t\r\n[\"a1\", \"a2\", {\"name2\":\"value1/'\", \"name3\":\"value2\"}]}");
    auto result = parser1.parse();
    print(std::cout, result); std::cout << std::endl;

    std::cout << result["name1"][2]["name3"].stringValue() << std::endl;

    JsonParser parser2(std::cin);
    print(std::cout, parser2.parse());
    std::cout << std::endl;

    char c; std::cin >> c;
    return 0;
}
