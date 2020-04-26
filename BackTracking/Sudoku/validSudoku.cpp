#include<bits/stdc++.h>
using namespace std;


class Solution {
public:
    const int R = 9;
    const int C = 9;
    bool rowcheck(const vector<vector<char>> &board){
        int cnt[10];
        for(int r = 0;r < R;++r){
            memset(cnt,0,sizeof cnt);
            for(int i = 0;i<C;++i){
                if(board[r][i]=='.') continue;
                if(++cnt[board[r][i]-'0'] == 2) return false;
            }
        }
        return true;
    }
    
    bool colcheck(const vector<vector<char>>&board){
        int cnt[10];
        for(int c = 0;c < C;++c){
            memset(cnt,0,sizeof cnt);
            for(int i = 0;i<R;++i){
                if(board[i][c]=='.') continue;
                if(++cnt[board[i][c]-'0']==2) return false;
            }
        }
        return true;
    }
    
    bool cellcheck(const vector<vector<char>> &board){
        vector<vector<vector<int>>> cnt(R,vector<vector<int>>(C,vector<int>(10,0)));
        for(int i = 0;i<R;++i){
            for(int j = 0;j<C;++j){
                if(board[i][j] == '.') continue;
                if(++cnt[i/3][j/3][board[i][j]-'0']==2) return false;
            }
        }
        return true;
    }
    
    bool isValidSudoku(vector<vector<char>>& board) {
        //rowcheck
        if(!rowcheck(board)) return false;
        if(!colcheck(board)) return false;
        if(!cellcheck(board)) return false;
        //colcheck
        //3*3 cell check
        return true;
    }
};  

int main(){

    return 0;
}