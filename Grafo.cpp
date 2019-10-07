
#include "Grafo.h"

Grafo::Grafo(int V)
{
  this->V = V;
  pesoUltimoCaminho = 0;
}

Grafo::Grafo()
{
  this->V = 0;
  pesoUltimoCaminho = 0;
}
// função que adiciona uma aresta
void Grafo::adicionarAresta(int v1, int v2, int x1, int y1, int x2, int y2)
{
  Aresta aresta(v1, v2, x1, y1, x2, y2);
  //aresta.print();
  arestas.push_back(aresta);
}

int Grafo::qntdArestas()
{
  return arestas.size();
}

int Grafo::obterV()
{
  return V;
}

float Grafo::obterUltimoPeso()
{
  return pesoUltimoCaminho;
}

// função que busca o subconjunto de um elemento "i"
int Grafo::buscar(int subset[], int i)
{
  if (subset[i] == -1)
    return i;
  return buscar(subset, subset[i]);
}

// função para unir dois subconjuntos em um único subconjunto
void Grafo::unir(int subset[], int v1, int v2)
{
  int v1_set = buscar(subset, v1);
  int v2_set = buscar(subset, v2);
  subset[v1_set] = v2_set;
}

/// função que roda o algoritmo de Kruskal
void Grafo::kruskal()
{
  vector<Aresta> arvore;
  int size_arestas = arestas.size();

  // ordena as arestas pelo menor peso
  sort(arestas.begin(), arestas.end());

  // aloca memória para criar "V" subconjuntos
  int *subset = new int[V];

  // inicializa todos os subconjuntos como conjuntos de um único elemento
  memset(subset, -1, sizeof(int) * V);

  for (int i = 0; i < size_arestas; i++)
  {
    int v1 = buscar(subset, arestas[i].obterVertice1());
    int v2 = buscar(subset, arestas[i].obterVertice2());
    cout << "v1: " << v1 << " v2: " << v2 << endl;
    if (v1 != v2)
    {
      // se forem diferentes é porque NÃO forma ciclo, insere no vetor
      cout << "inseriu"
           << " v1: " << v1 << " v2: " << v2 << endl;
      arvore.push_back(arestas[i]);
      unir(subset, v1, v2); // faz a união
    }
  }

  int size_arvore = arvore.size();

  // mostra as arestas selecionadas com seus respectivos pesos
  for (int i = 0; i < size_arvore; i++)
  {
    char v1 = 'A' + arvore[i].obterVertice1();
    char v2 = 'A' + arvore[i].obterVertice2();
    cout << "(" << v1 << ", " << v2 << ") = " << arvore[i].obterPeso() << endl;
  }
  V = size_arvore;
  arestas = arvore;

  for (int i = 0; i < size_arvore; i++)
  {

    cout << "(" << arestas[i].obterVertice1() << ", " << arestas[i].obterVertice2() << ") = " << arestas[i].obterPeso() << endl;
  }

  return;
}

int Grafo::passo(int i, int *caminho, int nAresta, vector<Aresta> arestas2, float *custo)
{
  if (i > V)
  {
    cout << "ja? i: " << i << "v: " << V << endl;
    return i;
  }

  // cout << "vertice: " << vertice << " i: " << i << endl;
  caminho[i] = nAresta;
  i++;
  cout << " caminho: " << caminho[i - 1] << " NARESTA: " << nAresta << endl;

  for (int j = 0; j < arestas2.size(); j++)
  {
    cout << "j: " << j << " vertice: " << nAresta << " v1: " << arestas2[j].obterVertice1() << " v2: " << arestas2[j].obterVertice2() << endl;

    if (nAresta == arestas2[j].obterVertice1())
    {
      cout << "entrei" << endl;
      if (arestas2[arestas2[j].obterVertice2()].obterPeso() != -1)
      {
        cout << "if 1 do loop: " << i << endl;
        *custo = *custo + arestas2[arestas2[j].obterVertice2()].obterPeso();
        arestas2[arestas2[j].obterVertice2()].setPeso(-1);
        i = this->passo(i, caminho, arestas2[j].obterVertice2(), arestas2, custo);
      }
    }
    if (nAresta == arestas2[j].obterVertice2())
    {
      if (arestas2[arestas2[j].obterVertice1()].obterPeso() != -1)
      {
        cout << "if 2 do loop: " << i << endl;
        *custo += arestas2[arestas2[j].obterVertice1()].obterPeso();
        arestas2[arestas2[j].obterVertice1()].setPeso(-1);
        cout << "i: " << i << " arestas2[j].v1: " << arestas2[j].obterVertice1() << endl;
        i = this->passo(i, caminho, arestas2[j].obterVertice1(), arestas2, custo);
      }
    }
  }

  return i;
}

int *Grafo::caminhoPreOrdem()
{
  int result, *caminho = (int *)malloc(sizeof(int) * V + 1);
  vector<Aresta> arestas2;
  arestas2 = arestas;
  arestas2[0].setPeso(-1);
  float *custo = (float *)malloc(sizeof(float));
  result = passo(0, caminho, 0, arestas2, custo);
  cout << "custo: " << *custo << endl;
  pesoUltimoCaminho = *custo;
  caminho[V + 1] = 0;
  return caminho;
}

void Grafo::copyToFinal(int *caminhoAtual, int *caminhoFinal)
{
  for (int i = 0; i < V; i++)
    caminhoFinal[i] = caminhoAtual[i];
  caminhoFinal[V] = caminhoAtual[0];
}

// função que encontra o valor minimo de uma aresta chegando em i
int Grafo::firstMin(int i)
{
  int min = 999999999;
  for (int j = 0; j < arestas.size(); j++)
  {
    if (arestas[j].obterVertice1() == i || arestas[j].obterVertice2() == i)
    {
      if (arestas[j].obterPeso() < min)
        min = arestas[j].obterPeso();
    }
  }
  return min;
}

// função que encontra o segundo menor valor de uma aresta chegando em i
int Grafo::secondMin(int i)
{
  int first = 999999999, second = 999999999;

  for (int j = 0; j < arestas.size(); j++)
  {
    if (i == j)
      continue;

    if (arestas[j].obterVertice1() == i || arestas[j].obterVertice2() == i)
    {
      if (arestas[j].obterPeso() < first)
      {
        second = first;
        first = arestas[j].obterPeso();
      }
      else if (arestas[j].obterPeso() <= second && arestas[j].obterPeso() != first)
        second = arestas[j].obterPeso();
    }
  }
  return second;
}

void Grafo::TSPRec(int limiteAtual, int pesoAtual, int level, int *caminhoAtual, float *pesoFinal, bool visitados[], int *caminhoFinal)
{
  // level == V significa que passou por todos os vertices alguma vez
  if (level == V)
  {

    // acha onde que a aresta atual liga com o primeiro vértice
    for (int i = 0; i < arestas.size(); i++)
    {
      if (caminhoAtual[level - 1] == arestas[i].obterVertice1())
      {
        if (arestas[i].obterVertice2() == 0)
        {

          //respostaAtual tem o peso da solução encontrada

          float respostaAtual = pesoAtual + arestas[i].obterPeso();

          // Atualiza o caminho e resultado final se o resultado atual é melhor

          if (respostaAtual < *pesoFinal)
          {
            copyToFinal(caminhoAtual, caminhoFinal);
            *pesoFinal = respostaAtual;
          }
        }
      }
      if (caminhoAtual[level - 1] == arestas[i].obterVertice2()) //checa o caso da aresta estar invertida
      {
        if (arestas[i].obterVertice1() == 0)
        {

          float respostaAtual = pesoAtual + arestas[i].obterPeso();

          if (respostaAtual < *pesoFinal)
          {
            copyToFinal(caminhoAtual, caminhoFinal);
            *pesoFinal = respostaAtual;
          }
        }
      }
    }
    return;
  }

  // para outros levels itera em todos os vértices procurando recursivamente por caminhos
  for (int i = 0; i < V; i++)
  {
    if (visitados[i] == false)
    {
      float tempPeso;
      int temp = limiteAtual;
      for (int k = 0; k < arestas.size(); k++)
      {
        if (i == arestas[k].obterVertice1())
        {

          if (caminhoAtual[level - 1] == arestas[k].obterVertice2())
          {

            tempPeso = arestas[k].obterPeso();
            pesoAtual += tempPeso;
          }
        }
        if (i == arestas[k].obterVertice2()) //testa se tiver invertido
        {

          if (caminhoAtual[level - 1] == arestas[k].obterVertice1())
          {

            tempPeso = arestas[k].obterPeso();
            pesoAtual += tempPeso;
          }
        }
      }

      // o limite atual é contado de forma diferente no segundo nível pois ainda não tem 2 valores
      if (level == 1)
        limiteAtual -= ((firstMin(caminhoAtual[level - 1]) + firstMin(i)) / 2);

      else
        limiteAtual -= ((secondMin(caminhoAtual[level - 1]) + firstMin(i)) / 2);

      // se a resposta atual é menor que o peso final ainda, precisamos explorar mais
      if (limiteAtual + pesoAtual < *pesoFinal)
      {
        caminhoAtual[level] = i;
        visitados[i] = true;

        // chama recursão do proximo level
        TSPRec(limiteAtual, pesoAtual, level + 1, caminhoAtual, pesoFinal, visitados, caminhoFinal);
      }

      // se não é menor então descarta as mudanças e da reset nas variáveis para tentar outro caminho
      pesoAtual -= tempPeso;
      limiteAtual = temp;

      memset(visitados, false, sizeof(bool) * V);
      for (int j = 0; j <= level - 1; j++)
        visitados[caminhoAtual[j]] = true;
    }
  }
}

void Grafo::TSP(int *caminho, bool visitados[], float *pesoFinal)
{
  int caminhoAtual[V + 1];

  // calculo inicial do peso para o primeiro vertice
  // formula: 1/2*(menor + segundo menor) para todos os vertices

  float limiteAtual = 0;
  memset(caminhoAtual, -1, sizeof(caminhoAtual));
  memset(visitados, 0, sizeof(caminhoAtual));

  // calcula o peso inicial
  for (int i = 0; i < V; i++)
    limiteAtual += (firstMin(i) + secondMin(i)) / 2;

  visitados[0] = true;
  caminhoAtual[0] = 0;

  // chamando a recursão com peso 0 e level 1
  TSPRec(limiteAtual, 0, 1, caminhoAtual, pesoFinal, visitados, caminho);
}

int *Grafo::caminhoDet()
{

  int *caminho = (int *)malloc(sizeof(int) * (V + 2));

  bool visitados[V];

  float *pesoFinal = (float *)malloc(sizeof(int));
  *pesoFinal = 99999;
  TSP(caminho, visitados, pesoFinal);

  cout << "Peso final: " << *pesoFinal << endl;
  pesoUltimoCaminho = *pesoFinal;
  return caminho;
}