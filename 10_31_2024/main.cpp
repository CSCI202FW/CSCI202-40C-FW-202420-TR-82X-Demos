#include <iostream>
#include <string>
#include <limits>
#include <cctype>
#include <stdexcept>
#include "donut.h"
#include "unorderedLinkedList.h"

void resetStream();
void codeGradeLoopFix(std::string errLocation);
std::string getIcing();
std::string getTopping(std::string);
std::string getDrizzle();

//lecture activity create ordered linked list

int main()
{
    unorderedLinkedList<int> intList;
    intList = intList;
    std::string ice;
    std::string top;
    std::string driz;

    ice = getIcing();
    top = getTopping(ice);
    driz = getDrizzle();

    return 0;
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
        throw std::invalid_argument(errLocation);
    }
}

std::string getIcing()
{
    std::string ice;
    std::cout << "Choose your icing from the choices below:" << std::endl;
    for (std::map<Donut::icingType, std::string>::iterator it = Donut::iceToStr.begin(); it != Donut::iceToStr.end(); ++it)
    {
        std::cout << it->second << std::endl;
    }
    std::cin >> std::ws;
    std::getline(std::cin, ice);
    std::string icingLower = ice;
    std::transform(icingLower.begin(), icingLower.end(), icingLower.begin(), ::tolower);
    while (!Donut::strToIce.count(icingLower))
    {
        codeGradeLoopFix("main.cpp::getIcing()");
        std::cout << ice << " is not a valid icing choice." << std::endl;
        std::cout << "Choose your icing from the choices below:" << std::endl;
        for (std::map<Donut::icingType, std::string>::iterator it = Donut::iceToStr.begin(); it != Donut::iceToStr.end(); ++it)
        {
            std::cout << it->second << std::endl;
        }
        std::cin >> std::ws;
        std::getline(std::cin, ice);
        icingLower = ice;
        std::transform(icingLower.begin(), icingLower.end(), icingLower.begin(), ::tolower);
    }
    return ice;
}
std::string getTopping(std::string icing)
{
    std::string top;
    std::cout << "Choose your topping from the choices below:" << std::endl;
    std::transform(icing.begin(), icing.end(), icing.begin(), ::tolower);
    if (icing == "none")
    {
        std::cout << "Cinnamon Sugar" << std::endl;
        std::cout << "Powdered Sugar" << std::endl;
        std::cout << "None" << std::endl;
    }
    else
    {
        for (auto it = Donut::topToStr.begin(); it != Donut::topToStr.end(); ++it)
        {
            std::cout << it->second << std::endl;
        }
    }
    std::cin >> std::ws;
    std::getline(std::cin, top);
    std::string topCopy = top;
    std::transform(topCopy.begin(), topCopy.end(), topCopy.begin(), ::tolower);
    if (icing == "none")
    {
        while (topCopy != "cinnamon sugar" && topCopy != "powdered sugar" && topCopy != "none")
        {
            codeGradeLoopFix("main.cpp::getTopping(\"none\")");
            std::cout << "Please choose a topping from the list" << std::endl;
            std::getline(std::cin, top);
            topCopy = top;
            std::transform(topCopy.begin(), topCopy.end(), topCopy.begin(), ::tolower);
        }
    }
    else
    {
        while (!Donut::strToTop.count(topCopy))
        {
            codeGradeLoopFix("main.cpp::getTopping()");
            std::cout << "Please choose a topping from the list" << std::endl;
            std::getline(std::cin, top);
            topCopy = top;
            std::transform(topCopy.begin(), topCopy.end(), topCopy.begin(), ::tolower);
        }
    }
    return top;
}

std::string getDrizzle()
{
    return "none";
}
