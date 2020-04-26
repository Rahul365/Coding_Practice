#include<bits/stdc++.h>
#define ll long long int
#define PII pair<ll,pair<int,int>>
using namespace std;
template<typename T>
class bit{
    vector<T> d;
    public:
    bit(){
        
    }
    
    bit(int size){
        d = vector<T>(size+1);
    }
    
    void update(int idx,T v){
        ++idx;
        while(idx < d.size()){
            d[idx] += v;
            idx += (idx & -idx);
        }
        
    }
    
    T read(int idx){
        ++idx;
        T sum = 0;
        while(idx > 0){
            sum += d[idx];
            idx -= (idx & -idx);
        }
        return sum;
    }
    
    T sum(int l,int r){
        return read(r) - read(l-1);
    }
};

template<typename T>
long long merge(T *a,int  l,int m,int r){
    long long inv = 0;
    int i = l;
    int j = m+1;
    T c[r-l+1];
    int id = 0;
    while(i <= m && j <= r){
        if(a[i] <= a[j]){
            c[id++] = a[i++];
        }
        else{
            c[id++] = a[j++]; 
            inv+=(m-i+1);
        }
    }
    
    while(i <= m){
        c[id++] = a[i++];
    }
    
    while(j <= r){
        c[id++] = a[j++];
    }
    
    for(int i = 0;i<id;++i){
        a[l++] = c[i];
    }
    return inv;
}

template<typename T>
long long mergesort(T *a,int l,int r){
    long long ans = 0;
    if(l < r){
        int m= l+(r-l)/2;
        ans += mergesort(a,l,m);
        ans += mergesort(a,m+1,r);
        ans += merge(a,l,m,r);
    }    
    return ans;
}

int main()
{
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        int a[n];
        for(int i = 0;i<n;++i){
            // cin >> a[i].first;
            // a[i].second = i;
            cin >> a[i];
        }
        //Using binaryIndexed Tree
        // sort(a , a+n,compare);
        // bit<long long> bt(n);
        // long long ans = 0;
        // for(int i= 0;i<n;++i){
        //     ans += bt.sum(a[i].second,n-1);
        //     bt.update(a[i].second,1);
        // }
        // cout << ans <<"\n";
        
        cout << mergesort(a,0,n-1) <<"\n";
    }
	return 0;
}