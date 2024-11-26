#include "graph.h"
#include <iostream>
#include <fstream>
// lecture activity for part B add the function connected to the graph class.
// the function will return true if the two vertexes are connected
// it will return false if they are not.
int main()
{
    graphType g;
    g.createGraph("graph2.txt");
    std::string output = g.printGraph();
    std::ofstream fout("g.txt");
    fout << output;
    std::cout << g.depthFirstTraversal() << std::endl
              << std::endl
              << std::endl;
    std::cout << g.breadthFirstTraversal() << std::endl;
    return 0;
}