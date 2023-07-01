#include "ListAdj.h"

static link NEWnode(vertex w, link next)
{
    link a;
    a = malloc(sizeof(struct node));
    a->w = w;
    a->next = next;
    return a;
}

Graph GRAPHinit(int V)
{
    vertex v;
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->A = 0;
    G->adj = malloc(V * sizeof(link));
    for (v = 0; v < V; ++v)
        G->adj[v] = NULL;
    return G;
}

void GRAPHinsertArc(Graph G, vertex v, vertex w)
{
    link a;
    for (a = G->adj[v]; a != NULL; a = a->next)
        if (a->w == w)
            return;
    G->adj[v] = NEWnode(w, G->adj[v]);
    G->A++;
}

void GRAPHremoveArc(Graph G, vertex v, vertex w)
{
    link p, q = NULL;
    for (p = G->adj[v]; p != NULL; p = p->next)
    {
        if (p->w == w)
        {
            if (q == NULL)
                G->adj[v] = p->next;
            else
                q->next = p->next;
            p = NULL;
            free(p);
            return;
        }
        q = p;
    }
}

void GRAPHshow(Graph G)
{
    link a;
    vertex v;
    for (v = 0; v < G->V; v++)
    {
        printf("%2d: ", v);
        for (a = G->adj[v]; a != NULL; a = a->next)
            printf("%2d", a->w);
        printf("\n");
    }
}

// =============================================================================================

bool GRAPHequal(Graph G, Graph H)
{

    link a;
    link b;
    vertex v;

    // verifica se o número de vértices (ou) o numero arestas são diferentes entre os grafos.
    if (G->V != H->V || G->A != H->A)
    {
        return false;
    }

    // percorre todos os vértices do grafo G.
    for (v = 0; v < G->V; v++)
    {
        // ponteiros para o início da listas.
        a = G->adj[v];
        b = H->adj[v];

        // percorre as duas listas de adjacência G (e) H ao mesmo tempo.
        while (a != NULL && b != NULL)
        {
            // se encontrar duas arestas diferentes entre os grafos G e H, retorna falso.
            if (a->w != b->w)
            {
                return false;
            }

            a = a->next;
            b = b->next;
        }
        // se, após percorrer ambas as listas, ainda houver elementos em uma das listas(ou),
        // isso significa que as listas têm tamanhos diferentes.
        if (a != NULL || b != NULL)
        {
            return false;
        }
    }

    return true;
}

vertex randV(Graph G)
{
    double r;
    r = rand() / (RAND_MAX + 1.0);
    return r * G->V;
}

Graph GRAPHrand(int V, int A)
{
    Graph G = GRAPHinit(V);
    while (G->A < A)
    {
        vertex v = randV(G);
        vertex w = randV(G);
        if (v != w)
            GRAPHinsertArc(G, v, w);
    }
    return G;
}

/* Constrói um grafo aleatório com vértices 0..V-1 e número esperado de arcos igual a A. A função supõe que V >= 2 e A <= V*(V-1). (Código inspirado no Program 17.8 de Sedgewick.) */
Graph GRAPHrandER(int V, int A)
{
    double prob = (double)A / (V * (V - 1));
    Graph G = GRAPHinit(V);
    for (vertex v = 0; v < V; ++v)
        for (vertex w = 0; w < V; ++w)
            if (v != w)
                if (rand() < prob * (RAND_MAX + 1.0))
                    GRAPHinsertArc(G, v, w);
    return G;
}

Graph GRAPHrandTournament(int V)
{
    Graph G = GRAPHinit(V);
    vertex v, w;
    int r;

    for (v = 0; v < V; v++)
    {
        for (w = v + 1; w < V; w++)
        {
            r = rand() % 2; // gera um valor aleatório de 0 ou 1.

            // Se r for 0, insere um arco do vértice v para o vértice w
            if (r == 0)
                GRAPHinsertArc(G, v, w);
            // Senão, insere um arco do vértice w para o vértice v.
            else
                GRAPHinsertArc(G, w, v);

            // garante que exatamente um dos arcos v-w ou w-v será incluído no torneio com igual probabilidade.
        }
    }
    return G;
}

bool GRAPHcheckWalk(Graph G, int seq[], int n)
{
    int i;
    link a;
    bool found;

    // Verifica se a sequência tem tamanho mínimo de 2 (um passeio tem pelo menos 2 vértices)
    if (n < 2)
        return false;

    // Verifica se cada par de vértices consecutivos na sequência forma uma aresta do grafo
    for (i = 0; i < n - 1; i++)
    {
        found = false;
        for (a = G->adj[seq[i]]; a != NULL; a = a->next)
        {
            if (a->w == seq[i + 1])
            {
                found = true;
                break;
            }
        }
        // nenhum arco foi encontrado no grafo que conecta o vértice "seq[i]" ao vértice "seq[i+1]
        if (found == false)
            return false;
    }
    return true;
}

void IsSink(Graph G)
{
    vertex v;
    vertex isSink[G->V];
    link a;
    vertex q;

    for (int i = 0; i < G->V; ++i)
        isSink[i] = -1;

    for (v = 0; v < G->V; ++v)
    {
        if (G->adj[v] != NULL)
        {
            isSink[v] = 0;
        }
        for (q = 0; (q < G->V) && (isSink[v] == -1); ++q)
        {
            for (a = G->adj[q]; a != NULL; a = a->next)
                if (a->w == v)
                {
                    isSink[v] = 1;
                    break;
                }
        }
    }

    printf("\nSink: ");
    for (int i = 0; i < G->V; ++i)
        if (isSink[i] == 1)
            printf("%d ", i);
}

void IsSource(Graph G)
{
    vertex v;
    vertex isSource[G->V];
    link a;
    vertex q;

    for (int i = 0; i < G->V; ++i)
        isSource[i] = 1;

    for (v = 0; v < G->V; ++v)
    {
        if (G->adj[v] == NULL)
        {
            isSource[v] = 0;
        }
        for (q = 0; (q < G->V) && (isSource[v] == 1); ++q)
        {
            for (a = G->adj[q]; a != NULL; a = a->next)
                if (a->w == v)
                {
                    isSource[v] = 0;
                    break;
                }
        }
    }

    printf("\nSource: ");
    for (int i = 0; i < G->V; ++i)
        if (isSource[i] == 1)
            printf("%d ", i);
}

int GRAPHindeg(Graph G, vertex v)
{
    link a;
    vertex vv;
    int count = 0;
    for (vv = 0; vv < G->V; vv++)
    {
        for (a = G->adj[vv]; a != NULL; a = a->next)
        {
            // verificando se o vértice "v" é o destino de um arco que começa no vértice "vv"
            if (a->w == v)
                count++;
        }
    }
    return count;
}

int GRAPHoutdeg(Graph G, vertex v)
{
    link a;
    int count = 0;
    for (a = G->adj[v]; a != NULL; a = a->next)
        count++;
    return count;
}

Graph GRAPHComplete(int V)
{
    Graph G = GRAPHinit(V);
    vertex v, w;

    // Percorre todos os vértices do grafo e seleciona um vértice v.
    for (v = 0; v < G->V; v++)
    {
        // Percorre todos os vértices do grafo e seleciona um vértice w.
        for (w = 0; w < G->V; w++)
        {
            GRAPHinsertArc(G, v, w);
        }
    }

    return G;
}

bool GRAPHisUndirected(Graph G)
{
    int cont, q;
    link a, b;
    vertex v;

    for (v = 0; v < G->V; ++v)
    {
        cont = 0;
        for (a = G->adj[v]; a != NULL; a = a->next)
        {
            q = a->w;
            for (b = G->adj[q]; b != NULL; b = b->next)
                // Se essa condição for verdadeira, significa que existe uma aresta que conecta v a q.
                // O valor da variável cont é alterado para 1.
                if (b->w == v)
                    cont = 1;
            // se a variável cont continuar com valor 0,
            // significa que o vértice v não é adjacente a nenhum outro vértice,
            // portanto o grafo não é não-direcionado(direcionado)
            if (cont == 0)
                return false;
        }
    }

    return true;
}

void UGRAPHdegrees(Graph G)
{
    vertex grau[G->V];
    link a;
    vertex v;

    //if (GRAPHisUndirected(G) == true)

    for (int i = 0; i < G->V; ++i)
        grau[i] = 0;

    for (v = 0; v < G->V; ++v)
        for (a = G->adj[v]; a != NULL; a = a->next)
            grau[v]++;

    printf("\nGraus dos vertices: \n");
    for (int i = 0; i < G->V; ++i)
        printf("%d: %d\n", i, grau[i]);
}

//----------------Grafos topológicos-------------------

bool isTopoNumbering(Graph G, int topo[])
{
    link a;
    vertex v;
    for (v = 0; v < G->V; ++v)
        for (a = G->adj[v]; a != NULL; a = a->next)
            if (topo[v] >= topo[a->w])
                return false;
    return true;
}

int topo[1000];
bool GRAPHisTopo(Graph G)
{
    link a;
    vertex v;
    int indeg[1000];         // Vetor para armazenar o grau de entrada de cada vértice do grafo.
    vertex fila[1000];       // Fila que guarda os vertices que sao fontes (indeg[v] == 0).
    int comeco = 0, fim = 0; // Controlar a fila de vértices que serão processados durante a execução do algoritmo.
    int cnt = 0;             // Contabilizar quantos vértices já foram incluídos na ordenação topológica.

    // percorre todos os vértices do grafo G e atribui o valor 0 ao seu grau de entrada (armazenado no vetor indeg[]).
    // para que o algoritmo de ordenação topológica comece a partir de um estado inicial.
    for (v = 0; v < G->V; ++v)
        indeg[v] = 0;

    for (v = 0; v < G->V; ++v)
        // percorre a lista de adjacência do vértice v.
        for (a = G->adj[v]; a != NULL; a = a->next)
            indeg[a->w] += 1; //Preenchimento do vetor com os graus de entrada dos vertices

    for (v = 0; v < G->V; ++v)
        if (indeg[v] == 0)
            fila[fim++] = v; //Os vertices que sao fontes sao guardados na fila

    while (comeco < fim)
    {
        // fila[comeco..fim-1] contém as fontes virtuais
        v = fila[comeco++];
        topo[v] = cnt++; //topo[] = Guarda a numeracao topologica dos vertices

        //Os arcos v-w vao sendo gradualmente removidos virtualmente, a fim de que cada vizinho de v torne-se uma fonte
        for (a = G->adj[v]; a != NULL; a = a->next)
        {
            indeg[a->w] -= 1; // remoção virtual do arco v-w
            if (indeg[a->w] == 0)
                fila[fim++] = a->w; //Os vertices que tornaram-se fontes sao adicionados à fila de fontes
        }
    }
    // true: todos os vértices foram numerados
    return cnt >= G->V;
}

bool GRAPHisRootedForest(Graph G)
{
    vertex v;
    link a;

    // para ser uma floresta precisa ser um grafo topologico.
    if (!GRAPHisTopo(G))
        return false;

    // verificando se existem vertices com grau de entrada > 1.
    // se existir n eh uma floresta
    for (v = 0; v < G->V; v++)
        if (GRAPHindeg(G, v) > 1)
            return false;

    return true;
}

vertex GRAPHgiveRoot(Graph G)
{
    link a;
    vertex v, q;
    vertex isRoot[G->V];

    for (int i = 0; i < G->V; ++i)
    {
        isRoot[i] = 1;

        for (v = 0; v < G->V; ++v)
        {
            if (G->adj[v] == NULL)
                isRoot[v] = 0;

            for (q = 0; (q < G->V) && (isRoot[v] == 1); ++q)
            {
                for (a = G->adj[q]; a != NULL; a = a->next)
                    if (a->w == v)
                    {
                        isRoot[v] = 0;

                        break;
                    }
            }
        }
    }

    for (int i = 0; i < G->V; i++)
        if (isRoot[i])
            return i;

    return -1;
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

static int visited[1000]; // armazena a numeração dos vértices usando os rótulos 0 e 1, para saber se está ao alcance ou nao.
static int cnt;           // conta o número de vezes que um vértice é descoberto durante uma busca.
static int cntt;          // conta as mortes de vértices(removidos)
static int pre[1000];     // armazena a ordem em que os vértices são visitados antes de visitar seus filhos(pré-ordem).
static int post[1000];    // armazena a ordem em que os vértices são visitados após visitar seus filhos(pós-ordem).
static vertex pa[1000];   // armazenar o pai de cada vértice na floresta.
static int num[1000];     // armazena a ordem em que os vértices são descobertos na bfs.
static int ident;         // identacao
static char indenta[100]; // identacao no rastreamento

static void reachR(Graph G, vertex v)
{
    visited[v] = 1;
    for (link a = G->adj[v]; a != NULL; a = a->next)
        if (visited[a->w] == 0)
            reachR(G, a->w);
}

bool GRAPHreach(Graph G, vertex s, vertex t)
{
    for (vertex v = 0; v < G->V; ++v)
        visited[v] = 0;
    reachR(G, s);
    if (visited[t] == 0)
        return false;
    else
        return true;
}

static void dfsR(Graph G, vertex v)
{
    pre[v] = cnt++;
    for (link a = G->adj[v]; a != NULL; a = a->next)
    {
        vertex w = a->w;
        if (pre[w] == -1)
            dfsR(G, w);
    }
}

void GRAPHdfs(Graph G)
{
    cnt = 0;
    for (vertex v = 0; v < G->V; ++v)
        pre[v] = -1;
    for (vertex v = 0; v < G->V; ++v)
        if (pre[v] == -1)
            dfsR(G, v); // começa nova etapa
}

static void dfsRForest(Graph G, vertex v)
{
    pre[v] = cnt++;
    for (link a = G->adj[v]; a != NULL; a = a->next)
    {
        vertex w = a->w;
        if (pre[w] == -1)
        {
            pa[w] = v; // v-w é arco da floresta
            dfsRForest(G, w);
        }
    }
}

void GRAPHdfsForest(Graph G)
{
    cnt = 0;
    for (vertex v = 0; v < G->V; ++v)
        pre[v] = -1;
    for (vertex v = 0; v < G->V; ++v)
        if (pre[v] == -1)
        {
            pa[v] = v; // v é uma raiz da floresta
            dfsRForest(G, v);
        }
}

static void dfsRPost(Graph G, vertex v)
{
    pre[v] = cnt++;
    for (link a = G->adj[v]; a != NULL; a = a->next)
        if (pre[a->w] == -1)
        {
            pa[a->w] = v;
            dfsRPost(G, a->w);
        }
    post[v] = cntt++; // numeração em pós-ordem
}

void GRAPHdfsPost(Graph G)
{
    cnt = cntt = 0;
    for (vertex v = 0; v < G->V; ++v)
        pre[v] = -1;
    for (vertex v = 0; v < G->V; ++v)
        if (pre[v] == -1)
        {
            pa[v] = v;
            dfsRPost(G, v);
        }
}

void printOrder(Graph G, int pre[])
{
    vertex vv[1000];
    for (vertex v = 0; v < G->V; ++v)
        vv[pre[v]] = v;
    printf("Ordem dos vertices descobertos: ");
    for (int i = 0; i < G->V; ++i)
        printf("%d ", vv[i]);
    printf("\n");
}

void printPre(Graph G)
{
    printf("v\tpre[v]\n");
    for (vertex v = 0; v < G->V; ++v)
        printf("%d\t%d\n", v, pre[v]);
}

void printPost(Graph G)
{
    printf("v\tpost[v]\n");
    for (vertex v = 0; v < G->V; ++v)
        printf("%d\t%d\n", v, post[v]);
}

static void dfsRTrace(Graph G, vertex v)
{
    pre[v] = cnt++;
    for (link a = G->adj[v]; a != NULL; a = a->next)
    {
        vertex w = a->w;
        if (pre[w] == -1)
        {
            pa[w] = v;
            printf("%s%d-%d dfsR(G,%d) \n", indenta, v, w, w);
            strcat(indenta, ". "); // adicionar um espaço em branco e um ponto à string "indenta"
            dfsRTrace(G, w);
        }
        else
            printf("%s%d-%d \n", indenta, v, w);
    }
    printf("%s%d\n", indenta, v);
    indenta[strlen(indenta) - 2] = '\0'; // diminuir o nível de indentação na saída do console
}

void GRAPHdfsTrace(Graph G)
{
    vertex v;
    for (v = 0; v < G->V; ++v)
        pre[v] = -1;

    for (v = 0; v < G->V; ++v)
        if (pre[v] == -1)
        {
            pa[v] = v;
            printf("%d dfsR(G,%d)\n", v, v);
            dfsRTrace(G, v);
        }
}

void GRAPHFileTrace(char *filename)
{
    FILE *fp;
    int V = 1; // total de vertices
    int v, w;  // arcos

    fp = fopen(filename, "r");
    if (!fp)
    {
        printf("Não foi possível abrir o arquivo %s.\n", filename);
        return;
    }

    // numero de vertices
    fscanf(fp, "%d", &V);
    Graph G = GRAPHinit(V);

    while (fscanf(fp, "%d %d", &v, &w) != EOF)
    {
        GRAPHinsertArc(G, v, w);
    }
    fclose(fp);
    GRAPHshow(G);
    printf("\n");
    GRAPHdfsTrace(G);
}

void GRAPHclassifyArcs(Graph G)
{
    GRAPHdfsPost(G);
    link a;
    vertex v, w;
    printf("Classificacao dos Arcos:\n");
    for (v = 0; v < G->V; v++)
        for (a = G->adj[v]; a != NULL; a = a->next)
        {
            w = a->w;
            //printf("\n%d-%d ", v, a->w);

            if (pre[v] < pre[w] && post[w] < post[v] && pa[w] == v)
                printf("%d-%d floresta\n", v, w);

            // se w é um ancestral de v então v-w é de retorno (= back arc);
            else if (pre[v] > pre[w] && post[v] < post[w])
                printf("%d-%d retorno\n", v, w);

            // se w é um descendente de v então v-w é de avanço (= forward arc = down arc);
            else if (pre[v] < pre[w] && post[v] > post[w])
                printf("%d-%d avanco\n", v, w);

            // se w é um primo de v então v-w é cruzado (= cross arc).
            else if ((pre[w] < pre[v] && post[w] < post[v]) &&
                     (pre[v] > pre[w] && post[v] > post[w]))
                printf("%d-%d cruzado\n", v, w);
        }
}

bool GRAPHcycle0(Graph G)
{
    GRAPHdfsPost(G); // calcula pre[] e post[]

    for (vertex v = 0; v < G->V; ++v)
    {
        for (link a = G->adj[v]; a != NULL; a = a->next)
        {
            vertex w = a->w;
            if (post[v] < post[w]) // v-w é de retorno
                return true;
        }
    }
    // post[v] > post[w] para todo arco v-w
    return false;
}

static bool dfsRhcy(Graph G, vertex v)
{
    pre[v] = cnt++;
    for (link a = G->adj[v]; a != NULL; a = a->next)
    {
        vertex w = a->w;
        if (pre[w] == -1)
        {
            if (dfsRhcy(G, w))
                return true;
        }
        else
        {
            if (post[w] == -1)
                return true; // base da recursão
        }
    }
    post[v] = cntt++;
    return false;
}

bool GRAPHcycle(Graph G)
{
    cnt = cntt = 0;
    for (vertex v = 0; v < G->V; ++v)
        pre[v] = post[v] = -1;
    for (vertex v = 0; v < G->V; ++v)
        if (pre[v] == -1)
            if (dfsRhcy(G, v))
                return true;
    return false;
}

// ===================================================================================================
// Busca em largura e distâncias:                                                                     |
// ===================================================================================================

void GRAPHbfs(Graph G, vertex s)
{
    int cnt = 0;
    vertex v;
    for (v = 0; v < G->V; ++v)
        num[v] = -1;
    QUEUEinit(G->V);
    num[s] = cnt++; // descoberto!
    //printf("Descoberto %d\n", num[s]);
    QUEUEput(s);

    printf("Ordem dos vertices descobertos: ");
    while (QUEUEempty() != 0)
    {
        vertex v = QUEUEget();
        link a;
        printf("%d ", v); // Print visited vertex
        for (a = G->adj[v]; a != NULL; a = a->next)
            if (num[a->w] == -1)
            {
                num[a->w] = cnt++; // descoberto!
                //printf("Descoberto %d\n", num[a->w]);
                QUEUEput(a->w);
            }
    }
    QUEUEfree();
}

void GRAPHbfsTree(Graph G, vertex s)
{
    int cnt = 0;
    for (vertex v = 0; v < G->V; ++v)
        num[v] = pa[v] = -1;
    QUEUEinit(G->V);
    num[s] = cnt++;
    pa[s] = s;
    QUEUEput(s);

    while (QUEUEempty() != 0)
    {
        vertex v = QUEUEget();
        for (link a = G->adj[v]; a != NULL; a = a->next)
            if (num[a->w] == -1)
            {
                num[a->w] = cnt++;
                pa[a->w] = v;
                QUEUEput(a->w);
            }
    }
    QUEUEfree();
}

void DAGspt(Dag G, vertex *vv, vertex s, vertex *pa, int *dist)
{
    const int INFINITY = G->V;
    for (vertex v = 0; v < G->V; ++v)
        pa[v] = -1, dist[v] = INFINITY;
    pa[s] = s, dist[s] = 0;

    for (int j = 0; j < G->V; ++j)
    {
        vertex v = vv[j];
        for (link a = G->adj[v]; a != NULL; a = a->next)
        {
            vertex w = a->w;
            if (dist[v] + 1 < dist[w])
            {
                dist[w] = dist[v] + 1; // relaxação de v-w
                pa[w] = v;
            }
        }
    }
}

void GRAPHspt(Graph G, vertex s, int *dist, vertex *pa)
{
    const int INFINITY = G->V;
    for (vertex v = 0; v < G->V; ++v)
        dist[v] = INFINITY, pa[v] = -1;
    dist[s] = 0, pa[s] = s;
    QUEUEinit(G->V);
    QUEUEput(s);

    while (QUEUEempty() != 0)
    {
        vertex v = QUEUEget();
        for (link a = G->adj[v]; a != NULL; a = a->next)
        {
            vertex w = a->w;
            if (dist[w] == INFINITY)
            {
                dist[w] = dist[v] + 1;
                pa[w] = v;
                QUEUEput(w);
            }
        }
    }
    QUEUEfree();
}

void printNum(Graph G)
{
    printf("v\tnum[v]\n");
    for (vertex v = 0; v < G->V; ++v)
        printf("%d\t%d\n", v, num[v]);
}

void printPa(Graph G)
{
    printf("v\tpa[v]\n");
    for (vertex v = 0; v < G->V; ++v)
        printf("%d\t%d\n", v, pa[v]);
}

// ===================================================================================================
// Florestas, árvores, conexão:                                                                      |
// ===================================================================================================

int cc[1000];
static int lo[1000]; // armazena os números de pré-ordem mínimo.
#define min(A, B) (A) < (B) ? (A) : (B);

static void dfsRconComps(UGraph G, vertex v, int id)
{
    cc[v] = id;
    for (link a = G->adj[v]; a != NULL; a = a->next)
        if (cc[a->w] == -1)
            dfsRconComps(G, a->w, id);
}

int UGRAPHconComps(UGraph G)
{
    int id = 0;
    for (vertex v = 0; v < G->V; ++v)
        cc[v] = -1;
    for (vertex v = 0; v < G->V; ++v)
        if (cc[v] == -1)
            dfsRconComps(G, v, id++);
    return id;
}

bool UGRAPHcircuit0(UGraph G)
{
    GRAPHdfsForest(G); // calcula pre[] e pa[]

    for (vertex v = 0; v < G->V; ++v)
    {
        for (link a = G->adj[v]; a != NULL; a = a->next)
        {
            vertex w = a->w;
            if (pre[w] < pre[v]) // v-w é de retorno
                if (w != pa[v])
                    return true;
        }
    }
    return false;
}

void UGRAPHlo(UGraph G)
{
    GRAPHdfsPost(G); // calcula pre[], post[] e pa[]
    vertex vv[1000];
    for (vertex v = 0; v < G->V; ++v)
        vv[post[v]] = v;
    // vv[0..V-1] é permutação em pós-ordem
    for (int i = 0; i < G->V; ++i)
    {
        vertex v = vv[i];
        lo[v] = pre[v];
        for (link a = G->adj[v]; a != NULL; a = a->next)
        {
            vertex w = a->w;
            if (pre[w] < pre[v])
            { // A
                if (w != pa[v])
                    lo[v] = min(lo[v], pre[w]);
            }
            else
            { // B
                if (pa[w] == v)
                    lo[v] = min(lo[v], lo[w]);
            }
        }
    }
}

void printLO(Graph G)
{
    printf("v\tlo[v]\n");
    for (vertex v = 0; v < G->V; ++v)
        printf("%d\t%d\n", v, lo[v]);
}

bool UGRAPHebicon3(UGraph G)
{
    UGRAPHlo(G); // calcula pre[], pa[] e lo[]
    for (vertex v = 0; v < G->V; ++v)
    {
        if (lo[v] == pre[v] && pa[v] != v)
            return false; // pa[v]-v é ponte
    }
    int roots = 0;
    for (vertex v = 0; v < G->V; ++v)
    {
        if (pa[v] == v)
            ++roots;
        if (roots > 1)
            return false; // G é desconexo
    }
    return true;
}

static bool dfsRbridge(UGraph G, vertex v)
{
    pre[v] = cnt++;
    lo[v] = pre[v];
    for (link a = G->adj[v]; a != NULL; a = a->next)
    {
        vertex w = a->w;
        if (pre[w] != -1)
        {                                   // v-w é de retorno ou avanço
            if (w != pa[v])                 // A
                lo[v] = min(lo[v], pre[w]); // B
        }
        else
        {
            pa[w] = v;
            if (dfsRbridge(G, w))      // calcula lo[w]
                return true;           // C
            if (lo[w] == pre[w])       // v-w é ponte
                return true;           // D
            lo[v] = min(lo[v], lo[w]); // E
        }
    }
    return false; // F
}

bool UGRAPHebicon(UGraph G)
{
    for (vertex v = 0; v < G->V; ++v)
        pre[v] = -1;
    cnt = 0;
    pa[0] = 0;
    if (dfsRbridge(G, 0)) // G tem ponte
        return false;
    for (vertex v = 1; v < G->V; ++v)
        if (pre[v] == -1) // G é desconexo
            return false;
    return true;
}
