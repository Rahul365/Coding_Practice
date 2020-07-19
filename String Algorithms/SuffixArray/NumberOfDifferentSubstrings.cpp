#include<bits/stdc++.h>
using namespace std;

void buildSuffix(string &s,vector<int> &p,vector<int> &c){
    s+='$';
    const int n = s.length();
    auto countsort = [&](vector<int> &p){
        vector<int> cnt(n);
        for(int v : p){
            ++cnt[c[v]];
        }
        for(int i = 1;i < n;++i){
            cnt[i] += cnt[i-1];
        }
        vector<int> p_new(n);
        for(int i = n-1;i>=0;--i){
            p_new[--cnt[c[p[i]]]] = p[i];
            assert(cnt[c[p[i]]]>=0);
        }
        p = p_new;
    };

    p = vector<int>(n);
    c = vector<int>(n);
    {
        vector<pair<char,int>> a(n);
        for(int i = 0;i<n;++i) a[i] = {s[i],i};
        sort(a.begin(),a.end());
        for(int i = 0;i<n;++i) p[i] = a[i].second;
        c[a[0].second] = 0;
        for(int i = 1;i<n;++i){
            c[a[i].second] = c[a[i-1].second] +(a[i].first!=a[i-1].first);
        }
    }

 
    for(int k = 0;(1<<k) < n;++k){
        for(int i = 0;i<n;++i){
            p[i] = (p[i]-(1<<k)+n)%n;
        }
        countsort(p);
        // for(int  i = 0;i<n;++i) cout << p[i] << " " <<s.substr(p[i]) <<" \n"[i==n-1];
        vector<int> c_new(n);
        c_new[p[0]] = 0;
        pair<int,int> prev = {c[p[0]],c[(p[0]+(1<<k))%n]};
        for(int i = 1;i<n;++i){
            pair<int,int> curr = {c[p[i]],c[(p[i]+(1<<k))%n]};
            c_new[p[i]] = c_new[p[i-1]] + (prev!=curr);
            prev = curr;
        }
        c = c_new;
    }
}

void buildlcp(string &s,vector<int> &p,vector<int> &c,vector<int> &lcp){
    int k = 0;
    const int n = s.length();
    lcp = vector<int>(n);
    for(int i = 0;i<n-1;++i){
        int pi = c[i];//position of the suffix starting from i in the suffix array
        int j = p[pi-1];//starting index of the suffix which is just before suffix i
        while(s[i+k] == s[j+k]) ++k;
        lcp[pi] = k;
        k = max(0,k-1);
    }
    // for(int  i = 0;i<n;++i){
    //     cout << p[i] << " " << s.substr(p[i]) <<"\n";
    // }
    // for(int i = 1;i<n;++i){
    //     cout << lcp[i] <<" ";
    // }
    // cout <<"\n";
}

int main(){
    string s;
    cin >> s;
    vector<int> p,c,lcp;
    buildSuffix(s,p,c);
    buildlcp(s,p,c,lcp);
    long long numberOfDifferentSubstrings = 0;
    int n = s.length();
    for(int i = 0;i<n-1;++i){
        // cout << (n-p[i]-1) << " "<<lcp[c[p[i]]] <<"\n";
        int pos_pi = c[i];
        int lengthOfsuffix = (n-i-1);
        numberOfDifferentSubstrings += lengthOfsuffix - lcp[pos_pi];
    }
    cout << numberOfDifferentSubstrings <<"\n";
    return 0;
}