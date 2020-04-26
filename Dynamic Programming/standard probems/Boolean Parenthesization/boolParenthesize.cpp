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
const int mod = 1003;

void addself(int &a,int b){
    a = (a + b)%mod;
}

int num_ways(string &exp,string &opr){
    const size_t n = exp.size();
    int T[n][n];
    int F[n][n];
    for(int i = 0;i<n;++i){
        T[i][i] = exp[i] == 'T';
        F[i][i] = exp[i] == 'F';
    }
    //T F T F
    // | & ^
    for(int len = 2;len <= n;++len){
        for(int i = 0;i<=n-len;++i){
            int j = i + len-1;
            //cout << i << " " <<j<<" : ";
            T[i][j] = F[i][j] = 0;
            for(int k = i;k < j;++k){//position of the operator
                //cout << k <<" ?? ";
                int tik = T[i][k] + F[i][k];
                int tkj = T[k+1][j] + F[k+1][j];
                if(opr[k] == '&'){
                    addself(T[i][j],T[i][k] * T[k+1][j]);
                    addself(F[i][j],tik * tkj - T[i][k]*T[k+1][j]);
                }
                else if(opr[k] == '|')
                {
                    addself(F[i][j],F[i][k]*F[k+1][j]);
                    addself(T[i][j],tik*tkj - F[i][k]*F[k+1][j]);
                }
                else if(opr[k] == '^')
                {
                    addself(T[i][j],T[i][k]*F[k+1][j] + F[i][k]*T[k+1][j]);
                    addself(F[i][j],T[i][k]*T[k+1][j] + F[i][k]*F[k+1][j]);
                }
            }
           // cout<<"\n";
        }
    }
    return T[0][n-1];
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
        cout<<num_ways(expression,operators)<<"\n";
    }
    return  0;
}