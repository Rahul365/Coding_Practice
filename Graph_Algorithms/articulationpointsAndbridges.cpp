#include<bits/stdc++.h>
using namespace std;
const int N = 1e5,NIL = -1;
int low[N],disc[N];//disc[N] -> stores the discovery time of vertex N
//low[N] -> stores the lowest discovery time in the sub-path explored from node N
int ttime = 0;//global variable to keep track of discovered vertices

vector<int> g[N];
vector<int> parent(N);//parent[root] = -1
vector<bool> vis(N,false);
vector<bool> AP(N,false);//to store the articulation points in graph
/*Articulation point : 
    A node in a graph which if deleted it and all the edges associated with it  results in
    increase in the number of connected components in given graph
*/
vector<pair<int,int>> bridges;//to store the bridges in the graph
/*
Bridges : 
    Those edges in the graph which if deleted results in increase in the number of connected components in graph
*/
void dfs(int u){
    disc[u] = low[u] = ++ttime;
    vis[u] = true;
    int child = 0;
    for(int v : g[u]){
        if(!vis[v]){
            par[v] = u;//assign parent of node v here to avoid processing parent of node u
            dfs(v);
            ++child;
            low[u] = min(low[u],low[v]);
            /*Condition to identify articulation points*/
            if((parent[u] == NIL && child > 1) || (parent[u]!=NIL && low[v] >= disc[u])){
                AP[u] = true;
            }
            /*
                Condition to identify bridges
                lowest discovery time of vertex v in the subgraph of u should be exactly greater than discovery time of u
            */
            if(low[v] > disc[u]){
                bridges.push_back({u,v});
            }
        }
        else if(parent[u] != v){
            low[u] = min(disc[v],low[u]);
        }
    }
}



int main(){
    return 0;
}
