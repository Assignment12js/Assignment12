#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "parser.h"
#include "graph.h"
#include "graph_lib.h"
#include "pqueue.h"


/**
* @brief reads a file, and creates a file_record
* @return a file_record
*/
file_record readFile(){
  FILE* file = fopen("data/Ok.txt", "r");
  file_record fr = parse_file(file);
  fclose(file);
  return fr;
}

/**
* @brief builds a graph
* @return a graph
*/
graph* buildGraph(){
  int i = readFile().location_count;
  graph* newGraph = graph_create(i, true);

  for(size_t i=0; i < readFile().road_count; i++){
    graph_add_edge(newGraph, readFile().roads[i].start, readFile().roads[i].end);
  }

  return newGraph;
}

bool isStronglyConnected(graph* g){
  bool isStrong;
  size_t size = graph_vertex_count(g);
  vertex_t parent[size];
  isStrong = graph_bfs(g, 0, parent);
  if(!isStrong){
    return false;
  }
  else{
    graph* reverse = graph_edge_reversal(g);
    isStrong = graph_bfs(reverse, 0, parent);
    if(!isStrong){
      return false;
    }
    else{
      return true;
    }
  }
}
void Dijkstra(graph *graph) {
  unsigned long start =readFile().trips[0].start;
  size_t v=graph_vertex_count(graph);
  vertex_t s=start;
  unsigned long n=v;
  double length[n][n];
  double dist[n];
  vertex_t parent[n];
  pqueue* Q;
  dist[s]=0;
  pqueue_push(Q, s, 0);
  for (int i=1; i<v; i++) {
dist[i]=-1;
  }
  for (int j=0; j<v; j++) {

  }
}

int main(){
  //file_record fr =readFile();
  //graph* obj = buildGraph();

  return EXIT_SUCCESS;

}
