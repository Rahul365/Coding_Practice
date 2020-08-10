#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+11;
const long long int inf = 1e18+1;
const int LG = 20;
const int K = 501;
vector<int> g[maxn];
int n,k;
long long int answer = 0;
long long int dp[maxn][K];
// https://codeforces.com/contest/161/problem/D
template<typename T>
T infv(T val){
    return val == inf? 0 : val;
}

void init(){
    for(int i= 0;i<maxn;++i)for(int j = 0;j<K;++j) dp[i][j] = 0LL;
    function<void(int,int)> dfs = [&](int u,int p){
        dp[u][0] = 1;
        for(int v : g[u]){
            if(v == p) continue;
            dfs(v,u);
            for(int i = 1;i<=k;++i)
                dp[u][i] += dp[v][i-1];
        }
    };
    
    long long int sub = 0LL;
    function<void(int,int)> dfsii =[&](int u,int p){
        answer += dp[u][k];
        for(int v : g[u]){
            if(v == p) continue;
            dfsii(v,u);
            for(int x = 1;x <= k-1;++x){
                //(number of nodes at distance x from node u in the subtree of it's child v) * (total number of nodes at remaining distance (k-x) in subtree of node u excluding the child v)
                sub += dp[v][x-1]* (dp[u][k-x] - dp[v][k-x-1]);
            }
        }
    };
    dfs(1,0);
    dfsii(1,0);
    //(sub/2) because the number of pairs are unordered
    answer += sub>>1;
    // for(int i = 1;i<=n;++i)
    // { 
    //     cerr << i << " : "; for(int j = 0;j<=k;++j) cerr << dp[i][j] <<" \n"[j==k];
    // }
}

int main(){
    scanf("%d%d",&n,&k);
    for(int i = 0;i<n-1;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    answer = 0LL;
    init();
    printf("%lld\n",answer);
    return 0;
}