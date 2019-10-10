#include "Aresta.h"

Aresta::Aresta(int v1, int v2, int x1, int y1, int x2, int y2)
{
  vertice1 = Vertice(v1, x1, y1);
  vertice2 = Vertice(v2, x2, y2);
  this->peso = sqrt(((pow((x2 - x1), 2)) + (pow((y2 - y1), 2))));
}

Aresta::Aresta(Vertice v1, Vertice v2)
{
  vertice1 = v1;
  vertice2 = v2;
  this->peso = sqrt(((pow((v2.getX() - v1.getX()), 2)) + (pow((v2.getY() - v1.getY()), 2))));
}

void Aresta::print()
{
  cout << "v1: (" << vertice1.getX() << "," << vertice1.getY() << ") v2: (" << vertice2.getX() << ","
       << vertice2.getY() << ") -> " << peso << endl;
}
int Aresta::obterVertice1()
{
  return vertice1.getNum();
}

int Aresta::obterVertice2()
{
  return vertice2.getNum();
}
Vertice Aresta::obterPVertice1()
{
  return vertice1;
}
Vertice Aresta::obterPVertice2()
{
  return vertice2;
}

double Aresta::obterPeso()
{
  return peso;
}

void Aresta::setPeso(double novoPeso)
{
  peso = novoPeso;
}
// sobrescrita do operador "<"
bool Aresta::operator<(const Aresta &aresta2) const
{
  return (peso < aresta2.peso);
}