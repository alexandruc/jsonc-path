#ifndef JSONPATH_H
#define JSONPATH_H

#include <string>

class JsonPath
{
public:
    explicit JsonPath(const std::string& json);
    ~JsonPath();

    /**
     * @brief Searches item with the given path (user.name.firstname)
     * @param path Path inside json file. Path is composed by json keys separated by the dot (.) character
     * @return A JsonPath reference to the current object
     */
    JsonPath& getItem(const std::string& path);

    /**
     * @brief Used on json array types to select an object item in the array
     * @param position 0-based index in the array
     * @return A JsonPath reference to the current object
     */
    JsonPath& at(unsigned int position);

    /**
     * @brief Gets the string value of the current key in selected by the getItem method
     * @return String value of the element selected
     */
    std::string stringValue();

    void clear();
private:
    JsonPath();

    struct Pimpl;
    Pimpl* m_pimpl;
};

#endif // JSONPATH_H
