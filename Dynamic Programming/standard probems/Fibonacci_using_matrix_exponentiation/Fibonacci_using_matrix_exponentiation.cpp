#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;


void multiply(long int A[2][2],long int B[2][2]){
    long int R[2][2];
    for(int i = 0;i<2;i++){
        for(int j = 0;j<2;j++){
            R[i][j] = 0;
            for(int k = 0;k<2;k++){
                R[i][j] = (R[i][j]+(A[i][k] * B[k][j]))%mod;
                // if(R[i][j] < 0)
                // R[i][j] -= mod;
            }
        }
    }
    
    for(int i =0;i<2;i++){
        for(int j =0;j<2;j++)
            A[i][j] = R[i][j];
    }
}


long int X[2][2];
void copy(long int A[2][2]){
    for(int i = 0;i<2;i++){
        for(int j =0;j<2;j++)
            X[i][j] = A[i][j];
    }
}

void pow(long int A[2][2],long int y){
    if(y == 0 || y == 1) return;
    pow(A,y/2);
    multiply(A,A);
    if(y&1){
        multiply(A,X);
    }
}

void powRec(long int A[2][2],long int y){
    copy(A);
    pow(A,y);
}

void powItr(long int A[2][2],long int y){
    long int R[2][2] = {{1,0},{0,1}};
    while(y!=0){
        if(y&1){
            multiply(R,A);
        }
        y >>=1;
        multiply(A,A);
    }
    for(int i = 0;i<2;i++){
        for(int j = 0;j<2;j++)
            A[i][j] = R[i][j];
    }
}

int main(){
    int t;
    cin>>t;
    while(t--){
        long int n;
        cin>>n;
        //here n =2  mean 2nd term which is 2
        long int A[2][2] = {{1,1},{1,0}};
        // powRec(A,n);
        powItr(A,n);
        int result = (A[0][0] + A[0][1])%mod;
        if(result < 0) 
            result += mod;
        cout<<result<<"\n";
    }
    return 0;
}