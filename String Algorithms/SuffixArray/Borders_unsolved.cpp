#include<bits/stdc++.h>
#define _LOG 1
using namespace std;
const int maxn = 4e5+11;
const int LG = 20;
const int inf = 1e9+7;
int sp[maxn][LG];
int LOG[maxn];
int prefsum[maxn];
using ll = long long int;
vector<int> p,c,lcp;
string s;

void buildsuffix(){
    s += '$';
    const int n = s.length();
    p = vector<int>(n);
    c = vector<int>(n);
    {
        vector<pair<char,int>> a(n);
        for(int i = 0;i<n;++i){
            a[i] = {s[i],i};
        }
        sort(a.begin(),a.end());
        for(int i = 0;i<n;++i) p[i] = a[i].second;
        c[a[0].second] = 0;
        for(int i = 1;i<n;++i)
        c[a[i].second] = c[a[i-1].second] + (a[i].first!=a[i-1].first);
    }

    auto countsort = [&](vector<int> &p,vector<int> &c){
        vector<int> cnt(n);
        for(int v : c) ++cnt[v];
        for(int i = 1;i<n;++i){
            cnt[i] += cnt[i-1];
        }
        vector<int> p_new(n);
        for(int i = n-1;i>=0;--i){
            p_new[--cnt[c[p[i]]]] = p[i];
            assert(cnt[c[p[i]]] >= 0);
        }
        p = p_new;
    };

    for(int k = 0;(1<<k) < n;++k){
        for(int i= 0;i<n;++i) 
        {
                p[i] = (p[i]-(1<<k)+n)%n;
        }
        countsort(p,c);
        vector<int> c_new(n);
        pair<int,int> prev = {c[p[0]],c[(p[0]+(1<<k))%n]};
        c_new[p[0]] = 0;
        for(int i = 1;i<n;++i){
            pair<int,int> now = {c[p[i]],c[(p[i]+(1<<k))%n]};
            c_new[p[i]] = c_new[p[i-1]] + (now!=prev);
            prev = now;
        }
        c = c_new;
    }

    
}

void buildlcp(){
    const int  n =s.length();
    lcp = vector<int>(n);
    int k = 0;
    for(int i = 0 ;i<n-1;++i){
        int pi = c[i];
        int j = p[pi-1];
        while(s[i+k]==s[j+k]) ++k;
        lcp[pi] = k;
        k = max(k-1,0);
    }
    if(_LOG)
    for(int i = 0;i<n;++i){
        cerr << p[i] << " " <<s.substr(p[i])<< " " << lcp[c[p[i]]]<<"\n";
    }
    if(_LOG)
    for(int i=0;i<n-1;++i){
        cerr << "Suffix => ("<<i << " "<< p[c[i]-1] <<") =  "<< lcp[c[i]]<<"\n";
    }
}

void buildRMQ(){
    LOG[1] = 0;
    for(int i=2;i<maxn;++i)
        LOG[i] = LOG[i>>1]+1;

    for(int i=0;i<maxn;++i){
        prefsum[i] = 0;
        for(int j =0 ;j<LG;++j){
            sp[i][j] = inf;
        }
    }
    const int n = s.length();
    for(int i= 0;i<n;++i){
        sp[i][0] = lcp[i];
    }
    for(int L = 1;L<LG;++L)
        for(int i = 0;i+(1<<L)<=n;++i)
            sp[i][L] = min(sp[i][L-1],sp[i+(1<<(L-1))][L-1]);
}

int LCP(int l,int r){
    if(l == r) return 0;
    if(l > r) swap(l,r);
    ++l;
    int L = LOG[r-l+1];
    return min(sp[l][L],sp[r-(1<<L)+1][L]);
}

ll count(ll n){
    return (n*(n+1))>>1LL;
}

void brute(ll n){
 ll ans = count(n);
    for(int i = 0;i<n;++i){
        cerr << "Prefix "<<i<<" => ";
        int cnt = 0;
        for(int j = i;j<n;++j){
            cerr << "("<<i<<","<<j<<"["<<(LCP(c[i],c[j])+1)<<"]) ";
            ans +=1LL* LCP(c[i],c[j]);
        }
        cerr<<"\n";
    }
    cout << ans <<"\n";
}


ll sum = 0;
void reducto(int n){
    vector<int> lvl;
    
    sum += lcp[c[p[n-1]]];
    for(int i = 0;i<n-1;++i){
        lvl.push_back(min(lcp[c[p[i]]],lcp[c[p[i+1]]]));
        sum += lcp[c[p[i]]];
    }

    while(lvl.size()!=0){
        ll currsum = lvl.back();
        vector<int> lvl_new;
        for(int i = 0;i<lvl.size()-1;++i){
            lvl_new.push_back(min(lvl[i],lvl[i+1]));
            currsum += lvl[i];
        }
        if(!currsum) break;
        sum += currsum;
        lvl = lvl_new;
    }
}


ll seg[4*maxn],segsum[4*maxn];//build over the lcp values
ll lazy[4*maxn];
void build(int i,int l,int r){
    if(l==r){
        seg[i] = segsum[i] = 0;
        return;
    }
    int m = l+(r-l)/2;
    build(i+i+1,l,m);
    build(i+i+2,m+1,r);
    seg[i] = seg[i+i+1] + seg[i+i+2];
}

void update(int i,int l,int r,int L,int R,int val){
    if(lazy[i]!=-1){
        seg[i] = lazy[i] * (r-l+1);
        segsum[i] = lazy[i] * (r-l+1);
        if(l!=r){
            lazy[i+i+1] = lazy[i+i+2] = lazy[i];
        }
        lazy[i] = -1;
    }
    if(l > r || L > R || r < L || R <l){
        return;
    }
    if(L<=l && r <=R){
        seg[i] = val * (r-l+1);
        segsum[i] = val * (r-l+1);
        if(l!=r){
            lazy[i+i+1] = lazy[i+i+2] = val;
        }
        return;
    }
    int m = l+(r-l)/2;
    update(i+i+1,l,m,L,R,val);
    update(i+i+2,m+1,r,L,R,val);
    seg[i] = seg[i+i+1] + seg[i+i+2];
    segsum[i] =segsum[i+i+1] =segsum[i+i+2];
}


void add(int i,int l,int r,int pos){
    if(lazy[i]!=-1){
        seg[i] = lazy[i];
        segsum[i] = lazy[i];
        if(l!=r){
            lazy[i+i+1] = lazy[i+i+2] = lazy[i];
        }
        lazy[i] = -1;
    }
    if(l > r || pos  < l || pos > r){
        return;
    }
    if(l == r && r == pos){
        seg[i]++;
        segsum[i] = seg[i] * l * 1LL;
        return;
    }
    int m = l+(r-l)/2;
    add(i+i+1,l,m,pos);
    add(i+i+2,m+1,r,pos);
    seg[i] = seg[i+i+1] + seg[i+i+2]; // count the number of elements
    segsum[i] = segsum[i+i+1] + segsum[i+i+2];//sum of lcps
}

ll rangecount(int i,int l,int r,int L,int R)
{
    if(lazy[i]!=-1){
            seg[i] = lazy[i] * (r-l+1);
            segsum[i] = lazy[i] * (r-l+1);
            if(l!=r){
                lazy[i+i+1] = lazy[i+i+2] = lazy[i];
            }
            lazy[i] = -1;
    }
    if(l > r || L > R || r < L || R <l){
        return 0LL;
    }
    if(L<=l && r<=R){
        return seg[i];
    }
    int m=l+(r-l)/2;
    return rangecount(i+i+1,l,m,L,R) + rangecount(i+i+2,m+1,r,L,R);
}

ll rangesum(int i,int l,int r,int L,int R){
    if(lazy[i]!=-1){
            seg[i] = lazy[i] * (r-l+1);
            segsum[i] = lazy[i] * (r-l+1);
            if(l!=r){
                lazy[i+i+1] = lazy[i+i+2] = lazy[i];
            }
            lazy[i] = -1;
    }
    if(l > r || L > R || r < L || R <l){
        return 0LL;
    }
    if(L<=l && r<=R){
        return segsum[i];
    }
    int m=l+(r-l)/2;
    return rangesum(i+i+1,l,m,L,R) + rangesum(i+i+2,m+1,r,L,R);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    for(int i = 0;i<4*maxn;++i){ seg[i] = 0LL,lazy[i]=-1 , segsum[i] = 0LL;}
    cin >> s;
    const int n = s.length();
    buildsuffix();
    buildlcp();
    buildRMQ();
    ll sum = 0;
    ll ans = count(n);
    // reducto(n+1);
    // cerr << sum <<"\n";
    // for(int i = 0;i<n;++i){
    //     int pi = c[i]; 
    //     int mn = lcp[pi];
    //     while(lcp[pi]!=0){
    //         cerr << pi << " ";
    //         mn = min(mn,lcp[pi]);
    //         sum += mn;
    //         --pi;
    //     }
    //     cerr <<"\n";
    // }
    vector<vector<pair<int,int>>> subs;
    vector<int> par;
    int id = -1;
    for(int i = 1;i<n+1;){
        if(i+1<n+1 && lcp[i+1] && lcp[i]==0){
            ++id;
            ++i;
        }
        else{
            ++i;
            continue;
        }
        par.push_back(i-1);
        vector<pair<int,int>> arr;
        for(;i<n+1 && lcp[i];++i){
            arr.push_back({lcp[i],i});
        }
        subs.push_back(arr);
    }
    auto it = par.begin();
    for(auto &v : subs){
        cerr << "par : " << *it <<" => ";
        ++it;
        sort(v.begin(),v.end());
        for(pair<int,int> p : v){
            cerr << p.first << " " << p.second << " | ";
        }
        cerr <<"\n";
    }

    // build(0,0,n+1);
    // update(0,0,n+1,0,n+1,0);
    // for(int i = 0;i<n+1;++i){
    //     int pi = c[p[i]];

    //     // if(_LOG) cerr << p[i] << " \n"[i==n];
        
    //     if(lcp[pi] == 0){
    //         update(0,0,n+1,0,n+1,0);
    //         // for(int i = 0;i<n+1;++i)
    //         //     cerr << rangesum(0,0,n+1,i,i)<<" \n"[i==n];
    //     }
    //     else{
    //         add(0,0,n+1,lcp[pi]);//point update
    //         ll gte = rangecount(0,0,n+1,lcp[pi],n+1);//greater than equal to
    //         ll currsum = (1LL*gte*lcp[pi]) + (1LL*rangesum(0,0,n+1,0,lcp[pi]-1));
    //         cerr << currsum << " \n"[i==0];
    //         sum += currsum;
    //     }
    // }
    if(_LOG) cerr << sum <<"\n";
    ans += sum;
    cout << ans <<"\n";
    return 0;
}