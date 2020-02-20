#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e6+1;
long long int pf[MAXN];
long long int sumsieve(){
    
    for(int i = 0;i<=MAXN;i++){
        pf[i] = i;
    }
    for(int i = 2;i<=MAXN;i+=2){
        pf[i] = 2;
    }
    long long int ans = 2;
    for(long long int i = 3;i<=MAXN;i+=2){
        if(pf[i] == i){
            ans+=i;
            for(long long int j = i*i;j<=MAXN;j+=i){
                if(pf[j] == j){
                    pf[j]  = i;
                }
            }
        }
    }
    return ans;
}

long long int sum(){
    int MAX = 2e6;
    long long int ans = 0;
    for(long long int i = 2;i<=MAX;++i){
        bool prime = true;
        for(long long int j = 2;j*j<=i;j++){
            if(i%j == 0)
            {
                prime = false;
                break;
            }
        }
        if(prime)
            ans += i;
    }
    return ans;
}

int main(){
    cout<<sum()<<"\n";
    cout<<sumsieve()<<"\n";
    return 0;
}