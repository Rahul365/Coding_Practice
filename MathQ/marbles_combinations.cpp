#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
const int maxn = 1e5+1;
const int mod = 1e9 + 7;
template<typename T>
T gcd(T a, T b){
    while(b){
        T t = a%b;
        a = b;
        b = t;
    }
    return a;
}


void printNcR(ll n, ll r) 
{ 
    // p holds the value of n*(n-1)*(n-2)..., 
    // k holds the value of r*(r-1)... 
    ll p = 1, k = 1; 
    // C(n, r) == C(n, n-r), 
    // choosing the smaller value 
    if (n - r < r) 
        r = n - r; 
  
    while (r) { 
        p *= n; 
        k *= r; 

        // gcd of p, k 
        ll m = gcd(p, k); 

        // dividing by gcd, to simplify product 
        // division by their gcd saves from the overflow 
        p /= m; 
        k /= m; 

        n--; 
        r--; 
    } 

        // k should be simplified to 1 
        // as C(n, r) is a natural number 
        // (denominator should be 1 ) . 
    // if our approach is correct p = ans and k =1 
    printf("%lld\n",p);
} 


// https://math.stackexchange.com/questions/849243/counting-problem-selecting-n-objects-among-k-infinite-collections
// https://www.mathsisfun.com/combinatorics/combinations-permutations.html
int main(){
    // computefact();
    int t;
    scanf("%d",&t);
    //since we have infinte set to choose from 
    // nCr => we have n = k and r = n-k
    // (n+r-1)Cr => (k + n-k-1)C(n-k) => (n-1)C(n-k)
    while(t--){
        ll n,k;
        scanf("%lld%lld",&n,&k);
        printNcR(n-1,n-k);
    }
    return 0;
}