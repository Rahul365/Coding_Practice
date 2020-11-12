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



ll apsum(ll n,ll a, ll b){
    return (ll)((n*a) + (((n*(n-1))/2)*b));
}

int n;
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

void rollback(int id){
    curr = states[id];
}

void init(){
    curr = new Node(0LL);
    curr->build(0,n-1);
    states[0] = curr;
    ch = 0;
}

int main(){
    freopen("pinput2.txt","r",stdin);
    cin >> n;
    init();
    int q;
    cin >> q;
    ll ans = 0;
    while(q--){
        int t,l,r,a,b;
        cin >> t;
        if(!t){
            cin >> l >> r;
            cout <<"SUM["<<l<<":"<<r<<"] = "<< (ans = curr->query(l,r)) << endl;
            continue;
        }
        if(t == 2){
            int x;
            cin >> x;
            x = (x + ans)%(ch+1);
            rollback(x);
            continue;
        }

        cin >> l >> r >> a >> b;
        if(l <= r){
            curr = curr->update(l,r,a,b);
        }
        else if(l > r){
            swap(l,r);
            curr = curr->update(l,r,a+(r-l)*b,-b);
        }
        ++ch; states[ch] = curr;
    }

    return 0;
}