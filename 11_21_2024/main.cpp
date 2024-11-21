#include "binarySearchTree.h"
#include "AVLTree.h"
#include <iostream>
#include <random>

int compareNumbers(const int &first, const int &second);

int main()
{
    AVLTree<int> tree(compareNumbers);
    std::uniform_int_distribution<int> distribution(1, 100);
    std::default_random_engine generator;

    /* for (int i = 0; i < 10; i++)
    {

        try
        {

            tree.insert(distribution(generator));
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
        }
    } */
    tree.insert(40);
    tree.insert(30);
    tree.insert(20);
    tree.insert(60);
    tree.insert(50);
    tree.insert(80);
    tree.insert(15);
    tree.insert(28);
    tree.insert(25);
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