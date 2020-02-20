/**
 * Disjoint Set union Application : 
 * Kruskal Minimum Spanning Tree, Cycle Detection ,dividing a cyclic graph into different components 
*/
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5;
int SIZE[N];//number of nodes in the component of Node N as root
int parent[N];//tells the root of the component to which node N belongs to
/**
 * To initialize the parent and size of each node
*/
void init(){
    for(int i = 0;i<N;i++)
    {
        SIZE[i] = 1;
        parent[i] = i;
    }
}
/**
 * return the root node for component to which the given node belongs to
*/
int root(int x){
    while(x != parent[x]){
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}
/**
 * connect node u and v iff they do not belong to same component 
*/
bool wunion(int u,int v){
    int rx = root(u);
    int ry = root(v);

    if(rx == ry) return false;
    
    if(SIZE[rx] < SIZE[ry]) swap(rx,ry);
    
    parent[ry] = rx;
    
    SIZE[rx] += SIZE[ry];
    
    return true;
}

int main(){
    init();

    return 0;
}