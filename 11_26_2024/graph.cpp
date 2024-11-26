#include "graph.h"

bool graphType::isEmpty() const
{
    return gSize == 0;
}

void graphType::createGraph(std::string filename)
{
    std::ifstream fin(filename);
    int index;
    int vertex;
    int adjcentVertex;
    if (!isEmpty())
    {
        clearGraph();
    }
    if (!fin.is_open())
    {
        throw std::runtime_error("Cannot open input file.");
    }
    fin >> gSize;
    if (gSize > maxSize)
    {
        if (graph != nullptr)
        {
            delete[] graph;
        }
        maxSize = gSize;
        graph = new unorderedLinkedList<int>[maxSize];
    }
    for (index = 0; index < gSize; index++)
    {
        fin >> vertex;
        fin >> adjcentVertex;
        while (adjcentVertex != -999)
        {
            graph[vertex].insert(adjcentVertex);
            fin >> adjcentVertex;
        }
    }
    fin.close();
}

void graphType::clearGraph()
{
    for (int i = 0; i < gSize; i++)
    {
        graph[i].destroyList();
    }
    delete[] graph;
    graph = nullptr;
    gSize = 0;
    maxSize = 0;
}

graphType::graphType(int size)
{
    maxSize = size;
    gSize = 0;
    if (maxSize > 0)
    {
        graph = new unorderedLinkedList<int>[maxSize];
    }
    else
    {
        graph = nullptr;
    }
}

graphType::graphType(const graphType &otherGraph)
{
    maxSize = 0;
    gSize = 0;
    graph = nullptr;
    copyGraph(otherGraph);
}

graphType::~graphType()
{
    clearGraph();
}

void graphType::copyGraph(const graphType &otherGraph)
{
    if (!this->isEmpty())
    {
        this->clearGraph();
    }
    else if (this->graph != nullptr)
    {
        delete[] this->graph;
    }
    this->maxSize = otherGraph.maxSize;
    this->gSize = otherGraph.gSize;
    this->graph = new unorderedLinkedList<int>[this->maxSize];
    for (int i = 0; i < this->gSize; i++)
    {
        this->graph[i] = otherGraph.graph[i];
    }
}
