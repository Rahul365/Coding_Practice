#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
// https://codeforces.com/problemset/problem/489/D
int main(){
    int n,m;
    scanf("%d%d",&n,&m);
    vector<vector<ll>> dp(n,vector<ll>(n,0));
    vector<pair<int,int>> edges;
    vector<int> g[n];
    for(int i = 0;i<m;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        g[u-1].push_back(v-1);
        edges.push_back({u-1,v-1});
    }
    sort(edges.begin(),edges.end());//Just make the solution a little bit faster
    for(int e = 0;e < m;++e){
        auto &ed = edges[e];
        for(int v : g[ed.second]){
            if(v != ed.first){
                dp[ed.first][v]++;
            }
        }
    }
    /*
    //Alternate Solution
        function<void(int,int,int)> dfs = [&](int u,int p1,int p2){
        if(p2!=-1){
            dp[p2][u]++;
            return;
        }
        
        for(int v : g[u]){
            if(v == u || v == p1 || v== p2) continue;
            dfs(v,u,p1);
        }
        };
        for(int i = 0;i<n;++i){dfs(i,-1,-1);}
    */
    ll answer = 0;
    for(int i = 0;i<n;++i){
        for(int j= 0;j<n;++j)
        {
            if(i != j && dp[i][j])
            {
                /*To Make a rhombus , we need at least two different paths from node u to v via some intermediate node x
                between u and v where x belongs to set of nodes X= {a,b,c,d,e,....,} where u,v not in X*/
                answer += (dp[i][j]*(dp[i][j]-1))/2;
            }
        }
    }
    printf("%lld\n",answer);
    return 0;
}