#include <stdbool.h>
#include <string.h>
#include "graph_lib.h"
#include "queue.h"

graph* graph_edge_reversal(graph* G) {
size_t n = graph_vertex_count(G);
graph* newGraph = graph_create(n, true);

for(size_t i=0;i< n;i++){
vertex_t vs[n];
  graph_neighbors(G, i, vs);
  size_t f = 0;
  graph_degree(G, i, &f);

  for(size_t j = 0; j<f; j++){
graph_add_edge(newGraph, vs[j], i);
  }
}
return newGraph;
}

bool graph_bfs(graph* G, vertex_t start, vertex_t* parent) { //stores an array of parent indices
size_t n = graph_vertex_count(G);
bool marked[n];
for (size_t i = 0; i < n; i++) {
parent[i] = i;
marked[i] = false;
}
marked[start]=true;
queue* Q = queue_create();
queue_add_last(Q, start);


while (!queue_empty(Q)) {
vertex_t current;
queue_get_first (Q, &current );
queue_remove_first(Q);


size_t current_deg;
graph_degree (G, current, &current_deg );
vertex_t neighbors[n];
graph_neighbors (G, current , neighbors);


for (size_t i = 0; i < current_deg; i++){
  if (!marked[neighbors[i]]) {
marked[neighbors[i]] = true;
parent[neighbors [ i ]] = current; //the array of parent indices
queue_add_last(Q, neighbors[i]);
}
}
}
for(size_t i=0; i <n; i++){
  if(marked[i] == false){
    return false;
  }
}
return true;
}
