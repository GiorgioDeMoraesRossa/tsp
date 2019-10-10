#include <stdlib.h>
#include <iostream>
#include <vector>
#include <algorithm> // sort
#include <string.h>  // memset
#include "Aresta.h"

using namespace std;

class Grafo
{
  int V, *caminho;        // número de vértices
  vector<Aresta> arestas; // vetor de arestas
  double pesoUltimoCaminho;

public:
  Grafo(int V);
  Grafo();
  ~Grafo(); // destructor
  void adicionarAresta(int v1, int v2, int x1, int y1, int x2, int y2);
  void adicionarAresta(Vertice v1, Vertice v2);
  int obterV();
  double obterUltimoPeso();
  int *obterCaminho();
  int buscar(int subset[], int i);
  void unir(int subset[], int v1, int v2);
  void kruskal();
  void passo(int *i, int *caminho, int nVertice, bool *visitados, double *custo);
  int *caminhoPreOrdem();
  void copyToFinal(int *caminhoAtual, int *caminhoFinal);
  int firstMin(int i);
  int secondMin(int i);
  void TSPRec(double limiteAtual, double pesoAtual, int nivel, int *caminhoAtual, double *custoFinal, bool *visitados, int *caminhoFinal);
  void TSP(bool *visitados, double *custoFinal);
  void caminhoDet();
};