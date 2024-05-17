# DesignDoc

## Data Structures

*the list of data structures, and the rationale behind each:*

### Node Struct

- **Usage:** Represents each vertex in the graph, and holds the properties (val, color, parent, distance) necessary for
  the BFS graph traversal algorithms.
- **Rationale:** Provides a simple way to encapsulate vertex properties that allows easy modification and direct access
  to vertex attributes.

### LinkedList Class

- **Usage:** Manages lists of nodes; used for the graph *adjacency lists* and a *queue* in BFS operations.
- **Rationale:** Effectively manages adjacency lists and queue.

### Graph Class

- **Usage:** Manages the overall graph structure using vectors of linked lists for adjacency lists and nodes for storing
  vertices. Facilitates graph operations like adding edges, BFS traversal, and shortest path calculation.
- **Rationale:** Ideal for modeling relationships between nodes

### Vectors

- **Usage:** To store pointers to the linked list representing adjacency lists for each vertex and to maintain a list of
  all vertex nodes in the graph.
- **Rationale:** Efficiently manage and provide quick access to adjacency lists and vertex nodes.

### Queue via LinkedList

- **Usage:** Embedded within the LinkedList class, functioning as a queue to manage nodes during BFS traversal.
- **Rationale:** Important for BFS where nodes must be processed in a first-in, first-out (FIFO) order.

## Functions

*the list of member/free-standing functions; include a brief description for this function if it’s NOT straightforward,
e.g., a simple accessor:*

### LinkedList Class Functions

- **createNode(T val):** Creates a new node with the specified value.
- **clearList():** Frees all nodes in the linked list to prevent memory leaks.
- **enqueue(T val):** Adds a new node with the given value to the end of the list.
- ***enqueue(Node<T> newNode)**: Adds an existing node to the end of the list.
- **dequeue():** Removes and returns the first node from the list, supporting the queue functionality required in BFS.
- **begin() const:** Returns the first node in the list, allowing iteration from the start of the list.
- **printLinkedList() const:** Returns a string representation of the entire list, showing all nodes in a chain (e.g., "
  A -> B -> C").

### Graph Class Functions

- **findVertex(const T& vertexValue) const:** Searches for and returns a vertex with the specified value.
- **findEdge(const T& vertex) const:** Finds and returns the adjacency list linked to a specific vertex, used for
  accessing a vertex's neighbors during graph traversal.
- ***processNode(Node<T> node, LinkedList<T>& queue)**: Marks a node as processed and enqueues its unvisited neighbors;
  used in BFS.
- **breadthFirstSearch(const T& startVertexValue):** Performs BFS from a given start vertex, initializing nodes and
  traversing the graph layer by layer.
- **addEdge(const T& vertex1, const T& vertex2):** Connects two vertices by adding each to the other’s adjacency list.
- **addVertex(const T& vertexValue):** Adds a new vertex to the graph if it doesn't already exist.
- **shortestPathToString(const T& start, const T& end):** Computes and returns the shortest path between two vertices as
  a string, utilizing BFS to find the path.
- **adjacencyListToString() const:** Provides a string representation of all adjacency lists in the graph, useful for
  debugging and visualization.
- **printBFSTree(const T& startVertexValue):** Prints a BFS traversal tree starting from a specified vertex, useful for
  visualizing the structure of the graph post-BFS.

### Free-standing Functions

- **to_string(const T& t):** Converts template values, such as the node of our graph's value, to a string; useful for
  printing node values when using templates.

### Print BFS Tree Pseudocode

1. Begin by implementing the breadth-first search algorithm, starting from the given source vertex, as shown in the
   class slides. This step organizes the nodes in the order they should be processed.
2. Iterate over each vertex in the list of vertices:
    1. For each vertex, check if it has no parent. A vertex with no parent is a root node or the starting point of a
       tree in the case of a disconnected graph (forest).
    2. For each root node found, begin printing a new tree by printing the root node at level 0. Then, process child
       nodes recursively.
    3. Perform the following tasks for each node:
        1. Check if the given node is null. A null node means there is no node to process, so return immediately.
        2. If the node is not null, print spaces based on the current level to visually represent the depth of the node
           in the tree hierarchy. For example, a node at level 2 will have more preceding spaces than a node at level 1.
        3. Then, print the node's value. If the current level is 0, indicating a root node, print three spaces followed
           by the node's value. If the current level is greater than 0, indicating a child node, print "|- " followed by
           the node's value to show the branching from the parent node.
        4. Iterate over each vertex in the list of vertices. For each vertex, check if the parent of the vertex is the
           current node. This means the vertex is a direct child of the current node. If this is the case, recursively
           process that child node, increasing the level by 1 to print the next level of the hierarchy.

Time Complexity excluding the BFS algorithm: O(V^2) where V is the number of vertices in the graph. This complexity
arises from the need to iterate over each vertex in the graph to print the BFS tree.

1. Identify Root Nodes: (O(V))
    2. Check if the node is null for each node recursively: (O(1))
    3. Print spaces based on level for each node recursively: (O(1))
    4. Print the node's value for each node recursively: (O(1))
    5. Find and Process Child Nodes for each node recursively: (O(V))

## Contributions

**Avinh Huynh:**

- Breadth-first search
- Shortest path
- Print BFS tree
- Unit tests

** Randolf Yu:**

- Project initialization
- Linked list and graph class implementation
- Unit tests

** Cesar A. Herrera:**

- Big 3
- Refactoring and debugging
- Unit tests
- Documentation