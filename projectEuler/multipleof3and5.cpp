#include<bits/stdc++.h>
using namespace std;


int main(){
    int N = 1000;

    // int ans = 0;
    // while(N--!=0){
    //     if(N%3 == 0 || N%5 == 0){
    //         ans+=N;
    //     }
     
    // }
    // cout<<ans<<"\n";
    int t[N];
    memset(t,0,sizeof(t));
    
    for(int i = 3;i<N;i++){
        t[i] = t[i-1];
        if(i%3==0 || i%5 == 0)
         t[i]+=i;
        
    }
    cout<<t[N-1]<<"\n";
    return 0;
}