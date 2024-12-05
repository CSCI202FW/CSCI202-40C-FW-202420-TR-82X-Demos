#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unordered_set>
#include <string>
#include <cmath>
#include <vector>
#include <functional>
#include <random>

const int HT_SIZE = 2000000;

int hashFunc(int key);
void setup();
// lecture activity suggest a change to mid-square or folding to try and improve the collisions
int main()
{

    int ht[HT_SIZE];
    int collisions = 0;
    int count = 0;

    for (int i = 0; i < HT_SIZE; i++)
    {
        ht[i] = -1;
    }
    std::ifstream nums("exp.txt");
    while (!nums.eof() && count < HT_SIZE / 2)
    {
        int num;
        nums >> num;
        int hashValue = hashFunc(num);
        if (ht[hashValue] == -1)
        {
            std::cout << num << " inserted at " << hashValue << std::endl;
            ht[hashValue] = num;
            count++;
        }
        else if (ht[hashValue] != num)
        {
            std::cout << num << " collided with " << ht[hashValue] << std::endl;
            collisions++;
        }
    }

    std::cout << "There were " << collisions << " collisions." << std::endl;
    std::cout << "There were " << count << " items inserted." << std::endl;
}

void setup()
{
    std::ofstream out("exp.txt");
    std::unordered_set<int> randomData;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1, 3000000);
    while (randomData.size() < 1000000)
    {
        randomData.insert(distribution(generator));
    }
    for (int i : randomData)
    {
        out << i << std::endl;
    }
    out.close();
}

int hashFunc(int key)
{
    /*  unsigned long keySquared = pow(key, 2);
     int numDigits = floor(log10(keySquared) + 1);
     int x = pow(10, numDigits / 2);
     int location = keySquared / x; */

    int location = 0;
    std::vector<int> segments;
    int seg;
    int numDigits = floor(log10(key) + 1);
    int x = pow(10, numDigits / 2 + 1);
    if (x < 10)
        x = 10;
    while (key > 0)
    {
        seg = key % x;
        key = key / x;
        segments.push_back(seg);
    }
    for (int i = 0; i < segments.size(); i++)
    {
        location += segments[i];
    }

    return location % HT_SIZE;
}
