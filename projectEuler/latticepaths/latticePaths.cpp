#include<bits/stdc++.h>
using namespace std;
/**
 * Starting in the top left corner of a 2×2 grid, and 
 * only being able to move to the right and down, 
 * there are exactly 6 routes to the bottom right corner.
 * How many routes are there in 20*20 grid?
 * 
*/
const int N = 100;
vector<vector<long long int>> grid(N,vector<long long int>(N,0));
int n;

bool issafe(int x,int y){
    return x>=0 && x<n && y>=0 && y<n;
}

long long int countpaths(int n){
    grid[0][0] = 2;//there are two ways to reach bottom right in 1*1 grid

    for(int i = 1;i<n;i++){
        grid[0][i] = grid[0][i-1] + 1;//number of ways to reach ith cell from 1st cell  = (number of ways to reach (i-1)th cell of 1st row) + 1;
        grid[i][0] = grid[i-1][0] + 1;//vice versa
    }
    for(int i = 1;i<n;i++){
        for(int j = 1;j<n;j++){
            grid[i][j] = grid[i][j-1] + grid[i-1][j];
        }
    }

    return grid[n-1][n-1];
}


long long int countpathsUsingBinomials(int n){
    long long int pascaltrianlge[2][2*n+1];
    memset(pascaltrianlge,0,sizeof(pascaltrianlge));
    pascaltrianlge[0][0] = 1;
    
    //so to get the number of paths for n*n grid
    //ans = pascaltriangle[row][col] where  row = 2*n and col = n

    for(int row  = 1;row<=2*n;++row){
        for(int col = 0;col<=row;col++){
            pascaltrianlge[row%2][col] = pascaltrianlge[(row+1)%2][col] + (col>0?pascaltrianlge[(row+1)%2][col-1]:0);
        }
    }

    return pascaltrianlge[(2*n)%2][n];
}

int main(){
    cin>>n;//grid size n*n
    cout<<countpaths(n)<<"\n";
    cout<<countpathsUsingBinomials(n)<<"\n";
    return 0;
}