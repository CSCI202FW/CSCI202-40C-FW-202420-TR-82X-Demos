#ifndef LINKEDI_H
#define LINKEDI_H
#include "node.h"

template <class t>
class linkedListIterator
{
public:
    linkedListIterator();
    linkedListIterator(node<t> *);
    t &operator*();
    linkedListIterator<t> operator++();
    linkedListIterator<t> operator+(int);
    bool operator==(const linkedListIterator<t> &) const;
    bool operator!=(const linkedListIterator<t> &) const;

private:
    node<t> *current;
};
template <class t>
linkedListIterator<t>::linkedListIterator()
{
    current = nullptr;
}
template <class t>
linkedListIterator<t>::linkedListIterator(node<t> *ptr)
{
    current = ptr;
}
template <class t>
t &linkedListIterator<t>::operator*()
{
    return *(current->data);
}
template <class t>
linkedListIterator<t> linkedListIterator<t>::operator++()
{
    current = current->link;
    return *this;
}

template <class t>
bool linkedListIterator<t>::operator==(const linkedListIterator<t> &right) const
{

    return (current == right.current);
}

template <class t>
bool linkedListIterator<t>::operator!=(const linkedListIterator<t> &right) const
{
    return (current != right.current);
}

#endif

template <class t>
linkedListIterator<t> linkedListIterator<t>::operator+(int x)
{
    node<t> *temp = current;
    for (int i = 0; i < x && temp != nullptr; i++)
    {
        temp = temp->link;
    }
    return linkedListIterator<t>(temp);
}
