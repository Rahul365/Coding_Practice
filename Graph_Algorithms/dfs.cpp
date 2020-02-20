#include<bits/stdc++.h>
using namespace std;
const  int N = 1e5;
bool vis[N];//for graphs
vector<int> g[N];//adjaceny list representation for graphss
/*Recursive Depth first search*/
void dfs(int u,int par){
    vis[u] = true;
    cout<<u<<" ";
    for(int v : g[u]){
        if(v == par || vis[v]) continue;
        dfs(v,u);
    }
}

/*Iterative Depth first search*/
void dfs(int u){
    stack<int> stk;
    stk.push(u);
    memset(vis,false,sizeof(vis));
    while(!stk.empty()){
        int u = stk.top();
        stk.pop();
        cout<<u<<" ";
        for(int v : g[u]){
            if(vis[v]) continue;
            vis[v] = true;
            stk.push(v);
        }
    }
    cout<<"\n";
}


int main(){
    return 0;
}