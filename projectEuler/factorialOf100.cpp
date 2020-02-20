#include<bits/stdc++.h>
using namespace std;

/**
 * calculate and print the factorial of n, where n=>[0,1000]
*/
const int MAXN = 2e5;
int res[MAXN];

void printfact(int n){
    memset(res,0,sizeof(res));
    res[0] = 1;
    int res_size = 1;//number of digits in the answer
    for(int x = 2 ;x<=n;x++){
        int carry = 0;
        for(int i =0 ;i<res_size || carry!=0;i++){
            int result = (res[i]*x)+ carry;
            carry = result/10;
            res[i] = result%10;
            if(i+1 > res_size)
                ++res_size;
        }
    }

    //print the factorial
    int st = res_size-1;
    while(st>=0){
        cout<<res[st--];
    }
    cout<<"\n";
}


int main(){
    printfact(20); 
    return 0;
}