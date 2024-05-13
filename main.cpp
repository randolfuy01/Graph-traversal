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

    Graph<int> demoGraph = {1, 2, 3, 4, 5, 6};

    demoGraph.addEdge(1, 2);
    demoGraph.addEdge(1, 3);
    demoGraph.addEdge(2, 3);
    demoGraph.addEdge(2, 3);
    demoGraph.addEdge(4, 3);
    demoGraph.addEdge(4, 6);
    demoGraph.addEdge(2, 6);
    demoGraph.addEdge(5, 6);

    std::cout << "\nGraph adjacency list:" << std::endl;
    std::cout << demoGraph.adjacencyListToString();

    std::cout << "\nBreadth First Search starting at " << "1" << std::endl;
    demoGraph.breadthFirstSearch(1);

    demoGraph.printBFSTree();

    std::cout << "\n" << demoGraph.shortestPathToString(1, 3);
    return 0;
}
