
#include <unordered_map>
#include <string>

class TextNumberConverter
{

protected:
    static const char * BILLION;
    static const char * MILLION;
    static const char * THOUSAND;
    static const char * HUNDRED;
    static const char * WHITE_SPACE;
    static const char * DASH;
    static const char * AND;
    static const char * ZERO;

    static std::unordered_map<std::string, uint8_t> numbersMap;
    static std::unordered_map<std::string, uint8_t> specialMap;

public:
    static std::string textToNumber(const std::string &text);
};