#include<bits/stdc++.h>
using namespace std;


const int INF = 1e9+7;
const int inf = 1e9+7;
const int LG = 20;
const int maxn = 4e5+10;
vector<int> a(maxn*4);
vector<int> p,c,lcp;
string s;
int sp[maxn][LG];
int LOG[maxn];


void buildsuffix(){
    s += ' ';
    const int n = s.length();
    c = vector<int>(n);//equivalence class values
    p = vector<int>(n);//order of suffixes
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


void buildlcp(){
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

void brute(vector<pair<int,int>> a){
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

void buildRMQ(int n){
    LOG[1] = 0;
    for(int i = 2;i<maxn;++i){
        LOG[i]=LOG[i>>1]+1;
    }

    for(int i = 0;i<maxn;++i)
        for(int j = 0;j<20;++j) 
            sp[i][j] = inf;

    for(int i = 0;i<n;++i)
    {
           sp[i][0] = lcp[i];
        //    cerr <<  lcp[i] << " \n"[i==n-1];
    }
    
    for(int L = 1;L<LG;++L)
        for(int i = 0;i+(1<<L) <= n;++i)
                sp[i][L] = min(sp[i][L-1],sp[i+(1<<(L-1))][L-1]);

    // for(int L = 0;L<LG;++L)
    //     for(int i = 0;i<n;++i)
    //         cerr << sp[i][L] << " \n"[i==n-1];

}

int main(){
    // string S ="";
    // for(int i = 33;i<=127;i++)        S+=char(i);
    // cerr << S <<"\n";
    cin >> s;
    buildsuffix();
    buildlcp();
    fill(a.begin(),a.end(),INF);
    // build(0,0,s.length()-1);
    buildRMQ(s.length());
    // cerr << min(c[0],c[4])+1 << " " << max(c[0],c[4]) <<"\n";
    auto LCP =[&](int l,int r){
        if(l > r) swap(l,r);
        // return 
        // int x = rangemin(0,s.length()-1,l+1,r,0);
        ++l;
        int L = LOG[r-l+1];
        // if(x!=min(sp[l][L],sp[r-(1<<L)+1][L])){
        //     cerr << l-1 << " " << r << " : "<< x << " "<<min(sp[l][L],sp[r-(1<<L)+1][L]) <<"\n";
        // }
        return min(sp[l][L],sp[r-(1<<L)+1][L]);
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
        if(_lcp < L2){
            return s[A.first + _lcp] < s[B.first + _lcp];
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