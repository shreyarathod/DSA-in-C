// Implement BFS & DFS traversal for graphs.
// You need to make use of an adjacency matrix for representing the graph
// The structure below should allow you to handle both directed and undirected graphs.
// For traversals, the respective function should accept starting node for traversal and perform traversal (BFS/ DFS).

#include "queue(graphs).c"

GraphRep *init_graph(int num_vertices, bool is_directed)
{
    GraphRep *graph = (GraphRep *)malloc(sizeof(GraphRep));
    graph->edges = (bool **)malloc(sizeof(bool *) * num_vertices);
    for (int i = 0; i < num_vertices; i++)
    {
        graph->edges[i] = (bool *)malloc(sizeof(bool) * num_vertices);
        for (int j = 0; j < num_vertices; j++)
        {
            graph->edges[i][j] = false;
        }
    }

    graph->nV = num_vertices;
    graph->nE = 0;
    graph->is_directed = is_directed;

    return graph;
}

void insert_edge(GraphRep *graph, Edge e)
{
    if (e.u >= 0 && e.u < graph->nV && e.v >= 0 && e.v < graph->nV)
    {
        graph->edges[e.u][e.v] = true;
        if (!graph->is_directed)
        {
            graph->edges[e.v][e.u] = true;
        }
        graph->nE++;
    }
    else
    {
        printf("Invalid Edge.");
    }
}

void remove_edge(GraphRep *graph, Edge e)
{
    if (e.u >= 0 && e.u < graph->nV && e.v >= 0 && e.v < graph->nV)
    {
        graph->edges[e.u][e.v] = false;
        if (!graph->is_directed)
        {
            graph->edges[e.v][e.u] = false;
        }
        graph->nE--;
    }
    else
    {
        printf("Invalid Edge.");
    }
}

// NOTE: During both DFS and BFS traversals, when at a vertex that is connected with multiple vertices, always pick the connecting vertex which has the lowest value first
// Both traversals will always update the following attributes of the Graph:
// 1. source -> stores the value of the starting vertex for the traversal
// 2. type -> stores the traversal type (BFS or DFS)
// 3. color --> indicates if all vertices have been visited or not. Post traversal, all vertices should be BLACK
// 4. predecessor --> this array would hold the predecessor for a given vertex (indicated by the array index).

// NOTE: BFS Traversal should additionally update the following in the graph:
// 1. distance --> this array would hold the number of hops it takes to reach a given vertex (indicated by the array index) from the source.
void traverse_bfs(GraphRep *graph, Vertex source)
{
    if (graph == NULL || source < 0 || source >= graph->nV)
    {
        printf("Invalid graph/source.");
        return;
    }

    graph->type = BFS;
    graph->source = source;
    graph->predecessor = (Vertex *)malloc(sizeof(Vertex) * graph->nV);
    graph->color = (Color *)malloc(sizeof(Color) * graph->nV);
    graph->distance = (int *)malloc(sizeof(int) * graph->nV);

    for (int i = 0; i < graph->nV; i++)
    {
        graph->predecessor[i] = -1;
        graph->color[i] = WHITE;
        graph->distance[i] = -1;
    }

    graph->color[source] = GRAY;
    graph->distance[source] = 0;

    Queue *queue = initialize_queue(graph->nV);
    enqueue(queue, source);

    while (!isEmpty(queue))
    {
        Vertex current = dequeue(queue);

        printf("%d ", current);

        for (int neighbor = 0; neighbor < graph->nV; neighbor++)
        {
            if (graph->edges[current][neighbor] && graph->color[neighbor] == WHITE)
            {
                graph->color[neighbor] = GRAY;
                graph->distance[neighbor] = graph->distance[current] + 1;
                graph->predecessor[neighbor] = current;
                enqueue(queue, neighbor);
            }
        }

        graph->color[current] = BLACK;
    }

    free(queue->array);
    free(queue);
    printf("\n");
}



// NOTE: DFS Traversal should additionally update the following in the graph:
// 1. distance --> Assuming 1 hop to equal 1 time unit, this array would hold the time of discovery a given vertex (indicated by the array index) from the source.
// 2. finish --> Assuming 1 hop to equal 1 time unit, this array would hold the time at which exploration concludes for a given vertex (indicated by the array index).
void dfs(GraphRep *graph, Vertex source);
void dfs_visit(GraphRep *graph, Vertex current);

// Main DFS traversal function
void traverse_dfs(GraphRep *graph, Vertex source) {
    if (graph == NULL || source < 0 || source >= graph->nV) {
        printf("Error: Invalid graph or source vertex\n");
        return;
    }

  
    graph->type = DFS;
    graph->source = source;
    graph->predecessor = (Vertex *)malloc(graph->nV * sizeof(Vertex));
    graph->color = (Color *)malloc(graph->nV * sizeof(Color));
    graph->distance = (int *)malloc(graph->nV * sizeof(int));
    graph->finish = (int *)malloc(graph->nV * sizeof(int));

    for (int i = 0; i < graph->nV; i++) {
        graph->predecessor[i] = -1;
        graph->color[i] = WHITE;
        graph->distance[i] = -1;
        graph->finish[i] = -1;
    }

    dfs(graph, source);

    
    free(graph->predecessor);
    free(graph->color);
    free(graph->distance);
    free(graph->finish);
}

// DFS helper functions
void dfs(GraphRep *graph, Vertex source) {
    graph->color[source] = GRAY;
    graph->distance[source] = 0;
    
    printf("%d ", source);

   
    for (int neighbor = 0; neighbor < graph->nV; neighbor++) {
        if (graph->edges[source][neighbor] && graph->color[neighbor] == WHITE) {
            graph->predecessor[neighbor] = source;
            dfs_visit(graph, neighbor);
        }
    }

    graph->color[source] = BLACK;
    graph->finish[source] = 0; 
}

void dfs_visit(GraphRep *graph, Vertex current) {
    graph->color[current] = GRAY;
    graph->distance[current] = graph->distance[graph->predecessor[current]] + 1;

    
    printf("%d ", current);

    for (int neighbor = 0; neighbor < graph->nV; neighbor++) {
        if (graph->edges[current][neighbor] && graph->color[neighbor] == WHITE) {
            graph->predecessor[neighbor] = current;
            dfs_visit(graph, neighbor);
        }
    }

    graph->color[current] = BLACK;
    graph->finish[current] = 0; 
}

// displays the path from the current 'source' in graph to the provided 'destination'.
// The graph holds the value of the traversal type, so the function should let the caller know what kind of traversal was done on the graph and from which vertex, along with the path.
void display_path(GraphRep *graph, Vertex destination){

printf("Source Vertex: %d\n", graph->source);
printf("Destination Vertex: %d\n", destination);
printf("Path: ");

Vertex current = destination;
while (current != graph->source) {
printf("%d <-", current);
current = graph->predecessor[current];
}
printf("%d\n", graph->source);
}


// display the graph in the matrix form
void display_graph(GraphRep *graph)
{
    for (int i = 0; i < graph->nV; i++)
    {
        for (int j = 0; j < graph->nV; j++)
        {
            printf("%d\t", graph->edges[i][j]);
        }
        printf("\n");
    }
}

int main(){
    GraphRep * graph = init_graph(5, true);
    Edge e1 = {0,1};
    Edge e2 = {1,3};
    Edge e3 = {3,4};
    Edge e4 = {2,4};
    Edge e5 = {0,2};
    Edge e6 = {0,3};

    insert_edge(graph, e1);
    insert_edge(graph, e2);
    insert_edge(graph, e3);
    insert_edge(graph, e4);
    insert_edge(graph, e5);
    insert_edge(graph, e6);

    printf("GRAPH:\n");
    display_graph(graph);

    printf("BFS\n");
    traverse_bfs(graph, 0);
    display_path(graph,4);
    printf("DFS:\n");
    traverse_dfs(graph,0);
    printf("\n");
    display_path(graph,1);

    return 0;
}
