#include<bits/stdc++.h>
using namespace std;

//  gcd(a,0) = a
//  gcd(a,b) = gcd(b, a mod b)
int gcd(int a,int b){
    while(b){
        int t = a%b;
        a = b;
        b = t;
    }
    return a;
}

int main(){
    cout<<gcd(3,34)<<"\n";
    return 0;
}