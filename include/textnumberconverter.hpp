
#include <unordered_map>
#include <string>

class TextNumberConverter
{
protected:

    //Constants 
    static const char * BILLION;
    static const char * MILLION;
    static const char * THOUSAND;
    static const char * HUNDRED;
    static const char * WHITE_SPACE;
    static const char * DASH;
    static const char * AND;
    static const char * ZERO;

    //Internal containers
    static std::unordered_map<std::string, uint8_t> numbersMap;
    static std::unordered_map<std::string, uint8_t> specialMap;

public:
    /**
     * \brief This function converts all the written numbers in words to digits in the middle of a paragraph.
     * \details Numbers which are not separated by at least a whitespace (for example: "eleven,twelve") will be considered as a format error
     * \param[in] text The text to convert
     * \param[out] textConverted user string where the converted text will be returned
     * \return true if everything was OK, false if a format error was found
     */
    static bool textToNumber(const std::string &text, std::string & textConverted);
};