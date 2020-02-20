#include<bits/stdc++.h>
using namespace std;
const int MAXN = 837799;
//rules
//n to  n/2 if n is even
//n to 3*n+1 if n is odd


int main(){
   
    int ans = 0;
    int maxlen = 0;
   

   for(int i = MAXN;i>=1;i--){
       int len = 0;
       long long  n  = i;
       while(n > 1){
           ++len;
           if(n&1) n = 3*n+1;
           else n = n>>1;
       }
   
       if(maxlen < len){
           ans = i;
           maxlen = len; 
       }
   }
  
   cout<<ans<<"\n";
   cout<<maxlen<<"\n";
   return 0;
}