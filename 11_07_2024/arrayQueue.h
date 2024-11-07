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
    arrrayQueue(int size = DEFAULT_QUEUE_SIZE);
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
#endif