#include<bits/stdc++.h>
#define removedups(v) sortvector(v); v.resize(unique(v.begin(),v.end()) - v.begin());
#define USE_FILE(i,o) freopen(i,"r",stdin); freopen(o,"w",stdout)
#define boost ios_base::sync_with_stdio(false); cin.tie(0)
#define readint(x) scanf("%d",&x)
#define printint(x) printf("%d",x)
#define printintln(x) printf("%d\n",x)
#define readint64(x) scanf("%lld",&x)
#define printint64(x) printf("%lld",x)
#define printpair(p) cerr<<p.first << " " p.second <<"\n" 
#define sortvector(v) sort(v.begin(),v.end())
#define sortvector_rev(v) sort(v.rbegin(),v.rend())
#define removedups(v) sortvector(v); v.resize(unique(v.begin(),v.end())-v.begin())
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
    vector<int> parent;
    vector<int> size;
    public:
     DSU(int n){
         parent = vector<int>(n);
         size = vector<int>(n);
         for(int i = 0;i<n;++i){
             parent[i] = i;
             size[i] = 1;
         }
     }

     int root(int u){
         while(u!=parent[u]){
             parent[u] = parent[parent[u]];
             u = parent[u];
         }
         return u;
     }

     bool Union(int u,int v){
         int ru = root(u);
         int rv = root(v);
         if(ru == rv) return false;
         if(size[ru] < size[rv]) swap(ru,rv);
         parent[rv] = ru;
         size[ru] += size[rv];
         return true;
     }
};

#define piii pair<ll, int>           //  g[u] = (w,v)  for prims algo

// https://www.codechef.com/problems/DDIMMST
int main(){
    if(false){
    #ifndef ONLINE_JUDGE

    freopen("input.txt", "r", stdin);

    freopen("output.txt", "w", stdout);

    #endif // ONLINE_JUDGE
    }

    int n,d;
    readint(n); readint(d);
    vector<vector<int>> points(n,vector<int>(d,0));
    for(int i = 0;i<n;++i){
        for(int j=0;j<d;++j){
            readint(points[i][j]);
        }
    }
    ll answer = 0;
    DSU dsu(n);
    vector<pair<ll,pair<int,int>>> edges;
    if(false){
        /*for subtask 1*/
            for(int u = 0;u<n;++u){
                for(int v = u+1;v<n;++v)
                {
                    ll cost = 0;
                    for(int j = 0;j<d;++j){
                        cost += abs(points[u][j]-points[v][j]);
                    }
                    edges.push_back({cost,{u,v}});
                }
            }
            
    }
    else{
        /*didn't work : sorting by summing the point dimensions is not stable way to sort
        --if(mask contains ith bit) then subtract that dimesion else add that dimension
        --building graph in O((2^d) * n) time instead of O(n*n) time
        --Solution in O((2^d) * n * log(n)) time
            Test case where simply summing of node values and sorting value will not be good approach
            Dimensions = 2;
            points = [{0,7},{4,5},{2,3}]
            {0,7} => 0+7 = 7
            {4,5} => 4+5 = 9
            {2,3} => 2+3 = 5
            So according to sort by sum logic, order should be 
            [A{2,3},B{0,7},C{4,5}]
            So A<->C with weight = |2-4| + |3-5| = 4
            Idea is to connect two distant nodes first
            i.e weight(A,C) = 2 + 2 = 4
            but weight(B,C) = 4 + 3 = 7 > weight(A,C). Hence this contradicts our idea of sorting by sum of the dimesions of point.
        */
        for(int mask = 0;mask < 1<<(d-1);++mask){
            piii minNode = {LLONG_MAX,-1};
            piii maxNode = {LLONG_MIN,-1};
            for(int u = 0;u<n;++u){
                ll weight = 0;
                for(int i = 0;i<d;++i){
                    if(mask & (1<<i))
                    weight += points[u][i];
                    else 
                    weight-=points[u][i];
                }
                if(minNode.first > weight){
                    minNode.first = weight;
                    minNode.second = u;
                }
                if(maxNode.first < weight){
                    maxNode.first = weight;
                    maxNode.second = u;
                }
            }
            int s = minNode.second;
            int e = maxNode.second;
            for(int i = 0;i < n;++i){
                ll weight_s = 0;
                ll weight_e = 0;
                for(int j = 0;j<d;++j){
                    weight_s += abs(points[s][j]-points[i][j]);
                    weight_e += abs(points[e][j]-points[i][j]);
                }
                edges.push_back({weight_s,{s,i}});
                edges.push_back({weight_e,{e,i}});
            }
        }
    }
    sortvector_rev(edges);
    for(auto e : edges){
        int u = e.second.first;
        int v = e.second.second;
        ll cost = e.first;
        if(dsu.Union(u,v)){
            answer += cost;
        }
    }
    printint64(answer);
    return 0;
}