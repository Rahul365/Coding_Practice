/*
Find the prime factors of each number and their powers. The LCM of all numbers will have a factorisation with the powers of each prime factor being the maximum of that of all the numbers.

Consider the list of numbers,
a[]={12, 16, 60, 35};

12=2^2 * 3^1, so the factor array would be {2,1,0,0,…}
where the ith element denotes the power of the ith prime.
Similarly the factor arrays of all other numbers can be found,
16={4,0,0,0,…}
60={2,1,1,0,…}
35={0,0,1,1,…}
The factor array of the LCM of all numbers would have the ith element equal to the maximum of all the numbers’s ith elements in their factor arrays.
So the LCM would be {4,1,1,1,…}=2^4 * 3^1 * 5^1 * 7^1=1680
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn = 100;
using ll = long long int;
vector<int> p(maxn);

void primefactors(int x){
    for(int i= 2;i <= sqrt(x);++i){
        if(x%i == 0){
            int cnt= 0;
            while(x%i == 0){
                x/=i;
                ++cnt;
            }
            p[i] = max(cnt,p[i]);
        }
    }
    if(x > 2 && p[x] < 1){
        p[x] = 1;
    }
}

int main(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i = 0;i<n;++i){
        cin >> a[i];
    }

    for(int i = 0;i<n;++i){
        //prime factors count
        int x = a[i];
        primefactors(x);
    }
    ll lcm = 1LL;
    for(int i = 1;i < maxn;++i){
        if(!p[i]) continue;
        lcm =  lcm * (1LL * pow(i,p[i]));
    }
    cout << lcm <<"\n";
    return 0;
}