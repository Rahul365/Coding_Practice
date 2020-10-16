#include<bits/stdc++.h>
#define ll long long int
#define PII pair<ll,pair<int,int>>
using namespace std;
const int maxn =50;
int dp[maxn][maxn];
int grid[maxn][maxn];

int main()
{
    int t;
    scanf("%d",&t);
    while(t--){
        int r,c;
        scanf("%d%d",&r,&c);
        
        for(int i = 0;i<r;++i){
            for(int j = 0;j<c;++j){
                scanf("%d",&grid[i][j]);
                // cerr<<grid[i][j] <<" \n"[j==c-1];
            }
        }
        dp[r-1][c-1] = grid[r-1][c-1] > 0?1:(abs(grid[r-1][c-1])+1);
        for(int i = r-2;i>=0;--i){
            dp[i][c-1] = max(dp[i+1][c-1] - grid[i][c-1],1);
        }
        for(int i = c-2;i>=0;--i){
            dp[r-1][i] = max(dp[r-1][i+1] - grid[r-1][i],1);
        }
        for(int i = r-2;i>=0;--i){
            for(int j = c-2;j>=0;--j){
                int min_exit_pts = min(dp[i+1][j],dp[i][j+1]);
                dp[i][j] = max(min_exit_pts - grid[i][j],1);
            }
        }
        printf("%d\n",dp[0][0]);
    }
	return 0;
}