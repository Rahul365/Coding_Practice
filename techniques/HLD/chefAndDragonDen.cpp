#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+10;
const int LG = 22;
using ll = long long int;
const ll inf = 1e9+7;
vector<int> g[2][maxn];
int n,q;
vector<ll> h(maxn),a(maxn);
vector<vector<ll>> seg(2,vector<ll>(4*maxn+1));
vector<vector<int>> pos(2,vector<int>(maxn));
vector<vector<int>> chainid(2,vector<int>(maxn,-1));
int cid = -1,pid = -1;
vector<vector<int>> chainhead(2,vector<int>(maxn,-1));
vector<vector<int>> subtree(2,vector<int>(maxn,0));
vector<ll> val(maxn);
vector<vector<int>> par(2,vector<int>(maxn,-1));

void build(int id,int i,int l,int r){
    if(l == r){
        seg[id][i] = val[l]; 
        return;
    }
    int m = l+(r-l)/2;
    build(id,i+i,l,m);
    build(id,i+i+1,m+1,r);
    seg[id][i] = seg[id][i+i] + seg[id][i+i+1];
}

ll rangesum(int id,int i,int l,int r,int L,int R){
    if(L > R ||  l > r || r < L || R < l) return 0LL;
    if(L<=l && r<=R){
        return seg[id][i];
    }
    int m = l+(r-l)/2;
    if(R <= m) return rangesum(id,i+i,l,m,L,R);
    if(m < L) return rangesum(id,i+i+1,m+1,r,L,R);
    return rangesum(id,i+i,l,m,L,R) + rangesum(id,i+i+1,m+1,r,L,R);
}

void update(int id,int i,int l,int r,int pos,ll val){
    if(l == r){
        seg[id][i] = val;
        return;
    }
    int m = l+(r-l)/2;
    if(pos <= m){
        update(id,i+i,l,m,pos,val);
    }
    if(m < pos){
        update(id,i+i+1,m+1,r,pos,val);
    }
    seg[id][i] = seg[id][i+i]  + seg[id][i+i+1];
}

void HLD(int i,int u,int p){
    if(chainhead[i][cid] == -1){
        chainhead[i][cid] = u;
    }
    chainid[i][u] = cid;
    pos[i][u] = ++pid;
    int heavy = -1;
    for(int v : g[i][u])
        if(v!=p)
            heavy = (heavy == -1 || subtree[i][v] > subtree[i][heavy]? v :heavy);
    if(heavy!=-1)//recurr the heavy child to continue down the road
        HLD(i,heavy,u);
    for(int v : g[i][u]){
        if(v == p || v == heavy) continue;
            ++cid;
            HLD(i,v,u);//start new chain
    }
}

ll getsum(int i,int u,int v){
    ll sum = 0;
    if(pos[i][u] > pos[i][v])
        swap(u,v);
    int lca = u; 
    auto liftNode = [&](int &u,int lca){
        while(chainid[i][u]!=chainid[i][lca]){
            int head = chainhead[i][chainid[i][u]];
            sum += rangesum(i,1,0,n+1,pos[i][head],pos[i][u]);
            u = par[i][head];
        }
    };
    liftNode(u,lca);
    liftNode(v,lca);
    return sum + rangesum(i,1,0,n+1,pos[i][lca],pos[i][v]);
}

int intime[2][maxn],outtime[2][maxn];
int tme = 0;

void dfs(int i,int u,int p){
    // cout << u <<" " <<p<<"\n";
    intime[i][u] = ++tme;
    subtree[i][u] = 1;
    par[i][u] = p;
    for(int v : g[i][u]){
        if(v == p) continue;
        dfs(i,v,u);
        subtree[i][u] += subtree[i][v];
    }
    outtime[i][u] = ++tme;
}

void init(){
    tme = 0;
    dfs(0,0,0);
    tme = 0;
    dfs(1,n+1,n+1);
    cid = 0;
    pid = -1;
    HLD(0,0,0);
    for(int i = 0;i<=n+1;++i){
        val[pos[0][i]] = a[i];
    }
    build(0,1,0,n+1);
    cid = 0;
    pid = -1;
    HLD(1,n+1,n+1);
    for(int i = 0;i<=n+1;++i){
        val[pos[1][i]] = a[i];
    }
    build(1,1,0,n+1);
}

void update(int i,int u , ll val){
    update(i,1,0,n+1,pos[i][u],val);
}

bool inpath(int u,int v,int i){
    return (intime[i][u] < intime[i][v] && outtime[i][u] > outtime[i][v]) 
    || (intime[i][u] > intime[i][v] && outtime[i][u] < outtime[i][v]);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n >> q;
    h[0] = h[n+1] = inf;
    a[0] = a[n+1] = 0;
    for(int i= 1;i<=n;++i){
        cin >> h[i];
    }
    for(int i =1;i<=n;++i){
        cin >> a[i];
    }
    //build left tree 
    //in decreasing direction from left to right
    stack<int> stk;
    stk.push(0);
    for(int i = 1;i<=n;++i){
        while(!stk.empty() && h[stk.top()] <= h[i]){
            stk.pop();
        }
        if(!stk.empty() && h[stk.top()] > h[i]){
            g[0][stk.top()].push_back(i);
            g[0][i].push_back(stk.top());
        }
        stk.push(i);
    }
    while(!stk.empty()) stk.pop();
    //build right graph
    //in decreasing direction from right to left
    stk.push(n+1);
    for(int i = n;i;--i){
        while(!stk.empty() && h[stk.top()] <= h[i]){
            stk.pop();
        }
        if(!stk.empty() && h[stk.top()] > h[i]){
            g[1][i].push_back(stk.top());
            g[1][stk.top()].push_back(i);
        }
        stk.push(i);
    }

    while(!stk.empty()) stk.pop();
    init();
    while(q--){
        int type;
        cin >> type;
        if(type == 1){
            int b; ll k;
            cin >> b >> k;
            update(0,b,k);
            update(1,b,k);
            a[b] = k;
        }
        else if(type == 2){
            int b,c;
            cin >> b >> c;
            ll ans = -1;
            if(b == c){
                ans = a[b];
            }
            if(b < c && inpath(b,c,0)){
                // cout <<"Yes";
                ans = max(ans,getsum(0,b,c));
            }
            if(b > c && inpath(b,c,1)){
                // cout <<"Yes";
                ans = max(ans,getsum(1,b,c));
            }
            cout << ans <<"\n";
        }
    }
    return 0;
}