#include<bits/stdc++.h>
using namespace std;
const int mod = 1003;

/**
 Given a boolean expression with following symbols.

 Symbols
    'T' ---> true
    'F' ---> false

 And following operators filled between symbols

 Operators
    &   ---> boolean AND
    |   ---> boolean OR
    ^   ---> boolean XOR

 Count the number of ways we can parenthesize the expression so that the value of expression evaluates to true.

For Example:
The expression is "T | T & F ^ T", it evaluates true
in 4 ways ((T|T)&(F^T)), (T|(T&(F^T))), (((T|T)&F)^T)
and (T|((T&F)^T)).

Return No_of_ways Mod 1003.
*/
int num_ways(string exp,string opr,int n){
    int T[n][n];
    int F[n][n];
    for(int i = 0;i<n;i++){
        if(exp[i]=='T'){
            T[i][i] = 1;
            F[i][i] = 0;
        }
        else{
            T[i][i] = 0;
            F[i][i] = 1;
        }
    }
    
    for(int gap = 1;gap<n;++gap){
        for(int i = 0,j = gap;j<n;i++,j++){
            T[i][j] = F[i][j] = 0;
            for(int g = 0;g<gap;g++){
                int k = i + g;
                int tik = T[i][k] + F[i][k];
                int tkj = T[k+1][j] + F[k+1][j];
                
                if(opr[k] == '&'){
                    T[i][j] += (T[i][k] * T[k+1][j])%mod;
                    F[i][j] += (tik*tkj - T[i][k] * T[k+1][j])%mod;
                }
                else if(opr[k] == '|'){
                    T[i][j] += (tik*tkj - F[i][k]*F[k+1][j])%mod;
                    F[i][j] += (F[i][k]*F[k+1][j])%mod;
                }
                else if(opr[k] == '^'){
                    T[i][j] += (T[i][k]*F[k+1][j] + F[i][k]*T[k+1][j])%mod;
                    F[i][j] += (T[i][k]*T[k+1][j] + F[i][k]*F[k+1][j])%mod;
                }
            }
        }
    }
    return T[0][n-1]%mod;
}


int main(){
    int t;
    cin>>t;
    while(t--){
        int n;
        cin>>n;
        string expression ="";
        string operators = "";
        char ch;
        for(int i = 0;i<n;i++){
            cin>>ch;
            if(ch == '&' || ch=='|' || ch=='^'){
                operators+=ch;
            }
            else{
                expression+=ch;
            }
        }
        cout<<num_ways(expression,operators,expression.length())<<"\n";
    }
    return  0;
}