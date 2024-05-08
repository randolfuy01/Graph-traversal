#ifndef PROJECT5_GRAPH_H
#define PROJECT5_GRAPH_H
#include <iostream>
#include <queue>
#include <vector>

// Node struct points to the next node
struct Node {
    Node* next;
    std::string val;
    int distance = 0;
};

// Singly Linked List implementation for the Graph
class LinkedList {

public:

    Node* head{};

    // Constructors

    LinkedList();

    explicit LinkedList(std::string val);

    // Big 3

    LinkedList(const LinkedList &source);

    virtual ~LinkedList();

    LinkedList& operator=(const LinkedList &source);

    // Member Functions

    void addNode(std::string val);

    std::string printLinkedList() const;

};

// Graph class that inherits from LinkedList
class Graph {
public:

    std::vector<LinkedList*> graph{};

    Graph();

    Graph(const Graph &source);

    Graph& operator=(const Graph &source);

    virtual ~Graph();

    void addEdge(const std::string& vertex1, const std::string& vertex2);

    void breadthFirstSearch(const std::string& start);

    void shortestPath(std::string start, std::string end);

    std::string printGraph() const;

};
#endif
