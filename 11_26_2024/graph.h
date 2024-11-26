#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "unorderedLinkedList.h"
#include "linkedQueue.h"

class graphType
{
public:
    bool isEmpty() const;
    void createGraph(std::string);
    void clearGraph();
    std::string printGraph() const;
    graphType(int size = 0);
    graphType(const graphType &);
    ~graphType();
    const graphType &operator=(const graphType &);
    std::string depthFirstTraversal();
    std::string dftAtVertex(int vertex);
    std::string breadthFirstTraversal();
    // add a function
    bool connected(int, int);

protected:
    int maxSize;
    int gSize;
    unorderedLinkedList<int> *graph;

private:
    void copyGraph(const graphType &);
    void dft(int v, bool visited[], std::string &output);
};

#endif