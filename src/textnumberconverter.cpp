
#include <iostream>
#include <cstring>
#include <algorithm>
#include <array>

#include <textnumberconverter.hpp>

// Initialization of static members

const char *TextNumberConverter::BILLION = "billion";
const char *TextNumberConverter::MILLION = "million";
const char *TextNumberConverter::THOUSAND = "thousand";
const char *TextNumberConverter::HUNDRED = "hundred";
const char *TextNumberConverter::WHITE_SPACE = " ";
const char *TextNumberConverter::DASH = "-";
const char *TextNumberConverter::AND = "and";
const char *TextNumberConverter::ZERO = "0";

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

bool TextNumberConverter::textToNumber(const std::string &text, std::string &textConverted)
{
    bool ret = true;
    const size_t INIT_POS = 0;
    const std::array<char, 9> symbols = {',', '.', ';', ':', '!', '?', ')', '|', '/'};
    size_t endingPos = std::string::npos;
    size_t dashPos = std::string::npos;
    size_t firstNumberPos = std::string::npos;
    size_t lastNumberPos = std::string::npos;
    size_t symbolPos = std::string::npos;
    std::string localText(text + " ");
    std::string iterateText(text + " ");
    std::string wordNumber;
    std::string finalString;
    uint32_t finalNumber = 0;
    uint32_t currentNumber = 0;
    uint32_t specialNumber = 0;
    uint32_t billions = 0;
    uint32_t millions = 0;
    uint32_t thousands = 0;
    bool firstWord = true;
    bool special = false;

    //convert the text to lowercase
    std::transform(localText.begin(), localText.end(), localText.begin(), ::tolower);

    iterateText=localText;

    //Iterate the whole text
    while (!iterateText.empty())
    {
        endingPos = iterateText.find(TextNumberConverter::WHITE_SPACE);
        dashPos = iterateText.find(TextNumberConverter::DASH);

        //First check if we have a special case (cases like twenty-one, thirty-two... etc)
        if ((endingPos != std::string::npos) && (endingPos != std::string::npos) && (dashPos < endingPos))
        {
            wordNumber = iterateText.substr(INIT_POS, dashPos + 1);
            iterateText = iterateText.substr(dashPos + 1, iterateText.length());
            if (specialMap.find(wordNumber) != specialMap.end())
            {
                if (std::string::npos == firstNumberPos)
                {
                    firstNumberPos = localText.find(wordNumber);
                    firstWord = false;
                }

                specialNumber = specialMap[wordNumber];
                special = true;
            }
            else
            {
                special = false;
            }
            lastNumberPos += (dashPos + 1);
            continue;
        }

        endingPos = iterateText.find(TextNumberConverter::WHITE_SPACE);

        //Check special symbols (',','.',';',':','!','?',')','|','/')
        symbolPos = std::string::npos;
        for (uint8_t i = 0; i < symbols.size(); i++)
        {
            size_t symbolPosAux = iterateText.find(symbols[i]);

            if ((std::string::npos != symbolPosAux) && (symbolPosAux < endingPos))
            {
                if ((std::string::npos == symbolPos) || (symbolPosAux < symbolPos))
                {
                    symbolPos = symbolPosAux;
                }
            }
        }
        if ((std::string::npos != symbolPos) && (symbolPos < endingPos))
        {
            if (endingPos != symbolPos + 1)
            {
                //Bad format detected, there is no whitespace after the detected number
                return false;
            }
            endingPos = symbolPos;
        }

        //Get numbers
        if (endingPos != std::string::npos)
        {
            wordNumber = iterateText.substr(INIT_POS, endingPos);
            iterateText = iterateText.substr(endingPos + 1, iterateText.length());

            if (numbersMap.find(wordNumber) != numbersMap.end())
            {
                if (std::string::npos == firstNumberPos)
                {
                    firstNumberPos = localText.find(wordNumber);
                    firstWord = false;
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
            else if (TextNumberConverter::AND == wordNumber)
            {
            }
            else if (!firstWord)
            {
                break;
            }

            lastNumberPos += (endingPos + 1);
            continue;
        }
    }

    firstNumberPos = (std::string::npos == firstNumberPos) ? 0 : firstNumberPos;
    lastNumberPos = (std::string::npos == lastNumberPos) ? 0 : lastNumberPos;
    finalNumber = billions + millions + thousands + currentNumber;

    finalString = text.substr(0, firstNumberPos) + std::to_string(finalNumber) + text.substr(lastNumberPos);

    //if there is more text to analyze call the same function recursively
    if (TextNumberConverter::ZERO != finalString)
    {
        ret = textToNumber(finalString, textConverted);
    }
    else
    {
        textConverted = text;
    }

    return ret;
}
