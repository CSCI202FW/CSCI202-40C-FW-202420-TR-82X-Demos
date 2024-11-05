#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H
#include "stackADT.h"
#include "node.h"
#include <stdexcept>

template <class t>
class linkedStack : public stackADT<t>
{
public:
    linkedStack();
    linkedStack(const linkedStack<t> &);
    const linkedStack<t> &operator=(const linkedStack<t> &);
    void initializeStack();
    bool isEmptyStack() const;
    bool isFullStack() const;
    void push(const t &);
    t top() const;
    t pop();
    ~linkedStack();

private:
    void copyStack(const linkedStack<t> &);
    node<t> *stackTop;
    int count;
};

template <class t>
linkedStack<t>::linkedStack()
{
    stackTop = nullptr;
    count = 0;
}

template <class t>
linkedStack<t>::linkedStack(const linkedStack<t> &othStack)
{
    stackTop = nullptr;
    count = 0;
    copyStack(othStack);
}

template <class t>
const linkedStack<t> &linkedStack<t>::operator=(const linkedStack<t> &othStack)
{
    if (this != &othStack)
    {
        copyStack(othStack);
    }
    return *this;
}

template <class t>
void linkedStack<t>::initializeStack()
{
    node<t> *temp;
    while (stackTop != nullptr)
    {
        temp = stackTop;
        stackTop = stackTop->link;
        delete temp;
    }
    count = 0;
}

template <class t>
bool linkedStack<t>::isEmptyStack() const
{
    return stackTop == nullptr;
}

template <class t>
bool linkedStack<t>::isFullStack() const
{
    return false;
}
template <class t>
linkedStack<t>::~linkedStack()
{
    initializeStack();
}

template <class t>
void linkedStack<t>::push(const t &newItem)
{
    node<t> *newNode;
    newNode = new node<t>;
    newNode->data = new t(newItem);
    newNode->link = stackTop;
    stackTop = newNode;
    count++;
}

template <class t>
t linkedStack<t>::top() const
{
    if (isEmptyStack())
        throw std::out_of_range("Empty Stack");

    return *(stackTop->data);
}

template <class t>
t linkedStack<t>::pop()
{
    node *temp;
    if (isEmptyStack())
        throw std::underflow_error("Stack underflow. Cannot remove from an empty stack.");
    t copyT(*(stackTop->data));
    temp = stackTop;
    stackTop = stackTop->link;
    delete temp;
    count--;
    return copyT;
}

template <class t>
void linkedStack<t>::copyStack(const linkedStack<t> &othStack)
{
    node<t> *newNode, *current, *last;
    if (!isEmptyStack())
    {
        initializeStack();
    }
    if (othStack.isEmptyStack())
    {
        this->stackTop = nullptr;
        count = 0;
    }
    else
    {
        /* linkedStack<t> revCpy;
        while(!otherStack.isEmptyStack())
            revCpy.push(othStack.pop());
        while(!revCpy.isEmptyStack())
        {
            push(revCpy.top());
            othStack.push(revCpy.pop());
        } */

        current = othStack.stackTop;
        this->stackTop = new node<t>;
        this->stackTop->data = new t(*(current->data));
        this->stackTop->link = nullptr;
        last = this->stackTop;
        current = current->link;
        while (current != nullptr)
        {
            newNode = new node<t>;
            newNode->data = new t(*(current->data));
            newNode->link = nullptr;
            last->link = newNode;
            last = newNode;
            current = current->link;
        }
        this->count = othStack.count;
    }
}

#endif