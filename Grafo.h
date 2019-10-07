#include <iostream>
#include <vector>
#include <malloc.h>
#include <algorithm> // sort
#include <string.h>  // memset
#include "Aresta.h"

using namespace std;

class Grafo
{
  int V;                  // número de vértices
  vector<Aresta> arestas; // vetor de arestas
  float pesoUltimoCaminho;

public:
  Grafo(int V);
  Grafo();
  void adicionarAresta(int v1, int v2, int x1, int y1, int x2, int y2);
  int obterV();
  float obterUltimoPeso();
  int qntdArestas();
  int buscar(int subset[], int i);
  void unir(int subset[], int v1, int v2);
  void kruskal();
  int passo(int i, int *caminho, int nAresta, vector<Aresta> arestas2, float *custo);
  int *caminhoPreOrdem();
  void copyToFinal(int *caminhoAtual, int *caminhoFinal);
  int firstMin(int i);
  int secondMin(int i);
  void TSPRec(int limiteAtual, int pesoAtual, int level, int *caminhoAtual, float *pesoFinal, bool visitados[], int *caminhoFinal);
  void TSP(int *caminho, bool visited[], float *pesoFinal);

  int *caminhoDet();
  void passoDet(int *caminhoFinal, int *caminhoAtual, bool visitados[], int nivel, int *pesoFinal, int PesoAtual);
  int *caminhoDet2();
};