#include<bits/stdc++.h>
#define removedups(v) sortvector(v); v.resize(unique(v.begin(),v.end()) - v.begin());
#define USE_FILE(i,o) freopen(i,"r",stdin); freopen(o,"w",stdout)
#define readint(x) scanf("%d",&x)
#define printint(x) printf("%d",x)
#define printintln(x) printf("%d\n",x)
#define readint64(x) scanf("%lld",&x)
#define printint64(x) printf("%lld ",x)
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
const int M6 = 1e6+1;
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


template<typename T>
class BIT{

    vector<T> data;
    int _n;
    public : 
    T read(int id){
        T sum = 0;
        for(++id;id>0;id-=(id & -id)){
            sum += data[id];
        }
        return sum;
    }


        BIT(int n){
            _n = n+1;
            data = vector<T>(_n);
        }

        void reset(){
            fill(data.begin(),data.end(),0);
        }

        void update(int id,T val){
            for(++id;id < _n;id += (id & -id)){
                data[id] += val;
            }
        }

        T rangesum(int l,int r){
            return read(r) - read(l-1);
        }
};


void brute(vector<pair<ll,ll>> &points,int q){
     vector<ll> ans(q);
        for(int i= 0;i<q;++i){
            ll l;
            ll r;
            readint64(l); l*=2;
            readint64(r); r*=2;
            
            ll m = l + (r-l)/2;
            for(auto &p : points){
                ll x = p.first;
                ll y = p.second;
                if(l <= x && x <= m && x-y >= l){
                        ++ans[i];
                }
                else if(m < x && x <= r && x + y <= r){
                        ++ans[i];
                }
            }
         }
 
         for(int i = 0 ;i < q;++i){
             printint64(ans[i]);
         }
         printf("\n");
}


BIT<ll> btree(M6);


int main(){
    int t;
    readint(t);
    while(t--){
        int n,q;
        readint(n);
        readint(q);
        vector<pair<ll,ll>> points = vector<pair<ll,ll>>(n);
        for(int i = 0;i<n;++i){
            ll x,y;
            readint64(x);
            readint64(y);
            points[i] = {(x-y),(x+y)};
        }
        sortvector(points);

        /*
            divide the given triangle with Hypotenuse from (l,0) to (r,0)
            into two triangles such that with points L(l,0),{ O(l + (r-l)/2,0),M(l+(r-l)/2,(r-l)/2) },R(r,0)
            let us consider the triangle LOM
            for all the points(x,y) such that l<= x <= (l+(r-l)/2) and x-y>=l 
            Those points will be inside the triangle LOM

            let us consider the triangel ROM
            for all the points (x,y) such that l+(r-l)/2 < x  <= r and r>=x +y
            Those points will be inside the triangle ROM 
        */

       vector<pair<pair<ll,ll>,int>> queries;
       for(int i = 0;i < q;++i){
           ll l,r;
           readint64(l); readint(r);
        //    l*=2  , r*=2;
           queries.push_back({{l,r},i});
       }
       sortvector(queries);
       vector<ll> ans(q);
       

       int j = n-1;
       for(int i = q-1;i>=0;--i){
           while(j>=0 && points[j].first>= queries[i].first.first){ 
               // A point is said to be in the triangle formed by points (l,0),((l+r)/2 , (r-l)/2),(r,0)
               //iff l <= (x-y) and (x+y) <= r (both these conditions holds, points for which this condition doesn't hold will not be in the triangle)
               btree.update(points[j].second,1);
               --j;
           }
           //query all the set values from 1 to r in the tree
           //only values from current point query[i] = {{l,r},pos}
           //will be set in the tree
           //querying till current query[i].r will give the number of points which lie inside given triangle {l,r}

           ans[queries[i].second] = btree.read(queries[i].first.second);
       }
        for(++j;j<n;++j) btree.update(points[j].second,-1);
        for(auto v : ans){
            printint64(v);
        }
        printf("\n");
    }
    return 0;
}

/**
1
6 3

1 2
14 7
6 3
8 7
11 10
14 2

0 10
2 22
11 17
*/