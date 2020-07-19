#include<bits/stdc++.h>
#define trace_vector(v) for(auto x : v) cerr << x << " "; cerr<<"\n";
using namespace std;
const int maxn = 4e5+11;
void counting_sort(vector<int> &order,vector<int> &c){
     const int n = (int)order.size();
     vector<int> cnt(maxn,0);

     for(int i = 0;i<n;++i) ++cnt[c[order[i]]];
     //  trace_vector(cnt);
     for(int i = 1;i<n;++i) cnt[i] += cnt[i-1];
     //  trace_vector(cnt);
     vector<int> order_new(n);
     for(int i = n-1;i>=0;--i){
         order_new[--cnt[c[order[i]]]] = order[i];
         assert(cnt[c[order[i]]]>=0);
    }
    order = order_new;
}

int main(){
    string s;
    cin >> s;
    s += '$';
    int n = s.length();
    vector<int> order(n);
    vector<int> c(n);//class value
    {
        vector<pair<char,int>> a(n);
        for(int i = 0;i<n;++i) a[i] = {s[i],i};
        sort(a.begin(),a.end());
        c[a[0].second] = 0;
        for(int i = 1;i<n;++i){
            if(a[i-1].first == a[i].first) c[a[i].second] = c[a[i-1].second];
            else c[a[i].second] = 1 + c[a[i-1].second];
        }
        for(int i = 0;i<n;++i){
            order[i] = a[i].second;
        }
        // trace_vector(order);
        // trace_vector(c);
    }

    int k = 0;
    while((1<<k) < n){
        for(int i = 0;i<n;++i){
            order[i] = order[i]-(1<<k);
            if(order[i] < 0) order[i]+=n;
        }

        counting_sort(order,c);
        
        vector<int> c_new(n);
        c_new[order[0]] = 0;
        pair<int,int> prev = {c[order[0]],c[(order[0] + (1<<k))%n]};
        for(int i = 1;i<n;++i){
            pair<int,int> now = {c[order[i]],c[(order[i] + (1<<k))%n]};
            c_new[order[i]] = c_new[order[i-1]] + (prev!=now);
            prev = now;
        }
        c = c_new;
        // trace_vector(order);
        // trace_vector(c);
        ++k;
    }

    for(int v : order)
        cout<< v << " " ;
    cout <<"\n";
        // cout << v <<" "<<s.substr(v) <<"\n";

    return 0;
}