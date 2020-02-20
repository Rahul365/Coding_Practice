#include<bits/stdc++.h>
#define ll long long int
using namespace std;
const ll N = 1e8;
ll spf[N];
ll ans = 1;
int cnt = 10001;
vector<ll> prime;
/*can compute first 1229 prime numbers only*/
void pf(){
    
    for(int i = 0;i<N;i++){
        spf[i] = i;
    }
    // for(int i = 2;i<N;i+=2){
    //     spf[i] = 2;
    // }

    for(int i = 2;i*i<N;i++){
        if(spf[i] == i){
            ans = i;
            prime.push_back(i);
            --cnt;
            for(int j = i*i;j<N;j += i){
                if(spf[j] == j){
                    spf[j] = i;
                }
            }
        }
    }
}

void nthprime(){
//    int one =1;
    while(cnt > 0){
        ++ans;
        bool isprime = true;
        for(int i = 2;i<=sqrt(ans);i++){
            if(ans%i == 0){
                isprime = false;
                break;
            }
        }
        if(isprime) {
            prime.push_back(ans);
            // if(--one == 0)cout<<ans<<"\n";
          --cnt;
        }
    }
}

int main(){
    // pf();


    nthprime();
    
    cout<<prime[prime.size()-1]<<"\n";
    return 0;
}