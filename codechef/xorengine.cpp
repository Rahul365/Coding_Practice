#include<bits/stdc++.h>
using namespace std;
const int maxn = 4e5+1;
using ll = long long int;
vector<pair<ll,int>> seg(2*maxn,{0,0});//(data,1 if settbitcount(data) is even else 0 )
vector<pair<ll,int>> pseg(2*maxn,{0,0});
ll a[maxn];

void build(int i,int l,int r){
    if(l == r){
        pseg[i] = seg[i] = {a[l],!(__builtin_popcountl(a[l])&1)};
        return;
    }
    int m = l + (r-l)/2;
    build(i+i+1,l,m);
    build(i+i+2,m+1,r);
    pseg[i] = seg[i] = {seg[i+i+1].first|seg[i+i+2].first,seg[i+i+1].second + seg[i+i+2].second};
}


pair<int,int> update(int i,int l,int r,ll p){
    if(l > r) return {0,0};
  //  cout << l << " " <<r<<" | ";
    pair<int,int> data;
    
    if(!(pseg[i].first & p)) {
        // cout << "("<<l << " , "<<r<<") ,";
        // cout << pseg[i].first << " " <<p<<" | ";
        data = pseg[i];
        data.first |= p;
        if(__builtin_popcountl(p)&1){//number of set bits in p are odd then even + odd = odd So odd and even swap
            int even = data.second;
            int odd = r-l+1 - even;
            // cout << even << " "  <<odd<<",";
            data.second = odd;
        }
        // else{//number of set bits in  p are even
        //     //then even + even = even
        //     //and odd(1) + even(2) = odd
        // }
        return data;//nothing to update down this tree
    }
    if(l == r){
            seg[i].first ^= p;
            seg[i].second = !(__builtin_popcountl(seg[i].first)&1);
            data = seg[i];
            seg[i] = pseg[i];//restoring previous state
            return data;
    }
    int m = l + ((r-l)>>1);
    pair<int,int> left = update(i+i+1,l,m,p);
    pair<int,int> right = update(i+i+2,m+1,r,p);
    data  = seg[i] = {left.first|right.first,left.second + right.second};
    seg[i] = pseg[i];
    return data;
}



int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    freopen("xorengineinput.txt","r",stdin);
    freopen("xorenginebrutetree.txt","w",stdout);
    int t;
    cin >> t;
    while(t--){
        int n,q;
        cin >> n >> q;
        for(int i = 0;i<n;++i) cin>>a[i];
        build(0,0,n-1);
        int deven = seg[0].second;
        while(q--){
            int x; cin >> x;
            int even = deven;
            if(__builtin_popcount(x)&1){
                //even + odd = even
                even = n-even;
            }
            //int even = update(0,0,n-1,x).second;
            cout << even << " " << (n - even )<<"\n";
        }
        // fill(seg.begin(),seg.end(),make_pair(0,0));
        // fill(pseg.begin(),pseg.end(),make_pair(0,0));
    }
    return 0;
}