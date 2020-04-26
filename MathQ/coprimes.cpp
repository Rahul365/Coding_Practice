#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6+11;
//https://www.codechef.com/APRIL20B/problems/UNITGCD
vector<int> prime;
vector<bool> isprime(maxn,true);
vector<bool> used(maxn,false);
void seive(){
    for(int i = 2;i*i<maxn;++i){
        if(isprime[i]){
            prime.push_back(i);
            for(int j = i*2;j<maxn;j+=i){
                isprime[j] = false;
            }
        }
    }
}


vector<int> factors(int n){
    vector<int> ans;
    for(int p : prime){
        if(p*p > n) break;
        if(n%p == 0){
            while(n%p == 0){
                n/=p;
            }
            ans.push_back(p);
        }
    }
    return ans;
}

int main(){
    seive();
    int t;
    scanf("%d",&t);
    while(t--){
        fill(used.begin(),used.end(),false);
        int n;
        scanf("%d",&n);
        if(n == 1){
            puts("1");
            printf("1 1\n");
        }
        else{
            printf("%d\n",n/2);
            vector<int> line;
            //aint primes
            line.push_back(1);
            for(int  p : prime){
                if(p > n) break;
                used[p] = true;
                line.push_back(p);
            }
            printf("%d ",line.size());
            for(int p  : line){
                printf("%d ",p);
            }
            printf("\n");
            line.clear();
            // aint consecutive pairs
            for(int i = 2;i <= n;)
            {
                if(i <  n && !used[i] && !used[i+1]){
                    used[i] = used[i+1] = true;
                    printf("2 %d %d\n",i,i+1);
                    i+=2;
                    continue;
                }
                if(!used[i]){
                    used[i] = true;
                    printf("1 %d\n",i);
                }
                ++i;
            }

        }
    }
    return 0;
}