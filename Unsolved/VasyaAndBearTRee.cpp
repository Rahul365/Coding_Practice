//UNSOLVED
#include<bits/stdc++.h>
using ll = long long int;
#define queries pair<pair<int,int>,pair<int,int>>
using namespace std;
const int maxn = 1e5+1;
const int mod = 1e9 + 7;
const int LG = 19;
vector<int> g[maxn];
vector<int> order;
vector<int> st(maxn),en(maxn);
vector<vector<int>> par(maxn,vector<int>(LG,-1));
int tt = -1;
vector<int> lvl(maxn);
int n;
vector<int> c(maxn);
vector<ll> h(maxn);

int findlca(int u,int v){
    if(lvl[u] < lvl[v]) swap(u,v);
    int lg;
    for(lg = 0; (1<<lg) <= lvl[u];++lg);
    --lg;
    for(int i = lg;i>=0;--i){
        if(lvl[u] - (1<<i) >= lvl[v]){
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
    par[u][0] = p;
    lvl[u] = 1 + lvl[p];
    st[u] = ++tt;
    order.push_back(u);
    for(int v : g[u]){
        if(v == p) continue;
        dfs(v,u);
    }
    en[u] = ++tt;
    order.push_back(u);
}


ll amount(int u,int v){
    return (h[u]-h[v]) * (h[u] - h[v]);
}

void addself(ll &a,ll b){
    a = (a + b);
}

const int block_size = 800;
bool comparequery(queries a,queries b){
    if(a.first.first/block_size != b.first.first/block_size) return a.first.first/block_size < b.first.first /block_size;
    return a.first.second < b.first.second;
}

class MO{
    deque<int> *pos;
    vector<bool> mrk;
    public:
    MO(){
        pos = new deque<int>[10];//queue of clrs
        mrk = vector<bool>(n,false);
    }

    
    void addfront(int node,ll &running_result){
                int clr = c[node];
                if(mrk[node]){
                    int x = pos[clr].front(); pos[clr].pop_front();
                    if(pos[clr].size()){
                        addself(running_result ,-amount(x,pos[clr].front()));
                    }
                }
                else{
                    if(pos[clr].size()){
                        addself(running_result , amount(node,pos[clr].front()));
                    }
                    pos[clr].push_front(node);
                }
                mrk[node] = !mrk[node];
    }

    void addback(int node,ll &running_result){
                int clr = c[node];
                if(mrk[node]){
                    int x = pos[clr].back(); pos[clr].pop_back();
                    if(pos[clr].size()){
                        addself(running_result,-amount(x,pos[clr].back()));
                    }
                }
                else
                {
                    if(pos[clr].size()){
                        addself(running_result, amount(node,pos[clr].back()));
                    }
                    pos[clr].push_back(node);
                }
                mrk[node] = !mrk[node];
    }

    vector<ll> compute(vector<queries> &q){
        sort(q.begin(),q.end(),comparequery);
        vector<ll> ans(q.size());
        int cl = 0;
        int cr = -1;
        int node;
        ll running_result = 0;
        for(auto &qq : q){
            int l = qq.first.first;
            int r = qq.first.second;
            int qnum = qq.second.second;
            ll &curr = ans[qnum];
            while(cr < r){
                //+
                ++cr;
                /*add to back*/
                node = order[cr];
                addback(node,running_result);
            }
            while(cr > r){
                /*Remove back*/
                node = order[cr];
                addback(node,running_result);
                --cr;
            }
            while(cl < l){
                //-
                /*Remove front*/
                node = order[cl];
                addfront(node,running_result);
                ++cl;
            }
            while(cl > l){
                --cl;
                node = order[cl];
                addfront(node,running_result);
                /*add back*/
            }
            curr = running_result;
        }
        return ans;
    }
};

int main(){
    scanf("%d",&n);
    //1 <= c[i] <= 10
    for(int i = 0;i<n;++i) {
        scanf("%d",&c[i]);
        --c[i];
    }
    for(int i = 0;i<n;++i){
        scanf("%lld",&h[i]);
    }
    for(int i = 0;i<n-1;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        --u,--v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    lvl[0] = -1;
    dfs(0,0);
    for(int i = 1;i<LG;++i){
        for(int j= 0;j<n;++j){
            if(par[j][i-1]!=-1){
                par[j][i] = par[par[j][i-1]][i-1];
            }
        }
    }
    int q;
    scanf("%d",&q);
    vector<queries> data;
    for(int i = 0;i<q;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        --u,--v;
        int lca = findlca(u,v);
        if(st[u] > st[v]) swap(u,v);
        if(lca==u){
            data.push_back({{st[u]+1,st[v]},{lca,i}});
        }
        else{
            data.push_back({{en[u],st[v]},{lca,i}});
        }
    }
    MO sol;
    vector<ll> ans = sol.compute(data);
    for(ll  &v : ans) printf("%lld\n",v);
    return 0;
}