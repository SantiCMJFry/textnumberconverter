# textnumberconverter
Author: Santiago Carmona Meco

Brief: Little library which converts written numbers in words to digits in the middle .

-----------------------------
Library
- src/textnumberconverter.hpp
- include/textnumberconverter.cpp

Tests
- src/test.cpp -> Tests (Binary:textNumberConverter_test)
- src/main.cpp -> Application which requests to enter texts and converts them using the library

GCOV coverage report
- textNumberConverter_coverage/index.html

How to compile (From the root):

$mkdir build

$cd build

$cmake ..

$make

How to compile to get GCOV coverage information:

$cmake -DCOVERAGE=ON ..

$make textNumberConverter_coverate







