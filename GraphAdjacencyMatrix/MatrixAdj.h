// REPRESENTAÇÃO POR MATRIZ DE ADJACÊNCIAS

/* Vértices de grafos são representados por objetos do tipo vertex. */
#define vertex int
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

struct graph
{
    // número de vértices.
    int V;
    // número de arcos do grafo.
    int A;
    // ponteiro para a matriz de adjacências do grafo.
    int **adj;
};

/* Um Graph é um ponteiro para um graph, ou seja, um Graph contém o endereço de um graph. */
typedef struct graph *Graph;

/* A função GRAPHinit() constrói um grafo com vértices 0 1 .. V-1 e nenhum arco. */
Graph GRAPHinit(int V);

/* A função MATRIXint() aloca uma matriz com linhas 0..r-1 e colunas 0..c-1. 
 * Cada elemento da matriz recebe valor val. */
static int **MATRIXint(int r, int c, int val);

/* A função GRAPHinsertArc() insere um arco v-w no grafo G. 
 * A função supõe que v e w são distintos, positivos e menores que G->V. 
 * Se o grafo já tem um arco v-w, a função não faz nada. */
void GRAPHinsertArc(Graph G, vertex v, vertex w);

/* A função GRAPHremoveArc() remove do grafo G o arco v-w. 
 * A função supõe que v e w são distintos, positivos e menores que G->V. 
 * Se não existe arco v-w, a função não faz nada. */
void GRAPHremoveArc(Graph G, vertex v, vertex w);

/* A função GRAPHshow() imprime, para cada vértice v do grafo G, em uma linha, todos os vértices adjacentes a v. */
void GRAPHshow(Graph G);

// =============================================================================================================

/* Percorre todos os vértices do grafo e, para cada um deles, verifica se ele não tem arestas de saída. 
 * Um sorvedouro (= sink) é um vértice que tem grau de saída nulo.
 * Calcula um vetor global isSink[] indexado pelos vértices
 * e com o valor "1" indicando que o vértice é sorvedouro ou "0" caso não seja. */
void IsSink(Graph G);

/** Identifica as fontes de um grafo, ou seja, os vértices que não têm nenhuma aresta apontando para eles. 
 * A função itera por cada vértice do grafo e verifica se ele é uma fonte ou não.
 * Uma fonte (= source) é um vértice que tem grau de entrada nulo
 * Calcula um vetor global isSource[] indexado pelos vértices
 * e com o valor "1" indicando que o vértice é fonte ou "0" caso não seja. */
void IsSource(Graph G);

/* Grau de entrada de um vértice v de um grafo G */
int GRAPHindeg(Graph G, vertex v);

/* Grau de saída de um vértice v de um grafo G */
int GRAPHoutdeg(Graph G, vertex v);

/* função para saber se um grafo é não-dirigido. */
bool GRAPHisUndirected(Graph G);

/* graus do vertices. */
int *UGRAPHdegrees(Graph G);

/* Verifica se dois grafos são iguais. */
bool GRAPHequal(Graph G, Graph H);

/* Cria um grafo completo, todos os vértices estarão conectados entre si. */
void GRAPHComplete(Graph G);

/* Esta função constrói um grafo aleatório.*/
Graph GRAPHrand(int V, int A);

/* Torneio aleatório. para cada par v w de vértices distintos, exatamente um de v-w e w-v */
void GRAPHrandTournament(Graph G);

/* Verifica passeio no grafo. */
bool GRAPHcheckWalk(Graph G, int seq[], int n);

/* -------------Ordenação Topológica-------------
 * Recebe uma numeração e um Grafo. 
 * E diz se a numeração é topologica para o grafo dado. */
int isTopoNumbering(Graph G, int topo[]);

/* Determina quais vertices sao acessiveis a partir de v. */
static void reachR(Graph G, vertex v);

/* A função GRAPHreach() recebe vértices s e t de um grafo G e decide se t está ao
alcance de s ou não. */
int GRAPHreach(Graph G, vertex s, vertex t);

//================== FILA ==================

// cria uma fila vazia.
void QUEUEinit(int V);

// coloca um vértice na fila
void QUEUEput(int y);

// tira um vértice da fila
int QUEUEget(void);

// verifica se a fila está vazia
int QUEUEempty(void);

// libera o espaço ocupado pela fila.
void QUEUEfree(void);

// ===================================================================================================
// Busca em profundidade:                                                                            |
// ===================================================================================================

/* A função dfsR() visita todos os vértices de G que podem ser alcançados a partir do
vértice v sem passar por vértices já descobertos. A função atribui cnt+k a pre[x] se
x é o k-ésimo vértice descoberto. */
static void dfsR(Graph G, vertex v);

/* A função GRAPHdfs() faz uma busca em profundidade no grafo G. 
Ela atribui um número de ordem pre[x] a cada vértice x de modo que o k-ésimo vértice descoberto
receba o número de ordem k. */
void GRAPHdfs(Graph G);

/* A função dfsR() visita todos os vértices de G que podem ser alcançados a partir de v sem passar por vértices já descobertos. 
Todos esses vértices, e só esses, tornam-se descendentes de v na floresta radicada definida por pa[]. 
Se x é o k-ésimo vértice descoberto, a função atribui cnt+k a pre[x]. */
static void dfsRForest(Graph G, vertex v);

/* A função GRAPHdfsForest() faz uma busca DFS no grafo G. 
Ela atribui um número de ordem pre[x] a cada vértice x 
(o k-ésimo vértice descoberto recebe o número de ordem k) e 
registra a correspondente floresta DFS no vetor de pais pa[]. */
void GRAPHdfsForest(Graph G);

/* Classificação dos arcos. 
função recebe um grafo, construe uma floresta DFS do grafo (invocando GRAPHdfs()), e
depois diz qual o tipo (de floresta, de avanço, de retorno, ou cruzado) de cada arco.*/
void GRAPHclassifyArcs(Graph G);

// ===================================================================================================
// Busca em largura e distâncias:                                                                     |
// ===================================================================================================

/* A função GRAPHbfs() implementa o algoritmo de busca em
largura. Ela visita todos os vértices do grafo G que estão ao
alcance do vértice s. */
void GRAPHbfs(Graph G, vertex s);
