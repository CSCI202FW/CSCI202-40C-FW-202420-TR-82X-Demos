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
    void copyStack(const arrayStack<T> &);
};

#endif