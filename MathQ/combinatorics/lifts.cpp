#include <bits/stdc++.h>
#define fastio ios_base::sync_with_stdio(false); cin.tie(0)
using namespace std;
using ll = long long int;
const int mod = 1e9+7;
const int N = 5004;
template<typename T>
void addself(T &a,T b){
    a+=b;
    /*using modulus(%) operator here causes TLE > 2 secs*/
    if(a >= mod) a-=mod;
    if(a < 0) a+=mod;
}

ll dp[2][N];

void solve(int n,int a,int b,int k){
    memset(dp,0LL,sizeof dp);
    clock_t time_req = clock();
    vector<int> movesf(n+1),movesb(n+1);
    if(a > b){
        /*mirror a and b such that a < b*/
        a = n-a+1;
        b = n-b+1;
    }
    
    for(int i = b-1;i>=1;--i){
        movesf[i] = abs(i-b)-1;
        movesb[i] = min(abs(i-b)-1,i-1);
    }
    for(int i = 1;i<b;++i) dp[k&1][i] = 1;
    for(int trips = k-1;trips>=0;--trips){
        int prev = (trips&1)^1;
        int curr = (trips&1);
        for(int floor = 1;floor<b;++floor){
            dp[curr][floor] = 0;
            addself(dp[prev][floor],dp[prev][floor-1]);
        }
        for(int floor = 1;floor<b;++floor){
                int L = movesf[floor];
                int R = movesb[floor];
                if(L){
                    addself(dp[curr][floor],dp[prev][floor+L]);
                    addself(dp[curr][floor],-dp[prev][floor]);
                }
                if(R){
                    addself(dp[curr][floor],-(floor-R?dp[prev][floor-R-1]:0));
                    addself(dp[curr][floor],dp[prev][floor-1]);
                }
        }
       }

    
    printf("%lld\n",dp[0][a]);
    fprintf(stderr, "%lld\n", dp[0][a]);
	fprintf(stderr, "%f\n", (float)(clock()-time_req)/CLOCKS_PER_SEC);
}
// https://codeforces.com/problemset/problem/479/E
int main()
{
    int n,a,b,k;
    scanf("%d%d%d%d",&n,&a,&b,&k);
    solve(n,a,b,k);
    return 0;
}