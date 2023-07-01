#include "ListAdj.h"

// Busca em profundidade

// gcc ListAdj.c main2.c -c && gcc ListAdj.o main2.o  && ./a.out
// gcc ListAdj.c main2.c -c && gcc ListAdj.o main2.o  && .\a.exe

int main()
{
    // Exemplo D. https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/reach.html
    printf("\n--> GRAPHreach:\n");
    Graph Greach = GRAPHinit(6);

    GRAPHinsertArc(Greach, 0, 2);
    GRAPHinsertArc(Greach, 0, 4);
    GRAPHinsertArc(Greach, 0, 3);
    GRAPHinsertArc(Greach, 2, 1);
    GRAPHinsertArc(Greach, 2, 4);
    GRAPHinsertArc(Greach, 3, 5);
    GRAPHinsertArc(Greach, 3, 4);
    GRAPHinsertArc(Greach, 4, 5);
    GRAPHinsertArc(Greach, 4, 1);
    GRAPHinsertArc(Greach, 5, 1);

    GRAPHshow(Greach);

    int v = 2, w = 3;

    if (GRAPHreach(Greach, v, w))
    {
        printf("\n%d esta ao alcance de %d\n",w,v);
    }
    else
    {
        printf("\n%d nao esta ao alcance de %d\n",w,v);
    }

    // Exemplo C. https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/dfs.html
    printf("\n--> GRAPHdfsTrace:\n");
    Graph G = GRAPHinit(6);

    GRAPHinsertArc(G, 0, 4);
    GRAPHinsertArc(G, 0, 1);
    GRAPHinsertArc(G, 2, 4);
    GRAPHinsertArc(G, 2, 3);
    GRAPHinsertArc(G, 2, 0);
    GRAPHinsertArc(G, 3, 5);
    GRAPHinsertArc(G, 3, 4);
    GRAPHinsertArc(G, 4, 5);
    GRAPHinsertArc(G, 4, 1);
    GRAPHinsertArc(G, 5, 1);

    GRAPHshow(G);
    printf("\n");
    GRAPHdfsTrace(G);

    // Exemplo B. https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/dfs-pre-and-pos.html
    printf("\n--> GRAPHdfs e GRAPHdfsPost:\n");
    Graph Gpost = GRAPHinit(6);

    GRAPHinsertArc(Gpost, 0, 4);
    GRAPHinsertArc(Gpost, 0, 1);
    GRAPHinsertArc(Gpost, 2, 4);
    GRAPHinsertArc(Gpost, 2, 3);
    GRAPHinsertArc(Gpost, 2, 0);
    GRAPHinsertArc(Gpost, 3, 5);
    GRAPHinsertArc(Gpost, 3, 4);
    GRAPHinsertArc(Gpost, 4, 5);
    GRAPHinsertArc(Gpost, 4, 1);
    GRAPHinsertArc(Gpost, 5, 1);

    GRAPHshow(Gpost);
    printf("\n");
    GRAPHdfs(Gpost);
    printPre(Gpost);
    printf("\n");
    GRAPHdfsPost(Gpost);
    printPost(Gpost);

    // Exemplo F. https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/dfs-forest.html
    printf("\n--> GRAPHclassifyArcs:\n");
    Graph G1 = GRAPHinit(6);

    GRAPHinsertArc(G1, 0, 5);
    GRAPHinsertArc(G1, 0, 1);
    GRAPHinsertArc(G1, 0, 2);
    GRAPHinsertArc(G1, 1, 2);
    GRAPHinsertArc(G1, 1, 0);
    GRAPHinsertArc(G1, 2, 4);
    GRAPHinsertArc(G1, 2, 3);
    GRAPHinsertArc(G1, 2, 1);
    GRAPHinsertArc(G1, 2, 0);
    GRAPHinsertArc(G1, 3, 2);
    GRAPHinsertArc(G1, 3, 4);
    GRAPHinsertArc(G1, 3, 5);
    GRAPHinsertArc(G1, 4, 3);
    GRAPHinsertArc(G1, 4, 2);
    GRAPHinsertArc(G1, 5, 3);
    GRAPHinsertArc(G1, 5, 0);

    GRAPHshow(G1);
    //GRAPHdfsTrace(G1);
    printf("\n");
    GRAPHclassifyArcs(G1);
    
    return 0;
}
