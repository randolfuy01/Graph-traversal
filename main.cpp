#include <iostream>
#include "UnitTests.h"
#include <string>

int main() {

    std::cout << "\n-------------------------------------------------\n";
    std::cout << "              Unit Tests    ";
    std::cout << "\n-------------------------------------------------\n";

    UnitTest::runAllTests();

    std::cout << "\n-------------------------------------------------\n";
    std::cout << "          CSC 340 Graph Demo 1";
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
    std::cout << "\n-------------------------------------------------\n";
    std::cout << "          END CSC 340 Graph Demo 1";
    std::cout << "\n-------------------------------------------------\n";
    std::cout << "\n-------------------------------------------------\n";
    std::cout << "          CSC 340 Graph Demo 2";
    std::cout << "\n-------------------------------------------------\n";

    // Set variables of the graph
    std::initializer_list<std::string> vertices2 = {"San Francisco", "Los Angeles", "Las Vegas", "Salt Lake City", "Denver", "Phoenix", "Albuquerque", "Dallas" , "New York"};

    std::initializer_list<std::pair<std::string, std::string>> edges2 = {
            {"San Francisco", "Los Angeles"},
            {"San Francisco", "Las Vegas"},
            {"Los Angeles", "Las Vegas"},
            {"Los Angeles", "Phoenix"},
            {"Las Vegas", "Phoenix"},
            {"Las Vegas", "Salt Lake City"},
            {"Salt Lake City", "Denver"},
            {"Phoenix", "Albuquerque"},
            {"Phoenix", "Dallas"},
            {"Albuquerque", "Dallas"},
            {"Albuquerque", "New York"},
            {"Dallas", "New York"}
    };

    // Set variables for the BFS and shortest path
    std::string bfsStart2 = "San Francisco";
    std::string shortestPathStart2 = "New York";
    std::string shortestPathEnd2 = "Denver";

    // Create the graph and add the edges
    Graph<std::string> demoGraph2 = vertices2;
    demoGraph2.addEdge(edges2);

    std::cout << "\nGraph adjacency list:" << std::endl;
    std::cout << demoGraph2.adjacencyListToString();

    std::cout << "\nBreadth First Search starting at " << bfsStart2 << ":" << std::endl;
    demoGraph2.printBFSTree(bfsStart2);

    std::cout << "\n" << demoGraph2.shortestPathToString(shortestPathStart2, shortestPathEnd2) << std::endl;

    std::cout << "\n-------------------------------------------------\n";
    std::cout << "          END CSC 340 Graph Demo 2";
    std::cout << "\n-------------------------------------------------\n";

    return 0;
}
