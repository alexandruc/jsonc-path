#ifndef JSONPATH_H
#define JSONPATH_H

#include <string>

class JsonPath
{
public:
    explicit JsonPath(const std::string& json);
    ~JsonPath();

    JsonPath& getItem(std::string path);

    std::string stringValue();
private:
    JsonPath();

    struct Pimpl;
    Pimpl* m_pimpl;
};

#endif // JSONPATH_H
