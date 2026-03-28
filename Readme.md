### Graph Theory

**Definition**

A **graph** G consists of a finite set of vertices V, and for all *v* ∊ V, a subset of V, E, called the finite set of vertices adjacent to *v* (edges).  Formally, a graph is denoted as a pair G(V, E) 

Depending on the requirements of the problem or application, graphs can be implemented using different methods, such as adjacency lists, adjacency matrices, or edge lists.

This demo implements a directed graph using linked lists for both the vertices and edges. The following type definitions are declared:

```C

// Forward declaration
typedef struct vertex_tag Vertex_type;
typedef struct edge_tag Edge_type;

// vertex node
struct vertex_tag {
    int label;                      // value serves as a unique identifer
    Edge_type *firstEdge;           // start of the adjacency linked list
    Vertex_type *nextVertex;        // next vertex node on the vertex linked list
};

// adjacency/edge node
struct edge_tag {
    Vertex_type *endPoint;          // vertex node to which the edge points to
    Edge_type *nextEdge;            // next edge node on the adjacency linked list
};

typedef Vertex_type *Graph_type;    // header for the linked list of vertices

```

The above type definitions are from pg 386 of reference 1. An additional field, "label", is included in the struct vertex_tag. The value of this field should be unique because it will be used to search for a target vertex node. It could also be used in the sorting of the linked list of vertex nodes. And, if needed, the value can be used in a binary search.

Creating an edge node using a pair of integers rather than a pair of pointers results in cleaner code. During debugging using XCode's built-in debugger, the programmer can easily identify which vertices are connected. Adding an edge with the statement:

```C
    addEdge(0, 1, graph);


looks neater than

    addEdge(p, q, graph);
~~~

where p and q are of type Vertex_type *.

Given below is a display of the graph produced by this toy demo.

vertex:0->edge(0, 1)->edge(0, 2)->NULL
vertex:1->edge(1, 2)->edge(1, 3)->NULL
vertex:2->NULL
vertex:3->edge(3, 0)->edge(3, 1)->edge(3, 2)->NULL


The graph pictorally:

![](Documentation/fig.png)


**Requirements**

A modern ANSI C compiler.

Compiled and debugged using XCode 11.3 running on macOS Mojave.




**References**

1) Data Structures and Program Design in C by Robert L. Kruse, Bruce P. Leung, Clovis L. Tondo

2) https://www.geeksforgeeks.org/dsa/introduction-to-graphs-data-structure-and-algorithm-tutorials/

3) https://brilliant.org/wiki/graph-theory/

4) https://www.geeksforgeeks.org/dsa/binary-search-on-singly-linked-list

5) https://www.geeksforgeeks.org/dsa/merge-sort-for-linked-list
