#include<bits/stdc++.h>
using namespace std;
const int mod = 1e9+7;
long int a,b,c,n,m;
long int C[3][3];//copy of original matrix

void copy(long int A[3][3]){
    for(int i = 0;i<3;i++){
        for(int j = 0;j<3;j++){
            C[i][j] = A[i][j];
        }
    }
}

void multiply(long int A[3][3],long int B[3][3]){
    long int M[3][3];
    for(int i = 0;i<3;i++){
        for(int j=0;j<3;j++){
            M[i][j] = 0;
            for(int k = 0;k<3;k++){
                M[i][j]  = (M[i][j] + (A[i][k]*B[k][j]))%m;
            }
        }
    }
    
    for(int i = 0;i<3;i++){
        for(int j = 0;j<3;j++){
            A[i][j] = M[i][j];
        }
    }
}


void powrec(long int A[3][3],int y){
    if(y == 0 || y == 1) 
        return;
        
    powrec(A,y/2);
    
    multiply(A,A);
    
    if(y&1){
        multiply(A,C);
    }
}

void powit(long int A[3][3],int y){
    long int R[3][3] = {
        {1,0,0},{0,1,0},{0,0,1}
    };
    
    while(y!=0){
        if(y&1){
            multiply(R,A);
        }
        y=y/2;
        multiply(A,A);
    }
    
    for(int i = 0;i<3;i++){
        for(int j = 0;j<3;j++){
            A[i][j] = R[i][j];
        }
    }
}

long int solve(){
    cin>>a>>b>>c>>n>>m;
    if(n<=3){
        if(n==3)
            return (a+b+c)%m;
        return 1;
    }
    
    long int A[3][3] = {
        {a+1,b-a,-b}
        ,{1,0,0}
        ,{0,1,0}
    };
    
    // Iterative exponentiation
    // powit(A,n-3);
    // Recursive Exponentiation
    copy(A);
    powrec(A,n-3);
    
    // for(int i= 0;i<3;i++){
    //     for(int j=0;j<3;j++)
    //     {
    //         cout<<A[i][j]<<" ";
    //     }
    //     cout<<"\n";
    // }
    long int result = ((A[0][0]*(a+b+c)) + A[0][1] + A[0][2])%m;
    /**
     * In most of programming languages when you perform modulo operation on negative number
     * like -5%3 = -2 but the result you get in programming language is -5%3 = -1.
     * So to take care of that convert the result to it's modulo equivalent.
     */
    return result < 0? result+m:result;
}


int main(){
    int t;
    cin>>t;
    while(t--){
        cout<<solve()<<"\n";
    }
    return 0;
}