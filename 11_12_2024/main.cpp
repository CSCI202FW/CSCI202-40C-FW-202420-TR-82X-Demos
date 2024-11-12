#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <climits>

void resetStream();
int factorial(int);

int main()
{
    factorial(7);
    return 0;
}

int factorial(int n)
{
    if (n == 0)
    {
        return 1;
    }
    else
    {
        return n * factorial(n - 1);
    }
}

void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "You did not enter a number." << std::endl;
}