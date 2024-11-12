#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
#include <climits>

// lecture activity. take iterative fibonacci number code from page 296 of the book
//  implement as a function
//  compare to the recursive version
//  which would you choose.

void resetStream();
int factorial(int);
template <class t>
t getNum(std::string, bool (*validFunc)(t, t, t), t = 0, t = 0);
template <class t>
bool numInRange(t, t, t);
template <class t>
bool numGT0(t, t = 0, t = 0);
long fibNum(long f[], long n);
void moveDisks(int, char source, char destination, char spare);

int main()
{
    int x = getNum<int>("Enter a number greater than 0: ", numGT0<int>);
    factorial(x);
    long fibNum1, fibNum2;
    long nthFibonacci;
    fibNum1 = getNum<long>("Enter the first Fibonacci Number: ", numGT0<long>);
    fibNum2 = getNum<long>("Enter the second Fibonacci number: ", numInRange<long>, fibNum1, fibNum1 + 100l);
    nthFibonacci = getNum("Enter the position of the desired Fibonacci number: ", numGT0, 0);
    long *fibseq = new long[nthFibonacci];
    for (int i = 0; i < nthFibonacci; i++)
    {
        fibseq[i] = -1;
    }
    fibseq[0] = fibNum1;
    fibseq[1] = fibNum2;
    std::cout << "The " << nthFibonacci << " th Fibonacci number is " << fibNum(fibseq, nthFibonacci);

    moveDisks(3, 'A', 'B', 'C');

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

long fibNum(long f[], long n)
{
    if (f[n - 1] != -1)
    {
        return f[n - 1];
    }
    f[n - 1] = fibNum(f, n - 1) + fibNum(f, n - 2);
    return f[n - 1];
}

void moveDisks(int count, char source, char destination, char spare)
{
    if (count > 0)
    {
        moveDisks(count - 1, source, spare, destination);
        std::cout << "Move disk " << count << " from " << source << " to " << destination << "." << std::endl;
        moveDisks(count - 1, spare, destination, source);
    }
}

void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "You did not enter a number." << std::endl;
}

template <class t>
t getNum(std::string prompt, bool (*validFunc)(t, t, t), t lower, t upper)
{
    t inputNum;
    std::cout << prompt;
    std::cin >> inputNum;
    std::cout << std::endl;
    if (!std::cin)
    {
        resetStream();
        return getNum(prompt, validFunc, lower, upper);
    }
    if (!validFunc(inputNum, lower, upper))
    {
        std::cout << "The data entered is invalid. Please try again." << std::endl;
        return getNum(prompt, validFunc, lower, upper);
    }
    return inputNum;
}

template <class t>
bool numInRange(t num, t lower, t upper)
{

    return lower <= num && num <= upper;
}

template <class t>
bool numGT0(t num, t, t)
{
    return num > 0;
}
