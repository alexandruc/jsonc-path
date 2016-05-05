#include <iostream>
#include "JsonPath.h"

int main()
{
    std::string json = "{\"id\" : 1}";
    JsonPath jpath(json);
    jpath.getItem("id.test.name");
    return 0;
}
