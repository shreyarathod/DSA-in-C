
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define colors for vertices
// WHITE -> Undiscovered
// GRAY -> Discovered
// BLACK -> Explored
typedef enum {
    WHITE,
    GRAY,
    BLACK
} Color;

// vertices are denoted by integers 0..N-1
typedef int Vertex;
typedef enum {BFS, DFS} TraversalType;
typedef struct Edge {Vertex u; Vertex v;} Edge;

typedef struct GraphRep {
    bool **edges; //adjacency matrix
    int nV; // #vertices
    int nE; // #edges
    bool is_directed; // 'true' if graph is a directed graph

    // ---Additional properties for BFS and DFS--
    TraversalType type;
    // Source vertex for traversal
    Vertex source;
    // Array to store predecessors for vertices
    Vertex *predecessor;   

    // Array to store colors
    Color *color;           

    // Array to store:
    // distance from source for all vertices (For BFS)
    // OR
    // time of arrival from source for all vertices (For DFS)
    int *distance;      

    // NOTE: Only for DFS
    // stores the time at which a given vertex has been fully explored
    int *finish; 

} GraphRep;


// TODO: complete all graph functions below
GraphRep *init_graph(int num_vertices, bool is_directed);
void insert_edge(GraphRep *graph, Edge e);
void remove_edge(GraphRep *graph, Edge e);
void traverse_bfs(GraphRep *graph, Vertex source);
void traverse_dfs(GraphRep *graph, Vertex source);
void display_path(GraphRep *graph, Vertex destination);
void display_graph(GraphRep *graph);
// NOTE: ONLY the graph functions above need to be implemented


// Queues
// This Queue ADT has already been implemented for you in 'queue.c' to focus solely on Graph traversals
typedef struct Queue
{
    int front;
    int rear;
    unsigned size;
    Vertex *array;

}Queue;

Queue* initialize_queue(unsigned size);
void display_queue(Queue* queue);
int isEmpty(Queue* queue);
int isFull(Queue* queue);
void enqueue(Queue *queue, Vertex vertex);
Vertex dequeue(Queue* queue);
Vertex front(Queue* queue);
Vertex rear(Queue* queue);