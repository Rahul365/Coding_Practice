#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
const ll mod = 1e9 + 7;
const int maxn = 1e5+11;
const int LG = 19;
const int MAXN = 1e6+1;
int spf[MAXN];
ll inv[2*MAXN];
vector<int> *g;
int par[maxn][LG];
int lvl[maxn];
int a[maxn];
ll ans[maxn];
vector<int> st(maxn),en(maxn);
vector<int> order(2*maxn);//preorder traversal of the nodes of the tree (contains more than 2*n-1 nodes)
int tt;//global time counter
vector<pair<int,int>> *factors;

void dofactorise(int n){
    factors = new vector<pair<int,int>>[n+1];
    factors[0] = {{1,0}};
    for(int i=1;i<=n;++i){
        int x  = a[i];
        int cnt = 0;
        while(x>1){
            cnt = 0;
            int p = spf[x];
            while(x%p == 0)
            {
                ++cnt;
                x/=p;
            }
            factors[i].push_back({p,cnt});
        }
    }
}

template<typename T>
T powermod(T x,T y){
    T r = 1LL;
    while(y){
        if(y&1LL){
            r = (r * x)%mod;
        }
        x = (x*x)%mod;
        y >>= 1LL;
    }
    return r;
}


void seive(){
    spf[0] = 1;
    for(int i = 1;i<MAXN;++i) spf[i] = i;
    for(int i = 2;i*i<MAXN;++i){
        if(spf[i] == i){
            for(int j = i*i;j<MAXN;j+=i)
                spf[j] = i;
        }
    }
}


void computeinvs(){
    inv[0] = inv[1] = 1;
    for(int i = 2;i<=2000000;++i){
        inv[i] = i;
        inv[i] = powermod(inv[i],mod-2);
    }
}

template<typename T>
void mul(T &a,T b){
    a = (a%mod * b%mod)%mod;
}

vector<int> factorcount(MAXN,0);
vector<int> mark(maxn,0);

void add(ll &res,int id){
    int node= order[id];
            // cerr << x << " : (";
    int dup = !mark[node]?1:-1;
    for(auto &p : factors[node]){
        // cerr <<"("<<p<<","<<(factorcount[p])<<") | ";
        mul(res,inv[factorcount[p.first]+1]);//remove the powers of p from the result completely
        factorcount[p.first] += (p.second*dup);
        assert(factorcount[p.first]>=0);
        // cerr <<"("<<p<<","<<(factorcount[p])<<") | ";
        mul(res,1LL * (factorcount[p.first]+1));//now multiply the total powers of p to the result
    }
     mark[node] = !mark[node];
            // cerr <<")\n";
}

void addlca(ll &res,int lca){
    for(auto &p : factors[lca]){
        // cerr <<"("<<p<<","<<(factorcount[p])<<") | ";
        mul(res,inv[factorcount[p.first]+1]);//remove the powers of p from the result completely
        // cerr <<"("<<p<<","<<(factorcount[p])<<") | ";
        mul(res,1LL * (factorcount[p.first]+p.second + 1));//now multiply the total powers of p to the result
    }
}

void Mos(vector<pair<pair<int,int>,pair<int,int>>> &queries){
    int cl = 0;
    int cr = -1;
    ll res = 1LL;
    for(auto &q : queries){
        int l = q.first.first;
        int r = q.first.second;
        assert(l <= r);
        int lca = q.second.first;
        int qno = q.second.second;
        while(cr < r)//adding while moving to right
        {
             ++cr;
            add(res,cr);
        }
        while(cl > l){//adding while moving to left
            --cl;
            add(res,cl);
        }
        
        while(cr > r){//removing while moving to left
            add(res,cr);
            --cr;
        }
        
        while(cl < l)//removing while moving to right
        {
            //in this case just remove powers 
            //A node will either occur once in the subrange or twice , Not more than that
            add(res,cl);
            ++cl;
        }
        

        ll withlca = res;
        if(lca){
            int x = a[lca];
            addlca(withlca,lca);
        }
        ans[qno] = withlca;
        // cerr << qno << " : " <<ans[qno] <<"\n";
    }
}

int findlca(int u,int v)
{
    if(lvl[u] < lvl[v]) swap(u,v);
    int lg = 0;
    for(;(1<<lg)<=lvl[u];++lg);
    --lg;
    for(int i = lg;i>=0;--i){
        if(lvl[u] - (1<<i) >= lvl[v])
        {
            u = par[u][i];
        }
    }
    if(u == v) return u;
    for(int i = lg;i>=0;--i){
        if(par[u][i]!=-1 && par[u][i]!=par[v][i])
         u = par[u][i],v = par[v][i];
    }
    return par[u][0];
}

void dfs(int u,int p){
    par[u][0] = p;
    lvl[u] = 1 + lvl[p];
    st[u] = ++tt;//time when node is first visited
    order[tt] = u;
    for(int v : g[u]){
        if(v == p) continue;
        dfs(v,u);
    }
    en[u] = ++tt;//time when node is last visited
    order[tt] = u;
}

const int B = 1000;
bool compareRange(pair<pair<int,int>,pair<int,int>> &a,pair<pair<int,int>,pair<int,int>> &b){
     if (a.first.first / B != b.first.first / B)
        return a.first.first/B < b.first.first/B;
    if(!((a.first.first/B)&1)) return a.first.second > b.first.second;
    return a.first.second < b.first.second;
}


int main(){
    computeinvs();
    seive();
    int t;
    scanf("%d",&t);
    while(t--){
        int n;
        scanf("%d",&n);
        tt = -1;
        g = new vector<int>[n+1];
        for(int i = 0;i<MAXN;++i) factorcount[i] = 0;
        for(int i= 0;i<=n;++i)
        {
          mark[i] = 0;
          st[i] = en[i] = lvl[i] = 0;
          for(int j = 0 ;j<LG;++j){
              par[i][LG] = -1;
          }
        }
        for(int i = 0;i<n-1;++i){
            int u,v;
            scanf("%d%d",&u,&v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        lvl[1] = -1;
        dfs(1,1);
        for(int j = 1;j<LG;++j)
        for(int i=1;i<=n;++i){
            if(par[i][j-1]!=-1){
                par[i][j] = par[par[i][j-1]][j-1];
            }
        }
        // for(int i= 0;i<=tt;++i) cerr << order[i]<<" \n"[i==tt];
        // for(int i= 1;i<=n;++i){
        //     cerr<<i << " : " <<st[i] << " , " <<en[i] <<"\n";
        // }
        // for(int i=1;i<=10;++i) cerr<<inv[i] <<" \n"[i==10];
        for(int i = 1;i<=n;++i){
            scanf("%d",&a[i]);
        }
        dofactorise(n);

        int q;
        scanf("%d",&q);
        vector<pair<pair<int,int>,pair<int,int>>> queries;
        
        for(int i = 0;i<q;++i)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            int lca = findlca(u,v);
            if(st[u] > st[v]) swap(u,v);
            if(lca == u){
                queries.push_back({{st[u],st[v]},{0,i}});//(node1,node2,lca(node1,node2),queriesNumber);
            }
            else{
                queries.push_back({{en[u],st[v]},{lca,i}});//(node1,node2,lca(node1,node2),queriesNumber);
            }
            /***
             * let  P =  LCA(u,v)
             * case 1 : P == u or  P == v
             *  Then nodes in order from l = min(st[u],st[v]) and r = max(st[u],st[v]) are considered
             * i.e. all nodes in order(l,....,r) which appear precisely once in the range are in the path from node u to v (inclusive)
             * 
             * case 2: P != u && P!=v
             * if(!(en[u] < st[v])) swap(u,v)
             * //so that en[u] < st[v]
             *  Then our query range will from l = en[u] to r = st[v]
             *  Then our answer will be result from  = order(l,...,r) + order(st[P],....,st[P]);
             *  here in this case we have to consider the lca separately
             * 
             * */
        }
        sort(queries.begin(),queries.end(),compareRange);
        Mos(queries);        
        for(int i= 0;i<q;++i)
        {
            printf("%lld\n",ans[i]);
        }
    }   
    return 0;
}