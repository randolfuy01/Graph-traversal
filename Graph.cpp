#include "Graph.h"

LinkedList::LinkedList(int val) {
    head -> prev = nullptr;
    head -> next = nullptr;
    head -> val = val;
}

LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

void LinkedList::addNode(int val) {
    Node* curr = head; // start at the head
    while (curr->next != nullptr) {
        curr = curr-> next; // iterate through the list until we reach the end
    }
    Node* newNode = new Node; // new node we are going to insert
    newNode -> val = val; // set the value of new node
    newNode -> next = nullptr; // set new node to be the last node
    newNode -> prev = curr; // set the new node's previous node to the current node
    curr -> next = newNode; // set the current node's next node to be the new node
}

void Graph::addEdge(int source, int destination) {
    LinkedList edge = LinkedList(source);
    edge.addNode(destination);
    graph.push_back(edge);
}

Graph::~Graph() {
    for (auto & i : graph) {
        i.~LinkedList();
    }
}

Graph::Graph(int val) : LinkedList(val) {
    graph = std::vector<LinkedList>();
}
