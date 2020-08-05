#include<bits/stdc++.h>
using namespace std;

vector<pair<int,int>> factors(int n){
    vector<pair<int,int>> ans;
    for(int i = 2;i*i<=n;++i){
        if(n%i == 0){
            ans.emplace_back(i,0);
            while(n%i == 0){
                n/=i;
                ++ans.back().second;
            }
        }
    }
    if(n > 1) ans.emplace_back(n,1);
    return ans;
}

int main(){
    int n;
    cin >> n;
    int divisors = 1;
    auto fact = factors(n);
    for(auto  p :fact){
        divisors *= p.second+1;
    }
    cout << "Total Divisors : " << divisors <<"\n";
    cout << "Proper Divisors (excluding 1 and n): "<< divisors-2 <<"\n";
    return 0;
}