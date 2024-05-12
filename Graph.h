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

// Section: Private Member Variables

    Node<T> *head{};

// Section: Private Member Functions

    Node<T> *createNode(T val) {
        Node<T> *newNode = new Node<T>;
        newNode->val = std::move(val);
        newNode->next = nullptr;
        return newNode;
    }

    void clearList() {
        Node<T> *current = head;
        while (current != nullptr) {
            Node<T> *next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
    }

public:

// Section: Public Constructors, Destructor, and Assignment Operator

    // Default Constructor - create an empty LinkedList
    LinkedList() : head(nullptr) {}

    // Constructor - create a new LinkedList with a single node
    LinkedList(T val) {
        head = createNode(val);
    }

    // Copy constructor - create a deep copy
    LinkedList(const LinkedList &source) {
        if (source.head == nullptr) {
            head = nullptr;
        } else {
            // Take care of the first Node separately (since it has no predecessor Node)
            head = new Node<T>;
            head->val = source.head->val;
            head->next = nullptr;

            Node<T> *thisCurrent = head;
            Node<T> *sourceCurrent = source.head->next;

            // Deep Copy source LinkedList
            while (sourceCurrent) {
                Node<T> *newNode = new Node<T>;
                newNode->val = sourceCurrent->val;
                newNode->next = nullptr;

                thisCurrent->next = newNode;
                thisCurrent = thisCurrent->next;
                sourceCurrent = sourceCurrent->next;  // Move forward in source LinkedList
            }
        }
    } // End of copy constructor

    // Destructor - deallocate memory
    ~LinkedList() {
        clearList();
    }

    // Copy assignment operator
    LinkedList &operator=(const LinkedList &source) {
        if (this != &source) {
            // First, deallocate any value that this instance currently holds
            clearList();  // Call clearList helper function to deallocate memory

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
        }
        return *this;
    } // End of copy assignment operator

// Section: Public Member Functions

    // Add a new node to the end of the list with the given value
    void enqueue(T val) {
        Node<T> *newNode = createNode(val);
        enqueue(newNode);
    }

    // Add a new node to the end of the list
    void enqueue(Node<T> *newNode) {

        // If the new node is nullptr, throw an exception
        if (newNode == nullptr) {
            throw std::invalid_argument("Attempted to enqueue a nullptr");
        }

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
    } // End of enqueue


    // Remove the first node from the LinkedList and return it
    Node<T> *dequeue() {

        // If the LinkedList is empty, return nullptr
        if (head == nullptr) {
            return nullptr;
        }

        Node<T> *current = head;
        Node<T> *previous = nullptr;

        Node<T> *temp = head;
        head = head->next;
        return temp;
    } // End of dequeue

    // Return the first node in the LinkedList
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
    } // End of printLinkedList

}; // End of LinkedList

// --------------------------
// Graph Class Declaration
// --------------------------
template<typename T>
class Graph {

private:

// Section: Private Friend Class

    friend class UnitTest;

// Section: Private Member Variables

    std::vector<LinkedList<T> *> edges{};
    std::vector<Node<T> *> vertices{};

// Section: Private Member Functions

    // Find a vertex in the vertices list by value
    Node<T> *findVertex(const T &vertexValue) const {
        for (auto &vertex: vertices) {
            if (vertex->val == vertexValue) {
                return vertex;
            }
        }
        return nullptr;
    }

    // Find a vertex in the vertices list by Node
    Node<T> *findVertex(Node<T> *vertex) const {
        return findVertex(vertex->val);
    }

    // Find an edge in the edges list by a vertex value
    LinkedList<T> *findEdge(const T &vertex) const {
        for (auto &edge: edges) {
            if (edge->begin()->val == vertex) {
                return edge;
            }
        }
        return nullptr;
    }

    // Overloaded findEdge function that takes a Node pointer and uses its value to find the edge
    LinkedList<T> *findEdge(Node<T> *vertex) const {
        return findEdge(vertex->val);
    }

public:

// Section: Public Constructors, Destructor, and Assignment Operator

    // Default Constructor - create an empty Graph
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

    // Destructor - deallocate memory
    ~Graph() {
        for (auto &i: edges) {
            delete i;
        }
    }

    // Copy assignment operator - create a deep copy
    Graph &operator=(const Graph &source) {
        if (this == &source) {
            return *this;
        }

        // Clean up existing resources
        for (auto &edge: edges) {
            delete edge;
        }
        edges.clear();

        // Copy LinkedList from source
        for (auto &edge: source.edges) {
            LinkedList<T> *temp = new LinkedList(*edge);
            edges.push_back(temp);
        }

        return *this;
    } // End of copy assignment operator

// Section: Public Member Functions

    // Add an edge between two vertices in the graph
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
    } // End of addEdge

    // Add a vertex to the vertices list by using input value to create a new Node
    void addVertex(const T &vertexValue) {
        for (auto &vertex: vertices) {
            if (vertex->val == vertexValue) {
                return;
            }
        }

        Node<T> *newNode = new Node<T>();
        newNode->val = vertexValue;
        vertices.push_back(newNode);
    }

    // Breadth-first search traversal of the graph starting from given vertex value
    void breadthFirstSearch(const T &startVertexValue) {
        // Find the starting vertex
        Node<T> *startNode = findVertex(startVertexValue);

        // If the starting vertex is not found, return
        if (startNode == nullptr) {
            throw std::runtime_error("Error: Start vertex '" + startVertexValue + "' not found");
        }

        // Reset all nodes to initial state before BFS traversal
        for (auto &vertex: vertices) {
            vertex->color = "white";
            vertex->distance = INT_MAX;
            vertex->parent = nullptr;
        }

        // Initialize the BFS queue with the startVertexValue node and set its initial state.
        LinkedList<T> bfsQueue;
        bfsQueue.enqueue(startNode);
        startNode->color = "gray";
        startNode->distance = 0;

        // Dequeue nodes from the BFS queue and process them until the queue is empty.
        while (bfsQueue.begin() != nullptr) {
            Node<T> *current = bfsQueue.dequeue();
            processNode(current, bfsQueue);
        }

    } // End of breadthFirstSearch

    // Shortest path from two given vertex values using breadth-first search
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
    } // End of shortestPath

    // Helper function to process a node during BFS traversal
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
    } // End of processNode

    // Prints edges
    std::string printGraphEdges() const {
        std::string result;
        for (auto &i: edges) {
            result += i->printLinkedList() + "\n";
        }
        return result;
    }


    // Traverse the graph and print the BFS tree by calling the printBFSTreeHelper function
    void printBFSTree() const {
        Node<T> *parent = nullptr;
        for (auto &vertex: vertices) {
            if (vertex->parent == nullptr) {
                printBFSTreeHelper(vertex, 0);
            }
        }
    }

    // Prints the BFS tree where each node is indented based on its level in the tree
    void printBFSTreeHelper(Node<T> *node, int level) const {
        if (node == nullptr) {
            return;
        }

        for (int i = 0; i < level; i++) {
            std::cout << "   ";
        }

        std::cout << (level == 0 ? "   " : "|- ") << node->val << ": " << node->distance << std::endl;

        for (auto &childNode: vertices) {
            if (childNode->parent == node) {
                printBFSTreeHelper(childNode, level + 1);
            }
        }
    } // End of printBFSTreeHelper

}; // End of Graph

#endif
