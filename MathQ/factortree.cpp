#include<bits/stdc++.h>
using namespace std;
using ll  = long long int;
const int N = 1e6+11;
const int maxn = 1e5+11;
const int LG = 19;
const int mod = 1e9+7;
vector<int> g[maxn];
int par[maxn][LG];
unordered_map<int,int> *pf[maxn];
unordered_map<int,int> pftree[maxn];
unordered_map<int,unordered_map<int,int>> prefact;
int level[maxn];
int n,q;

template<typename T>
unordered_map<T,T> primefactors(T n){
    unordered_map<T,T> res;
    if(n == 2){
        res[2] = 1;
    }
    if(n == 1){
        res[1] = 0;
    }
  
    for(T i = 2;i*i<=n;++i){
        if(n%i == 0){
            int occ = 0;
            while(n%i == 0){
                ++occ;
                n/=i;
            }
            res[i]=occ;
        }
    }
    if(n > 2){
        res[n] = 1;
    }
    return res;
}

int findlca(int u,int v){
    if(level[u] < level[v]) swap(u,v);
    int lg = 0;
    while((1<<lg) <= level[u])
        ++lg;
    --lg;

    for(int i = lg;i>=0;--i){
        if(level[u]-(1<<i) >= level[v]){
            u = par[u][i];
        }
    }
    if(v == u) return u;
    for(int i = lg;i>=0;--i)
    {
        if(par[u][i]!=-1 && par[u][i]!=par[v][i])
        {
             u = par[u][i],v = par[v][i];
        }
    }
    return par[u][0];
}

vector<int> in(maxn),out(maxn);

void dfsi(int u,int p){
    for(int v : g[u]){
        if(v == p) continue;
        dfsi(v,u);
        in[u] = max(in[u],1 + in[v]);
    }
}

void dfsii(int u,int p){
    int mx1(-1),mx2(-1);
    for(int v : g[u]){
        if(v == p) continue;
        if(mx1  < in[v]){
            mx2 = mx1;
            mx1 = in[v];
        }
        else if(mx2 < in[v]){
            mx2 = in[v];
        }
    }
    for(int v : g[u]){
        if(v == p) continue;
        int use = mx1;
        if(use == in[v]) use = mx2;
        out[v] = max(1 + out[u],2 + use);
        dfsii(v,u);
    }
}

int getroot(){
    fill(in.begin(),in.end(),0);
    fill(out.begin(),out.end(),0);
    dfsi(1,1);
    dfsii(1,1);
    int root = 0;
    int diff = INT_MAX;
    for(int i = 1;i<=n;++i){
        if(diff > abs(in[i]-out[i])){
            root = i;
            diff = abs(in[i]-out[i]);
        }
    }
    return root;
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i = 0;i<=n;++i) { g[i].clear(); pf[i] = NULL; pftree[i].clear(); level[i] = 0;}
        for(int i = 0;i<=n;++i){
            for(int j = 0;j < LG;++j){
                par[i][j] = -1;
            }
        }

        for(int i= 0;i<n-1;++i){
            int u,v;
            scanf("%d%d",&u,&v);
            g[u].push_back(v);
            g[v].push_back(u);
        }
        int root = 1;
        fill(in.begin(),in.end(),0);
        fill(out.begin(),out.end(),0);
        dfsi(1,1);
        dfsii(1,1);
        int diff = INT_MAX;
        for(int i = 2;i<=n;++i){
            if(diff > abs(in[i]-out[i])){
                root = i;
                diff = abs(in[i]-out[i]);
            }
        }
        for(int i = 0;i<n;++i){
            int x;
            scanf("%d",&x);
            if(prefact.count(x)==1){
                pf[i+1] = &prefact[x];
            }
            else{
                prefact[x] =  primefactors(x);//store the factorization of numbers 
                pf[i+1] = &prefact[x];
            }   
        }
      //  cerr << root <<"\n";
        queue<pair<int,int>> qq;
        qq.push({root,root});
        while(!qq.empty()){
            int u = qq.front().first;
            int p = qq.front().second;
            qq.pop();
            pftree[u] = *pf[u];
            if(u!=p)
            for(auto &pp : pftree[p])
                pftree[u][pp.first]+=pp.second;
            level[u] = level[p] + 1;
            par[u][0] = p;
            for(int v : g[u]){
                if(v == p) continue;
                qq.push({v,u});
            }
        }
        
        for(int i = 1;i<LG;++i){
            for(int j = 1;j<=n;++j){
                if(par[j][i-1]!=-1){
                    par[j][i] = par[par[j][i-1]][i-1];
                }
            }
        }
        scanf("%d",&q);
        unordered_map<int,int> res;
        while(q--){
            int u,v;
            scanf("%d%d",&u,&v);
            if(u > v) swap(u,v);
            int lca = findlca(u,v);
            // cout << "lca : "<<lca<<"\n";
            ll ans = 1;
            res = pftree[u];
            for(auto &p : pftree[v]){
                res[p.first]+=p.second;
            }
            for(auto &p : pftree[lca]){
                res[p.first] = abs(res[p.first]-2*p.second);
                if((*pf[lca]).count(p.first)==1){
                    res[p.first]+= (*pf[lca])[p.first];
                }
                else if(!res[p.first]){
                    res.erase(p.first);
                }
            }
            for(auto &p : res){
                 ans = (1LL * (p.second+1) * ans);
                 if(ans >= mod)
                  ans %= mod;
            }
            printf("%lld\n",ans);
        }
    }
    return 0;
}

