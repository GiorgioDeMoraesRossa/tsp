
#include "Grafo.h"

int main()
{

  Grafo g(7); // grafo
  // adiciona as arestas

  g.adicionarAresta(0, 1, -3, 2, -3, 1);
  g.adicionarAresta(0, 2, -3, 2, 4, 0);
  g.adicionarAresta(0, 3, -3, 2, 2, -2);
  g.adicionarAresta(0, 4, -3, 2, -2, -2);
  g.adicionarAresta(0, 5, -3, 2, 3, 2);
  g.adicionarAresta(0, 6, -3, 2, -3, -1);

  g.adicionarAresta(1, 2, -3, 1, 4, 0);
  g.adicionarAresta(1, 3, -3, 1, 2, -2);
  g.adicionarAresta(1, 4, -3, 1, -2, -2);
  g.adicionarAresta(1, 5, -3, 1, 3, 2);
  g.adicionarAresta(1, 6, -3, 1, -3, -1);

  g.adicionarAresta(2, 3, 4, 0, 2, -2);
  g.adicionarAresta(2, 4, 4, 0, -2, -2);
  g.adicionarAresta(2, 5, 4, 0, 3, 2);
  g.adicionarAresta(2, 6, 4, 0, -3, -1);

  g.adicionarAresta(3, 4, 2, -2, -2, -2);
  g.adicionarAresta(3, 5, 2, -2, 3, 2);
  g.adicionarAresta(3, 6, 2, -2, -3, -1);

  g.adicionarAresta(4, 5, -2, -2, 3, 2);
  g.adicionarAresta(4, 6, -2, -2, -3, -1);

  g.adicionarAresta(5, 6, 3, 2, -3, -1);

  int *result = g.caminhoDet();
  for (int i = 0; i < 8; i++)
  {
    char v1 = 'A' + result[i];
    cout << "iterador: " << i << " vertice: " << v1 << endl;
  }
  // cout << "custo final: " << result[9] << endl;
  return 0;
}