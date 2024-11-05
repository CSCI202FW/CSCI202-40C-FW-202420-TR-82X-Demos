#include <iostream>
#include <limits>
#include <cmath>
#include "arrayStack.h"
#include "linkedStack.h"
#include "donut.h"

void resetStream();
void codeGradeLoopFix(std::string errLocation);
long getBinaryNumber();
// for lecture activity modify the binary number conversion code
//  make a function that gets the user input (in string or long form)
// NOTE: if you use strings to get the int value of a character you subtract '0'
// validate the user input (if invalid throw an exception)
// make the userinput into a stack that has the right most digit at the top
// make a second fucntion that does the conversion on lines 41 -47

int main()
{

    long binNum = getBinaryNumber();
    long copyNum = binNum;
    linkedStack<int> binary;
    linkedStack<int> binaryRev;
    while (copyNum > 0)
    {
        int digit = copyNum % 10;
        if (digit != 0 && digit != 1)
        {
            std::cout << "Binary Numbers only have 1s and 0s." << std::endl;
            break;
        }
        binary.push(digit);
        copyNum = copyNum / 10;
    }
    while (!binary.isEmptyStack())
    {
        binaryRev.push(binary.pop());
    }

    int position = 0;
    int decimal = 0;
    while (!binaryRev.isEmptyStack())
    {
        decimal += binaryRev.pop() * pow(2, position);
        position++;
    }
    std::cout << binNum << " is " << decimal << " in decimal." << std::endl;

    try
    {
        Donut d("map", "bacon", "none");
    }
    catch (stackTrace e)
    {
        std::cout << e.what() << std::endl;
        e.push("main donut(\"map\", \"bacon\", \"none\")");
        std::cout << e.printTrace() << std::endl;
    }

    return 0;
}

long getBinaryNumber()
{
    long x;
    std::cout << "Enter a number in binary: ";
    std::cin >> x;
    while (!std::cin || x < 0)
    {
        if (!std::cin)
            resetStream();
        std::cout << "Enter a number in binary: ";
        std::cin >> x;
    }
    return x;
}
void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "You did not enter a number." << std::endl;
}

void codeGradeLoopFix(std::string errLocation)
{
    if (std::cin.eof())
    {
        std::cout << "There was a problem and there is no more input! @" + errLocation << std::endl;
        throw std::invalid_argument(errLocation); // return or throw an exception here to force the program to end or return from the function.
    }
}