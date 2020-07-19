#include<bits/stdc++.h>
using namespace std;

void buildSuffixArr(string &s,vector<int> &p,vector<int> &c){
    s += '$';
    const int n = s.length();
    auto countsort = [&](vector<int> &p){
        vector<int> cnt(n);
        for(int v : c) ++cnt[v];
        for(int i = 1;i<n;++i) cnt[i] += cnt[i-1];
        vector<int> p_new(n);
        for(int i = n-1;i>=0;--i){
            p_new[--cnt[c[p[i]]]] = p[i];
            assert(cnt[c[p[i]]] >= 0);
        }
        p = p_new;
    };
    c = vector<int>(n,0);
    p = vector<int>(n,0);

    {
        vector<pair<char,int>> a(n);
        for(int i = 0;i<n;++i) a[i] = {s[i],i};
        sort(a.begin(),a.end());
        for(int i = 0 ;i <n;++i) p[i] = a[i].second;
        c[a[0].second] = 0;
        for(int i = 1;i<n;++i){
            c[a[i].second] = c[a[i-1].second] + (a[i].first!=a[i-1].first);
        }
    }

    for(int k = 0 ;(1<<k) < n;++k){
        for(int i = 0;i<n;++i) p[i] = (p[i]-(1<<k)+n)%n;
        countsort(p);
        vector<int> c_new(n);
        c_new[p[0]] = 0;
        pair<int,int> prev = {c[p[0]],c[(p[0]+(1<<k))%n]};
        for(int i = 1;i<n;++i){
            pair<int,int> now= {c[p[i]],c[(p[i]+(1<<k))%n]};
            c_new[p[i]] = c_new[p[i-1]] + (prev!=now);
            prev = now; 
        }
        c = c_new;
    }
   
}


int pos = 0;

void buildlcp(const string &s,const vector<int> &p,const vector<int> &c,vector<int> &lcp){
    const int n = s.length();
    lcp = vector<int>(n,0);
    int k = 0;
    for(int i = 0;i<n-1;++i){   
        if(s[i]=='#'){
             continue;
        }
        int pi = c[i];
        int j = p[pi-1];
        while(s[i+k] == s[j+k]) ++k;
        lcp[pi] = k;
        k = max(0,k-1);
    }

    //  for(int i = 0;i<n;++i){
    //     cerr << p[i] << " " << s.substr(p[i]) <<"\n";
    // }
}

int main(){
    string s,t;
    cin >> s >> t;
    s +='#';
    pos = s.length()-1;
    s += t;
    vector<int> p,c,lcp;
    buildSuffixArr(s,p,c);
    buildlcp(s,p,c,lcp);
    
    int best_ans = 0;
    int best_pos = 0;
    
    for(int i = 0;i<s.length()-1;++i){
        int j = p[c[i]-1];
        if((i > pos && j < pos) || (i < pos && j > pos))
        {
            if(best_ans < lcp[c[i]]){
                    best_ans = lcp[c[i]];
                    best_pos = i;
            }
        }
    }

    // cout << best_pos << " " << best_ans <<"\n";
    cout << s.substr(best_pos,best_ans) <<"\n";
    return 0;
}