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
graph_add_edge(readFile(), vertex_t u, vertex_t v)
 }
}

int main(){
// file_record obj =readFile();
// for (size_t i = 0; i < obj.location_count; i++)
//  {
//      printf("    %zu: %s %lu\n", i, obj.locations[i].name, obj.locations[i].id);
//  }
  return EXIT_SUCCESS;

}
