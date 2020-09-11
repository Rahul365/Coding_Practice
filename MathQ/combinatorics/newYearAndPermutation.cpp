#include<bits/stdc++.h>
using namespace std;
const int maxn = 3e5+1;
// https://codeforces.com/problemset/problem/1284/C
int main(){
    int n;
    long long int m;
    cin >> n >> m;
    long long int fact[n+1];
    fact[0] = 1;
    for(long long i = 1;i<=n;++i){
        fact[i] = (1LL * i * fact[i-1])%m;
    }
    long long answer = 0;
    for(int gap = 0;gap < n;gap++){
        /*
        let r-l = gap
        number of such pairs are (n-gap)
        number of ways to arrange these (gap + 1)elements  = (gap+1)!
        So we have (n-gap) * (gap+1)! framed subsegments such that max(segment) - min(segment) = r-l
        Nows let consider this subsegment as single element
        so we have total n-(gap+1)+1 elements 
        And there are (n - (gap + 1) + 1)! ways to permutate them
        And also 0<=gap <= n-1
         for gap = 0 to n-1
         answer += Sum((n-gap)*(gap+1)! * (n-(gap+1)+1)!)%m 
        */
        long long int A = ((n-gap)*fact[gap+1])%m;
        long long int B = fact[n-(gap+1)+1];
        //cerr << (A * B) <<"\n";
        answer = (answer + (A * B)%m)%m;
    }
    cout << answer <<"\n";
    return 0;
}