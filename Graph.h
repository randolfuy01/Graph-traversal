#ifndef PROJECT5_GRAPH_H
#define PROJECT5_GRAPH_H
#include <iostream>
#include <queue>
#include <vector>

// Node struct points to the previous and next node
struct Node {
    Node* next;
    std::string val;
    int distance = 0;
};

// Double Linked List implementation for the Graph
class LinkedList {

public:

    Node* head{};

    LinkedList();

    LinkedList(std::string val);

    virtual ~LinkedList();

    void addNode(std::string val) const;

    std::string printLinkedList() const;

};

// Graph class that inherits from LinkedList
class Graph {
public:

    std::vector<LinkedList*> graph{};

    Graph();

    virtual ~Graph();

    void addEdge(const std::string& vertex1, const std::string& vertex2);

    void breadthFirstSearch(const std::string& start);

    void shortestPath(std::string start, std::string end);

    std::string printGraph() const;

};
#endif
