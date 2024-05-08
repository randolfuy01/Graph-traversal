#include "Graph.h"

#include <utility>

// Default constructor
LinkedList::LinkedList() {
    head = nullptr;
}

// Param constructor - Initialize the LinkedList with a head node
LinkedList::LinkedList(std::string val) {
    head = new Node();
    head -> val = std::move(val);
    head -> next = nullptr;
}

// Copy constructor - create a deep copy
LinkedList::LinkedList(const LinkedList &source) {
    Node *temp = source.head;
    if (temp == nullptr)
        head = nullptr;
    else {
        head = new Node;
        head->val = temp->val;
        Node *newCopy = head;
        while (temp->next) {
            temp = temp->next;
            newCopy->next = new Node;
            newCopy = newCopy->next;
            newCopy->val = temp->val;
        }
        newCopy->next = nullptr;
    }
}

// Destructor for the LinkedList
LinkedList::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr; // set head to nullptr to avoid the dangling pointer.
}

// Copy assignment operator
LinkedList &LinkedList::operator=(const LinkedList &source) {
    if (this == &source) {
        return *this;
    }

    // First, deallocate any value that this instance currently holds
    Node *current = head;
    while (current != nullptr) {
        Node *next = current->next;
        delete current;
        current = next;
    }

    // Then, copy values from source
    Node *temp = source.head;
    if (temp == nullptr) {
        head = nullptr;
    } else {
        head = new Node;
        head->val = temp->val;
        Node *newCopy = head;
        while (temp->next) {
            temp = temp->next;
            newCopy->next = new Node;
            newCopy = newCopy->next;
            newCopy->val = temp->val;
        }
        newCopy->next = nullptr;
    }

    return *this;
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
void LinkedList::addNode(std::string val) {
    Node* newNode = new Node();
    newNode -> val = std::move(val);
    newNode -> next = nullptr;

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current -> next = newNode;
    }
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
