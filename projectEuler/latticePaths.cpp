#include<bits/stdc++.h>
using namespace std;

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

int main(){
    cin>>n;//grid size n*n
    cout<<countpaths(n)<<"\n";
    return 0;
}