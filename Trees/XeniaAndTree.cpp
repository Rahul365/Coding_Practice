#include<bits/stdc++.h>
#define removedups(v) sortvector(v); v.resize(unique(v.begin(),v.end()) - v.begin());
#define USE_FILE(i,o) freopen(i,"r",stdin); freopen(o,"w",stdout)
#define readint(x) scanf("%d",&x)
#define printint(x) printf("%d",x)
#define readint64(x) scanf("%lld",&x)
#define printint64(x) printf("%lld",x)
#define printpair(p) cerr<<p.first << " " p.second <<"\n" 
#define sortvector(v) sort(v.begin(),v.end())
using namespace std;
const int maxn = 2e5+11;
const int MAXN = 1e5+5;
const int LG = 20;
const int INF = 1e9;
using ll = long long int;
using ull = unsigned long long int;
const ll MOD2 = 998244353;
const ll MOD1 = 1e9 + 7LL;

vector<int> g[MAXN],cg[MAXN];
vector<int> cpar(MAXN);
vector<int> ans(MAXN);
int n,m;

struct CDMP{
    vector<bool> dead;//to mark whehter given node is in the centroid or not
    vector<int> par;//centroid parent to a node is par[node]
    /**To find the centriod in the child subtree rooted from given root*/
    int oneCentroid(int root){
        static vector<int> sub(MAXN);
        function<void(int,int)> dfs = [&](int u,int p){
            sub[u] = 1;
            for(int v : g[u]){
                if(v==p || dead[v]) continue;
                dfs(v,u);
                sub[u] += sub[v];
            }
        };
        dfs(root,-1);
        int N = sub[root];
        function<int(int,int)> findcenter = [&](int u,int p){
            for(int v : g[u]){
                if(v == p || dead[v]) continue;
                if(2 * sub[v] > N) return findcenter(v,u);
            }
            return u;
        };
        return findcenter(root,-1);
    }

    void traverse(int u,int p,int d=0){
        // cout << u <<"("<<d<<") , ";
        par[u] = p;
        for(int v : cg[u]){
            if(v != p) {
                traverse(v,u,d+1);
            }
        }
    }

    vector<int> &decomposeTree(){
        par = vector<int>(MAXN,-1);
        dead = vector<bool>(MAXN,false);
        function<int(int)> rec = [&](int u){
            int c = oneCentroid(u);
            dead[c] = true;
            for(int v : g[c])
                if(!dead[v])
                {
                    int cv = rec(v);
                    cg[c].push_back(cv);
                    cg[cv].push_back(c);
                }

            // dead[c] = false;
            return c;
        };
        int r = rec(1);
        traverse(r,-1); 
        //cout <<"\n";
        return par;
    }

}cdmp;


struct computeLCA{
    int level[MAXN];
    int par[MAXN][LG];

    int findlca(int u,int v){
        if(level[u]  < level[v]) swap(u,v);
        int lg = 0;
        for(;(1<<lg) <= level[u];++lg);
        --lg;
        for(int i= lg;i >= 0;--i)
            if(level[u]-(1<<i) >= level[v])
                u = par[u][i];

        if(u == v) return u;
        for(int i = lg;i>=0;--i)
            if(par[u][i]!=-1 && par[u][i]!=par[v][i])
                u = par[u][i],v=par[v][i];
        return par[u][0];
    }

    int dist(int u,int v){
        return level[u] + level[v] - 2*level[findlca(u,v)];
    }

    void dfs(int u,int p){
        level[u] = 1 + level[p];
        par[u][0] = p;
        for(int v : g[u])
            if(v!=p){
                dfs(v,u);
            }
    }

    void build(){
        level[1] = 0;
        for(int i = 0;i<=n;++i)
            for(int j = 0;j<LG;++j)
                par[i][j] = -1;
        dfs(1,1);
        for(int l = 1; l < LG;++l)
            for(int i = 1;i<=n;++i)         
                if(par[i][l-1]!=-1){
                    par[i][l] = par[par[i][l-1]][l-1];
                }
    }
}lca;


void update(int x){
    int node = x;
    while(node > 0){
        // int d = lca.dist(node,x);
        // if(d < 0){
        //  cerr << x << ":"<<node<<" , ";
        //  cerr << d <<" lesser "<<ans[node]<<" | ";
        // }
        ans[node] = min(ans[node],lca.dist(node,x));
        node = cpar[node];
    }
}

int query(int x){
    int node = x;
    int ret = INF;
    while(node > 0){
        // cerr << lca.dist(node,x) <<" + "<<ans[node]<<" | ";
        ret = min(ret,lca.dist(node,x) + ans[node]);
        node = cpar[node];
    }
    return ret;
}

int main(){
    USE_FILE("xinput.txt","xoutput.txt");
    readint(n);
    readint(m);
    for(int i= 0;i<n-1;++i){
        int u,v;
        readint(u); readint(v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i= 0;i<=n;++i) ans[i] = INF;
    cpar = cdmp.decomposeTree();
    //for(int i = 1;i<=n;++i) cerr<<cpar[i] <<" " ;
     //cerr<<"\n";
    lca.build();
    // cerr << lca.level[1] << " " <<lca.level[19375] <<" "<<lca.level[lca.findlca(1,19375)]<<"|";
    // cerr << lca.dist(1,19375) <<"\n";

    update(1);
    while(m--){
        int t,x;
        readint(t);
        readint(x);
        if(t == 1){
            update(x);
        }
        else{
            printint(query(x));
            printf("\n");
        }
    }
    return 0;
}