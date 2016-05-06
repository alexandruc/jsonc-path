#include "JsonPath.h"
#include <cstring>
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

JsonPath::~JsonPath()
{
    json_object_put(m_pimpl->m_pJobj);
    delete m_pimpl;
}

JsonPath::JsonPath(const std::string& json) : m_pimpl(new Pimpl())
{
    m_pimpl->m_pJobj = json_tokener_parse(json.c_str());
}

namespace {

void parseJsonObject(json_object * jobj, const std::string& item, json_object*& currentObj) {

    json_object_object_foreach(jobj, key, val) {
        std::string strKey(key);
        if(strKey != item ){
            continue; //go to the next key, we don't need this one
        }
        else{
            //we found our json object for this item, keep a reference in order to extract a value, or
            currentObj = val;
            break;
        }
    }
}

void getReferenceToCurrentKey(json_object* jobjToSearch, const std::string& keyToSearch, json_object*& jobjFound){
    json_type type = json_object_get_type(jobjToSearch);
    if(type == json_type_object){
        parseJsonObject(jobjToSearch, keyToSearch, jobjFound);
    }
    else{
        switch(type) {
        case json_type_boolean:
        case json_type_double:
        case json_type_int:
        case json_type_string:
        case json_type_array: {
            jobjFound = jobjToSearch; //only 1 obj -> has the value we need
            break;
        }
        default: break;
        }
    }
}

}//namespace

JsonPath& JsonPath::getItem(const std::string& path)
{
    //extract path in a queue
    std::queue<std::string> pathQueue;
    size_t pos = 0;
    size_t newPos = 0;
    while( (newPos = path.find(".", pos) ) != std::string::npos){
        std::string item = path.substr(pos, newPos-pos);
        pathQueue.push(item);
        pos = newPos+1;
    }
    std::string lastItem = path.substr(pos);
    pathQueue.push(lastItem);

    //get the item in the path
    while(!pathQueue.empty()){
        std::string currentKey = pathQueue.front();
        pathQueue.pop();

        if( NULL == m_pimpl->m_pJCurrentObj &&
                NULL != m_pimpl->m_pJobj &&
                false == currentKey.empty()){
            getReferenceToCurrentKey(m_pimpl->m_pJobj, currentKey, m_pimpl->m_pJCurrentObj);
        }
        else if( NULL != m_pimpl->m_pJCurrentObj &&
                 false == currentKey.empty()){
            getReferenceToCurrentKey(m_pimpl->m_pJCurrentObj, currentKey, m_pimpl->m_pJCurrentObj);
        }
    }

    return *this;
}

std::string JsonPath::stringValue()
{
    std::string strValue = "";
    if(m_pimpl->m_pJCurrentObj != NULL){
        json_type type = json_object_get_type(m_pimpl->m_pJCurrentObj);

        switch(type) {
        case json_type_boolean: {
            strValue = (0 == json_object_get_boolean(m_pimpl->m_pJCurrentObj)) ? "false" : "true";
            break;
        }
        case json_type_double:{
            double num = json_object_get_double(m_pimpl->m_pJCurrentObj);
            char buffer[128];
            memset(buffer, 0, 128*sizeof(char));
            sprintf(buffer,"%f", num);
            strValue = buffer;
        }
        case json_type_int:{
            int num = json_object_get_int(m_pimpl->m_pJCurrentObj);
            char buffer[128];
            memset(buffer, 0, 128*sizeof(char));
            sprintf(buffer,"%d", num);
            strValue = buffer;
            break;
        }
        case json_type_string: {
            const char* str = json_object_get_string(m_pimpl->m_pJCurrentObj);
            strValue = str;
            break;
        }
        case json_type_object:
        case json_type_array:{
            strValue = json_object_to_json_string(m_pimpl->m_pJCurrentObj);
            break;
        }
        default: break;
        }
    }
    return strValue;
}

JsonPath& JsonPath::at(unsigned int position)
{
    json_object* pJObj = NULL;
    //we're in the root
    if(NULL == m_pimpl->m_pJCurrentObj){
        pJObj = m_pimpl->m_pJobj;
    }
    else { //we're in a node in the json
        pJObj = m_pimpl->m_pJCurrentObj;
    }

    m_pimpl->m_pJCurrentObj = json_object_array_get_idx(pJObj, position);

    return *this;
}

void JsonPath::clear()
{
    //clear old data
    m_pimpl->m_pJCurrentObj = NULL;
}
