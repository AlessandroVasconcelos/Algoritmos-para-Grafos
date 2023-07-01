#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "MatrixAdj.h"

Graph GRAPHinit(int V)
{
	Graph G = malloc(sizeof *G);
	G->V = V;
	G->A = 0;
	G->adj = MATRIXint(V, V, 0);
	return G;
}

static int **MATRIXint(int r, int c, int val)
{
	int **m = malloc(r * sizeof(int *));
	for (vertex i = 0; i < r; ++i)
		m[i] = malloc(c * sizeof(int));
	for (vertex i = 0; i < r; ++i)
		for (vertex j = 0; j < c; ++j)
			m[i][j] = val;
	return m;
}

void GRAPHinsertArc(Graph G, vertex v, vertex w)
{
	if (G->adj[v][w] == 0)
	{
		G->adj[v][w] = 1;
		G->A++;
	}
}

void GRAPHremoveArc(Graph G, vertex v, vertex w)
{
	if (G->adj[v][w] == 1)
	{
		G->adj[v][w] = 0;
		G->A--;
	}
}

void GRAPHshow(Graph G)
{
	vertex v, w;
	for (v = 0; v < G->V; ++v)
	{
		printf("%2d:", v);
		for (w = 0; w < G->V; ++w)
			if (G->adj[v][w] == 1)
				printf(" %2d", w);
		printf("\n");
	}
}

void IsSink(Graph G)
{
	vertex v, w;
	bool *isSink = calloc(G->V, sizeof(bool));

	for (v = 0; v < G->V; v++)
		isSink[v] = true;

	for (v = 0; v < G->V; v++)
		for (w = 0; w < G->V; w++)
			if (G->adj[v][w])
			{
				isSink[v] = false;

				break;
			}

	printf("\nSink: ");
	for (v = 0; v < G->V; v++)
		if (isSink[v])
			printf("%d ", v);
}

void IsSource(Graph G)
{
	vertex v, w;
	bool *isSource = calloc(G->V, sizeof(bool));

	for (v = 0; v < G->V; v++)
		isSource[v] = true;

	for (w = 0; w < G->V; w++)
		for (v = 0; v < G->V; v++)
			if (G->adj[v][w])
			{
				isSource[w] = false;

				break;
			}

	printf("\nSource: ");
	for (v = 0; v < G->V; v++)
		if (isSource[v])
			printf("%d ", v);
}

int GRAPHindeg(Graph G, vertex w)
{
	vertex v;
	int count = 0;

	for (v = 0; v < G->V; v++)
		if (G->adj[v][w])
			count++;

	return count;
}

int GRAPHoutdeg(Graph G, vertex v)
{
	vertex w;
	int count = 0;

	for (w = 0; w < G->V; w++)
		if (G->adj[v][w])
			count++;

	return count;
}

bool GRAPHisUndirected(Graph G)
{
	vertex v, w;

	for (v = 0; v < G->V; v++)
		for (w = 0; w < G->V; w++)
			if (G->adj[v][w])
				if (!G->adj[w][v])
					return false;

	return true;
}

int *UGRAPHdegrees(Graph G)
{
	int *degrees = calloc(G->V, sizeof(int));
	int arcs = 0;

	for (vertex v = 0; v < G->V && arcs < G->V; v++)
		for (vertex w = 0; w < G->V; w++)
			if (v > w && G->adj[v][w])
			{
				degrees[v]++;
				degrees[w]++;
				arcs += 2;
			}

	return degrees;
}

bool GRAPHequal(Graph G, Graph H)
{
	vertex v, w;
	// verifica se o número de vértices (ou) o numero arestas são diferentes entre os grafos.
	if (G->V != H->V || G->A != H->A)
		return false;

	for (v = 0; v < G->V; v++)
		for (w = 0; w < G->V; w++)
			// Compara os elementos das matrizes de adjacência dos grafos G e H na posição [v][w].
			// Se esses elementos forem diferentes, isso significa que há uma diferença entre os grafos.
			if (G->adj[v][w] != H->adj[v][w])
				return false;

	return true;
}

void GRAPHComplete(Graph G)
{
	vertex v, w;
	for (v = 0; v < G->V; v++)
	{
		for (w = v + 1; w < G->V; w++)
		{
			GRAPHinsertArc(G, v, w);
			GRAPHinsertArc(G, w, v);
		}
	}
}

Graph GRAPHrand(int V, int A)
{
	Graph G = GRAPHinit(V);

	srand(time(NULL));

	while (G->A < A)
	{
		vertex v = rand() % V;
		vertex w = rand() % V;
		if (v != w)
			GRAPHinsertArc(G, v, w);
	}

	return G;
}

void GRAPHrandTournament(Graph G)
{
	vertex v, w;
	int r;
	for (v = 0; v < G->V; ++v)
	{
		for (w = v + 1; w < G->V; ++w)
		{
			r = rand() % 2; // gera um valor aleatório de 0 ou 1.

			// Se r for 0, insere um arco do vértice v para o vértice w.
			if (r == 0)
				GRAPHinsertArc(G, v, w);

			// Senão, insere um arco do vértice w para o vértice v.
			else
				GRAPHinsertArc(G, w, v);
		}
	}
}

bool GRAPHcheckWalk(Graph G, int seq[], int n)
{
	int i;

	for (i = 0; i < n - 1; i++)

		// par de vértices que não formam uma aresta no grafo G, a função retorna false.
		// indicando que a sequência seq não representa um caminho válido no grafo G
		if (!G->adj[seq[i]][seq[i + 1]])
			return false;

	return true;
}

int isTopoNumbering(Graph G, int topo[])
{
	for (vertex v = 0; v < G->V; ++v)
		for (vertex w = 0; w < G->V; w++)
			if (G->adj[v][w] && topo[v] >= topo[w])
				return 0;

	return 1;
}

//================== FILA ==================
int queue[1000], begin, next;

int QUEUEget(void)
{
	return queue[begin++];
}

void QUEUEput(int y)
{
	queue[next++] = y;
}

int QUEUEempty(void)
{
	if (begin >= next)
		return 0;
	return 1;
}

void QUEUEinit(int V)
{
	begin = 0;
	next = 0;
}

void QUEUEfree(void)
{
	begin = 0;
	next = 0;
}

// ===================================================================================================
// Busca em profundidade:                                                                            |
// ===================================================================================================
static int cnt, indent, pre[1000], post[1000], pa[1000], num[1000], visited[1000];

static void reachR(Graph G, vertex v)
{
	visited[v] = 1;

	for (vertex w = 0; w < G->V; ++w)
		if (G->adj[v][w] && visited[w] == 0)
			reachR(G, w);
}

int GRAPHreach(Graph G, vertex s, vertex t)
{
	for (vertex v = 0; v < G->V; ++v)
		visited[v] = 0;

	reachR(G, s);

	if (visited[t] == 0)
		return 0;

	return 1;
}

static void dfsR(Graph G, vertex v)
{
	pre[v] = cnt++;

	for (vertex w = 0; w < G->V; w++)
	{
		if (G->adj[v][w])
		{
			for (int i = 0; i < indent; i++)
				printf(". ");
			printf("%d-%d", v, w);

			if (pre[w] == -1)
			{
				printf(" dfsR(G,%d)\n", w);
				indent++;
				dfsR(G, w);
			}
			else
				printf("\n");
		}
	}

	for (int i = 0; i < indent; i++)
		printf(". ");
	printf("%d\n", v);

	indent--;
}

void GRAPHdfs(Graph G)
{
	cnt = 0;

	for (vertex v = 0; v < G->V; ++v)
		pre[v] = -1;

	for (vertex v = 0; v < G->V; ++v)
		if (pre[v] == -1)
		{
			indent = 0;
			printf("%d dfsR(G,%d)\n", v, v);
			dfsR(G, v);
			printf("\n");
		}
}

static void dfsRForest(Graph G, vertex v)
{
	pre[v] = cnt++;

	for (vertex w = 0; w < G->V; w++)
	{
		if (G->adj[v][w])
		{
			for (int i = 0; i < indent; i++)
				printf(". ");
			printf("%d-%d", v, w);

			if (pre[w] == -1)
			{
				pa[w] = v;
				printf(" dfsRForest(G,%d)\n", w);
				indent++;
				dfsRForest(G, w);
			}
			else
				printf("\n");
		}
	}

	for (int i = 0; i < indent; i++)
		printf(". ");
	printf("%d\n", v);

	indent--;

	post[v] = cnt++;
}

void GRAPHdfsForest(Graph G)
{
	cnt = 0;

	for (vertex v = 0; v < G->V; ++v)
		pre[v] = pa[v] = -1;

	for (vertex v = 0; v < G->V; ++v)
		if (pre[v] == -1)
		{
			indent = 0;
			printf("%d dfsRForest(G,%d)\n", v, v);
			pa[v] = v;
			dfsRForest(G, v);
			printf("\n");
		}

	printf("\n\n");
}

void GRAPHclassifyArcs(Graph G)
{
	cnt = 0;

	for (vertex v = 0; v < G->V; ++v)
		pre[v] = post[v] = pa[v] = -1;

	for (vertex v = 0; v < G->V; ++v)
		if (pre[v] == -1)
		{
			pa[v] = v;
			dfsRForest(G, v);
		}

	printf("\n");

	for (vertex v = 0; v < G->V; ++v)
		for (vertex w = 0; w < G->V; ++w)
			if (G->adj[v][w])
			{
				if (pa[w] == v)
					printf("%d-%d floresta\n", v, w);

				else if (pre[v] < pre[w] && post[v] > post[w])
					printf("%d-%d avanco\n", v, w);

				else if (pre[v] > pre[w] && post[v] < post[w])
					printf("%d-%d retorno\n", v, w);

				else
					printf("%d-%d cruzado\n", v, w);
			}
}

// ===================================================================================================
// Busca em largura e distâncias:                                                                     |
// ===================================================================================================

void GRAPHbfs(Graph G, vertex s)
{
	int cnt = 0;
	for (vertex v = 0; v < G->V; ++v)
		pre[v] = -1;

	QUEUEinit(G->V);
	pre[s] = cnt++;
	QUEUEput(s);

	while (!QUEUEempty())
	{
		vertex v = QUEUEget();
		for (vertex w = 0; w < G->V; w++)
			if (G->adj[v][w] && num[w] == -1)
			{
				pre[w] = cnt++;
				QUEUEput(w);
			}
	}
	QUEUEfree();
}
