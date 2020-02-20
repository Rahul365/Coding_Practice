#include<bits/stdc++.h>
using namespace std;

int gcd(int a,int b)
{   
    if(a == 0) return b;
    return gcd(b%a,a);
}

int gcdI(int a,int b){
    while(a!=0){
        int t = b%a;
        b = a;
        a = t;
    }
    return b;
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int t;
    cin>>t;
    while(t--){
        int a,b;
        cin>>a>>b;
      if(gcdI(a,b)!=1) cout<<"Infinite\n";
      else cout<<"Finite\n";
    }
    return 0;
}