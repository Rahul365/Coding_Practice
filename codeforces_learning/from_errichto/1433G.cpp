#include<bits/stdc++.h>
#define removedups(v) sortvector(v); v.resize(unique(v.begin(),v.end()) - v.begin());
#define USE_FILE(i,o) freopen(i,"r",stdin); freopen(o,"w",stdout)
#define boost ios_base::sync_with_stdio(false); cin.tie(0)
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
using pii = pair<ll,int>;
const int N = 1002;


vector<pii> g[N];
vector<vector<ll>> wt(N,vector<ll>(N));
vector<ll> dijkstra(int source,int n)
{
    vector<ll> dist(n+1,LLONG_MAX);
    vector<bool> vis(n+1,false);
    priority_queue<pii, vector<pii>, greater<pii>> q; //min-priority queue
    //pair(ll,int) with minimum ll value will always be at the top
    q.push({0LL, source});
    dist[source] = 0LL;

    while (!q.empty())
    {
        int u = q.top().second; //get the vertex with smallest distance from the source
        q.pop();

        if (vis[u])
            continue;
        vis[u] = true;

        for (pii p : g[u])
        {
            int v = p.second;
            ll w = p.first;
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                q.push({dist[v], v});
            }
        }
    }
    // trace_vector(dist);
    // trace_vector(vis);
    return dist;
}

int main(){
    int n,m,k;
    readint(n); readint(m); readint(k);
    vector<pair<int,int>> edges;
    for(int i = 0;i<m;++i){
        int x,y;
        ll w;
        readint(x);readint(y);readint64(w);
        g[x].emplace_back(w,y);
        g[y].emplace_back(w,x);
        edges.emplace_back(x,y);
    }
    vector<pair<int,int>> p;
    for(int i = 0;i < k;++i){
        int a,b;
        readint(a); readint(b);
        if(a>b) swap(a,b);
        p.emplace_back(a,b);
    }
    ll answer = LLONG_MAX;
    vector<ll> D[n+1];
    for(int i = 1;i<=n;++i){
        D[i] = dijkstra(i,n);
    }
    for(auto e : edges){
        int u = e.first;
        int v = e.second;
        ll sub = 0;
        for(auto pp : p){
            int a = pp.first;
            int b = pp.second;
            /*Very logical statement here*/
            /*
            if(D[a][b] doesn't use edge u-v) then D[a][b] is already the shortest path
            and D[a][u]+D[v][b] or D[a][v] + D[u][b] both will be > D[a][b]
            else if(path(a,b) contains edge(u,v))
            then min(D[a][u] + D[v][b],D[a][v]+D[u][b]) will be the shortest as we are making the weight of the edge u,v to 0;

            */
            sub += min({D[a][b],D[a][u]+D[v][b],D[a][v]+D[u][b]});
        }
        answer = min(sub,answer);
    }
    printint64(answer);
    return 0;
}