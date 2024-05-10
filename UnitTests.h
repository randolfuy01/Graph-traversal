//
// Created by Randolf Gabrielle Uy on 5/7/24.
//

#ifndef PROJECT5_UNITTESTS_H
#define PROJECT5_UNITTESTS_H

#include <iostream>
#include <sstream>
#include "Graph.h"

typedef bool (*UnitTestFunc)();

bool LinkedListUnitTest1() {
    LinkedList list = *new LinkedList("A");
    list.enqueue("B");
    list.enqueue("C");
    list.enqueue("D"); // Should be A -> B -> C -> D
    std::string expected = "A -> B -> C -> D";
    std::string actual = list.printLinkedList();
    std::cout << "actual:   " << actual << "\nexpected: " << expected << std::endl;
    return expected == actual;
}

bool LinkedListUnitTest2() {
    LinkedList list = *new LinkedList("San Francisco");
    list.enqueue("Los Angeles");
    list.enqueue("New York");
    std::string expected = "San Francisco -> Los Angeles -> New York";
    std::string actual = list.printLinkedList();
    std::cout << "actual:   " << actual << "\nexpected: " << expected << std::endl;
    return expected == actual;
}

bool LinkedListCopyConstructorTest1() {
    LinkedList list1;
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

bool LinkedListCopyAssignmentOperatorTest1() {
    LinkedList list1;
    list1.enqueue("Hello");
    list1.enqueue("World");

    // Create an empty list and then assign to it to make a copy.
    LinkedList list2;
    list2 = list1;

    // Modify list1
    list1.enqueue("New Node");

    // Check that list2 didn't change after changing list1
    bool isCopyAssignmentPassing = (list2.printLinkedList() == "Hello -> World");

    return isCopyAssignmentPassing;
}

// TO-DO: Implement Graph Unit Tests
bool GraphUnitTest1() {
    Graph graph = *new Graph();
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

bool GraphUnitTest2() {
    Graph graph = *new Graph();
    graph.addEdge("San Francisco", "Los Angeles");
    graph.addEdge("San Francisco", "New York");
    graph.addEdge("Los Angeles", "New York");
    std::string expected = "San Francisco -> Los Angeles -> New York\nLos Angeles -> San Francisco -> New York\nNew York -> San Francisco -> Los Angeles\n";
    std::string actual = graph.printGraph();
    std::cout << "actual: \n" << actual << std::endl;
    std::cout << "expected: \n" << expected;
    std::vector<std::vector<std::string>> expectedValues = {{"San Francisco", "Los Angeles", "New York"}, {"Los Angeles", "San Francisco", "New York"}, {"New York", "San Francisco", "Los Angeles"}};
    for (int i = 0; i < graph.edges.size(); i++) {
        LinkedList* list = graph.edges[i];
        Node* current = list->head;
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

bool GraphCopyConstructorTest1() {
    Graph originalGraph;

    originalGraph.addEdge("A", "B");
    originalGraph.addEdge("A", "C");
    originalGraph.addEdge("B", "D");
    originalGraph.addEdge("C", "D");

    // Make a copy of the original graph
    Graph copiedGraph = originalGraph; // Calls the copy constructor

    // Check if the printed representations of the original and copied graph are same
    return (originalGraph.printGraph() == copiedGraph.printGraph());
}

std::string result (UnitTestFunc func, const std::string& unitTestName) {
    std::cout << std::endl << "> Begin " + unitTestName + ":" << std::endl;
    if (func()) {
        return "✅Passed Unit Test " + unitTestName;
    } else {
        return "❌ Failed Unit Test " + unitTestName;
    }
}

bool GraphCopyAssignmentOperatorTest1() {
    Graph originalGraph;
    originalGraph.addEdge("A", "B");
    originalGraph.addEdge("A", "C");
    originalGraph.addEdge("B", "D");
    originalGraph.addEdge("C", "D");

    // Create an empty graph for assignment
    Graph copiedGraph;

    // Create a copy of the original graph
    copiedGraph = originalGraph;

    // Check if the original graph matches the copied graph
    return (originalGraph.printGraph() == copiedGraph.printGraph());
}

bool GraphBFSUnitTest1() {
    Graph graph;
    graph.addEdge("A", "B");
    graph.addEdge("A", "C");
    graph.addEdge("B", "D");
    graph.addEdge("C", "D");
    graph.addEdge("D", "E");
    graph.addEdge("E", "F");
    graph.addEdge("F", "G");

    std::string expected = "A -> B -> C -> D -> E -> F -> G";
    std::string actual;
    
    graph.breadthFirstSearch("A");

    return expected == actual;
}

void runLinkedListUnitTests() {
    std::cout << result(LinkedListUnitTest1, "LinkedListUnitTest1") << std::endl;
    std::cout << result(LinkedListUnitTest2, "LinkedListUnitTest2") << std::endl;
    std::cout << result(LinkedListCopyConstructorTest1, "LinkedListCopyConstructorTest1") << std::endl;
    std::cout << result(LinkedListCopyAssignmentOperatorTest1, "LinkedListCopyAssignmentOperatorTest1") << std::endl;
    std::cout << result(GraphUnitTest1, "GraphUnitTest1") << std::endl;
    std::cout << result(GraphUnitTest2, "GraphUnitTest2") << std::endl;
    std::cout << result(GraphCopyConstructorTest1, "GraphCopyConstructorTest1") << std::endl;
    std::cout << result(GraphCopyAssignmentOperatorTest1, "GraphCopyAssignmentTest1") << std::endl;
    GraphBFSUnitTest1();
}
#endif //PROJECT5_UNITTESTS_H
