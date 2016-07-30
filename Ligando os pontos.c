#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// MAXV é uma constante que define a quantidade máxima de vértices
#define MAXV 100

// Matriz de adjacências
// Se MAdj[i][j] > 0, então há aresta que liga 'i' a 'j' com custo MAdj[i][j].
float MAdj[MAXV][MAXV];

// Armazena a distância mínima partindo de um vértice 'i' até todos os outros vértices
// dis[j] representa a menor distância de 'i' a 'j'.
float dis[MAXV];

// Calcula as distâncias de 'Vi' a todos os outros vértices de um grafo com 'V' vértices e armazena-as em dis[]
void dijkstra(int Vi, int V) {
  // vis[i] informa se o vértice 'i' já foi visitado/analisado ou não (inicialmente nenhum vértice foi)
  char vis[MAXV];
  memset (vis, 0, sizeof (vis));

  // Inicialmente afirmamos que a menor distância encontrada entre Vi e qualquer outro vértice (exceto o próprio Vi) é infinita
  memset (dis, 0x7f, sizeof (dis));
  dis[Vi] = 0;

  while (1) {
    int i, n = -1;

    for (i = 0; i < V; i++) {
      if (! vis[i] && (n < 0 || dis[i] < dis[n])) {
        n = i;
      }
    }

    if (n < 0) {
      break;
    }

    vis[n] = 1;

    for (i = 0; i < V; i++) {
      if (MAdj[n][i] && dis[i] > dis[n] + MAdj[n][i]) {
        dis[i] = dis[n] + MAdj[n][i];
      }
    }
  }
}

typedef struct {
  float x, y;
} point;

int main () {
  // Número de pontos
  int tamanho;
  scanf("%d", &tamanho);

  // Cria a lista de pontos
  point *pontos = (point*) malloc(tamanho * sizeof(point));
  for (int i = 0; i < tamanho; i++) {
    scanf("%f %f", &pontos[i].x, &pontos[i].y);
  }

  // Calcula a distância dos n pontos para os n pontos
  float x, y;
  for (int i = 0; i < tamanho; i++) {
    for (int j = 0; j < tamanho; j++) {
      x = abs(pontos[i].x - pontos[j].x);
      y = abs(pontos[i].y - pontos[j].y);
      MAdj[i][j] = (x && y) ? sqrt(pow(x, 2) + pow(y, 2)) : x + y;
    }
  }

  // Aplica o Dijkstra e coloca em dis as menores distâncias
  dijkstra(1, tamanho);

  // Soma as distâncias e imprime
  float resposta = 0;
  for (int i = 0; i < tamanho; i++) {
    resposta += dis[i];    
  }
  printf("%.2f\n", resposta);

  return 0;
}
