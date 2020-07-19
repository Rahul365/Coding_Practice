#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+11;
using ll = long long int;
/*Version of persistent segment tree using Pointer based approach*/
vector<int> a(maxn);
int n;
/*
    Supports : 
    1) Rollback 
    3) range query
    4) Range update using lazy propagations
*/
struct Node{
    Node *left,*right;
    ll sum = 0;
    ll lazy = 0;
    Node(ll _sum = 0){sum = _sum; left = right = NULL;  lazy = 0;}
    Node(Node *l,Node *r) { sum = (l?l->sum:0) + (r?r->sum:0); left= l; right = r; lazy = 0;}

    void build(int l,int r){
        if(l==r) return;
        int m = l + (r-l)/2;
        left = new Node(); left->build(l,m);
        right = new Node(); right->build(m+1,r);
    }

    Node *update(int l,int r,ll val){
        return update(0,n-1,l,r,val);
    }

    void propagate(int l,int r){
        if(!lazy) return;
        if(l!=r){
            left = new Node(*left); left->lazy += lazy;
            right = new Node(*right); right->lazy += lazy;
        }
        sum += (r-l+1)*lazy;
        lazy = 0;
    }

    Node *update(int l,int r,int L,int R,ll val){
        propagate(l,r);
        if(l > r || L > R || r < L || R < l) return this;
        int m = l + (r-l)/2;
        if(L<=l && r<=R){
            Node *x = new Node(*this);
            x->lazy += val;
            x->propagate(l,r);
            return x;
        }

        return new Node(left->update(l,m,L,R,val),right->update(m+1,r,L,R,val));
    }


    ll query(int l,int r){
        return query(0,n-1,l,r);
    }
    
    ll query(int l,int r,int L,int R){
        propagate(l,r);
        if(l > r || L > R || r < L || R < l) return 0;
        if(L<=l && r<=R) return sum;
        ll res = 0;
        int m = l+(r-l)/2;
        if(L <= m) res += query(l,m,L,R);
        if(m < R) res+= query(m+1,r,L,R);
        return res;
    }
};

vector<Node*> states(maxn);
Node *curr;
ll ch = 0;

void init(){
    curr = new Node();
    curr->build(0,n-1);
    states[0] = curr;
    ch = 1;
}

void rollback(int id){
    id %= ch;
    curr = states[id];
}

int main(){ 
    freopen("pinput.txt","r",stdin);
    scanf("%d",&n);
    init();
    int q;
    scanf("%d",&q);
    while(q--){
        int t;
        scanf("%d",&t);
        if(!t){
            //update
            ll l,r,val;
            scanf("%d%d%lld",&l,&r,&val);
            curr = curr->update(l,r,val);
            states[ch++] = curr;
        }
        else if(t == 1){
            //range query
            int l,r;
            scanf("%d%d",&l,&r);
            printf("SUM [%d:%d]: %d\n",l,r,curr->query(l,r));
        }
        else if(t == 2){
            int v; 
            scanf("%d",&v);
            rollback(v);
        }
        cout << "updates : " <<ch<<"\n";
    }
    return 0;
}