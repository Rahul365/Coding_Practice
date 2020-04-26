#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
const int mod = 10000003;

ll ispossible(vector<int> &c,ll total_time){
    int painters = 1;
    ll sum = 0;
    for(int i= 0;i<(int)c.size();++i){
        if(sum + c[i] > total_time){
            ++painters;
            sum = 0;
        }
        sum += c[i];
    }
    return painters;
}

int paint(int a,int b,vector<int> c){
    const int n = c.size();
    ll lower_time = c[0];
    ll upper_time = c[0];
    for(int i = 1;i<n;++i){
        lower_time = max(1LL*c[i],lower_time);
        upper_time += (1LL*c[i]);
    }
    ll ans = 0;
    while(lower_time <= upper_time){
        ll mid_time = lower_time + (upper_time - lower_time)/2;
        if(ispossible(c,mid_time) <= a){
            ans = mid_time;
            upper_time = mid_time-1;
        }
        else{
            lower_time = mid_time+1;
        }
    }
    return (ans*b)%mod;
}

int main(){ 
    cout << paint(1,1000000,{1000000,1000000}) <<"\n";
    return 0;
}