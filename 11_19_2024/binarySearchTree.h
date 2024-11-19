#ifndef SEARCH_H
#define SEARCH_H
#include "binaryTree.h"
#include <stdexcept>

template <class t>
class binarySearchTree : public binaryTree<t>
{
public:
    void insert(const t &insertItem);
    bool search(const t &searchItem);
    void deleteNode(const t &deleteItem);
    binarySearchTree(int (*comp)(const t &, const t &));

private:
    int (*compare)(const t &, const t &);
    void deleteFromTree(binaryNode<t> *&currentNode);
    bool search(const t &searchItem, binaryNode<t> *currentNode);
    void insert(binaryNode<t> *&insertItem, binaryNode<t> *&currentNode);
};

template <class t>
binarySearchTree<t>::binarySearchTree(int (*comp)(const t &item1, const t &item2))
{
    this->compare = comp;
}

template <class t>
void binarySearchTree<t>::insert(const t &insertItem)
{
    binaryNode<t> *newNode;
    newNode = new binaryNode<t>;
    newNode->data = new t(insertItem);
    newNode->left = nullptr;
    newNode->right = nullptr;
    insert(newNode, this->getRoot());
}

template <class t>
void binarySearchTree<t>::insert(binaryNode<t> *&insertItem, binaryNode<t> *&currentNode)
{
    if (currentNode == nullptr)
    {
        currentNode = insertItem;
    }
    else
    {
        int cmp = compare(*(insertItem->data), *(currentNode->data));
        if (cmp == 0)
        {
            throw std::invalid_argument("The item to be inserted is already in the tree -- duplicates are not allowed");
        }
        else if (cmp == 1) // new node is larger than current --> head right
        {
            insert(insertItem, currentNode->right);
        }
        else if (cmp == -1) // new node is smaller than current --> head left
        {
            insert(insertItem, currentNode->left);
        }
    }
}

template <class t>
bool binarySearchTree<t>::search(const t &searchItem)
{
    return search(searchItem, this->getRoot());
}

template <class t>
bool binarySearchTree<t>::search(const t &searchItem, binaryNode<t> *currentNode)
{
    if (currentNode == nullptr)
    {
        return false;
    }
    int cmp = compare(searchItem, *(currentNode->data));
    if (cmp == 0)
    {
        return true;
    }
    else if (cmp == 1)
    {
        return search(searchItem, currentNode->right);
    }
    else if (cmp == -1)
    {
        return search(searchItem, currentNode->left);
    }
    return false;
}

template <class t>
void binarySearchTree<t>::deleteNode(const t &deleteItem)
{
    binaryNode<t> *current;
    binaryNode<t> *trailCurrent;
    bool found = false;
    if (this->isEmpty())
    {
        throw std::invalid_argument("Cannot delete from an empty tree");
    }
    current = this->getRoot();
    trailCurrent = current;
    while (current != nullptr && !found)
    {
        int cmp = compare(deleteItem, *(current->data));
        if (cmp == 0)
        {
            found = true;
        }
        else
        {
            trailCurrent = current;
            if (cmp == 1)
            {
                current = current->right;
            }
            else
            {
                current = current->left;
            }
        }
    }
    if (!found)
    {
        throw std::invalid_argument("The item to be deleted is not in the tree");
    }
    else
    {
        if (current == this->getRoot())
            deleteFromTree(this->getRoot());
        else if (compare(deleteItem, *(trailCurrent->data)) == -1)
        {
            deleteFromTree(trailCurrent->left);
        }
        else
        {
            deleteFromTree(trailCurrent->right);
        }
    }
}

template <class t>
void binarySearchTree<t>::deleteFromTree(binaryNode<t> *&currentNode)
{
    binaryNode<t> *current;
    binaryNode<t> *trailCurrent;
    binaryNode<t> *temp;
    if (currentNode == nullptr)
        throw std::invalid_argument("The item to be deleted is not in the tree.");
    else if (currentNode->left == nullptr && currentNode->right == nullptr)
    {
        temp = currentNode;
        currentNode = nullptr;
        delete temp;
    }
    else if (currentNode->left == nullptr)
    {
        temp = currentNode;
        currentNode = temp->right;
        delete temp;
    }
    else if (currentNode->right == nullptr)
    {
        temp = currentNode;
        currentNode = temp->left;
        delete temp;
    }
    else
    {
        current = currentNode->left;
        trailCurrent = nullptr;
        while (current->right != nullptr)
        {
            trailCurrent = current;
            current = current->right;
        }
        t *tempData;
        tempData = currentNode->data;
        currentNode->data = current->data;
        current->data = tempData;
        if (trailCurrent == nullptr)
        {
            currentNode->left = current->left;
        }
        else
        {
            trailCurrent->right = current->left;
        }
        delete current;
    }
}

#endif