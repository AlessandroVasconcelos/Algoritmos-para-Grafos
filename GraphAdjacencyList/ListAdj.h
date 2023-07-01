// REPRESENTAÇÃO POR LISTAS DE ADJACÊNCIA

#ifndef _LIST_H
#define _LIST_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <assert.h>
#include <time.h>

/* O tipo UGraph é um sinônimo de Graph que tem a missão de deixar claro, para o leitor humano,
 que o grafo é não-dirigido. (O "U" de "UGraph" é uma abreviatura de "undirected".) */
#define UGraph Graph

#define Dag Graph

/* Vértices de grafos são representados por objetos do tipo vertex. */
#define vertex int

typedef struct node *link;

/* A lista de adjacência de um vértice v é composta por nós do tipo node. 
 * Cada nó da lista corresponde a um arco e contém um vizinho w de v e o endereço do nó seguinte da lista. 
 * Um link é um ponteiro para um node. */
struct node
{
    vertex w;
    //ponteiro para o próximo nó na lista de adjacência.
    link next;
};

/* A estrutura graph representa um grafo. */
struct graph
{
    // número de vértices.
    int V;
    // número de arcos do grafo.
    int A;
    // ponteiro para o vetor de listas de adjacência.
    link *adj;
};

/* Um Graph é um ponteiro para um graph, ou seja, um Graph contém o endereço de um graph. */
typedef struct graph *Graph;

/* A função NEWnode() recebe um vértice w e o endereço next de um nó e 
 * devolve o endereço a de um novo nó tal que a->w == w e a->next == next. */
static link NEWnode(vertex w, link next);

/* A função GRAPHinit() constrói um grafo com vértices 0 1 .. V-1 e nenhum arco. */
Graph GRAPHinit(int V);

/* A função GRAPHinsertArc() insere um arco v-w no grafo G. 
 * A função supõe que v e w são distintos, positivos e menores que G->V. 
 * Se o grafo já tem um arco v-w, a função não faz nada. */
void GRAPHinsertArc(Graph G, vertex v, vertex w);

/* Remove o arco v-w do grafo. */
void GRAPHremoveArc(Graph G, vertex v, vertex w);

/* imprime o grafo. */
void GRAPHshow(Graph G);

// ===================================================================================================

/* A função randV() devolve um vértice aleatório do grafo G. Vamos supor que G->V <= RAND_MAX. */
vertex randV(Graph G);

/* Esta função constrói um grafo aleatório com vértices 0..V-1 e exatamente A arcos. 
A função supõe que A <= V*(V-1). 
Se A for próximo de V*(V-1), a função pode consumir muito tempo.*/
Graph GRAPHrand(int V, int A);

/* Constrói um grafo aleatório com vértices 0..V-1 e número esperado de arcos igual a A. 
A função supõe que V >= 2 e A <= V*(V-1). */
Graph GRAPHrandER(int V, int A);

/* Torneio aleatório. para cada par v w de vértices distintos, exatamente um de v-w e w-v */
Graph GRAPHrandTournament(int V);

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

/* Graus do vertices */
void UGRAPHdegrees(Graph G);

/* Verifica se dois grafos são iguais. */
bool GRAPHequal(Graph G, Graph H);

/* Cria um grafo completo, todos os vértices estarão conectados entre si. */
Graph GRAPHComplete(int V);

/* Verifica passeio no grafo. */
bool GRAPHcheckWalk(Graph G, int seq[], int n);

/* -------------Ordenação Topológica-------------
 * Recebe uma numeração e um Grafo. 
 * E diz se a numeração é topologica para o grafo dado. */
bool isTopoNumbering(Graph G, int topo[]);

/* Verifica se um grafo eh topologico. */
bool GRAPHisTopo(Graph G);

/* Verifica se um grafo eh uma floresta radicada.
 * É um grafo topológico sem vértices com grau de entrada maior que 1.*/
bool GRAPHisRootedForest(Graph G);

/* Recebe uma floresta radicada e retorna uma raiz dessa floresta. */
vertex GRAPHgiveRoot(Graph G);

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

/* Determina quais vertices sao acessiveis a partir de v. */
static void reachR(Graph G, vertex v);

/* A função GRAPHreach() recebe vértices s e t de um grafo G e decide se t está ao
alcance de s ou não. */
bool GRAPHreach(Graph G, vertex s, vertex t);

/* A função dfsR() visita todos os vértices de G que podem ser alcançados a partir do
vértice v sem passar por vértices já descobertos. A função atribui cnt+k a pre[x] se
x é o k-ésimo vértice descoberto. */
static void dfsR(Graph G, vertex v);

/* A função GRAPHdfs() faz uma busca em profundidade no grafo G. 
Ela atribui um número de ordem pre[x] a cada vértice x de modo que o k-ésimo vértice descoberto
receba o número de ordem k. */
void GRAPHdfs(Graph G);

/* As funções GRAPHdfsPost() e dfsRPost() numera os vértices em pós-ordem.
A numeração é registrada num vetor post[] indexado pelos vértices:
o m-ésimo vértice a morrer recebe número m */
static void dfsRPost(Graph G, vertex v);

/* As funções GRAPHdfsPost() e dfsRPost() numera os vértices em pós-ordem.
A numeração é registrada num vetor post[] indexado pelos vértices:
o m-ésimo vértice a morrer recebe número m */
void GRAPHdfsPost(Graph G);

/* Permutação dos vértices em pré-ordem. inverte o vetor pre[].
Imprime a ordem em que os vértices foram descobertos, usando a numeração dos vértices do grafo. 
Essa ordem é definida pelo vetor pre[], que indica o momento em que cada vértice foi visitado pela primeira vez */
void printOrder(Graph G, int pre[]);

/* imprime o vetor pre*/
void printPre(Graph G);

/* imprime o vetor post*/
void printPost(Graph G);

/*Realiza uma dfs, imprimindo o rastreamento da funcao*/
static void dfsRPrint(Graph G, vertex v);

/*Realiza uma dfs, imprimindo o rastreamento da funcao*/
void GRAPHdfsPrint(Graph G);

/* Função auxiliar recursiva que implementa a busca em profundidade em um grafo. */
static void dfsRTrace(Graph G, vertex v);

/* Executa uma busca em profundidade (DFS) no grafo G e imprimi todo o rastreamento (trace) do processo de busca.*/
void GRAPHdfsTrace(Graph G);

/* Executa o trace de grafo em um arquivo de texto.*/
void GRAPHFileTrace(char *filename);

/* A função dfsR() visita todos os vértices de G que podem ser alcançados a partir de v sem passar por vértices já descobertos. 
Todos esses vértices, e só esses, tornam-se descendentes de v na floresta radicada definida por pa[]. 
Se x é o k-ésimo vértice descoberto, a função atribui cnt+k a pre[x]. */
static void dfsRForest(Graph G, vertex v);

/* A função GRAPHdfsForest() faz uma busca DFS no grafo G. 
Ela atribui um número de ordem pre[x] a cada vértice x 
(o k-ésimo vértice descoberto recebe o número de ordem k) e 
registra a correspondente floresta DFS no vetor de pais pa[]. */
void GRAPHdfsForest(Graph G);

/* Classificação dos arcos. função recebe um grafo,
construe uma floresta DFS do grafo (invocando GRAPHdfs()), e
depois diz qual o tipo (de floresta, de avanço, de retorno, ou cruzado) de cada arco.*/
void GRAPHclassifyArcs(Graph G);

/* Esta função decide se o grafo G tem um ciclo. */
bool GRAPHcycle0(Graph G);

/* A função dfsRhcy() devolve true se encontra um ciclo ao percorrer G
 a partir do vértice v e devolve false em caso contrário. */
static bool dfsRhcy(Graph G, vertex v);

/* Esta função decide se o grafo G tem um ciclo. */
bool GRAPHcycle(Graph G);

// ===================================================================================================
// Busca em largura e distâncias:                                                                     |
// ===================================================================================================

/* A função GRAPHbfs() implementa o algoritmo de busca em
largura. Ela visita todos os vértices do grafo G que estão ao
alcance do vértice s. A ordem em que os vértices são descobertos
é registrada no vetor num[]. */
void GRAPHbfs(Graph G, vertex s);

/* Árvore de busca em largura. */
void GRAPHbfsTree(Graph G, vertex s);

/* imprime o vetor pre*/
void printNum(Graph G);

/* imprime o vetor post*/
void printPa(Graph G);

/* A função recebe um dag G, uma permutação topológica vv[] dos vértices, e um vértice s de G. 
A função supõe que todos os vértices estão ao alcance de s. A função armazena em pa[] o vetor de pais de uma SPT de G com raiz s.
 As distâncias a partir de s são armazenadas no vetor dist[]. O espaço para os vetores pa[] e dist[] deve ser alocado pelo usuário.*/
void DAGspt(Dag G, vertex *vv, vertex s, vertex *pa, int *dist);

/* Esta função recebe um grafo G e um vértice s de G e armazena em pa[] o vetor de pais de uma SPT
do sub­grafo induzido pelos vértices que estão ao alcance de s. A SPT tem raiz s e as distâncias a partir de s 
são armazenadas no vetor dist[]. O espaço para os vetores pa[] e dist[] deve ser alocado pelo usuário. 
Esta implementação supõe que o grafo G é representado por listas de adjacência. */
void GRAPHspt(Graph G, vertex s, int *dist, vertex *pa);

// ===================================================================================================
// Florestas, árvores, conexão:                                                                      |
// ===================================================================================================

/* A função auxiliar dfsRconComps() atribui o número id a todos os vértices que estão na mesma componente conexa que v. 
A função supõe que o grafo G é representado por listas de adjacência. */
static void dfsRconComps(UGraph G, vertex v, int id);

/* A função UGRAPHconComps() devolve o número de componentes conexas do grafo não-dirigido G. 
Além disso, armazena no vetor cc[] uma numeração dos vértices tal que dois vértices v e w 
pertencem à mesma componente se e somente se cc[v] == cc[w]. */
int UGRAPHconComps(UGraph G);

/* Esta função decide se o grafo não-dirigido G tem algum circuito. */
bool UGRAPHcircuit0(UGraph G);

/* Esta função faz uma busca DFS no grafo não-dirigido G e calcula o lowest preorder number lo[] de cada vértice de G. 
Também calcula os vetores pre[], post[] e pa[] correspondentes à busca DFS. */
void UGRAPHlo(UGraph G);

/* Exibe o vetor lo[].*/
void printLO(UGraph G);

/* A função UGRAPHebicon3() decide se o grafo não-dirigido G é aresta-biconexo. 
(A função implementa o algoritmo de Tarjan.) */
bool UGRAPHebicon3(UGraph G);

/* A função UGRAPHebicon() decide se o grafo não-dirigido G é aresta-biconexo. 
(Esta é uma implementação on-the-fly do algoritmo de Tarjan.) */
bool UGRAPHebicon(UGraph G);

/* A função dfsRbridge() calcula lo[v]. 
Devolve true se houver uma ponte na subfloresta DFS que tem raiz v. Senão, devolve false. */
static bool dfsRbridge(UGraph G, vertex v);

#endif