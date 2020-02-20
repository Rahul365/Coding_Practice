#include<bits/stdc++.h>
#define ll long long int
using namespace std;
const int N = 1E7;
int pf[N+1];//stores the smallest prime factor of a NUMBER

void pfs(){
    //WORKS WELL UPTO 10^7 ,ABOVE THAT FACES MEMORY ISSUES
    for(int i = 0;i<=N;i++){
        pf[i] = i;
    }
    //initialize the prime factor for numbers which are multiple of 2
    for(int i = 2;i<=N;i+=2){
        pf[i] = 2;
    }

    for(int i = 3;i*i<=N;i++){
        if(pf[i] == i){
            for(int j = i*i;j<=N;j+=i){
                if(pf[j] == j)
                    pf[j] = i;
            }
        }
    }
}

void printPFS(int n){
    if(n <= 1) return;
    int t = 0;
    while(n!=1){
        cout<<pf[n]<<" ";
        n = n/pf[n];
    }
    cout<<"\n";
}


/**
 * Following are the steps to find all prime factors.
1) While n is divisible by 2, print 2 and divide n by 2.
2) After step 1, n must be odd. Now start a loop from i = 3 to square root of n. While i divides n, print i and divide n by i. After i fails to divide n, increment i by 2 and continue.
3) If n is a prime number and is greater than 2, then n will not become 1 by above two steps. So print n if it is greater than 2.
*/
void printPrimeFactors(long long int n){
    while(n%2 == 0){
        cout<<2<<" ";
        n/=2;
    }
    //N MUST BE ODD HERE
    for(long long int i = 3;i<=sqrt(n);i+=2)
    {
        while(n%i == 0)
        {
            cout<<i<<" ";
            n/=i;
        }

    }

    if(n > 2){
        cout<<n<<" ";
    }
    cout<<"\n";
}




ll largestprimefactor(ll n){
    ll ans = 2;
    while(n%2 == 0){
        ans = 2;
        n/=2;
    }
    
    for(ll i = 3;i<=sqrt(n);i+=2){
        while(n%i == 0){
            ans = max(ans,i);
            n/=i;
        }
    }
    if(n > 2){
        ans = max(ans,n);
    }
    return ans;
}

int main(){
    pfs();
    printPFS(13195);
    
    long long int n = 13195;
 
    // printPFS(n);
    printPrimeFactors(n);
    return 0;
}