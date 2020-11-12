// https://www.codechef.com/problems/QUERY
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
const int maxn = 1e5+11;
const int MAXN = 1e5+5;
const int LG = 20;
const int INF = 1e9;
using ll = long long int;
using ull = unsigned long long int;
const ll MOD2 = 998244353;
const ll MOD1 = 1e9 + 7LL;
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



vector<int> g[maxn];
int level[maxn];
int par[maxn][LG];
int subtree[maxn];//subtree size of the tree rooted down the node

int chainHead[maxn],pos[maxn];
int chainId[maxn];

int val[maxn];
int n;//number of nodes
int m;//number of edges

ll apsum(ll n,ll a, ll b){
    return (ll)((n*a) + (((n*(n-1))/2)*b));
}

struct Node{
    ll data = 0,a = 0,b = 0;
    bool lazy = false;
    Node *left,*right;
    Node(ll _data = 0,Node *l = NULL,Node *r = NULL){
            lazy = false;
            data = _data; a=b=0; left = l; right = r;
    }    
    
    Node(Node *l,Node *r){
            lazy = false;
            data = (l?l->data:0) + (r?r->data:0); left = l; right = r;  a = b = 0;
    }

    Node(Node *x){ 
        lazy = false;
        data = x->data; left = x->left; right = x->right; a = x->a; b = x->b;
    }

    void build(int l,int r){
        if(l == r) return;
        int m = l+(r-l)/2;
        left  = new Node();   left->build(l,m);
        right = new Node();   right->build(m+1,r);
    }

    Node *update(int l,int r,ll a,ll b){
        return update(0,n-1,l,r,a,b);
    }

    void propagate(int l,int r){
        if(!lazy) return;
        int m = l +(r-l)/2;
        data += apsum(r-l+1,a,b);
        if(l!=r){
            left = new Node(*left); left->a+=a; left->b+=b; left->lazy = true;
            right = new Node(*right); right->a+=a+(m-l+1)*b; right->b+=b; right->lazy = true;
        }
        lazy = false;
        a = b = 0;
    }

    Node *update(int l,int r,int L,int R,ll a,ll b){
        int m = l + (r-l)/2;
        propagate(l,r);
        if(l > r || L > R || r < L || R < l)  return this;
        if(L<=l && r <= R){
            Node *x = new Node(*this);
            x->a += a + (l-L)*b;
            x->b += b;
            x->lazy = true;
            x->propagate(l,r);
            return x;
        }
        return new Node(left->update(l,m,L,R,a,b),right->update(m+1,r,L,R,a,b));
    }

    ll query(int l,int r){
        return query(0,n-1,l,r);
    }

    ll query(int l,int r,int L,int R){
        int m = l+(r-l)/2;
        propagate(l,r);
        if(l > r || L > R || r<L||R<l) return 0;
        if(L<=l&&r<=R) return data;
        ll sum = 0;
        if(L <= m) sum += left->query(l,m,L,R);
        if(m <  R) sum += right->query(m+1,r,L,R);
        return sum;
    }
};

Node* states[maxn] , *curr = NULL;

ll ch = 0;


void dfs(int u,int p){
    subtree[u] = 1;
    level[u] = 1 + level[p];
    par[u][0] = p;
    for(int v : g[u])
        if(v!=p){
            dfs(v,u);
            subtree[u] += subtree[v];   
        }
}

int findlca(int u,int v){
    if(level[u] < level[v]) swap(u,v);
    int lg = 0;
    while((1<<lg) <= level[u]) ++lg;
    --lg;

    for(int i = lg;i>=0;--i)
        if(level[u] - (1<<i) >= level[v])
            u = par[u][i];

    if(u == v) return u;

    for(int i = lg;i>=0;--i)
        if(par[u][i]!=-1 && par[u][i]!=par[v][i])
            u = par[u][i], v = par[v][i];
    
    return par[u][0];
}

void HLD(int u,int p,int &cid,int &pid){
    if(chainHead[cid]==-1)
    {
         chainHead[cid] = u;
    }
    chainId[u] = cid;
    pos[u] = pid++;
    int heavy = -1;
    // for(int v : g[u])
    //     if(v!=p && 2*subtree[v] >= subtree[u]){
    //         heavy = v;
    //         break;
    //     }
    for(int v : g[u])
        if(v!=p)
            heavy = (heavy == -1 || subtree[heavy]<subtree[v])?v:heavy;
    
    if(heavy ==-1) return;

    HLD(heavy,u,cid,pid);

    for(int v : g[u])
        if(v!=p && v!=heavy)
            HLD(v,u,++cid,pid);
}





void init(){
    for(int i = 0;i<=n;++i){
        chainHead[i] = chainId[i] = pos[i] = -1;
        level[i] = subtree[i] = 0;
        for(int j = 0;j < LG;++j)
            par[i][j] = -1;
    }

    dfs(1,1);

    for(int i = 1;i < LG;++i)
        for(int j = 1;j <= n;++j)
            if(par[j][i-1]!=-1){
                par[j][i] = par[par[j][i-1]][i-1];
            }

    int cid = 0;//chain id
    int pid = 0;//position of node in the segment tree
    HLD(1,1,cid,pid);
    curr = new Node(0LL);
    curr->build(0,n-1);
    states[0] = curr; ch = 0;
}


void change(int u,int v,ll a,ll b){
    int L = findlca(u,v);
    //[u:L] , (L:v]
    ll cnt = 0;
    while(chainId[u]!=chainId[L]){
        int head = chainHead[chainId[u]];
        cnt = abs(pos[head] - pos[u])+1;
        // cerr << pos[chainHead[chainId[u]]] << " : " << pos[u]<<"("<<(a + (cnt-1)*b)<<","<<-b<<") , ";
        curr = curr->update(pos[head],pos[u],a +(cnt-1)*b,-b);
        u = par[head][0];
        a+=cnt*b;
    }
    if(u!=L){
        cnt = abs(pos[L]+1-pos[u])+1;
        curr = curr->update(pos[L]+1,pos[u],a +(cnt-1)*b,-b);
        a+=cnt*b;
    }

    // cerr << pos[L] << " : " << pos[u]<<"("<<(a + (cnt-1)*b)<<","<<-b<<") , ";
    curr = curr->update(pos[L],pos[L],a,b);
    a+=b;
    stack<pair<int,int>> stk;
    while(chainId[v]!=chainId[L]){
        int head = chainHead[chainId[v]];
        // cerr << pos[chainHead[chainId[v]]] << " : " << pos[v]<<"("<<(a + (N-cnt)*b)<<","<<b<<") , ";
        // persistentTree.update(pos[chainHead[chainId[v]]],pos[v],a,b);
        stk.push({pos[head],pos[v]});
        v = par[head][0];
    }

    if(v!=L){
        // cerr << pos[L]+1 << " : " << pos[v]<<"("<<(a + (N-cnt)*b)<<","<<b<<") , ";
        stk.push({pos[L]+1,pos[v]});
        // persistentTree.update(pos[L]+1,pos[v],a,b);
    }
    // cerr <<"\n";
    while(!stk.empty()){
        auto p = stk.top();
        stk.pop();
        cnt = abs(p.first-p.second)+1;
        curr = curr->update(p.first,p.second,a,b);
        a+=cnt*b;
    }
    states[ch] = curr;  
}


ll getsum(int u,int v){
    int L = findlca(u,v);
    ll ans = curr->query(pos[L],pos[L]);
    while(chainId[u]!=chainId[L]){
        int head = chainHead[chainId[u]];
        ans += curr->query(pos[head],pos[u]);
        u = par[head][0];
    }
    if(u != L)    ans += curr->query(pos[L]+1,pos[u]);
    while(chainId[v]!=chainId[L]){
        int head = chainHead[chainId[v]];
        ans += curr->query(pos[head],pos[v]);
        v = par[head][0];
    }
    if(v != L)  ans += curr->query(pos[L]+1,pos[v]);
    return ans;
}

void rollback(int id){
    curr = states[id];
}

int main(){
    freopen("qinput.txt","r",stdin);
    scanf("%d%d",&n,&m);
    for(int i = 1;i<n;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        // --u,--v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    init();
    ll ans = 0;
    // cerr << "Chains : " << chn <<"\n";
    ll x,y,a,b;
    char type[3];
    while(m--){
        scanf("%s",type); // get the type of the query
        if(type[0] == 'c'){
            //range update query
            readint64(x); readint64(y); readint64(a); readint64(b);
            x = (x + ans)%n+1;
            y = (y + ans)%n+1;
            ++ch;//count the changing state
            change(x,y,a,b);
            // persistentTree.printtree(persistentTree.states.back(),0,n-1); cerr<<"\n";
        } 
        else if(type[0] == 'q'){
            //query the sum of values on the path from node x to y
            readint64(x); readint64(y);
            x = (x + ans)%n + 1;
            y = (y + ans)%n + 1;
            ans = getsum(x,y);
            printint64(ans);
            printf("\n");
            // cerr << x << " , " << y <<"\n";
        }
        else{
            readint64(x);
            int id = (x + ans)%(ch+1);
            rollback(id);
        }
    }
    return 0;
}