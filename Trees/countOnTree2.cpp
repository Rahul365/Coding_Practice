#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
const int maxn = 4e5 +11;
const int LG = 19;
vector<int> *g;
int lvl[maxn];
int compress[maxn];
int par[maxn][LG];//parent table
int *a;
int n,m;
vector<int> order;//tree traversal
vector<int> st(maxn),en(maxn);
int tt;//global timer

int findlca(int u,int v){
    if(lvl[u] < lvl[v]) swap(u,v);
    int lg = 0;
    for(lg = 0;(1<<lg)<=lvl[u];++lg); --lg;
    for(int i = lg;i>=0;--i){
        if(lvl[u]-(1<<i) >= lvl[v]){
            u = par[u][i];
        }
    }
    if(u == v) return u;
    for(int i = lg;i>=0;--i){
        if(par[u][i]!=-1 && par[u][i]!=par[v][i]){
            u = par[u][i],v = par[v][i];
        }
    }
    return par[u][0];
}

void dfs(int u,int p){
    st[u] = ++tt;
    order.push_back(u);
    par[u][0] = p;
    lvl[u]  = 1 + lvl[p];
    for(int v: g[u]){
        if(v==p) continue;
        dfs(v,u);
    }
    en[u] = ++tt;
    order.push_back(u);
}

const int BlockSize = 700;
bool comparefunc(pair<pair<int,int>,pair<int,int>> &a,pair<pair<int,int>,pair<int,int>> &b){
    if(a.first.first/BlockSize != b.first.first/BlockSize) return a.first.first/BlockSize < b.first.first/BlockSize;
    return a.first.second < b.first.second;
}

/*Coordinate Compression*/
void compressValues(){
    vector<int> c;
    for(int i=0;i<n;++i){
        c.push_back(a[i]);
    }
    sort(c.begin(),c.end());
    c.resize(unique(c.begin(),c.end()) - c.begin());
    //for finding the element position in c array
    auto findpos = [&](int key){
        int l = 0;
        int r = c.size()-1;
        while(l <= r){
            int  m = l+(r-l)/2;
            if(c[m] == key) return m;
            if(c[m] > key){
                r = m-1;
            }
            else 
            {
                l = m+1;
            }
        }
        return -1;
    };


    for(int i = 0;i<n;++i){
        a[i] = findpos(a[i]);
    }
}

int main(){
    scanf("%d%d",&n,&m);
    a = new int[n];
    g = new vector<int>[n];
    memset(lvl,0,sizeof lvl);
    memset(compress,0,sizeof compress);
    for(int i = 0;i<n;++i) 
    {
        scanf("%d",&a[i]);
    }
    for(int i = 0;i<n-1;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        --u,--v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for(int i= 0;i<n;++i)
        for(int j = 0;j<LG;++j)
         par[i][j] = -1;
    tt = -1;
    lvl[0] = -1;
    dfs(0,0);
    for(int i = 1;i<LG;++i){
        for(int j = 0;j<n;++j){
            if(par[j][i-1]!=-1){
                par[j][i] = par[par[j][i-1]][i-1];
            }
        }
    }
    vector<int> ans(m);
    vector<pair<pair<int,int>,pair<int,int>>> queries;
    for(int i = 0;i<m;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        --u,--v;
        if(st[u] > st[v]) swap(u,v);
        int lca = findlca(u,v);
        if(lca == u)
        queries.push_back({{st[u],st[v]},{-1,i}});
        else 
        queries.push_back({{en[u],st[v]},{lca,i}});
    }

    sort(queries.begin(),queries.end(),comparefunc);
    compressValues();
    //Mos algo
    int cl = 0;
    int cr = -1;
    int result = 0;
    vector<bool> mark(n,false);
    auto add = [&](int node){
            if(mark[node] && --compress[a[node]] == 0) {--result;}
            else if(!mark[node] && ++compress[a[node]] == 1){ ++result;}
            mark[node] = !mark[node];
    };
    
    for(auto &q : queries){
        int l = q.first.first;
        int r = q.first.second;
        int lca = q.second.first;
        int qno = q.second.second;
        while(cr < r){
            ++cr;
            int node = order[cr];
            add(node);
        }
        while(cl < l){
            int node = order[cl];
            add(node);
            ++cl;
        }
        while(cl > l){
            --cl;
            int node = order[cl];
            add(node);    
        }
        while(cr > r){
            int node = order[cr];
            add(node);
            --cr;
        }
        int withlca = result;
        if(lca!=-1){
            if(compress[a[lca]]==0)
                ++withlca;
        }
        ans[qno] = withlca;
    }
    for(int &v : ans)
        printf("%d\n",v);
    
    delete[] a;
    delete[] g;
    return 0;
}