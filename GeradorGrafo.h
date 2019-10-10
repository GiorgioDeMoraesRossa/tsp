#include "Grafo.h"
#include <time.h>
/*
O atributo "tam" define o tamanho do plano cartesiano imaginado para o grafo (sempre quadrado)
*/
using namespace std;

class GeradorGrafo
{
  int tam;

public:
  GeradorGrafo(int tam);
  Grafo GerarArestas(int nVertices);
};