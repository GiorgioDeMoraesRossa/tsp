
#include "GeradorGrafo.h"
#define V 20 //número de vértices
int main()
{

  Grafo g(V); // grafo

  // cria um gerador(passando o tamanho do plano cartesiano) e gera as arestas
  GeradorGrafo gerador(V + (V * 1 / 3 + 1)); //plano 21x21 quando V(número de vértices) é 15
  g = gerador.GerarArestas(V);
  g.kruskal(); // roda o algoritmo de Kruskal para transformar o grafo em árvore mínima
  // chama a função que constrói um caminho em pré ordem

  int *result = g.caminhoPreOrdem();

  //imprime
  for (int i = 0; i <= V; i++)
  {
    char v1 = 'A' + result[i];
    cout << "Passo: " << i + 1 << " vertice: " << v1 << endl;
  }
  cout << "custo final: " << g.obterUltimoPeso() << endl;
  free(result);
  return 0;
}