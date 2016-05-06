#include <iostream>
#include "JsonPath.h"

int main()
{
    std::string json = "{\"id\" : 1}";
    JsonPath jpath(json);
    std::cout << jpath.getItem("id").stringValue() << std::endl;
    return 0;
}
