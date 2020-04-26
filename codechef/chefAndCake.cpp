#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
const ll mod = 1e9 + 7;
const ll INF = mod+1;
const int maxn = 1e7+11;
ll N,K,Q;
vector<ll> A(maxn);
vector<ll> M(maxn);

template<typename T>
T power(T a,T b,T m=1e9 + 7){
    T r = 1LL;
    while(b){
        if(b&1){
            r  = (1LL * r%m * a%m)%m;
        }
        a =(1LL * a%m * a%m)%m;
        b >>= 1;
    }
    return r;
}
/*
class Node{
    public:
        ll min_val;
        ll occ;   
        Node(){}
        Node(ll val){
            min_val = val;
            occ = 1;
        }
};

Node merge(Node a,Node b){
        Node res(INF);
        if(a.min_val == b.min_val){
            res.min_val = a.min_val;
            res.occ = a.occ + b.occ;
        }
        else if(a.min_val < b.min_val){
            res.min_val = a.min_val;
            res.occ = a.occ;
        }   
        else{
            res.min_val = b.min_val;
            res.occ = b.occ;
        }
        return res;
} 



vector<Node> seg(4*maxn+1,Node());

void build(int i,int l,int r){
    if(l == r){
        seg[i].min_val = A[l];
        seg[i].occ = 1;
        return;
    }
    int m = (l+r)>>1;
    build(i+i,l,m);
    build(i+i+1,m+1,r);
    seg[i] = merge(seg[i+i],seg[i+i+1]);
}

Node query(int i,int l,int r,int L,int R){
    Node res(INF);
    if(l > r or R < l or r < L){
        return res;
    }
    if(L <=l && r<=R){
        return seg[i];
    }
    int m = (l+r)>>1;
    return merge(query(i+i,l,m,L,R),query(i+i+1,m+1,r,L,R));
}
*/
int main(){

    scanf("%lld%lld%lld",&N,&K,&Q);
    ll a, b, c, d, e, f, r, s, t, m;
    
    scanf("%lld %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld", &a,&b,&c,&d,&e,&f,&r,&s,&t,&m,&A[1]);
    ll L1, La, Lc, Lm, D1, Da, Dc, Dm;
    scanf("%lld %lld %lld %lld %lld %lld %lld %lld",&L1,&La,&Lc,&Lm,&D1,&Da,&Dc,&Dm);
    ll tx = t;
    for(ll i= 2;i<=N;++i){
        tx = (tx * t)%s;
        if(tx  <= r)        // Here t^x signifies "t to the power of x"
		    A[i] = ((a*A[i-1] + b)%m *A[i-1] + c) % m;
	    else
		    A[i] = ((d*A[i-1] + e)%m *A[i-1] + f) % m;
    }
    deque<int> q;
    M[0] = INF;
    for(int i = 1;i<=K;++i){
        while(!q.empty() && A[q.back()] >= A[i]){
            q.pop_back();
        }
        q.push_back(i);
    }
    for(int i = K+1;i<=N+1;++i){
        M[i-K] = A[q.front()];
        if(i == N+1) break;
        while(!q.empty() && q.front() < i-K+1)
            q.pop_front();
        while(!q.empty() && A[q.back()] >= A[i]){
            q.pop_back();
        }
        q.push_back(i);
    }
    // build(1,1,N);
    ll sum = 0LL;
    ll product = 1LL;
    for(int i  = 1;i<=Q;++i){
        L1 = (La * L1 + Lc) % Lm;
        D1 = (Da * D1 + Dc) % Dm; 
        int L = L1 + 1;
        int R = min(L + K - 1 + D1, N);
        // cout << L << " "<< R<<"\n";
        // ll ans = min(query(1,1,N,L,L+K-1).min_val,(R-L+1 > K?query(1,1,N,R-K+1,R).min_val:INF));
        ll ans = min(M[L],M[R-K+1]);
        sum  = (sum + ans);
        product = (product * ans)%mod;
    }
       
    printf("%lld %lld\n",sum,product);
    return 0;
}