#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

int main(){
    Graph G;
    G = GRAPH_load("graph.txt");
    if(G==NULL) return -1;
    GRAPH_dfs(G);
    graph_to_DAG(G);
    GRAPH_dfs(G);
    GRAPH_longest_path(G);
    GRAPH_free(G);
    return 0;
}