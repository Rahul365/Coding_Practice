#include<bits/stdc++.h>
using namespace std;
const int N = 200+2;
void print(int M[N][N],int n,int m){
    for(int i= 0;i<n;i++)
    {
        for(int j = 0;j<m;j++)
            cout<<M[i][j]<<" ";
        cout<<"\n";
    }
}
/***
 * https://csacademy.com/contest/junior-challenge-2017-day-2/task/cntgigelmat/solution/
 */
/*
0 -> up
1 -> left
2 -> upleft diagonal
3 -> right
4 -> down 
5 -> downright diagonal

*/

int UP = 0;
int LEFT = 1;
int LEFTUP = 2;
int RIGHT = 3;
int DOWN = 4;
int DOWNRIGHT = 5;
int reach[6][N][N];
int n,m;
int R[N+1];
int L[N+1];

/*O(n^2) time*/
void computedirections(int M[N][N]){
    for(int i = 0;i<n;i++){
        for(int j = 0;j<m;j++){
            if(i == 0 || j == 0)
            {
                reach[UP][i][j] = reach[LEFT][i][j] = reach[LEFTUP][i][j] = M[i][j];
            }
            else if(M[i][j] == 1){
                reach[UP][i][j] = 1 + reach[UP][i-1][j];
                reach[LEFT][i][j] = 1 + reach[LEFT][i][j-1];
                reach[LEFTUP][i][j] = 1 + reach[LEFTUP][i-1][j-1];
            }
        }
    }


    for(int i = n-1;i>=0;i--){
        for(int j = m-1; j>=0;j--){
            if(i == n-1 || j == m-1){
                reach[DOWN][i][j] = reach[RIGHT][i][j] = reach[DOWNRIGHT][i][j] = M[i][j];
            }
            else if(M[i][j] == 1){
                reach[DOWN][i][j] = 1  + reach[DOWN][i+1][j];
                reach[RIGHT][i][j] = 1 + reach[RIGHT][i][j+1];
                reach[DOWNRIGHT][i][j] = 1 + reach[DOWNRIGHT][i+1][j+1];
            }
        }
    }
}


void computeR(){
    //pending....
}

int main(){
    
    int mat[N][N] = {{1,1,1},{1,1,0},{1,1,1}};
    
    return 0;
}