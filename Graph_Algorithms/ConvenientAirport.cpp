#include<bits/stdc++.h>
#define removedups(v) sortvector(v); v.resize(unique(v.begin(),v.end()) - v.begin());
#define USE_FILE(i,o) freopen(i,"r",stdin); freopen(o,"w",stdout)
#define readint(x) scanf("%d",&x)
#define printint(x) printf("%d",x)
#define readint64(x) scanf("%lld",&x)
#define printint64(x) printf("%lld",x)
#define printpair(p) cerr<<p.first << " " p.second <<"\n" 
#define sortvector(v) sort(v.begin(),v.end())
#define trace_vector(v) for(auto x : v) cerr << x <<" ";cerr<<"\n";
using namespace std;
const int maxn = 2e5+11;
const int MAXN = 1e5+5;
const int LG = 20;
const int INF = 1e9;
using ll = long long int;
using ull = unsigned long long int;
const ll MOD2 = 998244353;
const ll MOD1 = 1e9 + 7LL;
ll *inv;
/*compute x^y*/
template<typename T>
T power(T a,T b,T mod = MOD1){
    T r = 1LL;
    while(b){
        if(b&1LL){
            r = (r * a)%mod;
        }
        a = (a * a)%mod;
        b >>= 1LL;
    }
    return r;
}
/*compute inversions*/
void inversions()
{
    inv = new ll[maxn];
    inv[0]= 0;
    for(int i = 1;i<maxn;++i){
        inv[i] = power((ll)i,MOD1-2LL);
    }
}

/*compute gcd(a,b)*/
template<typename T>
T gcd(T a,T b){
    while(b){
        T t = b % a;
        a = b;
        b = t;
    }
    return a;
}

class DSU{
    public:
    int parent[MAXN];
    vector<pair<int,int>> edges[MAXN];

    DSU(){
        for(int i = 0;i<MAXN;++i){
            parent[i] = i;
        }
    }

    int root(int u){
        while(u!=parent[u]){
            parent[u] = parent[parent[u]];
            u = parent[u];
        }
        return u;
    }


    bool wunion(int u,int v){
        int r_u = root(u);
        int r_v = root(v);
        if(r_u == r_v)
        {
            edges[r_u].push_back({u,v});
            return false;
        }
        if(edges[r_u].size() < edges[r_v].size()){
            swap(r_u,r_v);
        }
        parent[r_v] = r_u;
        for(auto e : edges[r_v]) edges[r_u].push_back(e);
        return true;
    }
};



multiset<int> g[MAXN];
void erase(pair<int,int> edge){
    g[edge.first].erase(g[edge.first].find(edge.second));
    g[edge.second].erase(g[edge.second].find(edge.first));
}

void solve(){
    int n,m;
    readint(n);
    readint(m);
    for(int i = 0;i<n;++i) g[i].clear();
    DSU dsu;
    int inconv = 0;
    for(int i = 0;i<m;++i){
        int u,v;
        readint(u);
        readint(v);
        --u,--v;
        dsu.wunion(u,v);
        g[u].insert(v);
        g[v].insert(u);
    }
    /*Separate non-Tree Roots and Tree roots(including Single node tree Components)*/
    vector<int> nonTreeRoots,treeRoots;
    for(int i = 0;i<n;++i){
        if(dsu.parent[i] == i){
            if(dsu.edges[i].empty()){
                /*This could be either a single Node Tree Component or Tree Component with more than 1 node*/
                treeRoots.push_back(i);
            }
            else{
                nonTreeRoots.push_back(i);
            }
        }
    }
    int N = nonTreeRoots.size();
    vector<pair<int,int>> extraEdges;
    if(N>1) //if there are more than one non tree components
    for(int i = 0;i<N;++i){ 
        //merge all non tree components in cyclic order
        auto e1 = dsu.edges[nonTreeRoots[i]].back();
        auto e2 = dsu.edges[nonTreeRoots[(i+1)%N]].back();
        erase(e1);
        //Remove back edge (f,s) and connect it to next component back edge(ff,ss)
        //as (s,ff) 
        //also remove edge(f,s)
        g[e1.second].insert(e2.first);
        g[e2.first].insert(e1.second);
        if(!i) extraEdges.push_back({e2.first,e1.second});//Only one extra edge will be left after integrating all non Tree Components
    }
    if(N>1)
    for(int i = 0;i<N;++i){
         dsu.edges[nonTreeRoots[i]].pop_back();//remove the back edge as it is already used
    }
    //Maintain the list of all extra edges
    for(int r : nonTreeRoots)
        for(auto e : dsu.edges[r])
            extraEdges.push_back(e);

    vector<int> singleRoots;//tree Components with 1 node
    while(!extraEdges.empty()){
        auto e = extraEdges.back();
        if(treeRoots.empty()) break;
        int r = treeRoots.back(); treeRoots.pop_back();
        if(g[r].empty()){
                singleRoots.push_back(r);
        }   
        else{
            int c = (*g[r].begin());
            /*erase that extra edge*/
            erase(e);
            /*erase one edge of the tree component*/
            erase({r,c});
            /*Merge Tree Component with Super Non Tree Component for 0 inconvenience*/
            g[e.first].insert(r);
            g[r].insert(e.first);
            g[e.second].insert(c);          
            g[c].insert(e.second);

            extraEdges.pop_back();
        }
    }
    /*TreeRoots will contain now single Node Tree Components + (TreeComponents with more than 1 node)*/
    for(int node : singleRoots) treeRoots.push_back(node);
    inconv = 0;/*For every Tree Component (nodes>=1) , inconvenience of 2 will be charged*/
    for(auto e : extraEdges){
        if(treeRoots.size() == 0){
            break;
        }
        if(treeRoots.size() == 1){
            erase(e);
            int node = treeRoots.back(); treeRoots.pop_back();
            g[e.first].insert(node);
            g[e.second].insert(node);
            g[node].insert(e.first);
            g[node].insert(e.second);
            inconv+=2;
            break;
        }
        erase(e);
        int u = treeRoots.back(); treeRoots.pop_back();
        int v = treeRoots.back(); treeRoots.pop_back();
        g[e.first].insert(u);
        g[u].insert(e.first);
        g[e.second].insert(v);
        g[v].insert(e.second);
        inconv+=2;
    }

    /*
        When there is no Non Tree Component left
    */

    int u = nonTreeRoots.empty()?treeRoots[0]:nonTreeRoots[0];
    for(int v : treeRoots){
        if(nonTreeRoots.empty() && treeRoots[0]==v) continue;
        inconv+=2;
        g[u].insert(v);
        g[v].insert(u);
    }

    vector<pair<int,int>> alledges;
    for(int i = 0 ;i < n;++i)
        for(int j : g[i]){
            if(i < j)
            alledges.push_back({i,j});
        }
    
    printf("%d %d\n",inconv,(int)alledges.size());
    for(auto e : alledges){
        printf("%d %d\n",e.first+1,e.second+1);
    }
}

int main(){
    int T;
    readint(T);
    while(T--){
        solve();
    }
    return 0;
}