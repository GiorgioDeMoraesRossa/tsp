#include "GeradorGrafo.h"

GeradorGrafo::GeradorGrafo(int tam)
{
  this->tam = tam;
  srand(time(NULL));
}
Grafo GeradorGrafo::GerarArestas(int nVertices)
{
  Vertice *vertices = (Vertice *)malloc(sizeof(Vertice) * nVertices);
  Grafo grafo(nVertices);
  cout << "Gerando vértices e arestas..." << endl;
  for (int i = 0; i < nVertices; i++)
  {
    Vertice temp(i, rand() % this->tam, rand() % this->tam);
    vertices[i] = temp;
    cout << "Vertice: " << i << " (" << temp.getX() << "," << temp.getY() << ")" << endl;
    for (int j = 0; j < i; j++)
      grafo.adicionarAresta(vertices[j], vertices[i]);
  }
  cout << "Vértices e arestas gerados" << endl;
  free(vertices);//testar
  return grafo;
}