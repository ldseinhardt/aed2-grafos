#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <limits.h>
#include <string.h>
#include <queue>
#include <string.h>

using namespace std;

// Número máximo de vértices do grafo
#define MAX 100

// Verifica se há um caminho de s até t e guarda o caminho em parent
bool bfs(int rGraph[MAX][MAX], int s, int t, int parent[]) {
  // Cria uma lista de visitados
  bool visited[MAX];
  memset(visited, 0, sizeof(visited));

  //cria uma fila com os 's'e marca os vertices visitados
  queue <int> q;
  q.push(s);
  visited[s] = true;
  parent[s] = -1;

  while (!q.empty()) {
    int u = q.front();
    q.pop();

    for (int v = 0; v < MAX; v++) {
      if (!visited[v] && rGraph[u][v] > 0) {
        q.push(v);
        parent[v] = u;
        visited[v] = true;
      }
    }
  }

  return visited[t];
}

// Ford Fulkerson
int fordFulkerson(int graph[MAX][MAX], int s, int t) {
  int u, v;

  // Cria o gráfico residual
  int rGraph[MAX][MAX];
  for (u = 0; u < MAX; u++) {
    for (v = 0; v < MAX; v++) {
      rGraph[u][v] = graph[u][v];
    }
  }

  int parent[MAX];  // Caminhos armazenados do bfs

  int max_flow = 0;  // Fluxo = 0, inicialmente

  // Aumenta o fluxo enquanto houver caminho
  while (bfs(rGraph, s, t, parent)) {
    int path_flow = INT_MAX;
    for (v = t; v != s; v = parent[v]) {
      u = parent[v];
      path_flow = min(path_flow, rGraph[u][v]);
    }

    for (v = t; v != s; v = parent[v]) {
      u = parent[v];
      rGraph[u][v] -= path_flow;
      rGraph[v][u] += path_flow;
    }

    max_flow += path_flow;
  }

  return max_flow;
}

int main () {
  int grafo[MAX][MAX];

  int computadores;
  scanf("%d", &computadores);

  for (int i = 0; i < computadores; i++) {
    for (int j = 0; j < computadores; j++) {
      grafo[i][j] = 0;
    }
  }

  int s, t, c;
  scanf("%d %d %d", &s, &t, &c);

  int v1, v2, v3;
  for (int i = 0; i < c; i++) {
    scanf("%d %d %d", &v1, &v2, &v3);
    grafo[v1-1][v2-1] = v3;
  }

  printf("%d\n", fordFulkerson(grafo, s-1, t-1));

  return 0;
}
