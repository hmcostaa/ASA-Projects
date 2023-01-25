#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>


using namespace std;

struct Graph{

    int V, E;

    vector<pair<int, pair<int, int>>>graph;

    Graph(int vertices, int edges){
        V = vertices;
        E = edges;
    }

    void addToGraph(int w, int v, int e){
        graph.push_back({w, {v, e}});
    }

    int computeKruskal();
};

void makeSet(int *p, int *r, int v){
    p[v] = v;
    r[v] = 0;
}

int findSet(int *p, int *r, int v){
    if(v != p[v]){
        p[v] = findSet(p, r, p[v]);
    }
    return p[v];
}

void link(int *p, int *r, int v, int v2){
    if(r[v] > r[v2]){
        p[v2] = v;
    }
    else{
        p[v] = v2;
        if(r[v] == r[v2]){
            r[v2] += 1;
        }
    }
}

void Union(int *p, int *r, int v, int v2){
    link(p, r,findSet(p, r, v), findSet(p, r, v2));
}

int Graph::computeKruskal() {

    int *parents = new int[V + 1];
    int *ranks = new int[V + 1];
    int max = 0;

    for(int i = 0; i <= V; i++){
        makeSet(parents, ranks, i);
    }

    sort(graph.begin(), graph.end(), greater<pair<int, pair<int, int>>>());

    vector<pair<int, pair<int, int>>>::iterator it;
    for(it = graph.begin(); it != graph.end(); it++){

        int u = it->second.first;
        int v = it->second.second;

        int rootU = findSet(parents, ranks, u);
        int rootV = findSet(parents, ranks, v);

        if(rootU != rootV){
            max += it->first;
            Union(parents, ranks, rootU, rootV);
        }
    }
    return max;
}


int main(){

	int V, E, n;

    n = scanf("%d", &V);
    if(n == 0){
        return 0;
    }
    n = scanf("%d", &E);
    if(n == 0){
        return 0;
    }

    Graph graph(V, E);

	for(int i = 0; i < E; i++){
        int w, v, e;
        n = scanf("%d %d %d", &v, &e, &w);
        if(n == 0){
            return 0;
        }
        graph.addToGraph(w, v, e);
	}

    int max = graph.computeKruskal();

    printf("%d\n", max);

    return 0;
}