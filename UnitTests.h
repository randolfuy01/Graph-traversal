//
// Created by Randolf Gabrielle Uy on 5/7/24.
//

#ifndef PROJECT5_UNITTESTS_H
#define PROJECT5_UNITTESTS_H

#include <iostream>
#include <sstream>
#include "Graph.h"

class UnitTest {

private:

    static bool LinkedListIntegerUnitTest() {
        LinkedList<int> list = *new LinkedList<int>(1);
        list.enqueue(2);
        list.enqueue(3);
        list.enqueue(4);
        std::string expected = "1 -> 2 -> 3 -> 4";
        std::string actual = list.printLinkedList();
        return expected == actual;
    }

    static bool LinkedListStringUnitTest() {
        LinkedList<std::string> list;
        list.enqueue("San Francisco");
        list.enqueue("Los Angeles");
        list.enqueue("New York");
        std::string expected = "San Francisco -> Los Angeles -> New York";
        std::string actual = list.printLinkedList();
        return expected == actual;
    }

    static bool LinkedListCharUnitTest() {
        LinkedList<char> list;
        list.enqueue('a');
        list.enqueue('b');
        list.enqueue('c');
        std::string expected = "a -> b -> c";
        std::string actual = list.printLinkedList();
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
        LinkedList<int> list1;
        list1.enqueue(1);
        list1.enqueue(2);

        // Create an empty list and then assign to it to make a copy.
        LinkedList<int> list2;
        list2 = list1;

        // Modify list1
        list1.enqueue(3);

        // Check that list2 didn't change after changing list1
        return (list2.printLinkedList() == "1 -> 2");
    }

    static bool GraphUnitTest1() {
        Graph<char> graph = *new Graph<char>();
        graph.addEdge('A', 'B');
        graph.addEdge('A', 'C');
        graph.addEdge('A', 'D');
        graph.addEdge('B', 'C');
        graph.addEdge('B', 'D');
        graph.addEdge('C', 'D');
        std::string expected = "A -> B -> C -> D\nB -> A -> C -> D\nC -> A -> B -> D\nD -> A -> B -> C\n";
        std::string actual = graph.printGraphEdges();
        return expected == actual;
    }

    static bool GraphUnitTest2() {
        Graph graph = *new Graph<std::string>();
        graph.addEdge("San Francisco", "Los Angeles");
        graph.addEdge("San Francisco", "New York");
        graph.addEdge("Los Angeles", "New York");
        std::string expected = "San Francisco -> Los Angeles -> New York\nLos Angeles -> San Francisco -> New York\nNew York -> San Francisco -> Los Angeles\n";
        std::string actual = graph.printGraphEdges();
        std::vector<std::vector<std::string>> expectedValues = {{"San Francisco", "Los Angeles",   "New York"},
                                                                {"Los Angeles",   "San Francisco", "New York"},
                                                                {"New York",      "San Francisco", "Los Angeles"}};

        for (int i = 0; i < graph.getEdges().size(); i++) {
            LinkedList<std::string> *list = graph.getEdges()[i];
            const Node<std::string> *current = list->begin();
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
        return (originalGraph.printGraphEdges() == copiedGraph.printGraphEdges());
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
        return (originalGraph.printGraphEdges() == copiedGraph.printGraphEdges());
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

        // Verify that the BFS has correctly assigned parents in the BFS tree starting from node 'C'
        if (graph.findVertex("A")->parent != graph.findVertex("C")) return false;
        if (graph.findVertex("F")->parent != graph.findVertex("C")) return false;
        if (graph.findVertex("B")->parent != graph.findVertex("A")) return false;
        if (graph.findVertex("D")->parent != graph.findVertex("B")) return false;
        if (graph.findVertex("E")->parent != graph.findVertex("B")) return false;

        return true;
    }

    // Test for when path found
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

        return expected == actual;
    }

    // Test for when start vertex does not exist
    static bool GraphShortestPathUnitTest2() {
        Graph<std::string> graph;
        graph.addEdge("A", "B");
        graph.addEdge("A", "C");
        graph.addEdge("B", "D");
        graph.addEdge("D", "E");

        std::string expected = "Error: Start vertex 'X' not found";
        std::string actual = graph.shortestPath("X", "B"); // Non-existent start vertex

        return expected == actual;
    }

    // Test for when the end vertex does not exist
    static bool GraphShortestPathUnitTest3() {
        Graph<std::string> graph;
        graph.addEdge("A", "B");
        graph.addEdge("A", "C");
        graph.addEdge("B", "D");
        graph.addEdge("D", "E");

        std::string expected = "Error: End vertex 'Y' not found";
        std::string actual = graph.shortestPath("A", "Y"); // Non-existent end vertex

        return actual == expected;
    }

    // Test when both vertices exist, but not connected
    static bool GraphShortestPathUnitTest4() {
        Graph<std::string> graph;
        graph.addEdge("A", "B");
        graph.addEdge("A", "C");
        graph.addEdge("B", "D");
        graph.addEdge("D", "E");

        graph.addVertex("Z");

        std::string expected = "No path from A to Z";
        std::string actual = graph.shortestPath("A", "Z");

        return actual == expected;
    }

    // Helper function to print the result of a unit test
    static std::string result(std::function<bool()> func, const std::string &unitTestName) {
        if (func()) {
            return "✅ Passed Unit Test " + unitTestName;
        } else {
            return "❌ Failed Unit Test " + unitTestName;
        }
    }

public:
    static void runAllTests() {
        std::cout << "Running all unit tests..." << std::endl;

        // List of all tests paired with their names
        std::vector<std::pair<std::function<bool()>, std::string>> tests = {
                {LinkedListIntegerUnitTest,             "LinkedListIntegerUnitTest"},
                {LinkedListStringUnitTest,              "LinkedListStringUnitTest"},
                {LinkedListCharUnitTest,                "LinkedListCharUnitTest"},
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
