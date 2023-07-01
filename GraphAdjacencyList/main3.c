#include "ListAdj.h"

// Busca em largura e distâncias

// gcc ListAdj.c main3.c -c && gcc ListAdj.o main3.o  && ./a.out
// gcc ListAdj.c main3.c -c && gcc ListAdj.o main3.o  && .\a.exe

int main()
{

    // Exemplo A. https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/bfs.html
    printf("\n--> GRAPHbfs:\n");
    Graph G = GRAPHinit(6);

    GRAPHinsertArc(G, 0, 4);
    GRAPHinsertArc(G, 0, 3);
    GRAPHinsertArc(G, 0, 2);
    GRAPHinsertArc(G, 1, 4);
    GRAPHinsertArc(G, 1, 2);
    GRAPHinsertArc(G, 2, 4);
    GRAPHinsertArc(G, 3, 5);
    GRAPHinsertArc(G, 3, 4);
    GRAPHinsertArc(G, 4, 5);
    GRAPHinsertArc(G, 5, 1);

    GRAPHshow(G);
    printf("\n");
    GRAPHbfs(G, 0);

    // Exemplo C. https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/bfs.html
    printf("\n\n--> GRAPHbfsTree:\n");
    GRAPHbfsTree(G,0);
    printPa(G);

    
    return 0;
}
