/**
* This header provides the functions for working with and processing an input file
* @author Sam Gearou
* @author Josh Gearou
* @date 8 Dec 2015
*/

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


/**
* @brief reads in an input file
* @return the file that was read in
*/
file_record readFile();


/**
* @brief constructs a binary tree based on the contents of a file
@return the graph
*/
graph* buildGraph();


/**
* @brief tests if a directed graph is strongly connected
* @param g the graph that is to be tested for strong connectivity
* @return true if the graph is strongly connected
*/
bool isStronglyConnected(graph* g);


/**
* @brief calculates the shortest path from a specified vertex (location)
* to all other locations
* @param g the graph that is used to calculate the shortest paths
* @param index the start vertex of a trip
* @param type either 'T' or 'D' depending on if the user wants the shortest distance
* or the shortest driving time 
*/
void Dijkstra(graph* g, int index, char type);



#endif//__PARSER_H__
