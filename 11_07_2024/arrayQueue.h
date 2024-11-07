#ifndef ARRAYQUEUE_H
#define ARRAYQUEUE_H
#include "queueADT.h"
#include <stdexcept>

template <class t>
class arrayQueue : public queueADT<t>
{
public:
    const static int DEFAULT_QUEUE_SIZE = 100;
    bool isEmptyQueue() const;
    bool isFullQueue() const;
    void initializeQueue();
    t front() const;
    t back() const;
    void enqueue(const t &queueElement);
    t dequeue();
    const arrayQueue<t> &operator=(const arrayQueue<t> &);
    arrayQueue(const arrayQueue<t> &);
    arrayQueue(int size = DEFAULT_QUEUE_SIZE);
    ~arrayQueue();

private:
    t **list;
    int maxQueueSize;
    int queueFront;
    int queueRear;
    int count;
    void copyQueue(const arrayQueue<t> &);
};

template <class t>
bool arrayQueue<t>::isEmptyQueue() const
{
    return count == 0;
}

template <class t>
bool arrayQueue<t>::isFullQueue() const
{
    return count == maxQueueSize;
}

template <class t>
void arrayQueue<t>::initializeQueue()
{
    if (!this->isEmptyQueue())
    {

        for (int i = 0; i < maxQueueSize; i++)
        {
            if (list[i] != nullptr)
            {
                delete list[i];
                list[i] = nullptr;
            }
        }
        /* int i = this->queueFront;
        bool end = false;
        while(!end)
        {
            if (i == this->queueRear)
            {
                end = true;
            }
            delete list[i++];
            i = i % maxQueueSize;
            //if(i >= maxQueueSize)
            //{
            //    i = 0;
            //}
        } */
    }
    this->queueFront = 0;
    this->queueRear = this->maxQueueSize - 1;
    this->count = 0;
}

template <class t>
t arrayQueue<t>::front() const
{
    if (this->isEmptyQueue())
    {
        throw std::out_of_range("Cannot view an item in an empty queue.");
    }
    return *(list[queueFront]);
}

template <class t>
t arrayQueue<t>::back() const
{
    if (this->isEmptyQueue())
    {
        throw std::out_of_range("Cannot view an item in an empty queue.");
    }
    return *(list[queueRear]);
}

template <class t>
void arrayQueue<t>::enqueue(const t &queueElement)
{
    if (this->isFullQueue())
    {
        throw std::overflow_error("Cannot add to a full queue.");
    }
    this->queueRear = (this->queueRear + 1) % maxQueueSize;
    list[queueRear] = new t(queueElement);
    count++;
}
template <class t>
t arrayQueue<t>::dequeue()
{
    if (this->isEmptyQueue())
    {
        throw std::underflow_error("Cannot delete from an empty queue.");
    }
    t returnItem(*list[this->queueFront]);
    delete list[this->queueFront];
    list[this->queueFront] = nullptr;
    this->queueFront = ++this->queueFront % this->maxQueueSize;
    this->count--;
    return returnItem;
}

template <class t>
const arrayQueue<t> &arrayQueue<t>::operator=(const arrayQueue<t> &othQueue)
{
    if (this != &othQueue)
        copyQueue(othQueue);
    return *this;
}

template <class t>
arrayQueue<t>::arrayQueue(const arrayQueue<t> &othQueue)
{
    this->count = 0;
    this->list = nullptr;
    copyQueue(othQueue);
}

template <class t>
void arrayQueue<t>::copyQueue(const arrayQueue &othQueue)
{
    if (!this->isEmptyQueue())
    {
        this->initializeQueue();
    }
    delete[] this->list;
    this->maxQueueSize = othQueue.maxQueueSize;
    this->count = othQueue.count;
    this->list = new t *[this->maxQueueSize];
    this->queueFront = othQueue.queueFront;
    this->queueRear = othQueue.queueRear;

    for (int i = 0; i < this->maxQueueSize; i++)
    {
        if (othQueue.list[i] != nullptr)
        {
            this->list[i] == new t(*(othQueue.list[i]));
        }
    }
    /*  bool end = false;
     for (int i = queueFront; !end; i++)
     {
         if (i >= this->maxQueueSize)
             i = 0;
         this->list[i] = new t(*(othQueue.list[i]));
         if (i == this->queueRear)
             end = true;
     } */
}

template <class t>
arrayQueue<t>::arrayQueue(int size)
{
    if (size <= 0)
    {
        size = DEFAULT_QUEUE_SIZE;
    }
    this->maxQueueSize = size;
    this->list = new t *[this->maxQueueSize];
    this->count = 0;
    for (int i = 0; i < maxQueueSize; i++)
    {
        this->list[i] = nullptr;
    }
    this->initializeQueue();
}

template <class t>
arrayQueue<t>::~arrayQueue()
{
    initializeQueue();
    delete[] list;
    list = nullptr;
}
#endif