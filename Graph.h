#ifndef PROJECT5_GRAPH_H
#define PROJECT5_GRAPH_H
#include <iostream>
#include <queue>
#include <vector>

// Node struct points to the next node
struct Node {
    Node* next;
    std::string val;
    std::string color = "white";
    Node* parent = nullptr;
    int distance = 9999;
};

// Singly Linked List implementation for the Graph
class LinkedList {
private:
    
    Node* createNode(std::string val);

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

    void enqueue(std::string val);
    void enqueue(Node* newNode);
    Node dequeue();

    std::string printLinkedList() const;

};

// Graph class that inherits from LinkedList
class Graph {
public:

    std::vector<LinkedList*> edges{};
    std::vector<Node*> vertices{};

    Graph();

    Graph(const Graph &source);
    Graph& operator=(const Graph &source);
    virtual ~Graph();

    void addEdge(const std::string& vertex1, const std::string& vertex2);
    void addVertex(const std::string& vertex);

    void breadthFirstSearch(const std::string& start);

    void shortestPath(std::string start, std::string end);

    std::string printGraph() const;
    void printBFSTree() const;
    void printBFSTreeHelper(Node* node, int level) const;

};
#endif
