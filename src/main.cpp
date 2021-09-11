
#include <iostream>
#include <cstring>
#include <algorithm>

#include <textnumberconverter.hpp>


int main()
{
    std::string input;
    std::cout << "Enter a text ";
    getline(std::cin, input);

    std::string finalString = TextNumberConverter::textToNumber(input);

    std::cout << "final text:\n" << finalString << std::endl;

    return 0;
}
