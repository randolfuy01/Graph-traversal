#include <iostream>
#include "UnitTests.h"

int main() {

    std::cout << "\n-------------------------------------------------\n";
    std::cout << "              Unit Tests    ";
    std::cout << "\n-------------------------------------------------\n";

    UnitTest::runAllTests();

    std::cout << "\n-------------------------------------------------\n";
    std::cout << "          CSC 340 Graph Demo";
    std::cout << "\n-------------------------------------------------\n";

    // Set variables of the graph
    std::initializer_list<int> vertices = {1, 2, 3, 4, 5, 6, 7, 8};

    std::initializer_list<std::pair<int, int>> edges = {
            {1, 2},
            {1, 3},
            {2, 4},
            {2, 5},
            {3, 6},
            {3, 7},
            {4, 8},
            {5, 8},
            {6, 8},
            {7, 8}
    };

    // Set variables for the BFS and shortest path
    int bfsStart = 1;
    int shortestPathStart = 2;
    int shortestPathEnd = 8;

    // Create the graph and add the edges
    Graph<int> demoGraph = vertices;
    demoGraph.addEdge(edges);

    std::cout << "\nGraph adjacency list:" << std::endl;
    std::cout << demoGraph.adjacencyListToString();

    std::cout << "\nBreadth First Search starting at " << bfsStart << ":" << std::endl;
    demoGraph.printBFSTree(bfsStart);

    std::cout << "\n" << demoGraph.shortestPathToString(shortestPathStart, shortestPathEnd) << std::endl;

    return 0;
}
