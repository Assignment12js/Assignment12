#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "parser.h"
#include "graph.h"

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
  size_t n = graph_vertex_count(g);
  for(size_t i =0; i < n; i++){
    vertex_t neighbors[n];
    graph_neighbors(g, i, neighbors);
  size_t deg;
   graph_degree(g, i, &deg);
    for(size_t j=0; j < deg; j++){

    }
  }
}

int main(){
 //file_record fr =readFile();
//graph* obj = buildGraph();

  return EXIT_SUCCESS;

}
