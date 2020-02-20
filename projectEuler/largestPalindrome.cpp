#include<bits/stdc++.h>
#define ll long long int
using namespace std;

/*
    largest palindrome made from the product of two digit numbers is 91 * 99 = 9009
    find the largest palindrom made from the product three digit numbers.
*/

bool palindrome(ll x){
    ll rev = 0;
    ll t = x;
    while(x){
        rev = rev * 10   + x%10;
        x = x/10;
    }
    return t == rev;
}

ll largestpalindromethreedigits(){
    ll ans = 0;
    for(ll i = 999;i>=100;i--){
        for(ll j =  i;j>=100;j--){
            if(palindrome(i*j)){
                ans = max(ans,i*j);
                break;
            }
        }
    }
    return ans;
}

int main(){
    cout<<largestpalindromethreedigits()<<"\n";
    return 0;
}