#include<bits/stdc++.h>
using namespace std;
using ll = long long int;

template<typename T>
class bit{
    int N;
    vector<T> data;
    public:
    bit(int _N){
        data = vector<T>(_N,0);
        N = _N;
    }
    
    void update(int idx,T val){
        ++idx;
        while(idx < N){
            data[idx] += val;
            idx += (idx & -idx);
        }
    }

    T read(int idx){
        ++idx;
        T sum = 0;
        while(idx > 0){
            sum += data[idx];
            idx -=(idx & -idx);
        }
        return sum;
    }

    T rangesum(int l,int r){
        return read(r) - read(l-1);
    }
};

int n;
template<typename T>
class seg{
    vector<T> tree;
    vector<T> push;
    public:
    seg(int n){
        tree = vector<T>(4*n+1,0);
        push = vector<T>(4*n+1,0);
    }
    
    void update(int i,int pos,T val,int l=0,int r=n){
        if(l > r) return;
        if(l == r){
            tree[i] += val;
            return;
        }
        int m  = l +(r-l)/2;
        if(pos <= m){
            update(i+i,pos,val,l,m);
        }
        else{
            update(i+i+1,pos,val,m+1,r);
        }
        tree[i] = max(tree[i+i],tree[i+i+1]);
    }

    void modify(int i,int L,int R,T val,int l=0,int r=n){
        if(push[i]){
            tree[i]+=push[i];
            if(l!=r){
                push[i+i]   += push[i];
                push[i+i+1] += push[i];
            }
            push[i] = 0;
        }
        if(l > r || L > R ||   r < L ||R < l){
            return;
        }
        
        if(L <=l && r<= R){
            tree[i]+=val;
            if(l!=r){
                push[i+i]+=val;
                push[i+i+1] +=val;
            }
            return;
        }
        int m =l + (r-l)/2;
        modify(i+i,L,R,val,l,m);
        modify(i+i+1,L,R,val,m+1,r);
        tree[i] = max(tree[i+i],tree[i+i+1]);
    }

    ll query(int i,int L,int R,int l = 0,int r =n){
        if(l > r || L > R || r < L || R < l) return LLONG_MIN;
        if(push[i]){
            tree[i] += push[i];
            if(l!=r)
            {
                push[i+i] += push[i];
                push[i+i+1] += push[i];
            }
            push[i] = 0;
        }
        if(L<=l && r<=R){
            return tree[i];
        }
        int m =l +(r-l)/2;
        return max(query(i+i,L,R,l,m),query(i+i+1,L,R,m+1,r));
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        int q;
        cin >> n >> q;
        vector<int> b(n+1);
        seg<ll> tree1(n);
        seg<ll> tree2(n);
        b[0] = 0;
        ll pref = 0;
        for(int i = 1 ;i<=n;++i){
            cin >> b[i];
            pref += b[i];
            tree1.update(1,i,pref);
            tree2.update(1,i,-pref);
        }
        while(q--){
            char ch;
            int x,y;
            cin >> ch >> x >> y;
            if(ch == 'Q'){
                auto left  = tree2.query(1,0,x-1);
                auto right = tree1.query(1,y,n);
                // cout << right << " " <<left<<"\n";
                cout << (right + left) <<"\n";
            }
            else{
                tree1.modify(1,x,n,y - b[x]);
                tree2.modify(1,x,n,b[x] - y);
                b[x] = y;
            }
        }
    }
    return 0;
}