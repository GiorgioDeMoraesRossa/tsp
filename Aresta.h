#include "Vertice.h"
#include <math.h>
#include <iostream>
using namespace std;

class Aresta
{
  Vertice vertice1, vertice2;
  double peso;

public:
  Aresta(int v1, int v2, int x1, int y1, int x2, int y2);
  Aresta(Vertice v1, Vertice v2);
  void print();
  int obterVertice1();
  int obterVertice2();
  Vertice obterPVertice1();
  Vertice obterPVertice2();
  double obterPeso();
  void setPeso(double novoPeso);
  bool operator<(const Aresta &aresta2) const;
};