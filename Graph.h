#ifndef PROJECT5_GRAPH_H
#define PROJECT5_GRAPH_H
#include <queue>
#include <vector>

// Double Linked List implementation for the Graph
class LinkedList {

    // Node struct points to the previous and next node
    struct Node {
        Node* prev;
        Node* next;
        int val;
    };

public:

    explicit LinkedList(int val);

    virtual ~LinkedList();

    void addNode(int val);

private:
    Node* head{};

};

// Graph class that inherits from LinkedList
class Graph : private LinkedList{
public:

    explicit Graph(int val);

    virtual ~Graph();

    void addEdge(int source, int destination);

    void BreadthFirstSearch(int start);

    void ShortestPath(int start, int end);

private:
    std::vector<LinkedList> graph{};

};
#endif
