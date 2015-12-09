#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "parser.h"
#include "graph.h"
#include "graph_lib.h"
#include "pqueue.h"
#include <string.h>
#include <math.h>


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
  vertex_t end = readFile().trips[index].end;
  size_t n=graph_vertex_count(g); //number of vertices in the graph
  size_t roadC=graph_edge_count(g);
  int s= (int) roadC;
  int w = (int) start;
  int u = (int) n;
  int e = (int) end;
  vertex_t cur;
  double length[n][n]; //distance of a road in miles
  double length_1[n][n];
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
      length_1[readFile().roads[i].start][readFile().roads[i].end]=readFile().roads[i].distance;
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
  double d=dist[w];
  for (int i=w-1; i>-1; i--) { //set all the distances to a default value
    dist[i]=99999999;
  }
  for(int i= w+1; i<u; i++){
    dist[i]=99999999;
  }

  while(!pqueue_empty(&pq)){ //while the pqueue is not empty
    pqueue_top(&pq, &vkey, &priority);
    //printf("%zu\n", vkey);
    d=dist[vkey];
    graph_neighbors(g, vkey, neighbors);
    cur=vkey;
    if (d<=dist[cur]) {
      graph_degree(g, vkey, deg);
      for (size_t i=0; i<deg[0]; i++) {
        if (dist[cur] + length[cur][neighbors[i]]< dist[neighbors[i]]) {
          //printf("HELLO\n");
          dist[neighbors[i]]=dist[cur] + length[cur][neighbors[i]];
          parent[neighbors[i]]=cur;
          pqueue_push(&pq,neighbors[i], dist[neighbors[i]]);
          //printf("%zu\n", pqueue_size(&pq));
          //printf("neighbors%zu\n", neighbors[i]);
        }
      }
      pqueue_pop(&pq);
    }
  }
  //printf("%f\n", dist[8]);
  if(type == 'D'){
    printf("Shortest distance from %s to %s\n", readFile().locations[w].name, readFile().locations[e].name);
    printf("Begin at %s\n", readFile().locations[w].name);
    int end = e;
    int number=2;
    while(parent[end] != start){
      number++;
      end = parent[end];
    }
    end =e;
    int par[number];
    par[0] = end;
for(int i=1; i<number; i++){
par[i] = parent[end];
end = parent[end];
}
for(int i=number-2; i>-1; i--){
  printf("Continue to %s (%.2f miles)\n", readFile().locations[par[i]].name,
  length[par[i+1]][par[i]]);
}
printf("Total distance: %.2f miles \n", dist[par[0]]);
  }
  else if(type == 'T'){
    printf("Shortest driving time from %s to %s\n", readFile().locations[w].name, readFile().locations[e].name);
    printf("Begin at %s\n", readFile().locations[w].name);
    int end = e;
    int number=2;
    while(parent[end] != start){
      number++;
      end = parent[end];
    }
    end =e;
    int par[number];
    par[0] = end;
    for(int i=1; i<number; i++){
    par[i] = parent[end];
    end = parent[end];
    }
    int hr;
    int min;
    double sec;
    for(int i=number-2; i>-1; i--){
      if(length[par[i+1]][par[i]] < 1 && length[par[i+1]][par[i]] * 60 > 1){
        min = length[par[i+1]][par[i]] * 60;
        sec = (length[par[i+1]][par[i]] * 60 - min) * 60;
        printf("Continue to %s (%.2f miles @ %.2f mph = %d mins %.2f secs)\n", readFile().locations[par[i]].name,
        length_1[par[i+1]][par[i]], speed[par[i+1]][par[i]], min, sec);
      }
      else if(length[par[i+1]][par[i]] * 60 < 1){
        sec = (length[par[i+1]][par[i]] * 3600);
        printf("Continue to %s (%.2f miles @ %.2f mph = %.2f secs)\n", readFile().locations[par[i]].name,
        length_1[par[i+1]][par[i]], speed[par[i+1]][par[i]], sec);
      }
      else if(floor(length[par[i+1]][par[i]]) == length[par[i+1]][par[i]]){
        hr = length[par[i+1]][par[i]];
        min = 0;
        sec = 0.0;
        printf("Continue to %s (%.2f miles @ %.2f mph = %d hrs %d mins %.2f secs)\n", readFile().locations[par[i]].name,
        length_1[par[i+1]][par[i]], speed[par[i+1]][par[i]], hr, min, sec);
      }
      else{
      hr = (int) length[par[i+1]][par[i]];
      min =  (int) (length[par[i+1]][par[i]] - hr) * 60;
      sec = (((length[par[i+1]][par[i]] - hr) * 60) - (int) min) * 60;
      printf("Continue to %s (%.2f miles @ %.2f mph = %d hrs %d mins %.2f secs)\n", readFile().locations[par[i]].name,
      length_1[par[i+1]][par[i]], speed[par[i+1]][par[i]], hr, min, sec);
      }
    }

    if(dist[par[0]] < 1 && dist[par[0]] > 1){
      hr = (int) dist[par[0]];
      min = (int) (dist[par[0]] - hr) * 60;
      sec = (((dist[par[0]] - hr) * 60) - (int) min) * 60;
      printf("Total time: %d hrs %d mins %.2f secs\n", hr, min, sec);
    }
    else if(floor(dist[par[0]]) == dist[par[0]]){
      hr = dist[par[0]];
      min = 0;
      sec = 0.0;
      printf("Total time: %d hrs %d mins %.2f secs\n", hr, min, sec);
    }
    else if(dist[par[0]] * 60 < 1){
      sec = (dist[par[0]] * 3600);
      printf("Total time: %.2f secs\n", sec);
    }
    if(dist[par[0]] < 1 && dist[par[0]] * 60 > 1){
      min = dist[par[0]] * 60;
      sec = (dist[par[0]] * 60 - min) * 60;
      printf("Total time: %d mins %.2f secs\n", min, sec);
    }
    }
}
