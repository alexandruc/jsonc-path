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

    std::string data;
    if(false == loadFile(testFile, data)){
        return 1;
    }

    JsonPath jpath(data);
    std::cout << "parents: " << jpath.getItem("parents").stringValue() << std::endl;
    jpath.clear();
    std::cout << "parents[0].kind: " << jpath.getItem("parents").at(0).getItem("kind").stringValue() << std::endl;
    jpath.clear();
    std::cout << "parents[0].isRoot: " << jpath.getItem("parents").at(0).getItem("isRoot").stringValue() << std::endl;
    jpath.clear();
    std::cout << "parents[1].isRoot: " << jpath.getItem("parents").at(1).getItem("isRoot").stringValue() << std::endl;
    jpath.clear();
    std::cout << "parents[0].NotExisting: " << jpath.getItem("parents").at(0).getItem("NotExisting").stringValue() << std::endl;
    jpath.clear();
    std::cout << "owners[0].picture.url: " << jpath.getItem("owners").at(0).getItem("picture.url").stringValue() << std::endl;
    jpath.clear();
    std::cout << "spaces: " << jpath.getItem("spaces").at(0).stringValue() << std::endl;
    jpath.clear();
    std::cout << "userPermission: " << jpath.getItem("userPermission").stringValue() << std::endl;
    return 0;
}
