#include<bits/stdc++.h>
#define trace_vector(p) for(auto v: p) cerr << v << " "; cerr<<"\n"
using namespace std;


void buildsuffixArr(string &s,vector<int> &p,vector<int> &c){
    s += '$';
    
    const int n = s.length();

    auto counting_sort = [&](vector<int> &p,const vector<int> &c){
        const int n = p.size();
        vector<int> cnt(n);
        for(int i = 0;i<n;++i) ++cnt[c[p[i]]];
        for(int i = 1;i<n;++i) cnt[i] += cnt[i-1];
        vector<int> p_new(n);
        for(int i = n-1;i>=0;--i){
            p_new[--cnt[c[p[i]]]] = p[i];
            assert(cnt[c[p[i]]] >= 0);
        }
        p = p_new;
    };

    p = vector<int>(n);
    c = vector<int>(n);
    {
        //initial level 
        vector<pair<char,int>> a(n);
        for(int i = 0;i<n;++i) a[i] = {s[i],i};
        sort(a.begin(),a.end());
        for(int i = 0;i<n;++i) p[i] = a[i].second;
        c[a[0].second] = 0;//setting up equivalence class for substr of length 1
        for(int i = 1 ;i<n;++i){
            c[a[i].second] = (a[i].first!=a[i-1].first) + c[a[i-1].second];
        }
    }
    for(int k = 0;(1<<k) < n;++k){
        for(int i = 0;i <n;++i)
            p[i] = (p[i]-(1<<k) + n) %n;

        counting_sort(p,c);
        
        vector<int> c_new(n);
        
        pair<int,int> prev = {c[p[0]],c[(p[0]+(1<<k))%n]};
        
        c_new[p[0]] = 0;
        
        for(int i = 1;i<n;++i){
            pair<int,int> now = {c[p[i]],c[(p[i]+(1<<k))%n]};
            c_new[p[i]] = (now!=prev) + c_new[p[i-1]]; 
            prev = now;
        }
        
        c = c_new;
    }

    // trace_vector(p);
    // for(int i = 0;i<n;++i) cerr << c[p[i]] << " "; cout <<"\n";
}



int main(){
    string s;
    cin >> s;
    vector<int> p,c;
    buildsuffixArr(s,p,c);
    const int n = s.length();
    vector<int> lcp(n);
    int k = 0;
    for(int i = 0;i<n-1;++i){
        int pi = c[i];
        int j = p[pi-1];
        while(s[i+k] == s[j+k]) ++k;
        lcp[pi] = k;
        k = max(0,k-1);
    }
    
    for(int v : p) cout << v <<" "; cout <<"\n";
    for(int i = 0;i<n;++i) cout << lcp[p[i]] <<" \n"[i==n-1];
    return 0;
}