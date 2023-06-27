#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define maxSIZE 100

typedef struct Graph
{
    int vertices;
    int Arcs;
    int adjMatrix[maxSIZE][maxSIZE];

} Graph;

void initializeGraph(Graph* graph, int vertices)
{
    graph->vertices = vertices;
    graph->Arcs = 0;

    for (int i = 0; i < vertices; i++)
    {
        for (int j = 0; j < vertices; j++)
        {
            graph->adjMatrix[i][j] = 0;
        }
    }
}

void addArc(Graph* graph, int source, int destination)
{
    graph->adjMatrix[source][destination] = 1;
    graph->adjMatrix[destination][source] = 1;
    graph->Arcs++;
}

void displayGraph(Graph* graph)
{
    printf("Graph:\n");
    for (int i = 0; i < graph->vertices; i++)
    {
        for (int j = 0; j < graph->vertices; j++)
        {
            printf("%d ", graph->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

void dfs(Graph* graph, int vertex, int visited[])
{
    visited[vertex] = 1;
    printf("%d ", vertex);

    for (int i = 0; i < graph->vertices; i++)
    {
        if (graph->adjMatrix[vertex][i] == 1 && visited[i] == 0)
        {
            dfs(graph, i, visited);
        }
    }
}

void bfs(Graph* graph, int startVertex)
{
    int queue[maxSIZE];
    int visited[maxSIZE] = {0};

    int front = -1, rear = -1;

    visited[startVertex] = 1;
    queue[++rear] = startVertex;

    printf("BFS: ");

    while (front != rear)
    {
        int currentVertex = queue[++front];
        printf("%d ", currentVertex);

        for (int i = 0; i < graph->vertices; i++)
        {
            if (graph->adjMatrix[currentVertex][i] == 1 && visited[i] == 0)
            {
                visited[i] = 1;
                queue[++rear] = i;
            }
        }
    }
}

void storeGraph(Graph* graph, const char* filename)
{
    FILE* file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening the file.\n");
        return;
    }

    fprintf(file, "%d\n", graph->vertices);
    fprintf(file, "%d\n", graph->Arcs);

    for (int i = 0; i < graph->vertices; i++)
    {
        for (int j = i + 1; j < graph->vertices; j++)
        {
            if (graph->adjMatrix[i][j] == 1)
            {
                fprintf(file, "%d %d\n", i, j);
            }
        }
    }

    fclose(file);
}

int main()
{
    int vertices, Arcs;
    printf("Enter the number of vertices in the graph: ");
    scanf("%d", &vertices);

    Graph graph;
    initializeGraph(&graph, vertices);

    printf("Enter the number of Arcs in the graph: ");
    scanf("%d", &Arcs);

    srand(time(NULL));
    for (int i = 0; i < Arcs; i++)
    {
        int source = rand() % vertices;
        int destination = rand() % vertices;
        addArc(&graph, source, destination);
    }

    displayGraph(&graph);

    int visited[maxSIZE] = {0};
    printf("DFS: ");
    for (int i = 0; i < graph.vertices; i++)
    {
        if (visited[i] == 0)
        {
            dfs(&graph, i, visited);
        }
    }
    printf("\n");

    printf("Enter the starting vertex for BFS: ");
    int startVertex;
    scanf("%d", &startVertex);
    bfs(&graph, startVertex);
    printf("\n");

    const char* filename = "graph.txt";
    storeGraph(&graph, filename);
    printf("Graph stored in %s.\n", filename);
    return 0;
}
