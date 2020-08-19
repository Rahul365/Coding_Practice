#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
//https://codeforces.com/problemset/problem/322/B
int main(){
    ll r,g,b;
    scanf("%lld%lld%lld",&r,&g,&b);
    ll answer = 0;
    for(int i = 0;i<3;++i)
    if(r-i >= 0 && g-i>=0 && b-i>=0)
    answer = max(answer,i + (r-i)/3 + (g-i)/3 + (b-i)/3);
    printf("%lld\n",answer);
    return 0;
}