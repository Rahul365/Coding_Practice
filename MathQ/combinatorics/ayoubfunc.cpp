#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
long long int count(int n){
    return (1LL*n*(n+1))/2;
}

// https://codeforces.com/problemset/problem/1301/C

int main(){
    int t;
    cin >> t;
    while(t--){
        int n,m;
        cin >> n >> m;
        ll answer = count(n);
        /*
            1) total number of substrings  = n*(n+1)/2
            2)Number of substring with no symbol '1'
            If we want to calculate such substring we need to find only contiguos substrings of 0's only
            e.g. if l is the length of such substring , then we substract only l*(l+1)/2
        Given m be the number of 1's.
           If we have (n-m) 0's ,then we need to divide them into g = m+1 groups
           The goal is to minimize it as much as possible and can be acheived by dividing into groups as equal as possible
           let k = (n-m)/g groups
           k*(k+1)/2 be the number of groups of substrings with no symbol '1'
           Then also there will be a group of 0's left after with size will have k+1 zeroes
        */
       int k = (n-m)/(m+1);//number of 0's to be divided among g groups as equally as possible 
       answer -= count(k)*(m+1);//for every  group with k zeroes
       answer -= (k+1)*((n-m)%(m+1));//the last group may have size (k+1)
       cout << answer <<"\n";
    }
    return 0;
}