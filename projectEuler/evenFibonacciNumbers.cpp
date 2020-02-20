#include<bits/stdc++.h>
using namespace std;



int main(){
    long long int a = 1;
    long long int b = 2;
    long long int c = 0;
    long long int sum = 2;
    while(c <= 4000000)
    {
    
        c = a+b;
        a = b;
        b = c;
        sum += (c&1)?0:c;
        
    }
    cout<<sum<<"\n";
    return 0;
}