#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <thread>

#include "unorderedLinkedList.h"
#include "searchSort.h"

// which sort would you include in a program why?

int main()
{
    std::ifstream in("input.txt");
    unorderedLinkedList<int> list;
    unorderedLinkedList<int> slist;
    int iList[1000000];
    int i = 0;
    while (!in.eof())
    {
        int x;
        in >> x;
        list.insert(x);
        slist.insert(x);
        iList[i++] = x;
    }
    int searchTerm = 9357854;
    linkedListIterator<int> it = seqSearch(list, searchTerm);
    if (it == nullptr)
    {
        std::cout << "The item was not found in the list" << std::endl;
    }
    else
    {
        std::cout << *it << " is in the list." << std::endl;
    }
    // insertionSort(iList, 1000000);
    // std::cout << "Insertion Sort Finished" << std::endl;
    //  std::thread bsortThread(bubbleSort<int>, std::ref(list));
    //  std::thread sSortThread(selectionSort<int>, std::ref(slist));

    // sSortThread.join();
    // selectionSort(slist);
    // std::cout << "Selection Sort Finished" << std::endl;

    // bsortThread.join();
    // std::cout << "Bubble Sort Finished" << std::endl;

    list.mergeSort();
    std::cout << "Merge sort finished" << std::endl;

    return 0;
}