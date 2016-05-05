#include "JsonPath.h"
#include <json-c/json.h>
#include <string>
#include <iostream>
#include <queue>

struct JsonPath::Pimpl {
    std::string currentValue;
    json_object* m_pJobj; //base json file
    json_object* m_pJCurrentObj; //current json object being interogated
};

JsonPath::JsonPath()
{
}

JsonPath::JsonPath(const std::string& json) : m_pimpl(new Pimpl())
{
    m_pimpl->m_pJobj = json_tokener_parse(json.c_str());
}

JsonPath& JsonPath::getItem(std::string path)
{
    //extract path in a queue
    std::queue<std::string> pathQueue;
    size_t pos = 0;
    size_t newPos = 0;
    while( (newPos = path.find(".", pos) ) != std::string::npos){
        std::string item = path.substr(pos, newPos);
        pathQueue.push(item);
        pos = newPos+1;
    }

    //get the item in the path
    return *this;
}

std::string JsonPath::stringValue()
{
    return "";
}
