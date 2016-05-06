#include <iostream>
#include "JsonPath.h"

#include <fstream>

static bool loadFile(const std::string& file, std::string& data){
    std::fstream f(file);
    data.clear();
    if(f.is_open()){
        std::string line;
        while( std::getline(f, line)){
            data += line;
        }

        f.close();
    }
    else{
        std::cout << "Failed to load json file: " << file << std::endl;
        return false;
    }
    return true;
}

int main()
{
    std::string testFile = "../testdata/existing_key.json";

//    std::string json = "{\"id\" : 1}";
    std::string data;
    if(false == loadFile(testFile, data)){
        return 1;
    }

    JsonPath jpath(data);
    std::cout << "found data: " << jpath.getItem("parents.kind").stringValue() << std::endl;
    return 0;
}
