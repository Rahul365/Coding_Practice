#include<bits/stdc++.h>
using namespace std;

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

int main(){
    long long  n;
    scanf("%lld",&n);
    auto res = countdivisors(n);
    printf("%lld %lld\n",res.first , res.second);
    return 0;
}