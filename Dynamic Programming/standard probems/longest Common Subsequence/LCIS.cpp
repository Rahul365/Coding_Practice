#include<bits/stdc++.h>
#define ll long long int
#define PII pair<ll,pair<int,int>>
using namespace std;

// https://practice.geeksforgeeks.org/problems/longest-common-increasing-subsequence/0/
int main()
{
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(int &x  : a) cin >> x;
        int m;
        cin >> m;
        vector<int> b(m);
        for(int &x  : b) cin >> x;
        vector<int> lcis(m);
        for(int i = 0;i<n;++i){
            int current = 0;
            for(int j = 0;j<m;++j){
                if(a[i] == b[j]){
                    if(current + 1 > lcis[j]){
                        lcis[j] = current+1;
                    }
                }
                if(a[i] > b[j]){
                    if(lcis[j] > current){//continue with best length so far
                        current = lcis[j];
                    }
                }
            }
        }
        int ans = 0;
        for(int j = 0;j<m;j++) ans = max(ans,lcis[j]);
        cout << ans <<"\n";
    }
	return 0;
}