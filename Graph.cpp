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
Node LinkedList::dequeue() {
    Node* current = head;
    Node* previous = nullptr;

    // If the LinkedList is empty, return nullptr
    if (head == nullptr) {
        return Node();
    }

    Node* temp = head;
    head = head->next;
    return *temp;
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

// TO-DO: Implement breadthFirstSearch
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
        std::cout << "Vertex not found" << std::endl;
        return;
    }

    // Initialize the starting vertex
    startNode->color = "gray";
    startNode->distance = 0;
    startNode->parent = nullptr;

    // Create a queue
    LinkedList queue;
    queue.enqueue(startNode);

    // While the queue is not empty
    while (queue.head != nullptr) {
        Node u = queue.dequeue();

        // For each vertex adjacent to u
        for (auto & i : edges) {
            if (i->head->val == u.val) {
                Node* v = i->head->next;
                while (v != nullptr) {
                    if (v->color == "white") {
                        v->color = "gray";
                        v->distance = u.distance + 1;
                        v->parent = &u;
                        queue.enqueue(v);
                    }
                    v = v->next;
                }
            }
        }
        u.color = "black";
    }

    printBFSTree();
}

// Print the BFS tree in a file structure diagram
void Graph::printBFSTree() const {
    for (auto & i : vertices) {
        if (i->parent == nullptr) {
            std::cout << i->val << std::endl;
            printBFSTreeHelper(i, 1);
        }
    }
}

// Helper function to recursively print the BFS tree
void Graph::printBFSTreeHelper(Node* node, int level) const {
    for (int i = 0; i < level; i++) {
        std::cout << "  ";
    }
    std::cout << "|- " << node->val << std::endl;
    for (auto & i : edges) {
        if (i->head->val == node->val) {
            Node* child = i->head->next;
            while (child != nullptr) {
                printBFSTreeHelper(child, level + 1);
                child = child->next;
            }
        }
    }
}

// TO-DO: Implement shortestPath
void Graph::shortestPath(std::string start, std::string end) {
    breadthFirstSearch(start);

    Node* startNode = nullptr;
    Node* endNode = nullptr;

    for (auto & i : vertices) {
        if (i->val == start) {
            startNode = i;
        }
        if (i->val == end) {
            endNode = i;
        }
    }

    if (startNode == nullptr || endNode == nullptr) {
        std::cout << "Vertex not found" << std::endl;
        return;
    }

    if (endNode->parent == nullptr) {
        std::cout << "No path from " << start << " to " << end << std::endl;
    } else {
        std::cout << "Shortest path from " << start << " to " << end << ": ";
        Node* current = endNode;
        while (current != nullptr) {
            std::cout << current->val << " ";
            current = current->parent;
        }
        std::cout << std::endl;
    }
}


