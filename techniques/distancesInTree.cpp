#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+11;
const int inf = 1e9+7;
const int LG = 20;
vector<int> g[maxn];
int firstpos[maxn];
int LOG[maxn];
vector<int> euler;
int par[maxn][LG];
pair<int,int> spar[maxn][LG];
int level[maxn];
int n,k;

int lca(int u,int v){
    if(level[u]  < level[v]) swap(u,v);
    int lg = 0;
    while((1<<lg) <= level[u]){
        ++lg;
    }
    --lg;
    for(int i = lg;i>=0;--i){
        if(level[u] - (1<<i) >= level[v]){
            u = par[u][i];
        }
    }
    if(u == v) return u;
    for(int i= lg;i>=0;--i){
        if(par[u][i]!=-1 && par[v][i]!=-1 && par[u][i]!=par[v][i])
            u = par[u][i],v = par[v][i];
    }
    return par[u][0];   
}


void dfs(int u,int p){
    level[u] = 1 + level[p];
    par[u][0] = p;
    firstpos[u] = euler.size();
    euler.push_back(u);
    for(int v : g[u]){
        if(v == p) continue;
        dfs(v,u);
        euler.push_back(u);
    }
}

void buildLCA(){
    euler.clear();
    for(int i= 0;i<maxn;++i){
        level[i] = 0;
        firstpos[i] = -1;
        for(int j = 0;j<LG;++j){
            par[i][j] = -1;
            spar[i][j] = {inf,inf};
        }
    }
    dfs(0,0);
    for(int L = 1;L<LG;++L)
        for(int i = 0;i<n;++i)
            if(par[i][L-1]!=-1)
                par[i][L] = par[par[i][L-1]][L-1];

    // for(int l = 0;l<LG;++l)
    // for(int i = 0;i<n;++i)
    //     cerr << par[i][l] << " \n"[i==n-1];
    // for(int i= 0;i<n;++i)
    //     cerr << firstpos[i] << " \n"[i==n-1];
    // for(int v : euler) cerr << v << " "; cerr <<"\n";
    const int m = euler.size();
    for(int i = 0;i<m;++i){
        spar[i][0] = {level[euler[i]],euler[i]};
    }
    for(int L = 1;L < LG;++L)
        for(int i= 0;i+(1<<L) <= m;++i)
            if(spar[i][L-1].first!=inf)
            spar[i][L] = (spar[i][L-1].first < spar[i+(1<<(L-1))][L-1].first ?spar[i][L-1]:spar[i+(1<<(L-1))][L-1]);


    LOG[0] = LOG[1] = 0;
    for(int i = 2;i<maxn;++i)
     LOG[i] = 1 + LOG[i>>1];
}

int lca2(int u,int v)
{
    u = firstpos[u];
    v = firstpos[v];
    if(u > v) swap(u,v);
    int L = LOG[v - u + 1];
    auto &p1 = spar[u][L];
    auto &p2 = spar[v-(1<<L)+1][L];
    if(p1.first < p2.first) return p1.second;
    return p2.second;
}

int getdist(int u,int v){
    // cerr << u <<"," << v << " : " << lca(u,v) << " : " << lca2(u,v) <<" ||  "<<level[u]<<" " <<level[v] <<"\n";
    return level[u] + level[v] -2*level[lca2(u,v)];
}




int main(){
    scanf("%d%d",&n,&k);
    for(int i = 0;i<n-1;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        --u;
        --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    buildLCA();
    int ans = 0;
    /*O(n*n*logn) - TLE indeed*/
    /*O(n*n)*/
    for(int i= 0;i<n;++i)
        for(int j = i+1;j<n;++j)
         ans += getdist(i,j) == k;

    printf("%d\n",ans);
    return 0;
}