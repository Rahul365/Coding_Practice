#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+1;
int spf[maxn];
/**
 * 
 * This program computes the factors of number n^2 for given n by using the prime factors with exponents computed for just n.
 * Idea is to multiply all the exponents in the factorization of n by 2
 * Then apply recursion to generate all the factors of n^2 not exceeding maxn.
 */
void seive(){
    for(int i = 0;i<maxn;++i)
        spf[i] = i;
    for(int i = 2;i<maxn;++i)
        if(spf[i] == i)
            for(int j = i*2;j<maxn;j+=i){
                spf[j] = i;
            }
}


vector<pair<int,int>> primefactor(int n){
    vector<pair<int,int>> pf;
    while(n > 1){
       int p = spf[n];
       int c = 0;
       while(n%p == 0){
           n/=p;
           ++c;
       }
       pf.push_back({p,c});//{prime , exponent}
    }
    return pf;
}


void dfs(vector<pair<int,int>> &pf,vector<int> &f,int i = 0,long long x = 1LL){
    if(i >= pf.size() ||  x*pf[i].first >= maxn)
    {
        f.push_back(x);
        return;
    }
    //multiply the exponent of each prime pf[i].first by 2
    //then multiply prime pf[i].first ^ (2*pf[i].second) or pf[i].first<<pf[i].second
    for(int j = 0;j<= 2*pf[i].second && x < maxn;x*=pf[i].first,++j)
        dfs(pf,f,i+1,x);
}

int main(){
    seive();
    int n;
    cin >> n;
//    n*=n;
    vector<pair<int,int>> pf = primefactor(n);
    reverse(pf.begin(),pf.end());
    for(auto &f : pf){
       cout << f.first <<" ";
    }
    cout<<"\n";
    vector<int> f;//prime factors of n^2
    dfs(pf,f);
    for(int ff :f)
        cout << ff << " ";
    cout<<"\n";
    return 0;
}