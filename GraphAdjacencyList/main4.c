#include "ListAdj.h"

// Florestas, árvores, conexão

// gcc ListAdj.c main4.c -c && gcc ListAdj.o main4.o  && ./a.out
// gcc ListAdj.c main4.c -c && gcc ListAdj.o main4.o  && .\a.exe

int main()
{
  // Exemplo G. https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/e-biconnected-graphs.html
  Graph G = GRAPHinit(6);

  GRAPHinsertArc(G, 0, 5);
  GRAPHinsertArc(G, 0, 1);
  GRAPHinsertArc(G, 1, 0);
  GRAPHinsertArc(G, 1, 2);
  GRAPHinsertArc(G, 2, 1);
  GRAPHinsertArc(G, 2, 3);
  GRAPHinsertArc(G, 3, 2);
  GRAPHinsertArc(G, 3, 4);
  GRAPHinsertArc(G, 4, 3);
  GRAPHinsertArc(G, 4, 5);
  GRAPHinsertArc(G, 5, 4);
  GRAPHinsertArc(G, 5, 0);

  GRAPHshow(G);

  printf("\nNumero de componentes conexas do grafo: %d\n\n", UGRAPHconComps(G));

  if (UGRAPHcircuit0(G))
    printf("O grafo nao-dirigido tem circuito.\n\n");
  else
    printf("O grafo nao-dirigido nao tem circuito.\n\n");

  UGRAPHlo(G);
  printLO(G);

  printf("\n");
  if (UGRAPHebicon(G))
    printf("O grafo nao-dirigido e aresta-biconexo.\n");
  else
    printf("O grafo nao-dirigido nao e aresta-biconexo.\n");

  // Exemplo D. https://www.ime.usp.br/~pf/algoritmos_para_grafos/aulas/e-biconnected-graphs.html
  printf("\n--> UGRAPHlo:\n");
  Graph G1 = GRAPHinit(10);

  GRAPHinsertArc(G1, 0, 7);
  GRAPHinsertArc(G1, 0, 1);
  GRAPHinsertArc(G1, 1, 0);
  GRAPHinsertArc(G1, 1, 3);
  GRAPHinsertArc(G1, 1, 2);
  GRAPHinsertArc(G1, 2, 1);
  GRAPHinsertArc(G1, 2, 8);
  GRAPHinsertArc(G1, 2, 7);
  GRAPHinsertArc(G1, 2, 3);
  GRAPHinsertArc(G1, 3, 2);
  GRAPHinsertArc(G1, 3, 1);
  GRAPHinsertArc(G1, 3, 4);
  GRAPHinsertArc(G1, 4, 3);
  GRAPHinsertArc(G1, 4, 6);
  GRAPHinsertArc(G1, 4, 5);
  GRAPHinsertArc(G1, 5, 4);
  GRAPHinsertArc(G1, 5, 6);
  GRAPHinsertArc(G1, 6, 5);
  GRAPHinsertArc(G1, 6, 4);
  GRAPHinsertArc(G1, 7, 2);
  GRAPHinsertArc(G1, 7, 0);
  GRAPHinsertArc(G1, 7, 8);
  GRAPHinsertArc(G1, 8, 7);
  GRAPHinsertArc(G1, 8, 2);
  GRAPHinsertArc(G1, 8, 9);
  GRAPHinsertArc(G1, 9, 8);

  GRAPHshow(G1);
  UGRAPHlo(G1);
  printf("\n");
  printLO(G1);

  return 0;
}
