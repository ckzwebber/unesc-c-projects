#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define V 6
#define INFINITO 9999

typedef struct
{
    int itens[V];
    int frente, tras;
} Fila;

void DFSrecursivo(int grafo[V][V], int v, bool visitado[])
{
    visitado[v] = true;

    printf("%c ", v + 'A');

    for (int i = 0; i < V; i++)
    {
        if (grafo[v][i] != 0 && !visitado[i])
        {
            DFSrecursivo(grafo, i, visitado);
        }
    }
}

void DFS(int grafo[V][V], int inicio)
{
    bool visitado[V] = {false};

    printf("\nBusca em profundidade a partir de %c:\n", inicio + 'A');
    DFSrecursivo(grafo, inicio, visitado);
    printf("\n");
}

void inicializarGrafo(int grafo[V][V])
{
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            grafo[i][j] = 0;
        }
    }
}

void adicionarAresta(int grafo[V][V], int origem, int destino, int peso)
{
    grafo[origem][destino] = peso;
}

void imprimirGrafo(int grafo[V][V])
{
    printf("\nMatriz de adjacência (pesos):\n");
    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            printf("%2d ", grafo[i][j]);
        }
        printf("\n");
    }
}

void inicializarFila(Fila *f)
{
    f->frente = 0;
    f->tras = -1;
}

int filaVazia(Fila *f)
{
    return f->tras < f->frente;
}

void enfileirar(Fila *f, int valor)
{
    f->itens[++f->tras] = valor;
}

int desenfileirar(Fila *f)
{
    return f->itens[f->frente++];
}

void BFS(int grafo[V][V], int inicio)
{
    bool visitado[V] = {false};
    Fila fila;
    inicializarFila(&fila);

    visitado[inicio] = true;
    enfileirar(&fila, inicio);

    printf("\nBusca em largura a partir de %c:\n", inicio + 'A');

    while (!filaVazia(&fila))
    {
        int atual = desenfileirar(&fila);
        printf("%c ", atual + 'A');

        for (int i = 0; i < V; i++)
        {
            if (grafo[atual][i] != 0 && !visitado[i])
            {
                visitado[i] = true;
                enfileirar(&fila, i);
            }
        }
    }
    printf("\n");
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

void Dijkstra(int grafo[V][V], int inicio)
{
    int dist[V];
    bool visitado[V];
    int anterior[V];

    for (int i = 0; i < V; i++)
    {
        dist[i] = INFINITO;
        visitado[i] = false;
        anterior[i] = -1;
    }

    dist[inicio] = 0;

    for (int count = 0; count < V - 1; count++)
    {
        int u = menorDistancia(dist, visitado);
        if (u == -1)
            break;
        visitado[u] = true;

        for (int v = 0; v < V; v++)
        {
            if (!visitado[v] && grafo[u][v] != 0 && dist[u] + grafo[u][v] < dist[v])
            {
                dist[v] = dist[u] + grafo[u][v];
                anterior[v] = u;
            }
        }
    }

    printf("\nDistâncias mínimas a partir de %c:\n", inicio + 'A');
    for (int i = 0; i < V; i++)
    {
        printf("%c: %d\n", i + 'A', dist[i]);
    }

    printf("\nCaminho mínimo de A até E:");
    printf("\nA");
    imprimirCaminho(anterior, 4);
    printf(" (Distância: %d)\n", dist[4]);

    printf("\nCaminho mínimo de A até F:");
    printf("\nA");
    imprimirCaminho(anterior, 5);
    printf(" (Distância: %d)\n", dist[5]);
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

    DFS(grafo, 0);
    BFS(grafo, 0);
    Dijkstra(grafo, 0);

    return 0;
}
