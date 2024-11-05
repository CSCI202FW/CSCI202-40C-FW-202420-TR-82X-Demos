#ifndef ASTACK_H
#define ASTACK_H
#include "stackADT.h"
#include <stdexcept>

template <class t>
class arrayStack : public stackADT<t>
{
public:
    const static int DEFAULT_STACK_SIZE = 100;
    arrayStack(int = DEFAULT_STACK_SIZE);
    arrayStack(const arrayStack<t> &);
    const arrayStack<t> &operator=(const arrayStack<t> &);
    void initializeStack();
    bool isEmptyStack() const;
    bool isFullStack() const;
    void push(const t &);
    t top() const;
    t pop();
    ~arrayStack();

private:
    int maxStackSize;
    int stacktop;
    t **list;
    void copyStack(const arrayStack<t> &);
};

template <class t>
arrayStack<t>::arrayStack(int max)
{
    if (max <= 0)
    {
        max = DEFAULT_STACK_SIZE;
    }
    maxStackSize = max;
    stacktop = 0;
    list = new t *[maxStackSize];
}

template <class t>
arrayStack<t>::arrayStack(const arrayStack<t> &otherStack)
{
    stacktop = 0;
    list = nullptr;
    copyStack(otherStack);
}

template <class t>
const arrayStack<t> &arrayStack<t>::operator=(const arrayStack<t> &otherStack)
{
    if (this != &otherStack)
    {
        copyStack(otherStack);
    }
    return *this;
}

template <class t>
void arrayStack<t>::initializeStack()
{
    if (!isEmptyStack())
    {
        for (int i = 0; i < stacktop; i++)
        {
            delete list[i];
        }
    }
    stacktop = 0;
}

template <class t>
bool arrayStack<t>::isEmptyStack() const
{
    return stacktop == 0;
}

template <class t>
bool arrayStack<t>::isFullStack() const
{
    return stacktop == maxStackSize;
}

template <class t>
arrayStack<t>::~arrayStack()
{
    initializeStack();
    delete[] list;
}

template <class t>
void arrayStack<t>::push(const t &newItem)
{
    if (!isFullStack())
    {
        list[stacktop] = new t(newItem);
        stacktop++;
    }
    else
    {
        throw std::overflow_error("Stack Overflow. Cannot add to a full stack.");
    }
}

template <class t>
t arrayStack<t>::top() const
{
    if (isEmptyStack())
    {
        throw std::out_of_range("Empty Stack");
    }
    return *(list[stacktop - 1]);
}

template <class t>
t arrayStack<t>::pop()
{
    if (isEmptyStack())
    {
        throw std::underflow_error("Stack underflow. Cannot remove from an empty stack.");
    }
    else
    {
        t copyT(*(list[stacktop - 1]));
        delete list[stacktop - 1];
        stacktop--;
        return copyT;
    }
}

template <class t>
void arrayStack<t>::copyStack(const arrayStack<t> &othStack)
{
    if (!isEmptyStack())
    {
        initializeStack();
    }
    delete[] this->list;
    this->maxStackSize = othStack.maxStackSize;
    this->stackTop = othStack.stackTop;
    this->list = new t *[this->maxStackSize];
    for (int i = 0; i < this->stackTop; i++)
    {
        this->list[i] = new t(*(othStack.list[i]));
    }
}

#endif