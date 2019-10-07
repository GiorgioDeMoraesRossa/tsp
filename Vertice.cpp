#include "Vertice.h"
Vertice::Vertice(int num, int x, int y)
{
  this->x = x;
  this->y = y;
  this->num = num;
}
Vertice::Vertice()
{
  this->x = -1;
  this->y = -1;
  this->num = -1;
}
int Vertice::getX()
{
  return x;
}
int Vertice::getY()
{
  return y;
}
void Vertice::setX(int x)
{
  this->x = x;
}
void Vertice::setY(int y)
{
  this->y = y;
}
int Vertice::getNum()
{
  return num;
}
