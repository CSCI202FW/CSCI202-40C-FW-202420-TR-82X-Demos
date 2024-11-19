#include "binarySearchTree.h"
#include <iostream>
#include <random>

int compareNumbers(const int &first, const int &second);

int main()
{
    binarySearchTree<int> tree(compareNumbers);
    std::uniform_int_distribution<int> distribution(1, 100);
    std::default_random_engine generator;

    for (int i = 0; i < 10; i++)
    {

        try
        {

            tree.insert(distribution(generator));
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    std::cout << tree.inorderTraversal() << std::endl;
    std::cout << tree.preorderTraversal() << std::endl;
    std::cout << tree.postOrderTraversal() << std::endl;

    return 0;
}

int compareNumbers(const int &first, const int &second)
{
    if (first < second)
        return -1;
    else if (first == second)
        return 0;
    else
        return 1;
}