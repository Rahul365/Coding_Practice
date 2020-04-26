#include<bits/stdc++.h>
using namespace std;

// https://www.codechef.com/problems/EXPXOR
//TODO
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int n;
        scanf("%d",&n);
        vector<int> b(n);
        vector<double> p(n);
        int xor_all = 0;
        for(int i = 0;i<n;++i) scanf("%d",&b[i]) , xor_all ^= b[i];
        for(int i = 0;i<n;++i) scanf("%lf",&p[i]);

        //expected values(e1,e2,e3,...,en)
        //ev(N) = e1 * p(e1) + ........+ en*p(en);

    }
    return 0;
}