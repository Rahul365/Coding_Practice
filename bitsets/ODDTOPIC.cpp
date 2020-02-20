#include<bits/stdc++.h>
using namespace std;
const int maxn = 4002;

int main(){
    int n,m,q;
    cin >> n >> m >> q;
    int a[n],b[m];
    int len = max(n,m);
    bitset<maxn> A[len],B[len];
    for(int i = 0;i<n;++i)
    {
        cin>> a[i];
        if(i > 0)
        A[i] = A[i-1];
        A[i][a[i]] = A[i][a[i]] ^ 1;
    }
    
    for(int i = 0;i<m;++i){
        cin >> b[i];
        if(i > 0)
        B[i] = B[i-1];
        B[i][b[i]] = B[i][b[i]] ^ 1;
    }
    
    while(q--){
        int l[2],r[2];
        for(int i = 0;i<2;++i)
        {
            cin >> l[i] >> r[i];
            --l[i];
            --r[i];
        }
        bitset<maxn> t1 = A[r[0]] ^ (l[0]?A[l[0]-1]:0);
        bitset<maxn> t2 = B[r[1]] ^ (l[1]?B[l[1]-1]:0);
        
        cout << (t1^t2).count() <<"\n";
    }
    return 0;
}