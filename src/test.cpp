
#include <iostream>
#include <cstring>
#include <algorithm>
#include <textnumberconverter.hpp>

#define ASSERT_EQUAL(expected, value)   \
        do {                                        \
            if (expected != value)        \
            { \
                std::cout << "Expected " << expected << " value " << value << std::endl; \
                exit(1) ;  \
            }                             \
            std::cout << "----------------------------------------------------------------------------------" << std::endl; \
        } while(0)


#define CHECK_STEP(original, expectedText, generatedText)   \
        do {                                        \
            if (expectedText == generatedText)        \
            { \
               std::cout << "STEP OK: \noriginal: " << original << "\nexpected: " << expectedText << "\ngenerated: " << generatedText << std::endl; \
            }\
            else \
            {                                         \
               std::cout << "STEP ERROR (line "<<__LINE__<<"): \nexpected: " << expectedText << "\ngenerated: " << generatedText << std::endl; \
               exit(1) ;  \
            }                             \
            std::cout << "----------------------------------------------------------------------------------" << std::endl; \
        } while(0)

int main()
{

    //Test 1
    {
        std::string input("Hello one hundred twenty-three million four hundred fifty-six thousand seven hundred eighty-nine; How are you nine hundred eighty-seven million six hundred fifty-four thousand three hundred twenty-one");
        std::string generated;
        bool ret = TextNumberConverter::textToNumber(input, generated);
        ASSERT_EQUAL(true, ret);
        CHECK_STEP(input, "Hello 123456789; How are you 987654321", generated);
    }

    {
        std::string input("one hundred eleven million one hundred eleven thousand one hundred eleven. "
                          "two hundred twenty-two million two hundred twenty-two thousand two hundred twenty-two, "
                          "three hundred thirty-three million three hundred thirty-three thousand three hundred thirty-three; "
                          "four hundred forty-four million four hundred forty-four thousand four hundred forty-four: "
                          "five hundred fifty-five million five hundred fifty-five thousand five hundred fifty-five! "
                          "six hundred sixty-six million six hundred sixty-six thousand six hundred sixty-six? "
                          "seven hundred seventy-seven million seven hundred seventy-seven thousand seven hundred seventy-seven) "
                          "eight hundred eighty-eight million eight hundred eighty-eight thousand eight hundred eighty-eight| "
                          "nine hundred ninety-nine million nine hundred ninety-nine thousand nine hundred ninety-nine/");
        std::string generated;
        bool ret = TextNumberConverter::textToNumber(input, generated);
        ASSERT_EQUAL(true, ret);
        CHECK_STEP(input, "111111111. 222222222, 333333333; 444444444: 555555555! 666666666? 777777777) 888888888| 999999999/", generated);
    }

    {
        std::string input("I'll give you one billion five hundred forty-five million one hundred fifty-six thousand dollars for this bank; If you don't accept, then you will pay me five hundred million every month");
        std::string generated;
        bool ret = TextNumberConverter::textToNumber(input, generated);

        ASSERT_EQUAL(true, ret);
        CHECK_STEP(input, "I'll give you 1545156000 dollars for this bank; If you don't accept, then you will pay me 500000000 every month", generated);
    }

    {
        std::string input("The secret code is one hundred million two hundred and thirty thousand four hundred and ninety-five, don't forget it or we will lose the one billion nine hundred and fifty-two million three hundred and forty thousand three hundred and fifty-two euros.");
        std::string generated;
        bool ret = TextNumberConverter::textToNumber(input, generated);

        ASSERT_EQUAL(true, ret);
        CHECK_STEP(input, "The secret code is 100230495, don't forget it or we will lose the 1952340352 euros.", generated);
    }

    std::cout << "TEST OK" << std::endl;

    return 0;
}
