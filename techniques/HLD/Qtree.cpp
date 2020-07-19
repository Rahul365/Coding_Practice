#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e4+11;
const int LG = 20;
const int INF = 1e9+7;
vector<int> g[maxn];

int par[maxn][LG];
int level[maxn];
int indexOf[maxn],cost[maxn];

int value[maxn];
int chainHead[maxn];
int pos[maxn],subtree[maxn];
int chainId[maxn];
int cid = 0 ,pid = 0;
vector<pair<int,int>> edges;

int max(int a,int b){ return a>b?a:b; }


template<typename T>
class segmaxmentTree{
    T *segmax;
    T *arr;
    int N;
    int n;
    public :

    segmaxmentTree(){}

    segmaxmentTree(T *a,int n){
        arr = a;
        this->n = n;
        segmax = new T[4*n + 1];
        buildTree(0,0,n-1);
    }

    inline void buildTree(int id,int l,int r){
        if(l==r){
            segmax[id] = arr[l];
            return;
        }
        int m = l+(r-l)/2;
        buildTree(id+id+1,l,m);
        buildTree(id+id+2,m+1,r);
        segmax[id] = max(segmax[id+id+1],segmax[id+id+2]);
    }


    void update(int pos,T val,int id,int l,int r){
        if(l > r) return;
        if(l == r && pos == l){
            segmax[id] = arr[pos] = val;
            return;
        }
        int m = l+(r-l)/2;
        if(pos <= m) update(pos,val,id+id+1,l,m);
        else update(pos,val,id+id+2,m+1,r);
        segmax[id] = max(segmax[2*id+1],segmax[2*id+2]);
    }


    void update(int pos,T val){
         update(pos,val,0,0,n-1);
    }

    T query(int L,int R,int l,int r,int id){
        if(l > r || L > R || R < l || r < L) return 0;
        if(L <= l && r<=R){
            return segmax[id];
        }
        int m = l + (r-l)/2;
        if(R <= m) return query(L,R,l,m,id+id+1);
        else if(m < L) return query(L,R,m+1,r,id+id+2);
        return max(query(L,R,l,m,id+id+1),query(L,R,m+1,r,id+id+2));
    }


    T query(int L,int R){
        return query(L,R,0,n-1,0);
    }

    void reset()
    {
        for(int i = 0;i<N;++i)
        {
            segmax[i] = 0;
            if(i < n) arr[i] = 0;
        }
    }
};

segmaxmentTree<int> *st;


int findlca(int u,int v){
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



void dfs(int u,int p){
    subtree[u] = 1;
    par[u][0] = p;
    level[u] = 1 + level[p];
    
    for(int v : g[u])
        if(v!=p){
            dfs(v,u); 
            subtree[u] += subtree[v];  
        }

}

void HLD(int u,int p,int &cid){
    if(chainHead[cid]==-1) chainHead[cid] = u;
    pos[u] = pid++;
    chainId[u] = cid;
    int heavy = -1;
    for(int v : g[u])
        if(v!=p && 2*subtree[v]>=subtree[u]){
            heavy = v;
            break;
        }


    if(heavy!=-1){
      HLD(heavy,u,cid);
    }

    for(int v : g[u])
        if(v!=p && v!=heavy){
            HLD(v,u,++cid);
        }    
}

int qmax(int u,int v){
    int lca = findlca(u,v);
    // cout << lca <<"\n";
    int res = 0;
    auto lcaChainNode = [&](int &u){
        while(chainId[lca]!=chainId[u]){
            res = max(res,st->query(pos[chainHead[chainId[u]]],pos[u]));
            u = par[chainHead[chainId[u]]][0];
        }
    };
    if(lca!=u) lcaChainNode(u);
    if(lca!=v) lcaChainNode(v);
    if(pos[lca]+1 <= pos[u]) res = max(res,st->query(pos[lca]+1,pos[u]));
    if(pos[lca]+1 <= pos[v]) res = max(res,st->query(pos[lca]+1,pos[v]));
    return res;
}


void init(int n){
    for(int i = 0;i<n;++i){
        level[i] = 0; 
        chainHead[i] = -1;
        chainId[i] = -1;
        pos[i] = -1;
        for(int j = 0;j < LG;j++)
            par[i][j] = -1;
    }
    dfs(0,0);
    for(int i =1;i<LG;++i)
        for(int u = 0;u < n; ++u)
            if(par[u][i-1]!=-1){
                par[u][i] = par[par[u][i-1]][i-1];
            }

  
    int cid = 0;//chainId
    
    pid = 0;//position of node in the tree

    HLD(0,0,cid);

    value[0] = 0;
    for(int i = 0;i<n-1;++i){
        auto &p = edges[i];
        if(level[p.first] < level[p.second])
        {
                swap(p.first,p.second);
        }
        value[pos[p.first]] = cost[i];
    }
    
    // for(int i= 0;i<n;++i) cout << value[i] <<" \n"[i==n-1]; 

    st = new segmaxmentTree<int>(value,n);
}


void change(int eno,int c){
    int u = edges[eno].first;
    st->update(pos[u],c);
    cost[eno] = c;
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int n;
        scanf("%d",&n);
        for(int i = 0;i<n-1;++i){
            int u,v,c;
            scanf("%d %d %d",&u,&v,&c);
            --u,--v;
            g[u].push_back(v);
            g[v].push_back(u);
            cost[i] = c;//cost of the (i)th edge
            edges.push_back({u,v});
        }
        
        init(n);
        char cmd[100];
        while(1){
            scanf("%s",cmd);
            if(cmd[0] == 'D') break;
            int a,b;
            scanf("%d %d",&a,&b);
            if(cmd[0] == 'C'){
                //a->edgeid
                //b->new cost value
                change(a-1,b);
            }
            else if(cmd[0] == 'Q'){
                --a,--b;
                //query (a,b)
                printf("%d\n",qmax(a,b));
            }
        }

        
        for(int i = 0;i<n;++i){
            g[i].clear();
        }
        edges.clear();
    }
    return 0;
}