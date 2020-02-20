#include<bits/stdc++.h>
using namespace std;


int main(){
    long long int ans = 0;
    long long int cnt = 0;
    long long int num = 1;
    long long int sum = 0;
    while(cnt<500){
        sum +=num;//numth triangle number
        cnt = 0;
        for(int i = 1;i<=sqrt(sum);i++){
            if(sum%i == 0)
                cnt+=2;
        }
        // cout<<sum<<" "<<cnt<<"\n";
        
        num++;
    }
    cout<<sum<<"\n";
    return 0;
}