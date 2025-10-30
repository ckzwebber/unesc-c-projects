#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

#define V 6
#define INFINITO 9999

typedef struct
{
    int origem;
    int destino;
    int peso;
} Aresta;

void inicializarGrafo(int grafo[V][V])
{
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            grafo[i][j] = 0;
}

void adicionarAresta(int grafo[V][V], int origem, int destino, int peso)
{
    grafo[origem][destino] = peso;
}

void imprimirGrafo(int grafo[V][V])
{
    printf("\nMatriz de adjacência:\n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            printf("%2d ", grafo[i][j]);
        }
        printf("\n");
    }
}

int menorDistancia(int dist[], bool visitado[])
{
    int min = INFINITO, indiceMin = -1;
    for (int i = 0; i < V; i++)
    {
        if (!visitado[i] && dist[i] <= min)
        {
            min = dist[i];
            indiceMin = i;
        }
    }
    return indiceMin;
}

void imprimirCaminho(int anterior[], int j)
{
    if (anterior[j] == -1)
        return;
    imprimirCaminho(anterior, anterior[j]);
    printf(" -> %c", j + 'A');
}

void Dijkstra(int grafo[V][V], int inicio, int destino)
{
    int dist[V], anterior[V];
    bool visitado[V];

    for (int i = 0; i < V; i++)
    {
        dist[i] = INFINITO;
        anterior[i] = -1;
        visitado[i] = false;
    }

    dist[inicio] = 0;

    for (int c = 0; c < V - 1; c++)
    {
        int u = menorDistancia(dist, visitado);
        if (u == -1)
            break;
        visitado[u] = true;

        for (int v = 0; v < V; v++)
        {
            if (!visitado[v] && grafo[u][v] && dist[u] + grafo[u][v] < dist[v])
            {
                dist[v] = dist[u] + grafo[u][v];
                anterior[v] = u;
            }
        }
    }

    printf("\n[Dijkstra] Caminho mínimo de A até F:\nA");
    imprimirCaminho(anterior, destino);
    printf("\nDistância total: %d\n", dist[destino]);
}

void BellmanFord(Aresta arestas[], int numArestas, int inicio, int destino)
{
    int dist[V], anterior[V];

    for (int i = 0; i < V; i++)
    {
        dist[i] = INFINITO;
        anterior[i] = -1;
    }
    dist[inicio] = 0;

    for (int i = 1; i < V; i++)
    {
        for (int j = 0; j < numArestas; j++)
        {
            int u = arestas[j].origem;
            int v = arestas[j].destino;
            int peso = arestas[j].peso;

            if (dist[u] + peso < dist[v] && dist[u] != INFINITO)
            {
                dist[v] = dist[u] + peso;
                anterior[v] = u;
            }
        }
    }

    for (int j = 0; j < numArestas; j++)
    {
        int u = arestas[j].origem;
        int v = arestas[j].destino;
        int peso = arestas[j].peso;
        if (dist[u] + peso < dist[v])
        {
            printf("Grafo contém ciclo negativo!\n");
            return;
        }
    }

    printf("\n[Bellman-Ford] Caminho mínimo de A até F:\nA");
    imprimirCaminho(anterior, destino);
    printf("\nDistância total: %d\n", dist[destino]);
}

int main()
{
    int grafo[V][V];
    inicializarGrafo(grafo);

    adicionarAresta(grafo, 0, 1, 3);
    adicionarAresta(grafo, 0, 2, 7);
    adicionarAresta(grafo, 0, 3, 8);
    adicionarAresta(grafo, 1, 4, 9);
    adicionarAresta(grafo, 2, 5, 4);
    adicionarAresta(grafo, 3, 5, 5);

    imprimirGrafo(grafo);

    clock_t inicio = clock();
    Dijkstra(grafo, 0, 5);
    clock_t fim = clock();
    double tempoDijkstra = (double)(fim - inicio) / CLOCKS_PER_SEC;

    Aresta arestas[] = {
        {0, 1, 3}, {0, 2, 7}, {0, 3, 8}, {1, 4, 9}, {2, 5, 4}, {3, 5, 5}};
    int numArestas = sizeof(arestas) / sizeof(arestas[0]);

    inicio = clock();
    BellmanFord(arestas, numArestas, 0, 5);
    fim = clock();
    double tempoBellman = (double)(fim - inicio) / CLOCKS_PER_SEC;

    printf("\nTempo Dijkstra: %.8f s\n", tempoDijkstra);
    printf("Tempo Bellman-Ford: %.8f s\n", tempoBellman);

    return 0;
}
