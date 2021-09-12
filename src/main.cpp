
#include <iostream>
#include <cstring>
#include <algorithm>

#include <textnumberconverter.hpp>



int main()
{
    while (1)
    {
        std::string input;
        std::string generatedText;
        std::cout << "Enter a text ";
        getline(std::cin, input);
        if (TextNumberConverter::textToNumber(input, generatedText))
        {
            std::cout << generatedText << std::endl;
        }
        else
        {
            std::cout << "Bad format detected" << std::endl;
        }
    }
    return 0;
}
