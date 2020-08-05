#include<bits/stdc++.h>
using namespace std;
using ll = __int64;
// https://codeforces.com/problemset/problem/478/B
int main(){
    ll n,m;
    cin >> n >> m;
    ll cnt = n/m;//number of players equally divided in team
    ll extra = n%m;//number of extra players left
    //number  of extra players will be divided equally to all the min(m,cnt) teams to find the kmin
    ll kmax = n-m+1; kmax = (kmax*(kmax-1))/2;
    ll ep = cnt + (extra!=0);//number of extra players will be equally distributed to 'extra' number of teams
//    cerr << extra << " " << cnt << " " <<extra <<"\n";
    ll kmin =extra *  ((ep*(ep-1))>>1); 
    kmin += (m-extra)*((cnt * (cnt-1))>>1);
    cout << kmin << " " << kmax <<"\n";
    return 0;
}