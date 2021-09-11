
#include <iostream>
#include <cstring>
#include <algorithm>

#include <textnumberconverter.hpp>


#define ASSERT_EQUAL(original, expectedText, generatedText)   \
        do {                                        \
            if (expectedText == generatedText)        \
            { \
               std::cout << "STEP OK: \noriginal: " << original << "\nexpected: " << expectedText << "\ngenerated: " << generatedText << std::endl; \
            }\
            else \
            {                                         \
               std::cout << "STEP ERROR\nexpected: " << expectedText << "\ngenerated: " << generatedText << std::endl; \
               exit(1) ;  \
            }                             \
        } while(0)

int main()
{

    std::string input1("two hundred thirty-three thousand four hundred fifty");
    std::string generated1 = TextNumberConverter::textToNumber(input1);
    ASSERT_EQUAL(input1,"233450", generated1);

    std::string input2("five hundred forty-five million one hundred fifty-six thousand three hundred forty-one");
    std::string generated2 = TextNumberConverter::textToNumber(input2);
    ASSERT_EQUAL(input2,"545156341", generated2);

    std::string input3("I'll give you one billion five hundred forty-five million one hundred fifty-six thousand dollars for this bank; If you don't accept, then you will pay me five hundred million each month");
    std::string generated3 = TextNumberConverter::textToNumber(input3);
    ASSERT_EQUAL(input3,"I'll give you 1545156000 dollars for this bank; If you don't accept, then you will pay me 500000000 each month", generated3);



    std::cout << "TEST OK" << std::endl;

    return 0;
}
