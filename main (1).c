// João Pedro Silva Cassimiro - 2142600
#include <stdio.h>
#include <stdlib.h>

typedef struct grafo {
  int vertice;
  int aresta;
  int **m;
} GRAFO;

int **criaMatriz(int v) {
  int **m = malloc(v * sizeof(int *));
  for (int i = 0; i < v; i++) {
    m[i] = malloc(v * sizeof(int));
  }
  for (int i = 0; i < v; i++) {
    for (int i2 = 0; i2 < v; i2++) {
      m[i][i2] = 0;
    }
  }
  return m;
}

GRAFO *criar(int v) {
  GRAFO *novo = (GRAFO *)malloc(sizeof(GRAFO));
  novo->vertice = v;
  novo->aresta = 0;
  novo->m = criaMatriz(v);
  return novo;
}

void criaAdj(int ini, int fim, GRAFO *gr, int peso) {
  if (gr->m[ini][fim] == 0) {
    gr->m[ini][fim] = peso;
    gr->aresta++;
  }
}

void imprime(GRAFO *gr) {
  for (int i = 0; i < gr->vertice; i++) {
    printf("%d ", i);
  }
  printf("\n");
  for (int i = 0; i < gr->vertice; i++) {
    for (int i2 = 0; i2 < gr->vertice; i2++) {
      printf("%d ", gr->m[i][i2]);
    }
    printf("[%d]\n", i);
  }
}

void menorDistancia(GRAFO *gr, int inicio) {
  int visitado[gr->vertice];
  int dist[gr->vertice];
  int custo[gr->vertice][gr->vertice];
  int pred[gr->vertice];
  int cont;
  int min;
  int prox;
  for (int i = 0; i < gr->vertice; i++) {
    for (int i2 = 0; i2 < gr->vertice; i2++) {
      if (gr->m[i][i2] == 0) {
        custo[i][i2] = 300000000;
      } else {
        custo[i][i2] = gr->m[i][i2];
      }
    }
  }
  for (int i = 0; i < gr->vertice; i++) {
    visitado[i] = 0;
    dist[i] = custo[inicio][i];
    pred[i] = inicio;
  }

  dist[inicio] = 0;
  visitado[inicio] = 0;
  cont = 1;

  while (cont < gr->vertice - 1) {
    min = 300000000;
    for (int i = 0; i < gr->vertice; i++) {
      if (dist[i] < min && visitado[i] == 0) {
        min = dist[i];
        prox = i;
      }
    }
    visitado[prox] = 1;
    for (int i = 0; i < gr->vertice; i++) {
      if (visitado[i] == 0) {
        if (min + custo[prox][i] < dist[i]) {
          dist[i] = min + custo[prox][i];
          pred[i] = prox;
        }
      }
    }
    cont++;
  }
  for (int i = 0; i < gr->vertice; i++) {
    if (i != inicio) {
      printf("\nDistancia da origem ate o vertice %d: %d", i, dist[i]);
    }
  }
}

int main() {
  GRAFO *gr = criar(6);
  criaAdj(0, 1, gr, 1);
  criaAdj(1, 0, gr, 1);
  criaAdj(0, 2, gr, 4);
  criaAdj(2, 0, gr, 4);
  criaAdj(1, 2, gr, 4);
  criaAdj(2, 1, gr, 4);
  criaAdj(1, 3, gr, 2);
  criaAdj(3, 1, gr, 2);
  criaAdj(1, 4, gr, 7);
  criaAdj(4, 1, gr, 7);
  criaAdj(2, 3, gr, 3);
  criaAdj(3, 2, gr, 3);
  criaAdj(2, 3, gr, 5);
  criaAdj(3, 2, gr, 5);
  criaAdj(3, 4, gr, 4);
  criaAdj(4, 3, gr, 4);
  criaAdj(3, 5, gr, 6);
  criaAdj(4, 5, gr, 7);
  criaAdj(5, 4, gr, 7);
  criaAdj(2, 4, gr, 5);
  criaAdj(4, 2, gr, 5);
  criaAdj(5, 3, gr, 6);
  imprime(gr);
  menorDistancia(gr, 0);
  return 0;
}