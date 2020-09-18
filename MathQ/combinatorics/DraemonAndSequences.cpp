#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
// https://codeforces.com/problemset/problem/1329/B
/*
    Interesting problem , new perpective to view things
    Given d,m. Count the number of arrays such that following conditions hold true:
    1) length of array is n,n>=1
    2) 1<=a1<a2<a3<....<an-1<an<=d
    3) Build an array b[] for array a[]
    such that  b[1] = a[1], the b[i] = b[i-1] XOR a[i]
    And also b[1] < b[2] < b[3] <...<b[n] must hold for array a[]
    Find answer modulo m.(Note : m can be prime or not)

    Let h(x) be a function which give us the leftmost set bit position in a number x.
    e.g. h(1) = 0, h(2) = 1, h(3) =1 ,h(4) = 2 etc.
    Let's see some observations here:
    h(a1) = h(b1)
    All the constraints for array a[] hold iff
    h(ai)  < h(ai+1).
    Proof is simple : 
    Assume h(a0) = 0 , that means in range[2^0,2^1-1]
    For(b0 < b1=(b0 XOR a0)) condition to hold true, h(a0) < h(a1) must
    That is possible only if h(a1) = 1,2,3,....,(2^i <= d)

    The Maximum length of the array will be 2^len <= d such that 2^(len+1) > d;
    Also for every number in every range there are two choices either we can have a number from that interval 
    or we don't. i.e. 2 choices
    So basically for some i, we'll have
    (min(2^(i+1) - 1,d)-(2^i)+2) choices of either getting a number or not for a[pos] of the array.
    So we either pick or not at all.
    How many choices ? (min( (2^(i+1))  - 1, d) - (2^i) + 1(for including (2^(i+1))-1) + 1(choice of not picking at all))
    answer = (product of choices from each group)%m - 1;
    if(answer < 0) answer += m;
    
*/
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        ll d,m;
        scanf("%lld%lld",&d,&m);
        ll answer = 1;
        for(ll i = 0;i<30;++i){
            if(d < (1LL<<i)) break;
            answer = answer * ( min((1LL<<(i+1))-1LL,d) - (1L<<i) + 2 )%m;
        }
        --answer;
        if(answer < 0) answer += m;
        printf("%lld\n",answer);
    }
    return 0;
}