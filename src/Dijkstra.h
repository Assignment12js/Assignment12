#ifndef __DIJKSTRA_H__
#define __DIJKSTRA_H__

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "parser.h"
#include "graph.h"
#include "graph_lib.h"
#include "pqueue.h"
#include <string.h>
#include <math.h>

file_record readFile();

graph* buildGraph();

bool isStronglyConnected(graph* g);

void Dijkstra(graph* g, int index, char type);



#endif//__PARSER_H__
