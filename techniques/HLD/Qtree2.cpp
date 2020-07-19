#include<bits/stdc++.h>
using namespace std;
const int LG = 20;
const int maxn = 1e4 + 111;
vector<pair<int,int>> g[maxn];
int par[maxn][LG];
int level[maxn];
int dist[maxn];

int subtree[maxn];
int pos[maxn],chainId[maxn];
int chainHead[maxn];


void dfs(int u,int p){
    subtree[u] = 1;
    par[u][0] = p;
    level[u] = 1 + level[p];
    dist[u] += dist[p];
    for(pair<int,int> &y : g[u]){
        int c = y.second;
        int v = y.first;
        if(v!=p){
            dist[v] = c;
            dfs(v,u);
            subtree[u] += subtree[v];
        }
    }
}

void HLD(int u,int p,int &cid,int &pid){
    if(chainHead[cid] == -1)  chainHead[cid] = u;
    chainId[u] = cid;
    pos[u] = pid++;

    int heavy = -1;
    for(auto  v : g[u])
        if(v.first!=p && 2*subtree[v.first]>=subtree[u])
        {
            heavy = v.first;
            break;
        }
    
    if(heavy!=-1) HLD(heavy,u,cid,pid);

    for(auto v : g[u])
        if(v.first!=p && v.first!=heavy){
            HLD(v.first,u,++cid,pid);
        }
}



int findlca(int u,int v)
{
    if(level[u] < level[v]) swap(u,v);
    int lg = 0;
    while((1<<lg) <= level[u]) ++lg;
    --lg;
    for(int i = lg;i>=0;--i)
        if(level[u]-(1<<i) >= level[v])
            u = par[u][i];

    if(u == v) return u;
    for(int i = lg;i>=0;--i)
        if(par[u][i]!=-1 && par[u][i]!=par[v][i]){
            u = par[u][i];
            v = par[v][i];
        }


    return par[u][0];
}

int getdist(int u,int v){
    return dist[u] + dist[v] - 2 * dist[findlca(u,v)];
}

int getancestor(int u,int d){
    d = level[u] - d;
    int lg = 0;
    while((1<<lg) <= level[u]) ++lg;
    --lg;

    for(int i = lg;i>=0;--i)
    if(level[u]-(1<<i)>=d) u = par[u][i];

    return u;
}

int getkthnode(int u,int v,int k){
    int lca = findlca(u,v);
    int d  = 1 + level[u] -  level[lca];//distance of the node u to lca
    // cerr << d <<"\n";
    if(k <= d){
        //find the kth ancestor of u
        return 1 + getancestor(u,k-1);
    }
    k -= d;
    d = level[v] - level[lca];
    d-=k;//find and return the dth ancestor of node v
    return  1 + getancestor(v,d);
}

void init(int n){
    for(int i = 0;i<=n;++i)
    {
        /*
            chainHead[i] = chainId[i] = pos[i] = -1;
        */
        level[i] = 0;
        dist[i] = 0;

        for(int j = 0;j < LG;++j){
            par[i][j] = -1;
        }
    }
    dfs(0,0);
    for(int j = 1;j < LG;++j)
        for(int i = 0;i < n ;++i)
            if(par[i][j-1]!=-1){
                par[i][j] = par[par[i][j-1]][j-1];
            }
    /*
    //Not prefered way to solve it for "DIST a b" Query 
        int cid = 0;//chain id
        int pid = 0;//process id
        HLD(0,0,cid,pid);//building the HEavy light decomposition chains setting up the distance values
        bt =  new BIT(dist,n+1);//build the segment tree or binary indexed tree on distance values of edges assigned to their childs
    */
}

/*
//get the sum of edges weights from node u to v using HLD function
int getsum(int u,int v){
    int lca =findlca(u,v);
    int sum = 0;
    function<void(int)> lcaChainNode = [&](int &u){
        while(chainId[u]!=chainId[lca]){
            sum += bt->rangeSum(pos[chainHead[chainId[u]]],pos[u]);
            u = par[chainHead[chainId[u]]][0];
        }
    };
    lcaChainNode(u);
    lcaChainNode(v);
    return sum + bt->rangeSum(pos[lca]+1,max(pos[u],pos[v]);
}

*/
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int n;
        scanf("%d",&n);
        for(int i = 0;i<n-1;++i){
            int u,v,c;
            scanf("%d%d%d",&u,&v,&c);
            --u,--v;
            g[u].push_back({v,c});
            g[v].push_back({u,c});
        }
        init(n);
        char *cmd = new char[100];
    
        while(1){
            scanf("%s",cmd);
            if(cmd[0]=='D' && cmd[1]=='O') break;
            int u,v;
            scanf("%d%d",&u,&v);
            --u,--v;
            if(cmd[0]=='D'){
                printf("%d\n",getdist(u,v));
            }   
            else if(cmd[0]=='K'){
                int k;
                scanf("%d",&k);
                printf("%d\n",getkthnode(u,v,k));
            }    
        }


        for(int i = 0;i<n;++i){
            g[i].clear();
        }
    }
    return 0;
}


//5 2 1 3 6