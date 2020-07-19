#include<bits/stdc++.h>
#define removedups(v) sortvector(v); v.resize(unique(v.begin(),v.end()) - v.begin());
#define USE_FILE(infile,outfile) freopen(infile,"r",stdin); freopen(outfile,"w",stdout)
#define readint(x) scanf("%d",&x)
#define printint(x) printf("%d",x)
#define readint64(x) scanf("%lld",&x)
#define printint64(x) printf("%lld",x)
#define printpair(p) cerr<<p.first << " " p.second <<"\n" 
#define sortvector(v) sort(v.begin(),v.end())
#define e_vector(v) for(auto x : v) cerr << x <<" ";cerr<<"\n"
#define o_vector(v) for(auto x : v) cout << x <<" "; cout<<"\n"

using namespace std;
const int INF = 1e9+7;
const int maxn = 1e5+5;
const int LG = 20;

template<typename T>
class segmaxmentTree{
    T *segmax;
    T *segsum;
    T *arr;
    int N;
    int n;
    public :

    segmaxmentTree(){}
    segmaxmentTree(int n){
        N = 4*n+1;
        this->n = n;
        segmax = new T[4*n + 1];
        segsum = new T[4*n + 1];
        arr = new T[n];
        for(int i = 0;i<n;++i)
            arr[i] = 0; 
        for(int i = 0;i<N;++i)
            segmax[i] = -INF , segsum[i] = 0;
    }

    
    segmaxmentTree(T *a,int n){
        this->a = a;
        this->n = n;
        segmax = new T[4*n + 1];
        segsum = new T[4*n + 1];
        arr = a;
        buildTree(0,0,n-1);
    }

    inline void buildTree(int id,int l,int r){
        if(l==r){
            segmax[id] = arr[l];
            segsum[id] = arr[l];
            return;
        }
        int m = l+(r-l)/2;
        buildTree(id+id+1,l,m);
        buildTree(id+id+2,m+1,r);
        segmax[id] = max(segmax[id+id+1],segmax[id+id+2]);
        segsum[id] = segsum[id+id+1] + segsum[id+id+2];
    }


    void update(int pos,T val,int id,int l,int r){
        if(l > r) return;
        if(l == r && pos == l){
            segsum[id] = arr[pos] = val;
            segmax[id] = arr[pos] = val;
            return;
        }
        int m = l+(r-l)/2;
        if(pos <= m) update(pos,val,id+id+1,l,m);
        else update(pos,val,id+id+2,m+1,r);
        segmax[id] = max(segmax[2*id+1],segmax[2*id+2]);
        segsum[id] = segsum[id+id+1] + segsum[id+id+2];
    }


    void update(int pos,T val){
         update(pos,val,0,0,n-1);
    }

    T query(int L,int R,int l,int r,int id){
        if(l > r || L > R || R < l || r < L) return -INF;
        if(L <= l && r<=R){
            return segmax[id];
        }
        int m = l + (r-l)/2;
        if(R <= m) return query(L,R,l,m,id+id+1);
        else if(m < L) return query(L,R,m+1,r,id+id+2);
        return max(query(L,R,l,m,id+id+1),query(L,R,m+1,r,id+id+2));
    }

    T querysum(int L,int R,int l,int r,int id){
        if(l > r || L > R || R < l || r < L) return 0;
        if(L <= l && r<=R){
            return segsum[id];
        }
        int m = l + (r-l)/2;
        if(R <= m) return querysum(L,R,l,m,id+id+1);
        else if(m < L) return querysum(L,R,m+1,r,id+id+2);
        return querysum(L,R,l,m,id+id+1) + querysum(L,R,m+1,r,id+id+2);
    }

    T querysum(int L,int R){
        return querysum(L,R,0,n-1,0);
    }

    T query(int L,int R){
        return query(L,R,0,n-1,0);
    }
};

vector<int> g[maxn];
segmaxmentTree<int> st(maxn);//segment tree to handle range sum and range max query
int par[maxn][LG];//par[node][i]->ancestor of the node at distance 2^i from it
int level[maxn];//level of the node 
int sub[maxn];//subtree sizes
int chainId[maxn];//chain id of node
int nodePos[maxn];//store the position of node in the segmaxment tree
int chainHead[maxn];//Head/start node of the chain for some chain id given
int value[maxn];//value of the node given 

/*Just for validating the correctness of HLD algorithm*/
int chainSize[maxn];//length of chain for a chainid;
int parentChain[maxn];//to store the parent chain of the current chain id (for validation purpose)


int findlca(int u,int v){
    if(level[u]  < level[v]) swap(u,v);
    int lg =0 ;
    while((1<<lg) <= level[u]) ++lg;
    --lg;
    for(int i = lg;i>=0;--i){
        if(level[u] - (1<<i) >= level[v]){
            u = par[u][i];
        }
    }
    if(u == v) return u;
    
    for(int i = lg;i>=0;--i){
        if(par[u][i]!=-1 && par[u][i]!=par[v][i]){
            u = par[u][i];
            v = par[v][i];
        }
    }
    return par[u][0];
}

void dfs(int u,int p){
    par[u][0] = p;
    sub[u] = 1;
    level[u] = 1+level[p];
    for(int l = 1;l < LG;++l){
        if(par[u][l-1]!=-1){
            par[u][l] = par[par[u][l-1]][l-1];
        }
    }

    for(int v: g[u])
        if(v!=p){
            dfs(v,u);
            sub[u] += sub[v];
        }
}

int pos = 0;//position of node in the segmaxment tree
void HLD(int u,int p,int &chainid){
    if(chainHead[chainid] == -1) chainHead[chainid] = u; // record the head of this chain
    chainId[u] = chainid;//record the chain id in which node belongs
    nodePos[u] = pos++;//record the position of the node
    st.update(nodePos[u],value[u]);//update the value of node in segmaxment tree
    int heavy = -1; 
    for(int v : g[u])
        if(v!=p){
            if(2*sub[v] >= sub[u]){
                heavy = v;
                break;
            }               
        }
    if(heavy!=-1){
        HLD(heavy,u,chainid);/*recurse down the heavy child and add it to the current chain*/
    } 

    for(int v : g[u])
        if(v!=p && v != heavy){
            HLD(v,u,++chainid);/*recurse down to the next chains*/
            parentChain[chainId[v]] = chainId[u];//linking the next chain to its parent chain
        }
}



int queryHLD(int u,int v){
    int r = findlca(u,v);
    int res = -INF;
    /*O(log n)*/
    auto lcaChainNode = [&](int &u){
        while(chainId[u]!=chainId[r]){
            res = max(res,st.query(nodePos[chainHead[chainId[u]]],nodePos[u]));
            u = par[chainHead[chainId[u]]][0];
        }
    };
    lcaChainNode(u);
    lcaChainNode(v);
    return max(res,st.query(nodePos[r],max(nodePos[u],nodePos[v])));
}

int querySUM(int u,int v){
    // cout <<" in "<<u << "  " << v <<"\n";
    int sum = 0;
    int r = findlca(u,v);
    // cout <<"lca : "<< r << " of "<< u <<" and "<<v<<"\n";
    auto lcaChainNode = [&](int &u){
        while(chainId[u]!=chainId[r]){
            sum += st.querysum(nodePos[chainHead[chainId[u]]],nodePos[u]);
            u = par[chainHead[chainId[u]]][0];
        }
    };

    if(r!=u)
    lcaChainNode(u);
    if(r!=v)
    lcaChainNode(v);

    sum += st.querysum(nodePos[r],max(nodePos[u],nodePos[v]));

    return sum;
}

void init(int n){
    memset(chainHead,-1,sizeof chainHead);
    memset(chainSize,0,sizeof chainSize);
    for(int i = 0;i<=n;++i){
        level[i] = 0;
        sub[i] = 0;
        for(int j = 0;j<LG;++j)
            par[i][j] = -1;
    }
    dfs(0,0);//to build LCA table and compute subtree sizes of the trees rooted down at each node
    int chainid = 0;
    pos = 0;
    HLD(0,0,chainid);//to setup the segmaxment tree and other auxiliary data needed to HLD
    for(int i = 0;i<=n;++i){
        ++chainSize[chainId[i]];
    }
}
/* To Validate HLD Decomposition*/
void validateHLD(int n){
    map<int,vector<int>> ch;
    for(int i = 0;i<n;++i){
        ch[chainId[i]].push_back(i);
    }   
    cout <<"parentOfchain | chainhead  |  chainid nodes\n";
    for(auto it : ch){
        printf("%d ," ,parentChain[it.first]);
        printf("%d ,",chainHead[it.first]);
        printf("%d : ",it.first);
        o_vector(it.second);
    }

    printf("positions \n");
    for(int i = 0;i<n;++i){
        printf("%d %d\n",i,nodePos[i]);
    }
}

int main(){
    USE_FILE("input.txt","output.txt");
    int n;
    scanf("%d",&n);
    for(int i= 0;i<n-1;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i = 0;i<n;++i){
        scanf("%d",&value[i]);
    }

    init(n);

    validateHLD(n);
     
    int q;
    scanf("%d",&q);
    /*O(q * log(n) * log(n))*/
    while(q--){
        int opt,u,v;
        scanf("%d%d%d",&opt,&u,&v);
        if(opt){
            st.update(nodePos[u],v);
        }
        else
            printf("%d %d\n",queryHLD(u,v),querySUM(u,v));
    }
    
    return 0;
}