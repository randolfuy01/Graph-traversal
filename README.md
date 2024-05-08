Review these slides first. The last slide lists the requirements of this project, copied below for your reference:

## Checklist 

- [x] Declare a class Graph
- [x] Adopt the adjacency list representation
- [x] Represent each adjacency list as a “raw pointer”-based singly linked list
- [x] Include and implement the big-3
   - [x] LinkedList
      - [x] Destructor
      - [x] Copy Constructor
      - [x] Copy Assignment Operator
   - [x] Graph
      - [x] Destructor
      - [x] Copy Constructor
      - [x] Copy Assignment Operator
- [x] Member functions to construct a graph such as adding vertices and edges
- [ ] Implement the BFS algorithm on Slide 7
- [ ] Print out the BFS-tree from a given source vertex
- [ ] Print the shortest path from s to v by implement the recursive algorithm on Slide 10

## Submission:

Submit one PDF that consists of the following files in their specified order. Please remember to properly delimit different program files by starting from a new page.
your [design doc](DesignDoc.md).(No need to include the BFS and shortest-path algorithms. Simply referring to the corresponding slides will suffice. )

What you need to include:  
- the list of data structures, and the rationale behind each.  
- the list of member/free-standing functions; include a brief description for this function if it’s NOT straightforward, e.g., a simple accessor. For some functions, you should consider to describe it in pseudocode, For example, if you choose to generate a visual representation of the BFS tree.
- briefly describe each team member’s main contributions.  
- the header file (one header file should be sufficient, but okay to have multiple header files.)
- the cpp file that defines the member functions or other helper functions.
- your unit tests in a header file  
- the cpp file containing main()  
- Demonstration (<= 2 minutes):  

During the demo, you will:
compile your program files
run your program using a relatively small graph prepared by the instructor. This small graph will be described in the following format:
V: {0 1, 2, 3, 4, 5, 6, ...}    //the set of nodes, numbered sequentially from 1
E: {(0, 3), (1,2),  (2, 3), ...}        //the set of undirected edges
a source node for your program to produce a BFS-tree
a pair of nodes in V for your program to produce a shortest path

