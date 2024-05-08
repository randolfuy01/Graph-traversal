#include "Graph.h"

#include <utility>


// Initialize the LinkedList with a head node
LinkedList::LinkedList(std::string val) {
    head = new Node();
    head -> val = std::move(val);
    head -> next = nullptr;
}

// TO-DO: Destructor for the LinkedList ** FIX ME IF WRONG
LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}

// Print the LinkedList ex. A -> B -> C -> D
std::string LinkedList::printLinkedList() const {
    std::string result;
    Node* current = head;
    while (current->next != nullptr) {
        result += current->val + " -> ";
        current = current->next;
    }
    result += current->val;
    return result;
}

// Add a node to the LinkedList
void LinkedList::addNode(std::string val) const {
    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    Node* newNode = new Node();
    newNode -> val = std::move(val);
    newNode -> next = nullptr;
    current -> next = newNode;
}


// TO-DO: Implement or fix
void Graph::addEdge(const std::string& vertex1, const std::string& vertex2) {
    LinkedList* list1 = nullptr;
    LinkedList* list2 = nullptr;

    for (auto& list : graph) {
        if (list->head->val == vertex1) {
            list1 = list;
        }
        if (list->head->val == vertex2) {
            list2 = list;
        }
    }

    if (list1 == nullptr) {
        list1 = new LinkedList(vertex1);
        graph.push_back(list1);
    }
    if (list2 == nullptr) {
        list2 = new LinkedList(vertex2);
        graph.push_back(list2);
    }

    // Add the edges
    list1->addNode(vertex2);
    list2->addNode(vertex1);
}

std::string Graph::printGraph() const {
    std::string result;
    for (auto & i : graph) {
        result += i->printLinkedList() + "\n";
    }
    return result;
}

// TO-DO: Implement or fix
Graph::~Graph() {
    for (auto & i : graph) {
        delete i;
    }
}

Graph::Graph() {
    graph = std::vector<LinkedList*>();
}

// TO-DO: Implement breadthFirstSearch
void Graph::breadthFirstSearch(const std::string& start) {}

// TO-DO: Implement shortestPath
void Graph::shortestPath(std::string start, std::string end) {}
