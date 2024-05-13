# DesignDoc

## Data Structures

*the list of data structures, and the rationale behind each:*

### Node Struct

- **Usage:** Represents each vertex in the graph, and holds the properties (val, color, parent, distance) necessary for the BFS graph traversal algorithms.
- **Rationale:** Provides a simple way to encapsulate vertex properties that allows easy modification and direct access to vertex attributes.

### LinkedList Class

- **Usage:** Manages lists of nodes; used for the graph *adjacency lists* and a *queue* in BFS operations. 
- **Rationale:** Effectively manages adjacency lists and queue.

### Graph Class

- **Usage:** Manages the overall graph structure using vectors of linked lists for adjacency lists and nodes for storing vertices. Facilitates graph operations like adding edges, BFS traversal, and shortest path calculation.
- **Rationale:** Ideal for modeling relationships between nodes

### Vectors

- **Usage:** To store pointers to the linked list representing adjacency lists for each vertex and to maintain a list of all vertex nodes in the graph.
- **Rationale:** Efficiently manage and provide quick access to adjacency lists and vertex nodes.

### Queue via LinkedList

- **Usage:** Embedded within the LinkedList class, functioning as a queue to manage nodes during BFS traversal.
- **Rationale:** Important for BFS where nodes must be processed in a first-in, first-out (FIFO) order.


## Functions

*the list of member/free-standing functions; include a brief description for this function if it’s NOT straightforward, e.g., a simple accessor:*

### LinkedList Class Functions

- **createNode(T val):** Creates a new node with the specified value.
- **clearList():** Frees all nodes in the linked list to prevent memory leaks.
- **enqueue(T val):** Adds a new node with the given value to the end of the list.
- ***enqueue(Node<T> newNode)**: Adds an existing node to the end of the list.
- **dequeue():** Removes and returns the first node from the list, supporting the queue functionality required in BFS.
- **begin() const:** Returns the first node in the list, allowing iteration from the start of the list.
- **printLinkedList() const:** Returns a string representation of the entire list, showing all nodes in a chain (e.g., "A -> B -> C").

### Graph Class Functions

- **findVertex(const T& vertexValue) const:** Searches for and returns a vertex with the specified value.
- **findEdge(const T& vertex) const:** Finds and returns the adjacency list linked to a specific vertex, used for accessing a vertex's neighbors during graph traversal.
- ***processNode(Node<T> node, LinkedList<T>& queue)**: Marks a node as processed and enqueues its unvisited neighbors; used in BFS.
- **breadthFirstSearch(const T& startVertexValue):** Performs BFS from a given start vertex, initializing nodes and traversing the graph layer by layer.
- **addEdge(const T& vertex1, const T& vertex2):** Connects two vertices by adding each to the other’s adjacency list.
- **addVertex(const T& vertexValue):** Adds a new vertex to the graph if it doesn't already exist.
- **shortestPathToString(const T& start, const T& end):** Computes and returns the shortest path between two vertices as a string, utilizing BFS to find the path.
- **adjacencyListToString() const:** Provides a string representation of all adjacency lists in the graph, useful for debugging and visualization.
- **printBFSTree(const T& startVertexValue):** Prints a BFS traversal tree starting from a specified vertex, useful for visualizing the structure of the graph post-BFS.

### Free-standing Functions

- **to_string(const T& t):** Converts template values, such as the node of our graph's value, to a string; useful for printing node values when using templates.

**for some functions, you should consider to describe it in pseudocode, For example, if you choose to generate a visual representation of the BFS tree. (No need to include the BFS and shortest-path algorithms. Simply referring to the corresponding slides will suffice.)**

## Contributions

- briefly describe each team member’s main contributions.
