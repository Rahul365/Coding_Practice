#include<bits/stdc++.h>
using namespace std;
const int N = 9;
int grid[N][N];

bool validgrid(){
    vector<vector<vector<int>>> dp(3,vector<vector<int>>(3,vector<int>(10,0)));
    //check every 3*3 block
    for(int i = 0;i<N;++i){
        for(int j = 0;j<N;++j){
            if(grid[i][j] && ++dp[i/3][j/3][grid[i][j]] > 1) return false;
        }
    }

    vector<int> cnt(10,0);
    for(int row = 0;row<N;++row){
        //check every row
        for(int col = 0;col < N;++col){
            if(grid[row][col] && ++cnt[grid[row][col]] > 1) return false;
        }
        fill(cnt.begin(),cnt.end(),0);
        //checking for every column too
        //here we consider (row,col) = (col,row)
        for(int col = 0;col < N;++col){
            if(grid[col][row] && ++cnt[grid[col][row]] > 1) return false;
        }
        fill(cnt.begin(),cnt.end(),0);
    }
    return true;
}

bool fillgrid(int r,int c){
    if(r == N) 
        return true;
    int next_r = r + ((c+1)%N == 0);
    int next_c = (c+1)%N;
    if(grid[r][c] == 0){
        for(int val = 1;val <= 9;++val){
            grid[r][c] = val;
            if(validgrid() && fillgrid(next_r,next_c)){
                return true;
            }
            grid[r][c] = 0;
        }
    }
    else{
        return fillgrid(next_r,next_c);
    }
    return false;
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int numberOfgrids;
    cin >> numberOfgrids;
    while(numberOfgrids--){
        cerr << "Enter the initial grid (values from 1-9 are for initialization and 0 for blank)\n";
        for(int i = 0;i<N;++i){
            cerr <<"ROW #:"<<(i+1)<<" : ";
            for(int j =0;j<N;++j){
                grid[i][j] = 0;
                cin >> grid[i][j];
                cerr << grid[i][j] << " \n"[j==N-1];
            }
        }

        if(fillgrid(0,0)){
            cout << "GRID is Solved\n";
            for(int r = 0;r < N;++r)
                for(int c = 0; c < N;++c)
                    cout << grid[r][c] << " \n"[c==N-1];
        }
        else{
            cout << "GRID is INVALID\n";
        }
    }
    return 0;
}