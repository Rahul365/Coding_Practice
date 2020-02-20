#include<bits/stdc++.h>
#define ll long long int
using namespace std;
const int mod = 1e9 + 7;

int pow(int x,int y){
    int r = 1;
    while(y!=0){
        if(y&1) r = (r * x)%mod;
        y = y>>1;
        x = (x*x) %mod;
    }
    return r;
}

ll powlong(ll x,int y){
    ll r = 1;
    while(y!=0){
        if(y&1) r = r*x;
        y = y>>1;
        x = x*x;
    }
    return r;
}

int main(){
    int sum = 0;
    int arr[500];
    memset(arr,0,sizeof(arr));
    arr[0] = 1;
    for(int i =1 ; i<=1000;i++){
        arr[0] = 2*arr[0];
        for(int k = 1;k<500;k++){
          arr[k] = 2*arr[k] + arr[k-1]/10;
        }
        for(int j = 0 ;j<500;j++)
           arr[j] %=10;
    }
    
    for(int i = 0;i<500;i++)
        sum += arr[i];
    cout<<sum<<"\n";
    return 0;
}