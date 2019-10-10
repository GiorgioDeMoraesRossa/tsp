
#include "Grafo.h"
#define MAX 99999

Grafo::Grafo(int V)
{
  this->V = V;
  caminho = new int[V + 1];
  pesoUltimoCaminho = 0;
}

Grafo::Grafo()
{
  this->V = 0;
  pesoUltimoCaminho = 0;
}

Grafo::~Grafo()
{
  delete[] caminho;
}

// função que adiciona uma aresta
void Grafo::adicionarAresta(int v1, int v2, int x1, int y1, int x2, int y2)
{
  Aresta aresta(v1, v2, x1, y1, x2, y2);
  arestas.push_back(aresta);
}
//função que adiciona uma aresta porém recebe os vértices já prontos (e printa quais fez)
void Grafo::adicionarAresta(Vertice v1, Vertice v2)
{
  Aresta aresta(v1, v2);
  //  aresta.print();
  arestas.push_back(aresta);
}

int Grafo::obterV()
{
  return V;
}

double Grafo::obterUltimoPeso()
{
  return pesoUltimoCaminho;
}
int *Grafo::obterCaminho()
{
  return caminho;
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

// função que utiliza o algoritmo de Kruskal e transforma o grafo em uma árvore mínima
void Grafo::kruskal()
{
  vector<Aresta> arvore;
  int size_arestas = arestas.size();

  // ordena as arestas pelo menor peso
  sort(arestas.begin(), arestas.end());

  // aloca memória para criar "V" subconjuntos
  int *subset = new int[V];

  // inicializa todos os subconjuntos como conjuntos de um único elemento -1
  memset(subset, -1, sizeof(int) * V);

  for (int i = 0; i < size_arestas; i++)
  {
    int v1 = buscar(subset, arestas[i].obterVertice1());
    int v2 = buscar(subset, arestas[i].obterVertice2());
    if (v1 != v2)
    {
      // se forem diferentes é porque NÃO forma ciclo, insere no vetor
      arvore.push_back(arestas[i]);
      unir(subset, v1, v2); // faz a união
    }
  }
  // Salva a arvore nas arestas do grafo
  arestas = arvore;
  /*int size_arvore = arvore.size();

  // mostra as arestas selecionadas com seus respectivos pesos
  for (int i = 0; i < size_arvore; i++)
  {
    char v1 = 'A' + arvore[i].obterVertice1();
    char v2 = 'A' + arvore[i].obterVertice2();
    cout << "(" << v1 << ", " << v2 << ") = " << arvore[i].obterPeso() << endl;
  }*/

  return;
}
// função recursiva utilizada para andar pela árvore
void Grafo::passo(int *i, int *caminho, int nVertice, bool *visitados, double *custo)
{

  visitados[nVertice] = true;
  caminho[(*i)] = nVertice;
  *i = *i + 1;

  //procura o próximo vértice para visitar
  for (int j = 0; j < arestas.size(); j++)
  //passa por todas as arestas procurando arestas que passem pelo vértice atual(nVertice)
  {
    if (nVertice == arestas[j].obterVertice1())
    {
      if (!visitados[arestas[j].obterVertice2()])
      // verifica se o outro lado ja foi visitado, se não, visita
      {
        int auxVertice = arestas[j].obterVertice2();
        *custo = *custo + arestas[j].obterPeso();
        passo(i, caminho, auxVertice, visitados, custo);
      }
    }
    if (nVertice == arestas[j].obterVertice2()) // mesma coisa do if acima, porém para o outro "lado" da aresta
    {
      if (!visitados[arestas[j].obterVertice1()])
      {
        int auxVertice = arestas[j].obterVertice1();
        *custo = *custo + arestas[j].obterPeso();
        passo(i, caminho, auxVertice, visitados, custo);
      }
    }
  }
  // se chegou no ultimo nível ele não chama o passo pois o vetor de visitados esta todo True
  if (*i == V)
  {
    //seta o final do caminho para ser o início
    caminho[*i] = 0;
    int j, k;
    for (j = 0; j < arestas.size(); j++)
    //passa por todas as arestas procurando o ultimo vértice
    {
      if (nVertice == arestas[j].obterVertice1() || nVertice == arestas[j].obterVertice2())
        break;
    }
    for (k = 0; k < arestas.size(); k++)
    //passa por todas as arestas procurando o vértice 0
    {
      if (0 == arestas[k].obterVertice1() || 0 == arestas[k].obterVertice2())
        break;
    }
    Vertice v1, v2;
    //pegando o vértice 0
    if (arestas[k].obterVertice1() == 0)
    {
      v1 = arestas[k].obterPVertice1();
    }
    else
    {
      v1 = arestas[k].obterPVertice2();
    }
    //pegando o outro vértice(origem)
    if (arestas[j].obterVertice1() == 0)
    {
      v2 = arestas[j].obterPVertice1();
    }
    else
    {
      v2 = arestas[j].obterPVertice2();
    }
    //calculando o custo da volta
    *custo += sqrt(((pow((v2.getX() - v1.getX()), 2)) + (pow((v2.getY() - v1.getY()), 2))));
  }
  return;
}

//caminha pelo arvore (utilizar após o método kruskal) em pré ordem e retorna o caminho feito
int *Grafo::caminhoPreOrdem()
{
  int *caminho = (int *)malloc(sizeof(int) * V + 1);
  int *i = (int *)malloc(sizeof(int));
  bool *visitados = (bool *)malloc(sizeof(bool) * V);
  double *custo = (double *)malloc(sizeof(double));
  *custo = 0;
  caminho[0] = 0;
  i[0] = 0;
  visitados[0] = true;
  //caminha pela árvore em pré ordem

  passo(i, caminho, 0, visitados, custo);
  //int i, int *caminho, int nVertice, bool *visitados, double *custo)

  //salva o custo do caminho no objeto Grafo

  pesoUltimoCaminho = *custo;
  free(i);
  free(visitados);
  free(custo);
  return caminho;
}
// Copia o segundo vetor de inteiros para o primeiro, e bota ao final do segundo vetor o vértice inicial
void Grafo::copyToFinal(int *caminhoAtual, int *caminhoFinal)
{
  for (int i = 0; i < V; i++)
    caminhoFinal[i] = caminhoAtual[i];
  caminhoFinal[V] = caminhoAtual[0];
}

// função que encontra o valor minimo de uma aresta chegando em i
int Grafo::firstMin(int i)
{
  int min = MAX;
  //passa por todas as arestas procurando por arestas que passem em i, e verifica o menor custo dentre elas
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
  double first = MAX, second = MAX;

  for (int j = 0; j < arestas.size(); j++)
  {
    if (i == j)
      continue;

    // procura arestas que passem por i, e testa seu peso
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
// Recursão para percorrer o grafo procurando a melhor solução
void Grafo::TSPRec(double limiteAtual, double pesoAtual, int nivel, int *caminhoAtual, double *custoFinal, bool *visitados, int *caminhoFinal)
{

  // nivel == V significa que passou por todos os vertices alguma vez
  if (nivel == V)
  {
    // acha onde que a aresta atual liga com o primeiro vértice
    for (int i = 0; i < arestas.size(); i++)
    {
      if (caminhoAtual[nivel - 1] == arestas[i].obterVertice1())
      {
        if (arestas[i].obterVertice2() == 0)
        {

          //respostaAtual tem o peso da solução encontrada

          float respostaAtual = pesoAtual + arestas[i].obterPeso();

          // Atualiza o caminho e resultado final se o resultado atual é melhor

          if (respostaAtual < *custoFinal)
          {
            copyToFinal(caminhoAtual, caminhoFinal);
            pesoUltimoCaminho = respostaAtual; //salva no objeto o custo
            *custoFinal = respostaAtual;
          }
        }
      }
      if (caminhoAtual[nivel - 1] == arestas[i].obterVertice2()) //checa o caso da aresta estar invertida
      {
        if (arestas[i].obterVertice1() == 0)
        {

          float respostaAtual = pesoAtual + arestas[i].obterPeso();
          if (respostaAtual < *custoFinal)
          {
            copyToFinal(caminhoAtual, caminhoFinal);
            pesoUltimoCaminho = respostaAtual; //salva no objeto o custo
            *custoFinal = respostaAtual;
          }
        }
      }
    }
    return;
  }

  // para outros nivels itera em todos os vértices procurando recursivamente por caminhos
  for (int i = 0; i < V; i++)
  {
    if (visitados[i] == false)
    {
      // salva o estado antes de procurar um outro caminho, para caso o caminho seja ruim ter como voltar
      float tempPeso;
      int temp = limiteAtual;

      for (int k = 0; k < arestas.size(); k++) // procura em todas as arestas as que passam pelo vértice i
      {
        if (i == arestas[k].obterVertice1())
        {
          // ao achar uma aresta soma o peso e para de procurar
          if (caminhoAtual[nivel - 1] == arestas[k].obterVertice2())
          {
            tempPeso = arestas[k].obterPeso();
            pesoAtual += tempPeso;
            break;
          }
        }
        if (i == arestas[k].obterVertice2()) //testa se tiver invertido
        {

          if (caminhoAtual[nivel - 1] == arestas[k].obterVertice1())
          {

            tempPeso = arestas[k].obterPeso();
            pesoAtual += tempPeso;
            break;
          }
        }
      }

      // o limite atual é contado de forma diferente no segundo nível pois ainda não tem 2 valores
      if (nivel == 1)
        limiteAtual -= ((firstMin(caminhoAtual[nivel - 1]) + firstMin(i)) / 2);

      else
        limiteAtual -= ((secondMin(caminhoAtual[nivel - 1]) + firstMin(i)) / 2);

      // se a resposta atual é menor que o peso final ainda, precisamos explorar mais
      if (limiteAtual + pesoAtual < *custoFinal)
      {
        caminhoAtual[nivel] = i;
        visitados[i] = true;

        // chama recursão do proximo nivel
        TSPRec(limiteAtual, pesoAtual, nivel + 1, caminhoAtual, custoFinal, visitados, caminhoFinal);
      }

      // se não é menor então descarta as mudanças e da reset nas variáveis para tentar outro caminho
      pesoAtual -= tempPeso;
      limiteAtual = temp;

      memset(visitados, false, sizeof(bool) * V);
      for (int j = 0; j <= nivel - 1; j++)
        visitados[caminhoAtual[j]] = true;
    }
  }
}
// primeira etapa do branch and bound, basicamente seta as variáveis e o início do caminho
void Grafo::TSP(bool *visitados, double *custoFinal)
{
  int caminhoAtual[V + 1];

  // calculo inicial do peso para o primeiro vertice
  // formula: 1/2*(menor + segundo menor) para todos os vertices

  double limiteAtual = 0;
  memset(caminhoAtual, -1, sizeof(caminhoAtual));
  memset(visitados, 0, sizeof(caminhoAtual) - 1);

  // calcula o peso inicial
  for (int i = 0; i < V; i++)
    limiteAtual += (firstMin(i) + secondMin(i)) / 2;

  visitados[0] = true;
  caminhoAtual[0] = 0;

  // chamando a recursão com peso 0 e nivel 1
  TSPRec(limiteAtual, 0, 1, caminhoAtual, custoFinal, visitados, caminho);
}
// retorna o caminho que seria solução ótima para o TSP, utiliza o algoritmo "branch and bound"
void Grafo::caminhoDet()
{

  bool visitados[V];
  double custoFinal = MAX;

  //chama a primeira etapa do algoritmo
  TSP(visitados, &custoFinal);
}