#include<bits/stdc++.h>
using namespace std;
using ll = long long int;

template<typename T>
class Bit{
    vector<T> arr;
    T read(int id){
        T sum = 0;
        for(++id;id>0;id-=(id & -id))
            sum += arr[id];
        return sum;
    }
    
    public :
    Bit(int n){
        arr = vector<T>(n+10,0);
    }
    
    void update(int id,T val){
        for(++id;id < arr.size();id+=(id & -id))
            arr[id]+=val;
    }
    
    T query(int l,int r){
        return read(r) - read(l-1);
    }
};

void compressValues(vector<int> &a){
    vector<int> _a = a;
    sort(_a.begin(),_a.end());
    _a.resize(unique(_a.begin(),_a.end()) - _a.begin());
    auto findpos = [&](int key){
        int l = 0;
        int r = _a.size()-1;
        while(l <= r){
            int m = l+(r-l)/2;
            if(_a[m] == key){
                return m;
            }
            if(_a[m] < key){
                l = m+1;
            }
            else{
                r = m-1;
            }
        }
        return -1;
    };
    for(int  &v : a)
        v = findpos(v);
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    
    for(int i= 0;i<n;++i){
        cin >> a[i];
    }
    vector<int> org  = a;
    compressValues(a);
    
    Bit<ll> invL(n+1);//from left to right
    Bit<ll> invR(n+1);//from right to left
    ll invcnt = 0;
    for(int i= 0;i<n;++i){
        invcnt += invL.query(a[i]+1,n-1);
        invL.update(a[i],1);
        //cout <<invcnt<<"\n";
    }
    /*
    cout <<"element : inversionOfElement : totalCountofInversions from o to i\n";
    for(int i= 0;i<n;++i){
        cout << org[i] << " "  << inv_inv.query(i,i) << " " <<inv_inv.query(0,i) <<"\n";
    }
    */
    int l = n-2;
    int r = n-1;
    invL.update(a[r],-1); 
    invR.update(a[r], 1); 
    ll ans = 0;
    while(r){
        while(invcnt > k && l>=0){
            invL.update(a[l],-1);
            invcnt -= invL.query(a[l]+1,n-1) + invR.query(0,a[l]-1);//#elements > a[l] to left  +  < a[l] to right
            --l;
        }
        //cout << l+1 <<" "<<invcnt <<"\n";
        ans += l+1;
        --r;
        invR.update(a[r],1);
        if(l == r){
            invL.update(a[l],-1);
            --l;
        }
        else{
            invcnt += invL.query(a[r]+1,n-1) + invR.query(0,a[r]-1);//#elements > a[r] in left +  < a[r] in right
        }
    }
    cout << ans <<"\n";
    return 0;
}