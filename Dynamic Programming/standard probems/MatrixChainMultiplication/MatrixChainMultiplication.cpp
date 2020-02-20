#include<bits/stdc++.h>
#define ll long long int
#define PII pair<ll,pair<int,int>>
using namespace std;


void calculateMatrix(long long int *p,int l){
        int n = l-1;//number of matrices
        long long int M[n+1][n+1];//cost of multiplying i to j matrices
        for(int i =1;i<=n;i++){
            M[i][i] = 0;//cost of multiplying one matrix
        }
        
        for(int length = 2;length<=n;length++){
            for(int i = 1;i<=(n-length+1);i++){
                int j = i+length-1;//length of matrix chain to multiply
                M[i][j] = LLONG_MAX;//Multiply Matrices i ... j
                for(int k = i;k<=j;k++){
                    long long int val = min(M[i][j],M[i][k] + M[k+1][j] + (p[i-1]*p[k]*p[j]));
                    if(val < M[i][j])
                        M[i][j] = val;
                }
            }
        }
        cout<<M[1][n]<<"\n";
}

int main()
{
    int t;
    cin>>t;
    
    while(t--){
        int chainlength;
        cin>>chainlength;//
        long long int p[chainlength];//chain of matrices
        for(int i = 0;i<chainlength;i++){
            cin>>p[i];
        }
        
        calculateMatrix(p,chainlength);
    }
	return 0;
}