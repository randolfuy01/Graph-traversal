#ifndef PROJECT5_GRAPH_H
#define PROJECT5_GRAPH_H
#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <climits>  // For INT_MAX

// Node struct points to the next node
struct Node {
    Node* next = nullptr;
    std::string val;
    std::string color = "white";
    Node* parent = nullptr;
    int distance = INT_MAX; // signifies unvisited or unreachable node
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
    Node* dequeue();

    std::string printLinkedList() const;

};

// Graph class that inherits from LinkedList
class Graph {
private:
    friend class UnitTest;

    Node* findVertex(const std::string& vertex) const;
    Node* findVertex(Node* vertex) const;
    LinkedList* findEdge(const std::string& vertex) const;
    LinkedList* findEdge(Node* vertex) const;

    std::vector<LinkedList*> edges{};
    std::vector<Node*> vertices{};

public:

    Graph();
    Graph(const Graph &source);
    virtual ~Graph();
    Graph& operator=(const Graph &source);

    void addEdge(const std::string &vertex1, const std::string &vertex2);
    void addVertex(const std::string &vertex);

    void breadthFirstSearch(const std::string &start);
    std::string shortestPath(const std::string &start, const std::string &end);
    void processNode(Node *node, LinkedList &queue);

    std::string printGraph() const;
    void printBFSTree() const;
    void printBFSTreeHelper(Node *node, int level) const;

};
#endif
