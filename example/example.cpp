#include "../src/jsonparser.h"

int main()
{
    JsonParser parser(std::cin);
    print(std::cout, parser.parse());
    return 0;
}
