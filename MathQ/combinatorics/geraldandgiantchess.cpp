#include<bits/stdc++.h>
using namespace std;
#define FOR(i,n) for(int i = 0;i<(int)n;++i)
using ll = long long int;
const ll mod = 1e9+7;
const int maxn = 3e5+1;
ll fact[maxn];
template<typename T>
T power(T a,T b,T MOD = mod){
    T r = 1;
    while(b){
        if(b&1){
            r = (r * a)%MOD;
        }
        a = (a*a)%MOD;
        b>>=1;
    }
    return r;
}

template<typename T>
void addself(T &a,T b){
     a = (a + b)%mod;
     if(a < 0) a+=mod;
}

void compute(){
    fact[0] = 1;
    for(int i = 1;i<maxn;++i){
        fact[i] = (i*1LL*fact[i-1])%mod;
    }
}

ll nCr(ll n,ll r){
    ll ans = fact[n];
    ans = (ans * power(fact[n-r],mod-2LL,mod))%mod;
    ans = (ans * power(fact[r],mod-2LL))%mod;
    return ans;
}

// https://codeforces.com/problemset/problem/559/C
int main(){
    compute();
    int h,w,n;
    scanf("%d%d%d",&h,&w,&n);
    vector<pair<int,int>> points;
    function<ll(const pair<int,int> &,const pair<int,int> &)> getpaths = [](const pair<int,int> &A,const pair<int,int> &B){
        return nCr(B.first-A.first+1+B.second-A.second+1-2LL,min(B.first-A.first+1,B.second-A.second+1)-1LL);
    };
    FOR(i,n)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        points.emplace_back(x,y);
    }
    pair<int,int> src = {1,1};
    pair<int,int> dest = {h,w};
    sort(points.begin(),points.end());
    ll answer = nCr(h+w-2LL,min(h,w)-1LL);
    ll fromUp[n];
    for(int i = 0;i<n;++i)/*#paths from (1,1) to points[i]*/
        fromUp[i] = getpaths(src,points[i]);

    for(int i = 0;i<n;++i){
        ll &x = fromUp[i];
        for(int j = 0;j<i;j++){
            if(points[j].first <= points[i].first && points[j].second <= points[i].second){
                /*points covered in grid from top(1,1) to (points[i].first,points[i].second)*/
                ll y = fromUp[j];/*from (1,1) to points[j]*/
                y = (y * getpaths(points[j],points[i]))%mod;/*from j to i*/
                addself(x,-y);/*remove overlapping paths*/
            }    
        }
    }

   ll fromDown[n];/*from point to dest(h,w)*/
   for(int i= 0;i<n;++i){
       fromDown[i] = getpaths(points[i],dest);
   }

//    for(int i = n-1;i>=0;--i){
//        ll &x = fromDown[i];
//        for(int j = i+1;j<n;++j){
//            if(points[j].first >= points[i].first && points[j].second >= points[i].second){
//                /*if j point is below and after i point */
//                ll y = fromDown[j];/*from j to dest*/
//                y = (y * getpaths(points[i],points[j]))%mod;/*from i to j*/
//                addself(x,-y);
//            }
//        }
//    }
   for(int i= 0;i<n;++i){
       ll sub = (fromUp[i]*fromDown[i])%mod;
       addself(answer,-sub);
   }

    printf("%lld",answer);
   return 0;
}


