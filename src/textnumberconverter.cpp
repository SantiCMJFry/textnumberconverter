
#include <iostream>
#include <cstring>
#include <algorithm>

#include <textnumberconverter.hpp>

const char * TextNumberConverter::BILLION = "billion";
const char * TextNumberConverter::MILLION = "million";
const char * TextNumberConverter::THOUSAND = "thousand";
const char * TextNumberConverter::HUNDRED = "hundred";
const char * TextNumberConverter::WHITE_SPACE = " ";
const char * TextNumberConverter::DASH = "-";
const char * TextNumberConverter::AND = "and";
const char * TextNumberConverter::ZERO = "0";

std::unordered_map<std::string, uint8_t> TextNumberConverter::numbersMap = 
{
   {"one", 1},
   {"two", 2},
   {"three", 3},
   {"four", 4},
   {"five", 5},
   {"six", 6},
   {"seven", 7},
   {"eight", 8},
   {"nine", 9},
   {"ten", 10},
   {"eleven", 11},
   {"twelve", 12},
   {"thirteen", 13},
   {"fourteen", 14},
   {"fifteen", 15},
   {"sixteen", 16},
   {"seventeen", 17},
   {"eighteen", 18},
   {"nineteen", 19},
   {"twenty", 20},
   {"thirty", 30},
   {"forty", 40},
   {"fifty", 50},
   {"sixty", 60},
   {"seventy", 70},
   {"eighty", 80},
   {"ninety", 90},
};

std::unordered_map<std::string, uint8_t> TextNumberConverter::specialMap =
{
   {"twenty-", 20},
   {"thirty-", 30},
   {"forty-", 40},
   {"fifty-", 50},
   {"sixty-", 60},
   {"seventy-", 70},
   {"eighty-", 80},
   {"ninety-", 90},
};

std::string TextNumberConverter::textToNumber(const std::string & text)
{
    const size_t INIT_POS = 0;
    size_t endingPos = std::string::npos;
    size_t dashPos = std::string::npos;
    size_t firstNumberPos = std::string::npos;
    size_t lastNumberPos = std::string::npos;
    std::string localText(text + " ");
    std::string wordNumber;
    uint32_t finalNumber = 0;
    uint32_t currentNumber = 0;
    uint32_t specialNumber = 0;
    uint32_t billions = 0;
    uint32_t millions = 0;
    uint32_t thousands = 0;
    bool firstWord = true;
    bool special = false;

    //convert to lowercase
    std::for_each(localText.begin(), localText.end(), [](char &c)
                  { c = ::tolower(c); });

    while (!localText.empty())
    {
        endingPos = localText.find(TextNumberConverter::WHITE_SPACE);
        dashPos = localText.find(TextNumberConverter::DASH);
        if ((endingPos != std::string::npos) && (endingPos != std::string::npos) && (dashPos < endingPos))
        {
            wordNumber = localText.substr(INIT_POS, dashPos + 1);
            localText = localText.substr(dashPos + 1, localText.length());
            if (specialMap.find(wordNumber) != specialMap.end())
            {
            if (std::string::npos == firstNumberPos)
            {
                firstNumberPos = text.find(wordNumber);
                firstWord=false;
            }

                specialNumber = specialMap[wordNumber];
                special = true;
            }
            else
            {
                special = false;
            }
            lastNumberPos+=(dashPos+1);
            continue;
        }

        endingPos = localText.find(TextNumberConverter::WHITE_SPACE);
        if (endingPos != std::string::npos)
        {
            wordNumber = localText.substr(INIT_POS, endingPos);
            localText = localText.substr(endingPos + 1, localText.length());
            if (numbersMap.find(wordNumber) != numbersMap.end())
            {
                if (std::string::npos == firstNumberPos)
                {
                    firstNumberPos = text.find(wordNumber);
                    firstWord=false;
                }

                if (special)
                {
                    currentNumber += numbersMap[wordNumber] + specialNumber;
                }
                else
                {
                    currentNumber += numbersMap[wordNumber];
                }
                special = false;
            }
            else if (TextNumberConverter::BILLION == wordNumber)
            {
                billions = currentNumber * 1000000000;
                currentNumber = 0;
            }
            else if (TextNumberConverter::MILLION == wordNumber)
            {
                millions = currentNumber * 1000000;
                currentNumber = 0;
            }
            else if (TextNumberConverter::THOUSAND == wordNumber)
            {
                thousands = currentNumber * 1000;
                currentNumber = 0;
            }
            else if (TextNumberConverter::HUNDRED == wordNumber)
            {
                currentNumber *= 100;
            }
            else if (TextNumberConverter::AND == wordNumber) {}
            else if (!firstWord)
            {   
                break;
            }
            lastNumberPos+=(endingPos+1);
            continue;
        }
    }

    firstNumberPos = (std::string::npos == firstNumberPos) ? 0 : firstNumberPos;
    lastNumberPos = (std::string::npos == lastNumberPos) ? 0 : lastNumberPos;
    finalNumber=billions+millions+thousands+currentNumber;
    std::string finalString = text.substr(0,firstNumberPos) + std::to_string(finalNumber) +  text.substr(lastNumberPos);

    if (TextNumberConverter::ZERO != finalString)
    {
        finalString = textToNumber(finalString);
    }
    else
    {
        finalString = text;
    }
    return finalString;
}
