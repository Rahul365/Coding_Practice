#include<bits/stdc++.h>
using namespace std;


void buildsuffix(vector<int> &p,vector<int> &c,string &s){
    s += '$';
    const int n = s.length();
    c = vector<int>(n);
    p = vector<int>(n);
    {
        vector<pair<char,int>> a(n);
        for(int i = 0;i<n;++i) a[i] = {s[i],i};
        sort(a.begin(),a.end());
        for(int i = 0;i<n;++i) p[i] = a[i].second;
        c[a[0].second] = 0;
        for(int i = 1;i<n;++i){
            c[a[i].second] = c[a[i-1].second] + (a[i].first!=a[i-1].first);
        }
    }

    auto countsort = [&](vector<int> &p,vector<int> &c){
        vector<int> cnt(n);
        for(int v : c) ++cnt[v];
        for(int i = 1;i<n;++i) cnt[i]+=cnt[i-1];
        vector<int> p_new(n);
        for(int i = n-1;i>=0;--i){
            p_new[--cnt[c[p[i]]]] = p[i];
            assert(cnt[c[p[i]]] >= 0);
        }
        p = p_new;
    };

    for(int k = 0;(1<<k) < n;++k){
        for(int i = 0;i<n;++i){
            p[i] = (p[i]-(1<<k)+n)%n;
        }
        //sort by left half
        countsort(p,c);
        vector<int> c_new(n);
        c_new[p[0]] = 0;
        pair<int,int> prev = {c[p[0]],c[(p[0]+(1<<k))%n]};
        for(int i = 1;i<n;++i){
            pair<int,int> now = {c[p[i]],c[(p[i]+(1<<k))%n]};
            c_new[p[i]] = c_new[p[i-1]] + (now!=prev);
            prev = now;
        }
        c = c_new;
    }

    // for(int i = 0;i<n;++i){
    //     cout << p[i] << " " << s.substr(p[i]) <<"\n";
    // }
}


void buildlcp(vector<int> &p,vector<int> &c,const string &s,vector<int> &lcp){
    const int n = s.length();
    lcp = vector<int>(n);
    int k = 0;
    for(int i = 0;i<n-1;++i){
        int pi = c[i];
        int j = p[pi-1];
        while(s[i+k] == s[j+k]) ++k;
        lcp[pi] = k;
        k = max(k-1,0);
    }
    // for(int i = 0;i<n-1;++i) cout << lcp[i] <<" \n"[i==n-2];
    // for(int i = 0;i<n;++i){
    //     cerr << p[i] << " "<<lcp[c[p[i]]]<<" " <<s.substr(p[i])<<"\n";
    // }
}

const int INF = 1e9+7;
const int maxn = 4e5+10;
vector<int> a(maxn*4,INF);
vector<int> p,c,lcp;

void build(int i,int l,int r){
    if(l==r){
        a[i] = lcp[l];
        return;
    }
    int m = l+(r-l)/2;
    build(i+i+1,l,m);
    build(i+i+2,m+1,r);
    a[i] = min(a[i+i+1],a[i+i+2]);
}

int rangemin(int l,int r,int L,int R,int i){
    if(l > r || L > R || R < l || r < L){
        // cerr << l << " " << r <<"\n";
        // cerr << L << " " << R <<"\n";
        return INF;
    }
    if(L<=l && r<=R){
        return a[i];
    }
    int m = l+(r-l)/2;
    if(R <= m) return rangemin(l,m,L,R,i+i+1);
    else if(m<L) return rangemin(m+1,r,L,R,i+i+2);
    int left = rangemin(l,m,L,R,i+i+1);
    int right= rangemin(m+1,r,L,R,i+i+2);
    return min(left,right);
}

void brute(const string &s,vector<pair<int,int>> a){
    sort(a.begin(),a.end(),[&](const auto &p1,const auto &p2)
    {
        return s.substr(p1.first,p1.second-p1.first+1)<s.substr(p2.first,p2.second-p2.first+1) || 
            (s.substr(p1.first,p1.second-p1.first+1)==s.substr(p2.first,p2.second-p2.first+1) && p1<=p2);
    });
    cerr << " BRUTE \n";
    for(auto p : a){
        cout << p.first+1 << " " << p.second+1 <<" , ";
    }
    cout <<"\n"; 
}

int main(){
    string s;
    cin >> s;
    buildsuffix(p,c,s);
    buildlcp(p,c,s,lcp);
    build(0,0,s.length()-1);
    // cerr << min(c[0],c[4])+1 << " " << max(c[0],c[4]) <<"\n";
    auto LCP =[&](int l,int r){
        if(l > r) swap(l,r);
        return rangemin(0,s.length()-1,l+1,r,0);
    };
    // cerr << LCP(c[0] , c[4])<<"\n";
    int m;
    cin >> m;
    vector<pair<int,int>> q;
    for(int  i =0 ;i<m;++i){
        int x,y;
        cin >> x >> y;
        q.push_back({x-1,y-1});
    }

    sort(q.begin(),q.end(),[&](const auto &A,const auto &B){
        int L1 = A.second - A.first + 1;
        int L2 = B.second - B.first + 1;
        //_lcp <= (L1,L2)
        if(A.first == B.first){//for 0
            return L1 < L2;
        }
        int _lcp = LCP(c[A.first],c[B.first]);
        if(L1 < L2){
            if(_lcp < L1){
                return s[A.first + _lcp] < s[B.first + _lcp];
            }
            return L1 < L2;    
        }
        if(L1 == L2){
            if(_lcp < L1){
                return s[A.first + _lcp] < s[B.first + _lcp];
            }
            return A < B;
        }
        if(L1 > L2){
            if(_lcp < L2){
                return s[A.first + _lcp] < s[B.first + _lcp];
            }
            return L1 < L2;
        }
        return false;
    });
    // brute(s,q);
    // cerr << "OPTIMIZED\n";
    for(auto &v : q){
        cout << v.first+1 << " " << v.second+1 <<"\n";
    }
    return 0;
}