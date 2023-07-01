#include "ListAdj.h"

// gcc ListAdj.c main1.c -c && gcc ListAdj.o main1.o  && ./a.out
// gcc ListAdj.c main1.c -c && gcc ListAdj.o main1.o  && .\a.exe

int main()
{
    Graph G = GRAPHinit(7);

    GRAPHinsertArc(G, 0, 1);
    GRAPHinsertArc(G, 0, 2);
    GRAPHinsertArc(G, 0, 4);
    GRAPHinsertArc(G, 0, 6);
    GRAPHinsertArc(G, 1, 3);
    GRAPHinsertArc(G, 1, 2);
    GRAPHinsertArc(G, 2, 1);
    GRAPHinsertArc(G, 4, 3);
    GRAPHinsertArc(G, 4, 6);
    GRAPHinsertArc(G, 4, 2);
    GRAPHinsertArc(G, 5, 3);
    GRAPHinsertArc(G, 6, 4);

    GRAPHremoveArc(G, 0, 4);
    GRAPHshow(G);

    IsSink(G);   // vertice 3 não tem grau de saida. ->
    IsSource(G); // vertices 0 e 5 não tem grau de entrada. <-

    printf("\nGrau de entrada: %d", GRAPHindeg(G, 5));  // nenhuma aresta é formada com entrada no 0. 0-?
    printf("\nGrau de saida: %d\n", GRAPHoutdeg(G, 0)); // existem 3 arestas saindo do vertice 0. 0-1, 0-2 e 0-6

    printf("\n--> GRAPHisUndirected:\n");
    Graph G2 = GRAPHinit(6);

    GRAPHinsertArc(G2, 0, 5);
    GRAPHinsertArc(G2, 0, 1);
    GRAPHinsertArc(G2, 1, 0);
    GRAPHinsertArc(G2, 1, 2);
    GRAPHinsertArc(G2, 2, 1);
    GRAPHinsertArc(G2, 2, 3);
    GRAPHinsertArc(G2, 3, 2);
    GRAPHinsertArc(G2, 3, 4);
    GRAPHinsertArc(G2, 4, 3);
    GRAPHinsertArc(G2, 4, 5);
    GRAPHinsertArc(G2, 5, 4);
    GRAPHinsertArc(G2, 5, 0);
    GRAPHshow(G2);

    //Exemplo de um conjunto de arcos abaixo define um grafo não-dirigido:
    // 0-1 0-2 0-5 1-2 2-3 2-4 3-4 3-5
    // 1-0 2-0 5-0 2-1 3-2 4-2 4-3 5-3

    if (GRAPHisUndirected(G2) == true)
    {
        printf("\nO Grafo e nao-dirigido!\n");
    }
    else
    {
        printf("\nO Grafo eh dirigido!\n");
    }

    printf("\n--> GRAPHComplete:\n");
    Graph G3 = GRAPHComplete(5);
    Graph G4 = GRAPHComplete(5);
    GRAPHshow(G3);
    printf("\n");
    GRAPHshow(G4);

    printf("\n--> GRAPHequal:");
    if (GRAPHequal(G4, G3) == true)
    {
        printf("\nOs grafos sao iguais!\n");
    }
    else
    {
        printf("\nOs grafos sao diferentes!\n");
    }

    printf("\n--> GRAPHcheckWalk:\n");
    Graph G1 = GRAPHinit(5);
    GRAPHinsertArc(G1, 0, 1);
    GRAPHinsertArc(G1, 1, 2);
    GRAPHinsertArc(G1, 2, 3);
    GRAPHinsertArc(G1, 3, 4);
    GRAPHshow(G1);

    int seq1[] = {0, 1, 2, 3, 4}; // passeio válido
    int seq2[] = {0, 1, 2, 1, 3}; // não é passeio
    int seq3[] = {2, 1, 0};       // não é passeio
    // nao eh passeio quando contém um salto (jump), uma transição de um vértice para outro sem passar por uma aresta do grafo.

    bool isWalk1 = GRAPHcheckWalk(G1, seq1, 5);
    bool isWalk2 = GRAPHcheckWalk(G1, seq2, 5);
    bool isWalk3 = GRAPHcheckWalk(G1, seq3, 3);

    if (isWalk2 == true)
    {
        printf("\nA sequencia no grafo eh um passeio.\n");
    }
    else
    {
        printf("\nA sequencia no grafo nao eh um passeio.\n");
    }

    printf("\n--> GRAPHrand:\n");
    GRAPHshow(GRAPHrand(5, 6));

    printf("\n--> GRAPHrandER:\n");
    GRAPHshow(GRAPHrandER(5, 6));

    printf("\n--> GRAPHisRootedForest:\n");
    Graph Grooted = GRAPHinit(4);
    GRAPHinsertArc(Grooted, 0, 1);
    GRAPHinsertArc(Grooted, 0, 3);
    GRAPHinsertArc(Grooted, 1, 2);
    GRAPHshow(Grooted);

    if (GRAPHisRootedForest(Grooted))
        printf("\nO grafo eh uma floresta radicada.\n");
    else
        printf("\nO grafo nao eh uma floresta radicada.\n");

    return 0;
}
