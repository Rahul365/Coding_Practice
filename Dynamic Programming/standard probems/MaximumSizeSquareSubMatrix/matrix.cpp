#include<bits/stdc++.h>
using namespace std;
const int M = 100;
const int N = 100;

int B[M][N];//matrix of 0's and 1's
int L[M][N];//sum matrix to store the maximum dimension of subsquare

void printMaxSquareSubMatrix(int m,int n){
    // //copy the first column
    // for(int i = 0;i<m;i++){
    //     L[i][0] = B[i][0];
    // }
    // //copy the first row
    // for(int i = 0;i<n;i++){
    //     L[0][i] = B[0][i];
    // }
    
    int maxentry = 0;
    int max_x = 0;
    int max_y = 0;
    for(int i = 0;i<m;i++){
        for(int j = 0;j<n;j++){
            if(i ==0 || j == 0){
                L[i][j] = B[i][j];
            }
            else if(B[i][j]){
                L[i][j] = min(L[i][j-1],min(L[i-1][j-1],L[i-1][j]))  + 1;
            }
            else{
                L[i][j] = 0;
            }
            if(maxentry < L[i][j]){
                maxentry = L[i][j];
                max_x = i;
                max_y = j;
            }
        }
    }

    cout<<"Size : "<< maxentry<<" , Coordinates : ("<<max_x<<","<<max_y<<")"<<"\n";
    for(int i = max_x - maxentry+1 ; i <= max_x;i++){
        for(int j = max_y - maxentry+1 ; j <= max_y;j++){
            cout<<B[i][j]<<" ";
        }
        cout<<"\n";
    }
}
/*Space O(COLS)*/
void computeMaxSquareSubMatrixArea(int n,int m){
        int dp[m];
        int prev = 0;
        int ans = 0;
        memset(dp,0,sizeof(dp));
        for(int i = 0;i<n;i++){
            for(int j = 0;j<m;j++){
                int temp = dp[j];//prev row's cell L(i-1,j-1)
                if(i == 0){
                    dp[j] = (B[i][j] == '1');
                }
                else if(B[i][j] == '1'){
                    dp[j] = 1 + min(j>0?dp[j-1]:0,min(prev,dp[j]));
                }
                else{
                    dp[j] = 0;
                }
                ans = max(ans,dp[j]);
                prev = temp;
            }
        }
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int m;
    int n;
    cin>>m>>n;
    for(int i = 0;i<m;i++)
        for(int j = 0;j<n;j++)
            cin>>B[i][j];
    printMaxSquareSubMatrix(m,n);
    return 0;
}