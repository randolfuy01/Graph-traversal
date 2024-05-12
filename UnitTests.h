//
// Created by Randolf Gabrielle Uy on 5/7/24.
//

#ifndef PROJECT5_UNITTESTS_H
#define PROJECT5_UNITTESTS_H

#include <iostream>
#include <sstream>
#include "Graph.h"

class UnitTest {

    typedef bool (*UnitTestFunc)();

    static bool LinkedListUnitTest1() {
        LinkedList<std::string> list = *new LinkedList<std::string>("A");
        list.enqueue("B");
        list.enqueue("C");
        list.enqueue("D"); // Should be A -> B -> C -> D
        std::string expected = "A -> B -> C -> D";
        std::string actual = list.printLinkedList();
        std::cout << "actual:   " << actual << "\nexpected: " << expected << std::endl;
        return expected == actual;
    }

    static bool LinkedListUnitTest2() {
        LinkedList<std::string> list;
        list.enqueue("San Francisco");
        list.enqueue("Los Angeles");
        list.enqueue("New York");
        std::string expected = "San Francisco -> Los Angeles -> New York";
        std::string actual = list.printLinkedList();
        std::cout << "actual:   " << actual << "\nexpected: " << expected << std::endl;
        return expected == actual;
    }

    static bool LinkedListCopyConstructorTest1() {
        LinkedList<std::string> list1;
        list1.enqueue("Hello");
        list1.enqueue("World");

        // Create a copy using the copy constructor
        LinkedList list2(list1);

        // Modify list1
        list1.enqueue("New Node");

        // Check that list2 didn't change after changing list1
        bool isCopyConstructorPassing = (list2.printLinkedList() == "Hello -> World");

        return isCopyConstructorPassing;
    }

    static bool LinkedListCopyAssignmentOperatorTest1() {
        LinkedList<std::string> list1;
        list1.enqueue("Hello");
        list1.enqueue("World");

        // Create an empty list and then assign to it to make a copy.
        LinkedList<std::string> list2;
        list2 = list1;

        // Modify list1
        list1.enqueue("New Node");

        // Check that list2 didn't change after changing list1
        bool isCopyAssignmentPassing = (list2.printLinkedList() == "Hello -> World");

        return isCopyAssignmentPassing;
    }

// TO-DO: Implement Graph Unit Tests
    static bool GraphUnitTest1() {
        Graph<std::string> graph = *new Graph<std::string>();
        graph.addEdge("A", "B");
        graph.addEdge("A", "C");
        graph.addEdge("A", "D");
        graph.addEdge("B", "C");
        graph.addEdge("B", "D");
        graph.addEdge("C", "D");
        std::string expected = "A -> B -> C -> D\nB -> A -> C -> D\nC -> A -> B -> D\nD -> A -> B -> C\n";
        std::string actual = graph.printGraph();
        std::cout << "actual: \n" << actual << std::endl;
        std::cout << "expected: \n" << expected;
        return expected == actual;
    }

    static bool GraphUnitTest2() {
        Graph graph = *new Graph<std::string>();
        graph.addEdge("San Francisco", "Los Angeles");
        graph.addEdge("San Francisco", "New York");
        graph.addEdge("Los Angeles", "New York");
        std::string expected = "San Francisco -> Los Angeles -> New York\nLos Angeles -> San Francisco -> New York\nNew York -> San Francisco -> Los Angeles\n";
        std::string actual = graph.printGraph();
        std::cout << "actual: \n" << actual << std::endl;
        std::cout << "expected: \n" << expected;
        std::vector<std::vector<std::string>> expectedValues = {{"San Francisco", "Los Angeles",   "New York"},
                                                                {"Los Angeles",   "San Francisco", "New York"},
                                                                {"New York",      "San Francisco", "Los Angeles"}};

        for (int i = 0; i < graph.edges.size(); i++) {
            LinkedList<std::string> *list = graph.edges[i];
            Node<std::string> *current = list->head;
            int j = 0;
            while (current->next != nullptr) {
                if (current->val != expectedValues[i][j]) {
                    return false;
                }
                current = current->next;
                j++;
            }
        }
        return expected == actual;
    }

    static bool GraphCopyConstructorTest1() {
        Graph<std::string> originalGraph;

        originalGraph.addEdge("A", "B");
        originalGraph.addEdge("A", "C");
        originalGraph.addEdge("B", "D");
        originalGraph.addEdge("C", "D");

        // Make a copy of the original graph
        Graph copiedGraph = originalGraph; // Calls the copy constructor

        // Check if the printed representations of the original and copied graph are same
        return (originalGraph.printGraph() == copiedGraph.printGraph());
    }

    static bool GraphCopyAssignmentOperatorTest1() {
        Graph<std::string> originalGraph;
        originalGraph.addEdge("A", "B");
        originalGraph.addEdge("A", "C");
        originalGraph.addEdge("B", "D");
        originalGraph.addEdge("C", "D");

        // Create an empty graph for assignment
        Graph<std::string> copiedGraph;

        // Create a copy of the original graph
        copiedGraph = originalGraph;

        // Check if the original graph matches the copied graph
        return (originalGraph.printGraph() == copiedGraph.printGraph());
    }

    static bool GraphBFSUnitTest1() {
        Graph<std::string> graph;

        graph.addVertex("A");
        graph.addVertex("B");
        graph.addVertex("C");
        graph.addVertex("D");
        graph.addVertex("E");
        graph.addVertex("F");
        graph.addEdge("A", "B");
        graph.addEdge("A", "C");
        graph.addEdge("B", "D");
        graph.addEdge("B", "E");
        graph.addEdge("C", "F");

        graph.breadthFirstSearch("A");
        graph.printBFSTree();

        // Verify that the BFS has correctly assigned parents in the BFS tree starting from node 'A'
        if (graph.findVertex("B")->parent != graph.findVertex("A")) return false;
        if (graph.findVertex("C")->parent != graph.findVertex("A")) return false;
        if (graph.findVertex("D")->parent != graph.findVertex("B")) return false;
        if (graph.findVertex("E")->parent != graph.findVertex("B")) return false;
        if (graph.findVertex("F")->parent != graph.findVertex("C")) return false;

        return true;
    }

    static bool GraphBFSUnitTest2() {
        Graph<std::string> graph;

        graph.addVertex("A");
        graph.addVertex("B");
        graph.addVertex("C");
        graph.addVertex("D");
        graph.addVertex("E");
        graph.addVertex("F");
        graph.addEdge("A", "B");
        graph.addEdge("A", "C");
        graph.addEdge("B", "D");
        graph.addEdge("B", "E");
        graph.addEdge("C", "F");

        graph.breadthFirstSearch("C");
        graph.printBFSTree();

        // Verify that the BFS has correctly assigned parents in the BFS tree starting from node 'C'
        if (graph.findVertex("A")->parent != graph.findVertex("C")) return false;
        if (graph.findVertex("F")->parent != graph.findVertex("C")) return false;
        if (graph.findVertex("B")->parent != graph.findVertex("A")) return false;
        if (graph.findVertex("D")->parent != graph.findVertex("B")) return false;
        if (graph.findVertex("E")->parent != graph.findVertex("B")) return false;

        return true;
    }

// Path found
    static bool GraphShortestPathUnitTest1() {
        Graph<std::string> graph;
        graph.addEdge("A", "B");
        graph.addEdge("A", "C");
        graph.addEdge("B", "D");
        graph.addEdge("B", "G");
        graph.addEdge("C", "H");
        graph.addEdge("C", "I");
        graph.addEdge("C", "J");
        graph.addEdge("J", "K");

        std::string expected = "Shortest path from A to I: A -> C -> I";
        std::string actual = graph.shortestPath("A", "I");

        graph.printBFSTree();
        std::cout << "start: A, end; I" << std::endl;

        std::cout << "expected: " << expected << std::endl;
        std::cout << "actual  : " << actual << std::endl;

        return expected == actual;
    }

// Start vertex does not exist
    static bool GraphShortestPathUnitTest2() {
        Graph<std::string> graph;
        graph.addEdge("A", "B");
        graph.addEdge("A", "C");
        graph.addEdge("B", "D");
        graph.addEdge("D", "E");

        std::string expected = "Error: Start vertex 'X' not found";
        std::string actual = graph.shortestPath("X", "B"); // Non-existent start vertex

        graph.printBFSTree();
        std::cout << "start: X, end; B" << std::endl;

        std::cout << "expected: " << expected << std::endl;
        std::cout << "actual  : " << actual << std::endl;

        return expected == actual;
    }

// End vertex does not exist
    static bool GraphShortestPathUnitTest3() {
        Graph<std::string> graph;
        graph.addEdge("A", "B");
        graph.addEdge("A", "C");
        graph.addEdge("B", "D");
        graph.addEdge("D", "E");

        std::string expected = "Error: End vertex 'Y' not found";
        std::string actual = graph.shortestPath("A", "Y"); // Non-existent end vertex

        graph.printBFSTree();
        std::cout << "start: A, end; I" << std::endl;

        std::cout << "expected: " << expected << std::endl;
        std::cout << "actual  : " << actual << std::endl;

        return actual == expected;
    }

// Both vertices exist, but not connected
    static bool GraphShortestPathUnitTest4() {
        Graph<std::string> graph;
        graph.addEdge("A", "B");
        graph.addEdge("A", "C");
        graph.addEdge("B", "D");
        graph.addEdge("D", "E");

        graph.addVertex("Z"); // Add a discontinuous vertex

        std::string expected = "No path from A to Z";
        std::string actual = graph.shortestPath("A", "Z");

        graph.printBFSTree();
        std::cout << "start: A, end; Z" << std::endl;

        std::cout << "expected: " << expected << std::endl;
        std::cout << "actual  : " << actual << std::endl;

        return actual == expected;
    }

    // Other static test functions as before

    static std::string result(std::function<bool()> func, const std::string &unitTestName) {
        std::cout << std::endl << "> Begin " + unitTestName + ":" << std::endl;
        if (func()) {
            return "✅ Passed Unit Test " + unitTestName;
        } else {
            return "❌ Failed Unit Test " + unitTestName;
        }
    }

public:
    static void runAllTests() {
        // List of all tests paired with their names
        std::vector<std::pair<std::function<bool()>, std::string>> tests = {
                {LinkedListUnitTest1,                   "LinkedListUnitTest1"},
                {LinkedListUnitTest2,                   "LinkedListUnitTest2"},
                {LinkedListCopyConstructorTest1,        "LinkedListCopyConstructorTest1"},
                {LinkedListCopyAssignmentOperatorTest1, "LinkedListCopyAssignmentOperatorTest1"},
                {GraphUnitTest1,                        "GraphUnitTest1"},
                {GraphUnitTest2,                        "GraphUnitTest2"},
                {GraphCopyConstructorTest1,             "GraphCopyConstructorTest1"},
                {GraphCopyAssignmentOperatorTest1,      "GraphCopyAssignmentTest1"},
                {GraphBFSUnitTest1,                     "GraphBFSUnitTest1"},
                {GraphBFSUnitTest2,                     "GraphBFSUnitTest2"},
                {GraphShortestPathUnitTest1,            "GraphShortestPathUnitTest1"},
                {GraphShortestPathUnitTest2,            "GraphShortestPathUnitTest2"},
                {GraphShortestPathUnitTest3,            "GraphShortestPathUnitTest3"},
                {GraphShortestPathUnitTest4,            "GraphShortestPathUnitTest4"}
        };

        // Iterate through each test, execute it, and print the result
        for (const auto &test: tests) {
            std::cout << result(test.first, test.second) << std::endl;
        }
        std::cout << "Done" << std::endl;
    }
};

#endif //PROJECT5_UNITTESTS_H
