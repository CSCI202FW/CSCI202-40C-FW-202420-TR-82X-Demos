#ifndef UNORDERED_H
#define UNORDERED_H
#include "linkedList.h"

template <class t>
class unorderedLinkedList : public linkedListType<t>
{
public:
    enum directiont
    {
        FORWARD,
        BACKWARD
    };
    unorderedLinkedList(directiont = FORWARD);
    void insert(const t &newInfo);
    void deleteNode(const t &deleteItem);
    bool search(const t &searchItem) const;
    void swap(const t &item1, const t &item2);
    void mergeSort();

private:
    directiont direction;
    void insertFirst(const t &newInfo);
    void insertLast(const t &newInfo);
    void recMergeSort(node<t> *&head);
    void divideList(node<t> *first1, node<t> *&first2);
    node<t> *mergeList(node<t> *first1, node<t> *merge2);
};

template <class t>
unorderedLinkedList<t>::unorderedLinkedList(directiont d) : direction(d)
{
}

template <class t>
void unorderedLinkedList<t>::insert(const t &newInfo)
{
    if (direction == FORWARD)
    {
        insertLast(newInfo);
    }
    else
    {
        insertFirst(newInfo);
    }
}

template <class t>
void unorderedLinkedList<t>::deleteNode(const t &deleteItem)
{
    node<t> *current;
    node<t> *trailCurrent;
    bool found;
    if (this->isEmptyList())
    {
        throw std::out_of_range("Cannot delete from empty list");
    }
    else
    {
        if (*(this->head->data) == deleteItem)
        {
            current = this->head;
            this->head = this->head->link;
            this->count--;
            if (this->head == nullptr)
            {
                this->tail = nullptr;
            }
            delete current;
        }
        else
        {
            found = false;
            trailCurrent = this->head;
            current = this->head->link;
            while (current != nullptr && !found)
            {
                if (*(current->data) != deleteItem)
                {
                    trailCurrent = current;
                    current = current->link;
                }
                else
                {
                    found = true;
                }
            }
            if (found)
            {
                trailCurrent->link = current->link;
                this->count--;
                if (this->tail == current)
                {
                    this->tail = trailCurrent;
                }
                delete current;
            }
            else
            {
                throw std::out_of_range("Item not found in list. Cannot delete");
            }
        }
    }
}

template <class t>
bool unorderedLinkedList<t>::search(const t &searchItem) const
{
    node<t> *current;
    bool found = false;
    current = this->head;
    while (current != nullptr && !found)
    {
        if (*(current->data) == searchItem)
        {
            found = true;
        }
        else
        {
            current = current->link;
        }
    }
    return found;
}

template <class t>
void unorderedLinkedList<t>::insertFirst(const t &newInfo)
{
    node<t> *newNode;
    newNode = new node<t>;
    newNode->data = new t(newInfo);
    newNode->link = nullptr;
    if (this->isEmptyList())
    {
        this->head = newNode;
        this->tail = newNode;
    }
    else
    {
        newNode->link = this->head;
        this->head = newNode;
    }
    this->count++;
}

template <class t>
void unorderedLinkedList<t>::insertLast(const t &newInfo)
{
    node<t> *newNode;
    newNode = new node<t>;
    newNode->data = new t(newInfo);
    newNode->link = nullptr;
    if (this->isEmptyList())
    {
        this->head = newNode;
        this->tail = newNode;
    }
    else
    {
        this->tail->link = newNode;
        this->tail = newNode;
    }
    this->count++;
}

template <class t>
void unorderedLinkedList<t>::swap(const t &item1, const t &item2)
{
    node<t> *current1;
    node<t> *trailCurrent1 = nullptr;
    node<t> *current2;
    node<t> *trailCurrent2 = nullptr;

    current1 = this->head;
    bool found = false;
    while (current1 != nullptr && !found)
    {
        if (*(current1->data) == item1)
        {
            found = true;
        }
        else
        {
            trailCurrent1 = current1;
            current1 = current1->link;
        }
    }
    if (!found)
        return;
    found = false;
    current2 = this->head;
    while (current2 != nullptr && !found)
    {
        if (*(current2->data) == item2)
        {
            found = true;
        }
        else
        {
            trailCurrent2 = current2;
            current2 = current2->link;
        }
    }
    if (!found)
        return;
    node<t> *temp = current1->link;
    current1->link = current2->link;
    if (current2 != temp)
        current2->link = temp;
    else
        current2->link = current1;
    // current2->link = temp;
    if (trailCurrent1 != nullptr)
    {
        trailCurrent1->link = current2;
    }
    else
    {
        this->head = current2;
    }
    if (trailCurrent2 != nullptr)
    {
        trailCurrent2->link = current1;
    }
    else
    {
        this->head = current1;
    }
    if (current1->link == nullptr)
    {
        this->tail = current1;
    }
    else if (current2->link == nullptr)
    {
        this->tail = current2;
    }
}

template <class t>
void unorderedLinkedList<t>::mergeSort()
{
    recMergeSort(this->head);
    if (this->head == nullptr)
    {
        this->tail = nullptr;
    }
    else
    {
        this->tail = this->head;
        while (this->tail->link != nullptr)
        {
            this->tail = this->tail->link;
        }
    }
}

template <class t>
void unorderedLinkedList<t>::recMergeSort(node<t> *&head)
{
    node<t> *otherHead;
    if (head != nullptr)
    {
        if (head->link != nullptr)
        {
            divideList(head, otherHead);
            recMergeSort(head);
            recMergeSort(otherHead);
            head = mergeList(head, otherHead);
        }
    }
}

template <class t>
void unorderedLinkedList<t>::divideList(node<t> *first1, node<t> *&first2)
{
    node<t> *middle;
    node<t> *current;
    if (first1 == nullptr || first1->link == nullptr)
    {
        first2 = nullptr;
    }
    else
    {
        middle = first1;
        current = first1->link;
        if (current != nullptr)
            current = current->link;
        while (current != nullptr)
        {
            middle = middle->link;
            current = current->link;
            if (current != nullptr)
                current = current->link;
        }
        first2 = middle->link;
        middle->link = nullptr;
    }
}
template <class t>
node<t> *unorderedLinkedList<t>::mergeList(node<t> *first1, node<t> *first2)
{
    node<t> *lastSmall;
    node<t> *newHead;
    if (first1 == nullptr)
        return first2;
    if (first2 == nullptr)
        return first1;
    else
    {
        if (*(first1->data) < *(first2->data))
        {
            newHead = first1;
            first1 = first1->link;
            lastSmall = newHead;
        }
        else
        {
            newHead = first2;
            first2 = first2->link;
            lastSmall = newHead;
        }
        while (first1 != nullptr && first2 != nullptr)
        {
            if (*(first1->data) < *(first2->data))
            {
                lastSmall->link = first1;
                lastSmall = lastSmall->link;
                first1 = first1->link;
            }
            else
            {
                lastSmall->link = first2;
                lastSmall = lastSmall->link;
                first2 = first2->link;
            }
        }
        if (first1 == nullptr)
        {
            lastSmall->link = first2;
        }
        else
        {
            lastSmall->link = first1;
        }
        return newHead;
    }
}
#endif