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
  FILE* file = fopen("data/sample.txt", "r");
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
void Dijkstra(graph* g) {
  vertex_t start =readFile().trips[0].start; //start of the trip
  size_t n=graph_vertex_count(g); //number of vertices in the graph
  double length[n][n]; //distance of a road in miles
  double dist[n]; // current best distance
  vertex_t parent[n]; //array of parent pointers
  dist[start]=0; //start distance
  pqueue pq; //priority queue
  pqueue_init(&pq); //initialization of the priority queue
  pqueue_push(&pq, start, 0); //push the start into pqueue
  for (size_t i=1; i<n; i++) { //set all the distances to a default value
dist[i]=99999999;
  }
while(!pqueue_empty(&pq)){ //while the pqueue is not empty

}
}

int main(){
  file_record fr =readFile();
  graph* obj = buildGraph();
  Dijkstra(obj);

  return EXIT_SUCCESS;

}
