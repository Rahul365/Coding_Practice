#include<bits/stdc++.h>
#define ll long long int
using namespace std;

int gcd(int a,int b){
    while(b){
        int t = a%b;
        a = b;
        b = t;
    }
    return a;
}

/*
    totient(n) = count(all numbers k in the range [1,n] such that gcd(k,n)==1)
*/
int phiI(int n){
    int phi = 1;
    for(int i = 2;i<n;i++){
        phi += (gcd(i,n)==1);
    }
    return phi;
}

/*
    totient(n) = n * product(1 - 1/p) such that p is divisor of n
*/
int phiII(int n){
    float phi = n;
    for(int p = 2;p*p<=n;++p){
        if(n%p == 0){
            while(n%p == 0) n/=p;
            phi *= (1.0 - (1.0/(float)p));
        }
    }
    //if n has prime factor > n
    if(n > 1){
        phi *= (1.0 - (1.0/(float)n));
    }
    return (int)phi;
}
//to avoid the float values
int phiIII(int n){
    int phi = n;
    for(int  p =2;p*p<=n;++p){
        if(n%p == 0){
            phi -= (phi/p);
            while(n%p == 0) n/=p;
        }
    }
    if(n > 1){
        phi -= (phi/n);
    }
    return phi;
}


const ll MAXN = 1e5+1;
vector<ll> p;
void simpleseive(){
    vector<bool> isprime(MAXN,true);
    for(ll n = 2;n<=MAXN;++n){
        if(isprime[n]){
            p.push_back(n);
            for(ll m = n*2;m<=MAXN;m+=n){   
                isprime[m] = false;
            }
        }
    }
}


ll phiIV(ll n){
    ll result = n;
    for(ll i = 0;p[i]*p[i] <= n;++i){
        if(n%p[i]==0){
            result -= result/p[i];
            while(n%p[i]==0) n/=p[i];
        }
    }
    if(n > 1){
        result -= result/n;
    }
    return result;
}

//compute n <= N such that ratio n/phi(n) is maximum possible
// phi(n) = n * productof((p-1)/p)
// n/phi(n) = productof(p/(p-1)) where k = 1 to n and p is prime which divides n
// n = productof(p/(p-1)) * phi(n)
//so all that's left is to minimize the product (p-1)/p  such that p divides n
/*
    returns a number x <= n 
    such that ratio (x/phi(x)) is maximum for all x = 1 to x<=n
*/
ll findn(ll n){
    ll res = 1;
    for(ll v : p){
        if(res * v <= n){
            res *= v;
        }
    }
    return res;
}

int main(){
    simpleseive();
    for(ll i = 1;i<=10;i++){
        cout<<phiI(i)<<" "<<phiII(i)<<" "<<phiIII(i)<<" "<<phiIV(i)<<" "<<findn(i)<<"\n";
    }
    return 0;
}