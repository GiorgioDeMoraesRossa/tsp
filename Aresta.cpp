#include "Aresta.h"

Aresta::Aresta(int v1, int v2, int x1, int y1, int x2, int y2)
{
  vertice1 = Vertice(v1, x1, y1);
  vertice2 = Vertice(v2, x2, y2);
  this->peso = sqrt(((pow((x2 - x1), 2)) + (pow((y2 - y1), 2))));
}
void Aresta::print()
{
  cout << "Peso da aresta v1: " << vertice1.getNum() << " v2: " << vertice2.getNum() << " -> " << peso << endl;
}
int Aresta::obterVertice1()
{
  return vertice1.getNum();
}

int Aresta::obterVertice2()
{
  return vertice2.getNum();
}

float Aresta::obterPeso()
{
  return peso;
}

void Aresta::setPeso(float novoPeso)
{
  peso = novoPeso;
}
// sobrescrita do operador "<"
bool Aresta::operator<(const Aresta &aresta2) const
{
  return (peso < aresta2.peso);
}