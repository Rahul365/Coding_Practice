#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+11,INF = -2e5;//lower bound is must(why?)

vector<int> g[N];
int in[N];//in[i] height of the subtree rooted at node i
int out[N];//out[i] height of the subtree rooted-out at node i
int mark[N];//to mark the affected nodes

void dfsI(int u,int p){
    if(mark[u])
        in[u] = 0;
    else
        in[u] = INF;
    for(int v : g[u]){
        if(v == p) continue;
        dfsI(v,u);
        in[u] = max(1 + in[v],in[u]);
    }
}

void dfsII(int u,int p){
    int mx1(INF),mx2(INF);
    for(int v : g[u]){
        if(v == p) continue;
        if(in[v] >= mx1){
            mx2 = mx1;
            mx1 = in[v];
        }
        else if(in[v] > mx2){
            mx2 = in[v];
        }
    }
    
    for(int v : g[u]){
        if(v == p) continue;
        int use = mx1;
        if(use == in[v])
            use = mx2;
        out[v] = max(1 + out[u],2 + use);
        if(mark[v] && out[v] < 0) out[v] = 0;
        dfsII(v,u);
    }
}

int main(){
        int n,m,d;
        cin>>n>>m>>d;
        int affected;
        for(int i = 0;i<m;i++){
            cin>>affected;
            mark[affected] = 1;
        }
       
        int x,y;
        for(int i = 1;i<=n-1;i++)
        {
            cin>>x>>y;
            g[x].push_back(y);
            g[y].push_back(x);
        }
    
        dfsI(1,0);
        if(mark[1]) out[1] = 0;
        else out[1] = INF;
        dfsII(1,0);
        int ans = 0;
        
        for(int i = 1;i<=n;i++){
              ans += (in[i]<=d && out[i]<=d);
        }
       cout<<ans<<"\n";
        return 0;
}