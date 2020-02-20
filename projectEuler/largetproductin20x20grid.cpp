#include<bits/stdc++.h>
using namespace std;



int main(){
    freopen("grid.txt","r",stdin);
    freopen("grid_output.txt","w",stdout);
    long long int ans = 0;
    int n = 20;
    long long int grid[n][n];
    for(int i =0;i<n;i++){
        for(int j = 0;j<n;j++){
            cin>>grid[i][j];
        }
    }

    for(int i  = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            if(i >= 3){
                //up direction
                ans = max(ans, grid[i][j] * grid[i-1][j] * grid[i-2][j] * grid[i-3][j]);
            }
            if(j >= 3)
            {
                //left direction
                ans = max(ans, grid[i][j] * grid[i][j-1] * grid[i][j-2] * grid[i][j-3]);
            }

            if(i >= 3 && j >=3){
                //up left diagonal
                ans = max(ans,grid[i][j] * grid[i-1][j-1] * grid[i-2][j-2] * grid[i-3][j-3]);
            }
            if(i>=3 && j < n-3){
                //up right diagonal
                ans = max(ans,grid[i][j] * grid[i-1][j+1] * grid[i-2][j+2] * grid[i-3][j+3]);
            }
        }
    }
    cout<<ans<<"\n";
    return 0;
}