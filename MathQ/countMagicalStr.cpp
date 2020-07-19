#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
using ll = long long int;
template<typename T>
T power(T x , T y){
    T r = 1LL;
    while(y){
        if(y&1) r = (r*x)%mod;
        x = (x*x)%mod;
        y>>=1;
    }
    return r;
}

template<typename T>
class dsu{
    vector<T> _size;
    vector<T> parent;
    int N;
    public:
    dsu(int _N){
        N = _N;
        _size = vector<T>(N,1);
        parent = vector<T>(N);
        for(int i = 0;i<N;++i){
            parent[i] = i;
        }
    }

    int root(int x){
        while(parent[x]!=x){
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }

    bool wunion(int x,int y){
        int rx = root(x);
        int ry = root(y);
        if(rx == ry) return false;
        if(_size[rx] < _size[ry]) swap(rx,ry);
        _size[rx] += _size[ry];
        parent[ry] = rx;
        return true;
    }

    int NumberOfComponents(){
        int components = 0;
        for(int i=0;i<N;++i){
            components += parent[i]==i;
        }
        return components;
    }
};

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int n,m;
        scanf("%d%d",&n,&m);
        dsu<int> _dsu(n);
        vector<vector<bool>> edges(n,vector<bool>(n,false));
        for(int q = 0;q< m ;++q){
            int l,r;
            scanf("%d%d",&l,&r);
            if(l > r) swap(l,r);
            --l,--r;
            while(l<r && !edges[l][r]){
                edges[l][r] = true;
                ++l;
                --r;
            } 
        }
        for(int i=0;i<n;++i){
            for(int j = i+1; j < n;++j){
                if(edges[i][j]){
                    _dsu.wunion(i,j);
                }
            }
        }
        
        ll ans = power(26LL,(ll)_dsu.NumberOfComponents());
        //L,R = 1,(N=7)
        //L,R = 1,3
        //1,2,3,4,5,6,7
        //a,c,a,b,a,c,a
        //0,1,2,3,4
        //n = 5
        printf("%lld\n",ans);
    }
    //1 2 3 4 5
    //a a b a b
    return 0;
}