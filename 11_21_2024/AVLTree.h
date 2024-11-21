#ifndef AVLTREE_H
#define AVLTREE_H
#include "binarySearchTree.h"
#include <sstream>

template <class t>
class AVLTree : public binarySearchTree<t>
{
public:
    void insert(const t &insertItem);
    void deleteNode(const t &deleteItem);
    AVLTree(int (*comp)(const t &, const t &));

private:
    void balanceFromLeft(binaryNode<t> *&root);
    void balanceFromRight(binaryNode<t> *&root);
    void rotateToLeft(binaryNode<t> *&currentNode);
    void rotateToRight(binaryNode<t> *&currentNode);
    void insertIntoAVL(binaryNode<t> *&root, binaryNode<t> *newNode, bool &isTaller);
};

template <class t>
AVLTree<t>::AVLTree(int (*comp)(const t &, const t &)) : binarySearchTree<t>(comp) {}

template <class t>
void AVLTree<t>::insert(const t &insertItem)
{
    bool isTaller = false;
    binaryNode<t> *newNode;
    newNode = new binaryNode<t>;
    newNode->data = new t(insertItem);
    newNode->bfactor = 0;
    newNode->height = 1;
    newNode->left = nullptr;
    newNode->right = nullptr;
    insertIntoAVL(this->getRoot(), newNode, isTaller);
}

template <class t>
void AVLTree<t>::insertIntoAVL(binaryNode<t> *&root, binaryNode<t> *newNode, bool &isTaller)
{
    if (root == nullptr)
    {
        root = newNode;
        isTaller = true;
    }
    else
    {
        int cmp = compare(**newNode, **root);
        if (cmp == 0)
        {
            throw std::invalid_argument("No duplicates allowed");
        }
        else if (cmp == -1)
        {
            insertIntoAVL(root->left, newNode, isTaller);
            if (isTaller)
            {
                switch (root->bfactor)
                {
                case -1:
                    balanceFromLeft(root);
                    isTaller = false;
                    break;
                case 0:
                    root->bfactor = -1;
                    isTaller = true;
                    break;
                case 1:
                    root->bfactor = 0;
                    isTaller = false;
                }
            }
        }
        else
        {
            insertIntoAVL(root->right, newNode, isTaller);
            if (isTaller)
            {
                switch (root->bfactor)
                {
                case -1:
                    root->bfactor = 0;
                    isTaller = false;
                    break;
                case 0:
                    root->bfactor = 1;
                    isTaller = true;
                    break;
                case 1:
                    balanceFromRight(root);
                    isTaller = false;
                }
            }
        }
    }
}

template <class t>
void AVLTree<t>::balanceFromLeft(binaryNode<t> *&currentNode)
{
    binaryNode<t> *lTree;
    binaryNode<t> *childRTree;
    lTree = currentNode->left;
    switch (lTree->bfactor)
    {
    case -1: // left subtree of current node is left high
        currentNode->bfactor = 0;
        lTree->bfactor = 0;
        rotateToRight(root);
        break;
    case 0:
        throw std::runtime_error("Left subtree is balanced.");
    case 1: // left subtree of current node is right high while the current node is left high
        childRTree = lTree->right;
        switch (childRTree->bfactor)
        {
        case -1:
            currentNode->bfactor = 0;
            lTree->bfactor = 0;
            break;
        case 0:
            currentNode->bfactor = 0;
            lTree->bfactor = 0;
        case 1:
            currentNode->bfactor = 0;
            lTree->bfactor = -1;
        }
        childRTree->bfactor = 0;
        rotateToLeft(lTree);
        currentNode->left = lTree;
        rotateToRight(currentNode);
    }
}
template <class t>
void AVLTree<t>::rotateToRight(binaryNode<t> *&currentNode)
{
    binaryNode<t> *newRootNode; // left child that will become the new root in the subtree node after rotation
    if (currentNode == nullptr)
    {
        throw std::out_of_range("Cannot rotate empty node.");
    }
    else if (currentNode->left == nullptr)
    {
        throw std::out_of_range("Cannot rotate empty node.");
    }
    else
    {
        newRootNode = currentNode->left;
        currentNode->left = newRootNode->right;
        newRootNode->right = currentNode;
        currentNode = newRootNode;
    }
}

template <class t>
void AVLTree<t>::balanceFromRight(binaryNode<t> *&currentNode)
{
    binaryNode<t> *rSubTree;
    rSubTree = root->right;
    switch (rSubTree->bfactor)
    {
    case 1:
        currentNode->bfactor = 0;
        rSubTree->bfactor = 0;
        rotateToLeft(currentNode);
        break;
    case 0:
        throw std::runtime_error("Right Subtree is balanced.");
    case -1:
        switch (rSubTree->left->bfactor)
        {
        case -1:
            currentNode->bfactor = 0;
            rSubTree->bfactor = 1;
            break;
        case 0:
            currentNode->bfactor = 0;
            rSubTree->bfactor = 0;
            break;
        case 1:
            currentNode->bfactor = -1;
            rSubTree->bfactor = 0;
        }
        rSubTree->left->bfactor = 0;
        rotateToRight(currentNode->right);
        rotateToLeft(currentNode);
    }
}
#endif