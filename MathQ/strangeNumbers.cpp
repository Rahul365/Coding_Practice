#include<bits/stdc++.h>
using namespace std;
//https://www.codechef.com/APRIL20B/problems/STRNO
template<typename T>
pair<T,T> countdivisors(T num){
    T ans = 1;
    T primes  = 0;
    for(T i = 2 ; i*i <= num;++i)
    {
        if(num%i == 0){
            T occ = 1;
            ++primes;
            while(num%i == 0){
                ++occ;
                num/=i;
            }
            ans *= occ;
        }
    }
    if(num > 2){
        ans *= 2;
        ++primes;
    }
    return {ans,primes};
}
/*Count the total number of primes in which X can be represented*/
template<typename T>
T countPowers(T num){
    T ans = 0;
    for(T i = 2 ; i*i <= num;++i)
    {
        if(num%i == 0){
            while(num%i == 0){
                ++ans;
                num/=i;
            }
        }
    }
    if(num > 2){
        ++ans;
    }
    return ans;
}

int main()
{
    int t;
    scanf("%d",&t);
    while(t--){
        long long int x,k;
        scanf("%lld%lld",&x,&k);
        bool ok  = countPowers(x) >= k;
        if(ok){
            puts("1");
        }
        else{
            puts("0");
        }
    }
    return 0;
}