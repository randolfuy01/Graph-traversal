#include "Graph.h"

#include <utility>

// START OF LINKED LIST CLASS

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

// Enqueue the end of the LinkedList with a new node
void LinkedList::enqueue(std::string val) {
    Node* newNode = createNode(val);
    enqueue(newNode);
}

void LinkedList::enqueue(Node* newNode) {

    // If the LinkedList is empty, set the head to the new node
    if (head == nullptr) {
        head = newNode;
    
    // Otherwise, add the new node to the end of the LinkedList
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Dequeue the front node of the LinkedList
Node* LinkedList::dequeue() {
    Node* current = head;
    Node* previous = nullptr;

    // If the LinkedList is empty, return nullptr
    if (head == nullptr) {
        return nullptr;
    }

    Node* temp = head;
    head = head->next;
    return temp;
}

Node* LinkedList::createNode(std::string val) {
    Node* newNode = new Node;
    newNode->val = std::move(val);
    newNode->next = nullptr;
    return newNode;
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

// END OF LINKED LIST CLASS


// START OF GRAPH CLASS


// This function adds an edge between two vertices in the edges, creating new vertex lists if they don't already exist.
void Graph::addEdge(const std::string& vertex1, const std::string& vertex2) {
    LinkedList* list1 = nullptr;
    LinkedList* list2 = nullptr;

    // Search for if the vertex already exists in the edges
    for (auto& list : edges) {
        if (list->head->val == vertex1) {
            list1 = list;
        };
        if (list->head->val == vertex2) {
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
void Graph::addVertex(const std::string& vertex) {
    for (auto & i : vertices) {
        if (i->val == vertex) {
            return;
        }
    }
    Node* newNode = new Node();
    newNode->val = vertex;
    vertices.push_back(newNode);
}

// Prints edges
std::string Graph::printGraph() const {
    std::string result;
    for (auto & i : edges) {
        result += i->printLinkedList() + "\n";
    }
    return result;
}

// Destructor
Graph::~Graph() {
    for (auto & i : edges) {
        delete i;
    }
}

Graph::Graph() {
    edges = std::vector<LinkedList*>();
}

// Copy constructor - create a deep copy
Graph::Graph(const Graph &source) {
    for (auto &i: source.edges) {
        LinkedList *temp = new LinkedList(*i);
        edges.push_back(temp);
    }
}

// Copy assignment operator
Graph &Graph::operator=(const Graph &source) {
    if (this == &source) {
        return *this;
    }

    // Clean up existing resources
    for(auto &i : edges) {
        delete i;
    }
    edges.clear();

    // Copy LinkedList from source
    for(auto &i : source.edges) {
        LinkedList *temp = new LinkedList(*i);
        edges.push_back(temp);
    }

    return *this;
}

// Find a vertex in the vertices list
Node* Graph::findVertex(Node* vertex) const {
    return findVertex(vertex->val);
}

Node* Graph::findVertex(const std::string& vertex) const {
    for (auto & i : vertices) {
        if (i->val == vertex) {
            return i;
        }
    }
    return nullptr;
}

// Find the LinkedList that contains the edges for a given vertex
LinkedList* Graph::findEdge(Node* vertex) const {
    return findEdge(vertex->val);
}

LinkedList* Graph::findEdge(const std::string& vertex) const {
    for (auto & i : edges) {
        if (i->head->val == vertex) {
            return i;
        }
    }
    return nullptr;
}

void Graph::breadthFirstSearch(const std::string& start) {
    // Initialize all vertices to white
    for (auto & i : vertices) {
        i->color = "white";
        i->distance = 9999;
        i->parent = nullptr;
    }

    // Find the starting vertex
    Node* startNode = nullptr;
    for (auto & i : vertices) {
        if (i->val == start) {
            startNode = i;
            break;
        }
    }

    // If the starting vertex is not found, return
    if (startNode == nullptr) {
        //std::cout << "Vertex not found" << std::endl;
        return;
    }

    // Initialize the starting vertex
    startNode->color = "gray";
    startNode->distance = 0;
    startNode->parent = nullptr;

    // Create a LinkedList to act as a queue
    LinkedList queue;
    queue.enqueue(startNode);

    // While the queue is not empty
    while (queue.head != nullptr) {
        Node* nextInQueue = queue.dequeue(); // Dequeue the front node and get the next node

        // For each vertex adjacent to nextInQueue
        LinkedList* currentEdge = findEdge(nextInQueue->val);
        Node* currentChild = currentEdge->head->next;

        while (currentChild != nullptr) {
            Node* currentVertex = findVertex(currentChild->val);

            if (currentVertex->color == "white") { // Check if the vertex has not been visited
                currentVertex->color = "gray";
                currentVertex->distance = nextInQueue->distance + 1;
                currentVertex->parent = nextInQueue;
                queue.enqueue(currentVertex);
            }

            currentChild = currentChild->next;
        }

        nextInQueue->color = "black"; // Mark the vertex as visited after processing its neighbors
    }

}

void Graph::printBFSTree() const {
    Node* parent = nullptr;
    for (auto & i : vertices) {
        if (i->parent == nullptr) {
            printBFSTreeHelper(i, 0);
        }
    }
}

void Graph::printBFSTreeHelper(Node* node, int level) const {
    if (node == nullptr) {
        return;
    }

    for (int i = 0; i < level; i++) {
        std::cout << "   ";
    }

    std::cout << (level == 0 ? "   " : "|- ") << node->val << ": " << node->distance << std::endl;

    for (auto & i : vertices) {
        if (i->parent == node) {
            printBFSTreeHelper(i, level + 1);
        }
    }
}

// Calculates the shortest path in the graph between two given nodes
std::string Graph::shortestPath(const std::string& start, const std::string& end) {
    breadthFirstSearch(start);

    Node* startNode = nullptr;
    Node* endNode = nullptr;

    // Locate and assign the start and end nodes based on their values
    for (auto& vertex : vertices) {
        if (vertex->val == start) {
            startNode = vertex;
        }
        if (vertex->val == end) {
            endNode = vertex;
        }
        if (startNode && endNode) {
            break; // stop searching if both nodes are found
        }
    }

    // Check and handle different error scenarios
    if (startNode == nullptr) {
        return "Start vertex not found";
    }
    if (endNode == nullptr) {
        return "End vertex not found";
    }
    if (endNode->parent == nullptr) {
        return "No path from " + start + " to " + end;
    }

    // Construct a string representing the shortest path from the start node to the end node
    std::string path = endNode->val;
    for (Node *current = endNode->parent; current != nullptr; current = current->parent) {
        path.insert(0, current->val + " ");
    }
    path = "Shortest path from " + start + " to " + end + ": " + path;

    return path;
}



