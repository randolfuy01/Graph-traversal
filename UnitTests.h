//
// Created by Randolf Gabrielle Uy on 5/7/24.
//

#ifndef PROJECT5_UNITTESTS_H
#define PROJECT5_UNITTESTS_H

#include <iostream>
#include "Graph.h"

typedef bool (*UnitTestFunc)();

bool LinkedListUnitTest1() {
    LinkedList list = *new LinkedList("A");
    list.addNode("B");
    list.addNode("C");
    list.addNode("D"); // Should be A -> B -> C -> D
    std::string expected = "A -> B -> C -> D";
    std::string actual = list.printLinkedList();
    std::cout << "actual:   " << actual << "\nexpected: " << expected << std::endl;
    return expected == actual;
}

bool LinkedListUnitTest2() {
    LinkedList list = *new LinkedList("San Francisco");
    list.addNode("Los Angeles");
    list.addNode("New York");
    std::string expected = "San Francisco -> Los Angeles -> New York";
    std::string actual = list.printLinkedList();
    std::cout << "actual:   " << actual << "\nexpected: " << expected << std::endl;
    return expected == actual;
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
    std::string expected = "san Francisco -> Los Angeles -> New York\nLos Angeles -> San Francisco -> New York\nNew York -> San Francisco -> Los Angeles\n";
    std::string actual = graph.printGraph();
    std::cout << "actual: \n" << actual << std::endl;
    std::cout << "expected: \n" << expected;
    std::vector<std::vector<std::string>> expectedValues = {{"San Francisco", "Los Angeles", "New York"}, {"Los Angeles", "San Francisco", "New York"}, {"New York", "San Francisco", "Los Angeles"}};
    for (int i = 0; i < graph.graph.size(); i++) {
        LinkedList* list = graph.graph[i];
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

std::string result (UnitTestFunc func, const std::string& unitTestName) {
    std::cout << std::endl << "> Begin " + unitTestName + ":" << std::endl;
    if (func()) {
        return "✅Passed Unit Test " + unitTestName;
    } else {
        return "❌ Failed Unit Test " + unitTestName;
    }
}

void runLinkedListUnitTests() {
    std::cout << result(LinkedListUnitTest1, "LinkedListUnitTest1") << std::endl;
    std::cout << result(LinkedListUnitTest2, "LinkedListUnitTest2") << std::endl;
    std::cout << result(GraphUnitTest1, "GraphUnitTest1") << std::endl;
    std::cout << result(GraphUnitTest2, "GraphUnitTest2") << std::endl;
}
#endif //PROJECT5_UNITTESTS_H
