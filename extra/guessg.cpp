#include<bits/stdc++.h>
using namespace std;
using ll  = long long;
char ans(ll n)
{
    cout << n <<"\n"; fflush(stdout);
    char ch;
    cin  >> ch;
    if(ch == 'E') exit(0);
    return ch;
}

ll getpos(ll pos,set<pair<ll,ll>> &s){
    ll cnt= 0;
    for(auto p : s){
        ll c = p.second-p.first + 1;
        if(cnt + c >= pos) return min(p.second,p.first+pos-cnt);
        cnt += c;
    }
    return 0;
}

ll getcount(set<pair<ll,ll>> &s){
    ll N = 0L;
    for(auto p : s)  N += p.second -p.first +1;
    return N;
}

void split(set<pair<ll,ll>> &s,ll m)
{
    for(auto p : s){
        if(p.first <= m && m <= p.second){
            if(p.first <= m-1) s.insert({p.first , m-1});
            if(m+1 <= p.second) s.insert({m+1,p.second});
            s.erase(p);
            break;
        }
    }
}

void removeleft(set<pair<ll,ll>> &s,ll m){
    for(auto p : s){
        if(p.first <= m && m <= p.second){
            s.erase(p);
            if(m+1<=p.second)
            s.insert({m+1,p.second});
            break;
        }
    }
    vector<pair<ll,ll>> tmp;
    for(auto p : s) 
        if(p.second <= m) tmp.push_back(p);
    for(auto p : tmp)
        s.erase(p);
}

void removewithin(set<pair<ll,ll>> &s,ll l,ll r){
    split(s,l);
    split(s,r);
    vector<pair<ll,ll>> tmp;
    for(auto p : s)
        if(l<=p.first && p.second <= r){
            tmp.push_back(p);
        }
    for(auto p : tmp)
        s.erase(p);
}

void removeright(set<pair<ll,ll>> &s,ll m){
    for(auto p : s){
        if(p.first <= m && m <= p.second){
            s.erase(p);
            if(p.first <= m-1)
            s.insert({p.first,m-1});
            break;
        }
    }
    vector<pair<ll,ll>> tmp;
    for(auto p : s) 
        if(p.first >= m) tmp.push_back(p);
    for(auto p : tmp)
        s.erase(p);
}

void printset(set<pair<ll,ll>> &s){
   for(auto p : s){
       cout <<"("<<p.first << " " << p.second <<") ";
   } 
   cout << "\n";
}

int main(){
    ll n;
    cin >> n;
    set<pair<ll,ll>> s;
    s.insert({1,n});
    while(!s.empty()){
        // printset(s);
        ll N = getcount(s);
        ll p1 = N/2;
        ll m1 = getpos(p1,s);
        char x = ans(m1);
        if(x == 'G'){
            ll p2 = N/3;
            ll m2 = getpos(p2,s);
            char y = ans(m2);
            if(y == 'G'){
                split(s,m1);
                removeleft(s,m2);
            }
            else{
                removewithin(s,m2,m1);
                while(!s.empty()){
                    // printset(s);
                    //here we will use m2
                    ll M = 0;
                    ll K = 0;
                    for(auto p : s){
                        if(p.second < m2){
                            M += p.second-p.first+1;
                        }
                        else{
                            K += p.second-p.first+1;
                        }
                    }  
                    ll p = 0;
                    if(y == 'G'){
                        p = (M+K)/3;
                        ll m = getpos(p,s);
                        char a = ans(m);
                        if(a == 'G'){
                            split(s,m2);
                            removeleft(s,m);
                            break;
                        }
                        else{
                            removewithin(s,m,m2);
                            m2 = m;
                            y = a;
                        }
                    }
                    else if(y=='L'){
                        p = M + (2*K)/3;
                        ll m = getpos(p,s);
                        char a = ans(m);
                        if(a == 'L'){
                            split(s,m);
                            removeright(s,m);
                            break;
                        }
                        else{
                            removewithin(s,m2,m);
                            m2 = m;
                            y = a;
                        }
                    }
                }
            }
         }
         else if(x == 'L')
         {
            ll p2 = (2*N)/3;
            ll m2 = getpos(p2,s);
            char y = ans(m2);
            if(y == 'L'){
                split(s,m1);
                removeright(s,m2);
            }
            else{
                removewithin(s,m1,m2);
                while(!s.empty()){
                    // printset(s);
                    //here we will use m2
                    ll M = 0;
                    ll K = 0;
                    for(auto p : s){
                        if(p.second <= m2){
                            M += p.second-p.first+1;
                        }
                        else{
                            K += p.second-p.first+1;
                        }
                    }  
                    ll p = 0;
                    if(y == 'G'){
                        p = (M+K)/3;
                        ll m = getpos(p,s);
                        char a = ans(m);
                        if(a == 'G'){
                            split(s,m2);
                            removeleft(s,m);
                            break;
                        }
                        else{
                            removewithin(s,m,m2);
                            m2 = m;
                            y = a;
                        }
                    }
                    else if(y=='L'){
                        p = M + (2*K)/3;
                        ll m = getpos(p,s);
                        char a = ans(m);
                        if(a == 'L'){
                            split(s,m);
                            removeright(s,m);
                            break;
                        }
                        else{
                            removewithin(s,m2,m);
                            m2 = m;
                            y = a;
                        }
                    }
                }
            }
         }
    }
    return 0;
}