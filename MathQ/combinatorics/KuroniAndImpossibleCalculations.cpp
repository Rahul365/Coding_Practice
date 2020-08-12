#include<bits/stdc++.h>
using namespace std;
// https://codeforces.com/problemset/problem/1305/C
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    for(int i = 0;i<n;++i){
        cin >> a[i];
        if(a[i] >= m) a[i]%=m;
    }
    sort(a.begin(),a.end());
    a.resize(unique(a.begin(),a.end())- a.begin());
    //this is just to check whether array contains duplicates or not
    /*
        2 cases:
         1) n  <=  m : Since (1<= m <= 1000) compute the answer in O(n^2)
         2) n  >  m : Then there will be atleast 1 integer occuring more than once or atleast two integers with same % m i.e (a-b)%m = a%m-b%m 
         //e.g. let m = 997 a = 1 and b = 998 then abs(1-998)%m = 1%m - 998%m = 0
     */
    long long int ans = a.size()==n;
    for(int i = n-1;i>=0 && ans!=0;--i){
        for(int j = i-1;j>=0 && ans!=0;--j){
            ans *= abs(a[j]-a[i]);
            ans %= m;
        }
    }
    cout << ans <<"\n";
    return 0;
}