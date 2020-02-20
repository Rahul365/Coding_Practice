#include<bits/stdc++.h>
#define eps 0.09  //some epsilon value to define how close the precision value must be
using namespace std;

float findsqrt(float num){
    float l = 1,r = num;
    float ans;
    while(r-l > eps){
     float mid = l + (r-l)/2;
        if(mid * mid <= num){
            ans = mid;
            l = mid;
        }
        else{
            r = mid;
        }
    }
    return ans;
}


int main(){
    float num = 6;
    cout<<findsqrt(num)<<"\n";
    return 0;
}