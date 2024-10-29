#include <iostream>
#include <regex>
#include <string>
#include <iomanip>
#include <set>

const std::set<int> MONTH30 = {4, 6, 9, 11};

int main()
{
    std::regex r{R"((\d{4})/((?:1[0-2])|(?:0?[1-9]))/((?:3[01])|(?:[12][0-9])|(?:0?[1-9])))"};
    while (true)
    {
        std::cout << "Enter a date (year/month/day) (q=quit): ";
        std::string str;
        if (!std::getline(std::cin, str) || str == "q")
        {
            break;
        }
        std::smatch parts;
        if (std::regex_match(str, parts, r))
        {
            int year = std::stoi(parts[1]);
            int month = std::stoi(parts[2]);
            int day = std::stoi(parts[3]);
            bool leap = false;
            bool valid = true;
            if (month == 2)
            {
                if (day <= 28)
                {
                    valid = true;
                }
                else if (day > 29)
                {
                    valid = false;
                }
                else
                {
                    if (year % 4 == 0)
                    {
                        if (year % 100 == 0)
                        {
                            if (year % 400 == 0)
                            {
                                leap = true;
                            }
                            else
                            {
                                leap = false;
                            }
                        }
                        else
                        {
                            leap = true;
                        }
                    }
                    else
                    {
                        leap = false;
                    }
                    if (leap)
                    {
                        valid = true;
                    }
                    else
                    {
                        valid = false;
                    }
                }
            }
            else if (MONTH30.count(month) && day > 30)
            {
                valid = false;
            }

            if (valid)
            {
                std::cout << "Valid Date!" << std::endl;
                std::cout << "You entered " << parts[0] << std::endl;
                std::cout << std::setfill('0');
                std::cout << "In ISO-8601 " << year << "-" << std::setw(2) << month << "-" << std::setw(2) << day << std::endl;
                std::cout << "In american format " << month << "/" << day << "/" << year << std::endl;
            }
            else
            {
                std::cout << "invalid date" << std::endl;
            }
        }
        else
        {
            std::cout << "invalid date" << std::endl;
        }
    }
    return 0;
}