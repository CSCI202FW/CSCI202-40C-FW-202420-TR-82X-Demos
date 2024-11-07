#include <iostream>
#include "arrayQueue.h"
#include "linkedQueue.h"
#include "fakePriorityQueue.h"
#include <cstdlib>

// lecture activity change fakepriorityqueue into a real priorityqueue by modifying enqueue
// the enqueue should do an ordered insert where ties always insert after.
int main()
{
    arrayQueue<int> q(5);
    for (int i = 0; i < 5; i++)
    {
        q.enqueue(i);
    }
    try
    {
        q.enqueue(6);
    }
    catch (std::overflow_error e)
    {
        std::cerr << e.what() << '\n';
    }

    int x = q.dequeue();
    q.enqueue(6);
    x = q.dequeue();
    std::cout << x << std::endl;

    linkedQueue<int> lq;
    /*  lq.enqueue(7);
     lq.enqueue(3);
     x = lq.dequeue();
     std::cout << x << std::endl; */
    fakepriorityqueue<int> pq;
    for (int i = 0; i < 20; i++)
    {
        int ins = rand() % 6 + 1;
        lq.enqueue(ins);
        pq.enqueue(ins);
    }

    std::cout << "regular queue: " << std::endl;
    while (!lq.isEmptyQueue())
    {
        std::cout << lq.dequeue() << std::endl;
    }
    std::cout << std::endl
              << std::endl;
    std::cout << "priority queue: " << std::endl;
    while (!pq.isEmptyQueue())
    {
        std::cout << pq.dequeue() << std::endl;
    }

    return 0;
}