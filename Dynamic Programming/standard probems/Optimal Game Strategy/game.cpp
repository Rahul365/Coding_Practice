#include<bits/stdc++.h>
using namespace std;


/**
 * Given n number of coins.
 * There are two players and they are playing a game in alternative turns.
 * In each turn ,a player can pick a coin from either and end of array and remove it from the selected end.
 * Find the max Amount you can make if you take the first turn.
 * 
*/
int pick(int *v,int i,int j){
    if(i >= j)
        return 0;
    
    int pickI = min(pick(v,i+1,j-1),pick(v,i+2,j)) + v[i];
    int pickJ = min(pick(v,i+1,j-1),pick(v,i,j-2)) + v[j];

    return max(pickI,pickJ);
}

int memo[1000][1000];//initialize all cells with value -1
void init(int n){
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++)
        {
            memo[i][j] = -1;
        }
    }
}

int pickMemoDP(int *v,int i,int j){
    if(i >= j)
        return 0;
    int &ans = memo[i][j];

    if(ans!=-1)
        return ans;
    ans = 0;
    int pickI = min(pick(v,i+1,j-1),pick(v,i+2,j)) + v[i];
    int pickJ = min(pick(v,i+1,j-1),pick(v,i,j-2)) + v[j];
    ans = max(pickI,pickJ);
    return ans;
}


int pickMAX(int *v,int n){
    int dp[n][n];

    for(int gap = 0;gap < n;gap++){
        for(int i = 0,j = gap;j<n;i++,j++){
            int x = (i+1 <= j-1)?dp[i+1][j-1]:0;
            int a = (i+2<=j)?dp[i+2][j]:0;
            int b = (i <= j-2)?dp[i][j-2]:0;
            dp[i][j] = max(min(a,x) + v[i],min(x,b) + v[j]);
        }
    }
    return dp[0][n-1];
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        int v[n];
        for(int i  = 0;i<n;i++)
            cin>>v[i];
        init(n);
        cout<<pickMAX(v,n)<<"\n";
        cout<<pickMemoDP(v,0,n-1)<<"\n";
        cout<<pick(v,0,n-1)<<"\n";
    }
    return 0;
}