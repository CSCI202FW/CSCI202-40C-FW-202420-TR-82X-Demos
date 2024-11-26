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

std::string graphType::printGraph() const
{
    std::ostringstream out;
    out << "digraph {" << std::endl; // comment this line out for the python output
    for (int i = 0; i < gSize; i++)
    {
        // original output works with pyton rendering program
        /* out << i << " ";
        graph[i].print(out);
        out << std::endl; */
        // remove the for loop below for the python output
        for (linkedListIterator<int> graphIt = graph[i].begin(); graphIt != graph[i].end(); ++graphIt)
        {
            out << i << "->" << *graphIt << ";" << std::endl;
        }
    }
    out << std::endl; // comment this line and the next line for python output
    out << "}";
    return out.str();
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

const graphType &graphType::operator=(const graphType &otherGraph)
{
    if (this != &otherGraph)
    {
        copyGraph(otherGraph);
    }
    return *this;
}

std::string graphType::depthFirstTraversal()
{
    bool *visited;
    visited = new bool[gSize];
    std::string output = "";
    for (int i = 0; i < gSize; i++)
    {
        visited[i] = false;
    }
    for (int i = 0; i < gSize; i++)
    {
        if (!visited[i])
        {
            dft(i, visited, output);
        }
    }
    delete[] visited;
    return output;
}

std::string graphType::dftAtVertex(int vertex)
{
    bool *visited;
    visited = new bool[gSize];
    for (int i = 0; i < gSize; i++)
    {
        visited[i] = false;
    }
    std::string out = "";
    dft(vertex, visited, out);
    delete[] visited;
    return out;
    return std::string();
}

std::string graphType::breadthFirstTraversal()
{
    linkedQueue<int> queue;
    bool *visited;
    visited = new bool[gSize];
    for (int i = 0; i < gSize; i++)
    {
        visited[i] = false;
    }
    std::string out = "";
    for (int i = 0; i < gSize; i++)
    {
        if (!visited[i])
        {
            queue.enqueue(i);
            visited[i] = true;
            out = out + " " + std::to_string(i) + " ";
            while (!queue.isEmptyQueue())
            {
                int u = queue.dequeue();
                for (auto graphIt = graph[u].begin(); graphIt != graph[u].end(); ++graphIt)
                {
                    int w = *graphIt;
                    if (!visited[w])
                    {
                        queue.enqueue(w);
                        visited[w] = true;
                        out = out + " " + std::to_string(w) + " ";
                    }
                }
            }
        }
    }
    return out;
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

void graphType::dft(int v, bool visited[], std::string &output)
{
    visited[v] = true;
    output = output + " " + std::to_string(v) + " ";
    linkedListIterator<int> graphIt;
    for (graphIt = graph[v].begin(); graphIt != graph[v].end(); ++graphIt)
    {
        int w = *graphIt;
        if (!visited[v])
        {
            dft(w, visited, output);
        }
    }
}
