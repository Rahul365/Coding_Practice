#include<bits/stdc++.h>
using namespace std;
long long mask = 1LL<<53;
bool powerof2(long long n){
    return !(n&(n-1));
}
/*
    Given T test cases 
    In each test given a Number N
    N -> number of cities (labeled from 1 to N)
    They are not connected yet.
    Task is to connect these cities in a way such that cost of connecting all the cities is minimum possible
    Cost of connecting two cities a and b  = (a&b) where '&' is bitwise AND operator
*/
long long power(long long a,long long b){
    long long result = 1;
    while(b){
        if(b&1) result *= a;
        a *= a;
        b>>=1;
    }
    return result;
}


/*
    Since cost of connecting two cities is bitwise and of their labels
    So it is obvious that cost of connecting two cities will be minimum if the only common set bit between two cities is lowest possible

    e.g. Let a = 1 and b = 7 , here cost of connecting (a,b) = 1&7 = 1(which is 2^0 i.e. lowest set bit)
    1) If n is power of 2 i.e !n&(n-1) then it will never be possible to connect all the cities 

    2) Each city belong to a group of lowest set bit

    e.g.
    Group 0th bit : {1,3,5,7,9,....} (each of the member have their 0th bit as the lowest set bit)
    Group 1st bit : {2,6,10,14,....}
    Group 2nd bit : {4,12,20,.....} 
    In general
    Group ith bit : {(2^i) + (k * (2^(i+1)))} where k = 0  to till (2^i) + (k * (2^(i+1))) <= n
    So it seems feasible to connect all the members of a group with each lowest member 
    Number of members in a group are N = (n + (2^i))/(2^(i+1))
    So total cost of connecting lowest member with all the other members of the group = (N-1) * (2^i)
    = ([(n - (2^i))/(2 * (2^i))] - 1)   * (2^i)
    = (n - 2^i)/(2*2^i) * 2^i

    What about cross group connections ? 
    For that it can be seen that we can connect city 2^i with 2^i + 1 for the lowest cost of 2^i
    for each bit position i > 0
    2 + 4 + 8 + 16 + .... + 2^(log2(n))

    for(int p = 2;p < n;p<<=1LL) ans += p;
      
*/
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int t;
    cin >> t;
    while(t--){
        long long n;
        cin >> n;
        if(powerof2(n)){//when n is power of 2 then it is impossible to connect cities
            cout << -1 <<"\n";
            continue;
        }
        long long ans = 0;
        for(long long i = 1;i<=n;i<<=1LL){
            ans += (n-i)/(i<<1LL) * i;
        }
        for(long long i = 2;i<n;i<<=1LL)
            ans += i;
        cout << ans <<"\n";
    }
    return 0;
}