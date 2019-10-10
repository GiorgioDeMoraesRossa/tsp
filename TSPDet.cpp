
#include "GeradorGrafo.h"
#define V 20 //número de vértices
int main()
{
  // cria um gerador(passando o tamanho do plano cartesiano) e gera as arestas
  GeradorGrafo gerador((V + (V * 1 / 3 + 1))); //plano 21x21 quando V(número de vértices) é 15

  Grafo g = gerador.GerarArestas(V); // o gerador de arestas retorna o Grafo gerado

  //chama a funçao que retorna o caminho

  cout << "Percorrendo grafo..." << endl;
  g.caminhoDet();

  int *result = g.obterCaminho();
  //imprime
  cout << "Caminho ótimo: " << endl;
  for (int i = 0; i <= V; i++)
  {
    char v1 = 'A' + result[i];
    cout << "Passo: " << i + 1 << " vertice: " << v1 << endl;
  }

  cout << "custo final: " << g.obterUltimoPeso() << endl;
  return 0;
}