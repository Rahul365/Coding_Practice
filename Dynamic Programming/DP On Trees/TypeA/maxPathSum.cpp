#include<bits/stdc++.h>
using namespace std;
const int N = 1e7;
/**
 * Given a tree of n nodes and n-1 edges.
 * Each node has a value assigned to it.
 * -----------( Root node is 1. )------------------
 * Find the maximum path value from root to leaf.
 * 
*/

int dp[N];//dp[i] stores the maximum for the subtree rooted at ith node 
int val[N];
vector<int> g[N];

void dfs(int u,int par){
    dp[u] = val[u];
    int mx = 0;
    for(int v : g[u]){
        if(v == par){
            continue;
        }
        dfs(v,u);
        mx = max(mx,dp[v]);
    }
    dp[u] += mx;
}


int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int n;
    cin>>n;
    int a,b;
    for(int i = 1;i<n;i++){
        //input edges
        cin>>a>>b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    //read the data for each node
    for(int i = 1;i<=n;i++){
        cin>>val[i];
    }


    //root node is 1
    dfs(1,0);
    cout<<dp[1]<<"\n";

    
    return 0;
}