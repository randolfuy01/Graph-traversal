#ifndef PROJECT5_GRAPH_H
#define PROJECT5_GRAPH_H

#include <iostream>
#include <queue>
#include <vector>
#include <set>
#include <climits>  // For INT_MAX

// --------------------------
// Node Struct Declaration
// --------------------------
template<typename T>
struct Node {
    Node *next = nullptr;
    T val;
    std::string color = "white";
    Node *parent = nullptr;
    int distance = INT_MAX; // signifies unvisited or unreachable node
};

// --------------------------
// LinkedList Class Declaration
// --------------------------
template<typename T>
class LinkedList {

private:

    Node<T> *head{};

    Node<T> *createNode(T val) {
        Node<T> *newNode = new Node<T>;
        newNode->val = std::move(val);
        newNode->next = nullptr;
        return newNode;
    }


public:


    LinkedList() {
        head = nullptr;
    }

    LinkedList(T val) {
        head = new Node<T>();
        head->val = std::move(val);
        head->next = nullptr;
    }

    LinkedList(const LinkedList &source) {
        Node<T> *temp = source.head;
        if (temp == nullptr)
            head = nullptr;
        else {
            head = new Node<T>;
            head->val = temp->val;
            Node<T> *newCopy = head;
            while (temp->next) {
                temp = temp->next;
                newCopy->next = new Node<T>;
                newCopy = newCopy->next;
                newCopy->val = temp->val;
            }
            newCopy->next = nullptr;
        }
    }

    ~LinkedList() {
        Node<T> *current = head;
        while (current != nullptr) {
            Node<T> *next = current->next;
            delete current;
            current = next;
        }
        head = nullptr; // set head to nullptr to avoid the dangling pointer.
    }

    LinkedList &operator=(const LinkedList &source) {
        if (this == &source) {
            return *this;
        }

        // First, deallocate any value that this instance currently holds
        Node<T> *current = head;
        while (current != nullptr) {
            Node<T> *next = current->next;
            delete current;
            current = next;
        }

        // Then, copy values from source
        Node<T> *temp = source.head;
        if (temp == nullptr) {
            head = nullptr;
        } else {
            head = new Node<T>;
            head->val = temp->val;
            Node<T> *newCopy = head;
            while (temp->next) {
                temp = temp->next;
                newCopy->next = new Node<T>;
                newCopy = newCopy->next;
                newCopy->val = temp->val;
            }
            newCopy->next = nullptr;
        }

        return *this;
    }

    // Member Functions

    void enqueue(T val) {
        Node<T> *newNode = createNode(val);
        enqueue(newNode);
    }


    void enqueue(Node<T> *newNode) {

        // If the LinkedList is empty, set the head to the new node
        if (head == nullptr) {
            head = newNode;

            // Otherwise, add the new node to the end of the LinkedList
        } else {
            Node<T> *current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newNode;
        }
    }


    Node<T> *dequeue() {
        Node<T> *current = head;
        Node<T> *previous = nullptr;

        // If the LinkedList is empty, return nullptr
        if (head == nullptr) {
            return nullptr;
        }

        Node<T> *temp = head;
        head = head->next;
        return temp;
    }

    const Node<T> *begin() const { return head; }

// Print the LinkedList ex. A -> B -> C -> D
    std::string printLinkedList() const {
        std::string result;
        Node<T> *current = head;
        while (current->next != nullptr) {
            result += current->val + " -> ";
            current = current->next;
        }
        result += current->val;
        return result;
    }

};

// --------------------------
// Graph Class Declaration
// --------------------------
template<typename T>
class Graph {
private:
    friend class UnitTest;

    Node<T> *findVertex(const T &vertex) const {
        for (auto &i: vertices) {
            if (i->val == vertex) {
                return i;
            }
        }
        return nullptr;
    }

// Find a vertex in the vertices list
    Node<T> *findVertex(Node<T> *vertex) const {
        return findVertex(vertex->val);
    }


// Find the LinkedList that contains the edges for a given vertex
    LinkedList<T> *findEdge(Node<T> *vertex) const {
        return findEdge(vertex->val);
    }

    LinkedList<T> *findEdge(const T &vertex) const {
        for (auto &edge: edges) {
            if (edge->begin()->val == vertex) {
                return edge;
            }
        }
        return nullptr;
    }

    std::vector<LinkedList<T> *> edges{};
    std::vector<Node<T> *> vertices{};

public:

    Graph() {
        edges = std::vector<LinkedList<T> *>();
    }

// Copy constructor - create a deep copy
    Graph(const Graph &source) {
        for (auto &i: source.edges) {
            LinkedList<T> *temp = new LinkedList(*i);
            edges.push_back(temp);
        }
    }

    ~Graph() {
        for (auto &i: edges) {
            delete i;
        }
    }

// Copy assignment operator
    Graph &operator=(const Graph &source) {
        if (this == &source) {
            return *this;
        }

        // Clean up existing resources
        for (auto &i: edges) {
            delete i;
        }
        edges.clear();

        // Copy LinkedList from source
        for (auto &i: source.edges) {
            LinkedList<T> *temp = new LinkedList(*i);
            edges.push_back(temp);
        }

        return *this;
    }

// This function adds an edge between two vertices in the edges, creating new vertex lists if they don't already exist.
    void addEdge(const T &vertex1, const T &vertex2) {
        LinkedList<T> *list1 = nullptr;
        LinkedList<T> *list2 = nullptr;

        // Search for if the vertex already exists in the edges
        for (auto &list: edges) {
            if (list->begin()->val == vertex1) {
                list1 = list;
            };
            if (list->begin()->val == vertex2) {
                list2 = list;
            }
        }

        // If the vertex doesn't exist, create a new vertex list
        if (list1 == nullptr) {
            list1 = new LinkedList(vertex1);
            edges.push_back(list1);
        }
        if (list2 == nullptr) {
            list2 = new LinkedList(vertex2);
            edges.push_back(list2);
        }

        // Add the edges
        list1->enqueue(vertex2);
        list2->enqueue(vertex1);

        // Add the vertices
        addVertex(vertex1);
        addVertex(vertex2);
    }

// This function adds a vertex to the vertices list
    void addVertex(const T &vertex) {
        for (auto &i: vertices) {
            if (i->val == vertex) {
                return;
            }
        }
        Node<T> *newNode = new Node<T>();
        newNode->val = vertex;
        vertices.push_back(newNode);
    }

    void breadthFirstSearch(const T &start) {
        // Find the starting vertex
        Node<T> *startNode = findVertex(start);

        // If the starting vertex is not found, return
        if (startNode == nullptr) {
            throw std::runtime_error("Error: Start vertex '" + start + "' not found");
        }

        // Reset all nodes to initial state before BFS traversal
        for (auto &vertex: vertices) {
            vertex->color = "white";
            vertex->distance = INT_MAX;
            vertex->parent = nullptr;
        }

        // Initialize the BFS queue with the start node and set its initial state.
        LinkedList<T> bfsQueue;
        bfsQueue.enqueue(startNode);
        startNode->color = "gray";
        startNode->distance = 0;

        // Dequeue nodes from the BFS queue and process them until the queue is empty.
        while (bfsQueue.begin() != nullptr) {
            Node<T> *current = bfsQueue.dequeue();
            processNode(current, bfsQueue);
        }

    }

// Calculates the shortest path in the graph between two given nodes
    std::string shortestPath(const T &start, const T &end) {

        // Handle the case where start is the same as end
        if (start == end) {
            return "Shortest path from " + start + " to " + end + ": " + start;
        }


        // Execute breadth-first search from the start node
        try {
            breadthFirstSearch(start);
        } catch (const std::runtime_error &e) {
            return e.what();
        }

        // Find the start and end nodes
        Node<T> *startNode = findVertex(start);
        Node<T> *endNode = findVertex(end);

        // Check and handle different error scenarios
        if (startNode == nullptr) {
            return "Error: Start vertex '" + start + "' not found";
        }
        if (endNode == nullptr) {
            return "Error: End vertex '" + end + "' not found";
        }
        if (endNode->parent == nullptr) {
            return "No path from " + start + " to " + end;
        }

        // Construct the path from end to start using parent pointers
        std::string path = endNode->val;
        Node<T> *current = endNode->parent;
        while (current != nullptr) {
            path = current->val + " -> " + path;
            current = current->parent;
        }

        return "Shortest path from " + start + " to " + end + ": " + path;
    }

    void processNode(Node<T> *node, LinkedList<T> &queue) {
        node->color = "black";  // Mark as processed to prevent re-enqueue
        LinkedList<T> *adjacencyList = findEdge(node->val);

        // Update distances and enqueue unvisited vertices for BFS traversal
        for (Node<T> *adjacentNode = adjacencyList->begin()->next;
             adjacentNode != nullptr; adjacentNode = adjacentNode->next) {
            Node<T> *adjacentVertex = findVertex(adjacentNode->val);
            if (adjacentVertex->color == "white") {
                adjacentVertex->color = "gray";
                adjacentVertex->distance = node->distance + 1;
                adjacentVertex->parent = node;
                queue.enqueue(adjacentVertex);
            }
        }
    }

// Prints edges
    std::string printGraph() const {
        std::string result;
        for (auto &i: edges) {
            result += i->printLinkedList() + "\n";
        }
        return result;
    }

    void printBFSTree() const {
        Node<T> *parent = nullptr;
        for (auto &i: vertices) {
            if (i->parent == nullptr) {
                printBFSTreeHelper(i, 0);
            }
        }
    }

    void printBFSTreeHelper(Node<T> *node, int level) const {
        if (node == nullptr) {
            return;
        }

        for (int i = 0; i < level; i++) {
            std::cout << "   ";
        }

        std::cout << (level == 0 ? "   " : "|- ") << node->val << ": " << node->distance << std::endl;

        for (auto &i: vertices) {
            if (i->parent == node) {
                printBFSTreeHelper(i, level + 1);
            }
        }
    }

};

#endif
