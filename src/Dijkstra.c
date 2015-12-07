#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "parser.h"
#include "graph.h"
#include "graph_lib.h"
#include "pqueue.h"
#include <string.h>


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
void Dijkstra(graph* g, int index, char type) {
  double priority;
  vertex_t start =readFile().trips[index].start; //start of the trip
  size_t n=graph_vertex_count(g); //number of vertices in the graph
  size_t roadC=graph_edge_count(g);
  int s= (int) roadC;
  vertex_t cur;
  double length[n][n]; //distance of a road in miles
  double speed[n][n]; //speed of the vehicle in miles per hour
  double dist[n]; // current best distance
  vertex_t parent[n]; //array of parent pointers
  dist[start]=0; //start distance
  pqueue pq; //priority queue
  pqueue_init(&pq); //initialization of the priority queue
  pqueue_push(&pq, start, 0); //push the start into pqueue
  for (int i=0; i<s; i++){
  if(type== 'D'){
    length[readFile().roads[i].start][readFile().roads[i].end]=readFile().roads[i].distance;
  }
  else if(type == 'T'){
length[readFile().roads[i].start][readFile().roads[i].end]=readFile().roads[i].distance/readFile().roads[i].speed;
      //this will all be in terms of hours!! need to change for the output
  }
}
  for(int i=0; i<s; i++){
     speed[readFile().roads[i].start][readFile().roads[i].end]=readFile().roads[i].speed;
  }
  //printf("%s\n", readFile().locations[0].name); //LOOK
  size_t deg[1];
  vertex_t neighbors[n];
  vertex_t vkey;
  double d=dist[0];
  for (size_t i=1; i<n; i++) { //set all the distances to a default value
dist[i]=99999999;
  }

while(!pqueue_empty(&pq)){ //while the pqueue is not empty
pqueue_top(&pq, &vkey, &priority);
d=dist[vkey];
graph_neighbors(g, vkey, neighbors);
cur=vkey;
if (d<=dist[cur]) {
  graph_degree(g, vkey, deg);
  for (size_t i=0; i<deg[0]; i++) {
    if (dist[cur] + length[cur][neighbors[i]]< dist[neighbors[i]]) {
  dist[neighbors[i]]=dist[cur] + length[cur][neighbors[i]];
  parent[neighbors[i]]=cur;
  pqueue_push(&pq,neighbors[i], dist[neighbors[i]]);
    }
    else {
      pqueue_pop(&pq);
    }
    if (neighbors[i]==readFile().location_count-1) {
      pqueue_pop(&pq);
    }
  }
}
}
printf("%s\n", readFile().locations[14].name);
if(type == 'D'){

}
}

int main(){
  file_record fr =readFile();
  graph* obj = buildGraph();
  int v = 0;
  char ok = 'D';
  Dijkstra(obj, v, ok);


  return EXIT_SUCCESS;

}
