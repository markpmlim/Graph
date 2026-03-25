//
//  Graph.c
//  Graph
//
//  Created by Mark Lim Pak Mun on 15/03/2026.
//  Copyright © 2026 Mark Lim Pak Mun. All rights reserved.
//
// Reference:
//  Data Structures and Program Design in C
//  Robert L. Kruse, Bruce P. Leung, Clovis L. Tondo
// pages 386 - 387 Figure 10.15 (a)
//
// Implementation of a directed graph using 2 linked lists.

#include <stdio.h>
#include <stdlib.h>


typedef unsigned Boolean_type;
#define TRUE            1
#define FALSE           0

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

// Queue structure for BFS
typedef struct Queue {
    int *items;                     // array of integers
    int numItems;                   // size of array of integers
    int front;
    int rear;
} Queue_type;

// Prototype the functions
Vertex_type* createVertex(int);
Edge_type *createEdge(Vertex_type *);
Vertex_type* findVertex(int, Graph_type);
void appendVertex(Vertex_type*, Graph_type*);
Boolean_type edgeExists(int, int, Graph_type);
void appendEdge(Edge_type*, Vertex_type*);
void addEdge(int, int, Graph_type);

Queue_type* createQueue(Graph_type graph);
void enqueue(int value, Queue_type*);
int dequeue(Queue_type*);
Boolean_type isEmpty(Queue_type*);

void depthFirstSearch(Graph_type);
void breadthFirstSearch(int, Graph_type);


//////// start of program code
Vertex_type* createVertex(int label)
{
    Vertex_type *newVertex = malloc(sizeof(Vertex_type));
    newVertex->label = label;
    newVertex->firstEdge = NULL;
    newVertex->nextVertex = NULL;
    return newVertex;
}

// dest is not NULL
Edge_type *createEdge(Vertex_type *dest)
{
    Edge_type *edge = malloc(sizeof(Edge_type));
    edge->endPoint = dest;
    edge->nextEdge = NULL;
    return edge;
}

// Return the vertex node; NULL is returned if it is not found.
Vertex_type* findVertex(int target, Graph_type graph)
{
    Vertex_type *p = graph;
    if (p == NULL) {
        // The linked list of vertices is empty.
        return NULL;
    }
    while (p != NULL) {
        if (p->label == target) {
            break;
        }
        p = p->nextVertex;
    }
    return p;
}

// Add the vertex node to the graph
// KIV. We should ensure the labels for each vertex is unique.
// before appending it to the linked list of vertices.
void appendVertex(Vertex_type *newVertex, Graph_type *graph)
{
    // 1. If the linked list is empty, make the new node the head
    // Checks if the linked link of vertices is empty.
    if (*graph == NULL) {
        *graph = newVertex;
        return;
    }

    // 2. Traverse to the last node
    Vertex_type* r = NULL;
    Vertex_type* p = *graph;         // Assume first vertex is not NULL
    while (p != NULL) {
        // Is the vertex already in the linked list?
        if (p == newVertex) {
            printf("Already in the vertex linked list: %d\n", p->label);
            return;             // yes
        }
        else {
            // No
            r = p;
            p = p->nextVertex;
        }
    } // while

    // 3. Link the new node to the last node
    r->nextVertex = newVertex;
}

// Does not check if the same edge is already in
// the linked list of edge nodes.
void appendEdge(Edge_type *newEdge, Vertex_type *srcVertex)
{
    Edge_type* p = srcVertex->firstEdge;
    if (p == NULL) {
        srcVertex->firstEdge = newEdge;
    }
    else {
        // 2. Traverse to the last node
        Edge_type* r = NULL;
        while (p != NULL) {
            // Is the edge edge to be added already in the linked list?
            if (p == newEdge) {
                printf("Edge already in the edge linked list\n");
                return;             // yes
            }
            else {
                r = p;
                p = p->nextEdge;
            }
        }
        // 3. Link the new edge node to the last node
        r->nextEdge = newEdge;
    }
}

// Append the edge to its

void appendEdge2(Edge_type *newEdge, Graph_type graph)
{
    
    // 2. Traverse to the last node
    Edge_type* r = NULL;
    Edge_type* p = graph->firstEdge;
    while (p != NULL) {
        // Is the edge to be added already in the linked list?
        if (p == newEdge) {
            printf("Edge already in the edge linked list\n");
            return;             // yes
        }
        else {
            r = p;
            p = p->nextEdge;
        }
    }
    
    // 3. Link the new node to the last node
    r->nextEdge = newEdge;
}


// graph cannot be NULL and the values of src and dest cannot be the same.
void addEdge(int src, int dest, Graph_type graph)
{
    if (src == dest) {
        printf("Invalid edge\n");
        return;
    }

    if (graph == NULL) {
        printf("The graph has no vertices\n");
    }
    else {
        Vertex_type *srcVertex  = findVertex(src, graph);
        Vertex_type *destVertex = findVertex(dest, graph);
        // Ensure both src and dest are not NULL
        if (srcVertex != NULL && destVertex != NULL) {
            Edge_type *edge = createEdge(destVertex);
            appendEdge(edge, srcVertex);
        }
        else {
            printf("Can't create an edge; one of the vertices does not exist\n");
        }
    }
}

/*
 This function can be used to verify that an edge exists.
 The graph must have at least one vertex.
 Both src and dest vertices must exists.
 */
Boolean_type edgeExists(int src, int dest, Graph_type graph)
{
    Boolean_type result = FALSE;
    if (graph == NULL) {
        printf("Empty graph");
        return result;
    }

    if (src == dest) {
        printf("Invalid edge\n");
        return result;
    }

    Vertex_type *srcVertex = findVertex(src, graph);
    Vertex_type *destVertex = findVertex(dest, graph);
    if (srcVertex != NULL && destVertex != NULL) {
        Edge_type *e = srcVertex->firstEdge;
        while (e != NULL) {
            if (e->endPoint->label == dest) {
                result = TRUE;
                break;
            }
            e = e->nextEdge;
        }
    }
    return result;
}

void printGraph(Graph_type graph)
{
    Vertex_type *p = graph;
    Vertex_type *q = NULL;
    Edge_type *e = NULL;
    if (p == NULL) {
        printf("Empty graph");
    }

    while (p != NULL) {
        printf("vertex:%d->", p->label);    // vertex i
        e = p->firstEdge;
        while (e != NULL) {
            q = e->endPoint;
            printf("edge(%d, %d)->",        // edge(i, j)
                   p->label, q->label);
            e = e->nextEdge;
        }
        printf("NULL\n");
        p = p->nextVertex;
    }
}


/*
 Given a linked list head pointer, compute and
 return the number of nodes in the vertex linked list.
 */
int length(Vertex_type* head)
{
    Vertex_type* currNode = head;
    int count = 0;
    while (currNode != NULL) {
        count++;
        currNode = currNode->nextVertex;
    }
    return count;
}

/*
 The DFS code is based on algorithm presented on pg 519
 Data Structures and Program Design in C (2nd Edition.)

 Robert L. Kruse, Clovis L. Tondo, Bruce P. Leung

 */
void visitNode(Vertex_type *p)
{
    printf("Visited %d\n", p->label);    // Process the current vertex node
}

void traverse(Vertex_type *p, Boolean_type isVisited[],
              void (*visit)(Vertex_type *))
{
    // Note: p should not be NULL
    int v = p->label;
    isVisited[v] = TRUE;
    visit(p);
    // Recurse for all the unvisited adjacent vertices
    Edge_type *e = p->firstEdge;
    while (e != NULL) {
        int w = e->endPoint->label;
        Vertex_type *dest = e->endPoint;
        if (!isVisited[w]) {
            traverse(dest, isVisited, *visit);
        }
        e = e->nextEdge;
    }
}

/*
 Pre: graph has been created.
 Post: The function "visitNode" has been performed at each vertex of
 "graph" in depth-first order.
 */
 void depthFirstSearch(Graph_type graph)
{
    int numVertices = length(graph);
    Boolean_type *isVisited = malloc(sizeof(Boolean_type));
    if (isVisited == NULL) {
        printf("Not enough memory for visited array\n");
        return;
    }
    for (int i=0; i< numVertices; i++) {
        isVisited[i] = FALSE;
    }
    Vertex_type *p = graph;
    while (p != NULL) {
        int startVertex = p->label;
        if (!isVisited[startVertex]) {
            traverse(p, isVisited, &visitNode);
        }
        p = p->nextVertex;
    }
    free(isVisited);
}

// helper functions for BFS function
Queue_type* createQueue(Graph_type graph)
{
    
    int numVertices = length(graph);
    Queue_type* queue = malloc(sizeof(Queue_type));
    queue->front = -1;
    queue->rear = -1;
    queue->numItems = numVertices;
    queue->items = malloc(sizeof(int));
    for (int i=0; i<numVertices; i++) {
        queue->items[i] = -1;
    }
    return queue;
}

Boolean_type isEmpty(Queue_type* queue)
{
    if (queue->front == -1 && queue->rear == -1) {
        return TRUE;
    }
    else {
        return FALSE;
    }
}

void enqueue(int value, Queue_type *queue)
{
    if (queue->rear == queue->numItems - 1) {
        printf("Queue Overflow\n");
    }
    else {
        if (queue->front == -1) {
            queue->front = 0;
        }
        queue->items[++queue->rear] = value;
        printf("Enqueued %d\n", value);
    }
}

int dequeue(Queue_type* queue)
{
    if (queue->front == -1 || queue->front > queue->rear) {
        printf("Queue Underflow\n");
        return -1;
    }
    else {
        int item = queue->items[queue->front++];
        printf("Dequeued: %d\n", item);
        if (queue->front > queue->rear) {
            queue->front = queue->rear = -1;
        }
        return item;
    }
}

void breadthFirstSearch(int startVertex, Graph_type graph)
{
    int numVertices = length(graph);

    Boolean_type *isVisited = malloc(sizeof(Boolean_type));
    if (isVisited == NULL) {
        printf("Not enough memory for queue\n");
        return;
    }
    for (int i=0; i< numVertices; i++) {
        isVisited[i] = FALSE;
    }

    Queue_type* queue = createQueue(graph);
    isVisited[startVertex] = TRUE;
    enqueue(startVertex, queue);

    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("Visited %d\n", currentVertex);
        Vertex_type *p = findVertex(currentVertex, graph);
 
        while (p != NULL) {
            Edge_type* e = p->firstEdge;
            while (e != NULL) {
                int adjVertex = e->endPoint->label;
                if (isVisited[adjVertex] == FALSE) {
                    isVisited[adjVertex] = TRUE;
                    enqueue(adjVertex, queue);
                }
                e = e->nextEdge;
            }
            p = p->nextVertex;
        }
    }
    free(queue->items);
    free(queue);
    free(isVisited);
}

int main(int argc, const char * argv[])
{
    Graph_type graph = NULL;
    for (int i=0; i<4; i++) {
        Vertex_type *vertex = createVertex(i);
        appendVertex(vertex, &graph);
    }

/*
    for (int i=0; i<4; i++) {
        printf("%p\n", findVertex(i, graph));
    }
 */
    addEdge(0, 1, graph);
    addEdge(0, 2, graph);
    addEdge(1, 2, graph);
    addEdge(1, 3, graph);
    addEdge(3, 0, graph);
    addEdge(3, 1, graph);
    addEdge(3, 2, graph);
    printGraph(graph);
    depthFirstSearch(graph);
    //breadthFirstSearch(3, graph);

    // Code to test the function edgeExists.
    // We should call the function "findVertex" before
    // adding a new vertex node to the linked list of vertices.
    Vertex_type *vertex = createVertex(4);
    appendVertex(vertex, &graph);
    addEdge(1, 4, graph);
    printGraph(graph);
    Boolean_type exists = edgeExists(1, 4, graph);

/*
    addEdge(vertex0, vertex2, FALSE, &graph);   // edge(0, 2)
    addEdge(vertex1, vertex2, TRUE,  &graph);   // edge(1, 2)
    addEdge(vertex1, vertex3, FALSE, &graph);   // edge(1, 3)
    addEdge(vertex3, vertex0, TRUE,  &graph);   // edge(3, 0)
    addEdge(vertex3, vertex1, FALSE, &graph);   // edge(3, 1)
    addEdge(vertex3, vertex2, FALSE, &graph);   // edge(3, 2)


    addEdge(vertex1, vertex2);
    printf("verter 0: %p %p\n", vertex0->firstEdge->nextEdge, vertex0->firstEdge->endPoint);
    printf("verter 1: %p %p\n", vertex1->firstEdge, vertex1->nextVertex);
    printf("verter 2: %p %p\n", vertex2->firstEdge, vertex2->nextVertex);
 */
    return 0;
}
