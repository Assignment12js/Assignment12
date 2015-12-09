/**
* This header provides the functions for finding the shortest path of a graph.
* @author Sam Gearou
* @author Josh Gearou
* @date 8 Dec 2015
*/
#ifndef __GRAPH_LIB_H__
#define __GRAPH_LIB_H__

#include "graph.h"

/**
 * Takes an input graph and produces a new graph with all edge directions reversed.
 *
 * Note: The returned graph is a NEW graph. Do not modify the orginal graph!
 *
 * @param  G input graph
 * @return   new graph with reversed edges.
 */
graph* graph_edge_reversal(graph* G);

/**
 * Performs a BFS without restart.
 *
 * The output of this search is an array of parent indexies. The start vertex
 * and any vertices not reachable by the search should be considered their own
 * parent.
 *
 * @param G      the graph to search
 * @param start  vertex to start the search with
 * @param parent[out] the output array of parents
 */
bool graph_bfs(graph* G, vertex_t start, vertex_t* parent);

#endif//__GRAPH_LIB_H__
