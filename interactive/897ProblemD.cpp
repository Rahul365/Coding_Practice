#include<bits/stdc++.h>
using namespace std;

int search(vector<int> &a,int n,int val){
    int l = 1;
    int r = n;
    int ans = n;
    while(l <= r){
        int m = l + (r-l)/2;
        if(a[m] < val){
            l = m+1;
        }
        else if(a[m] >=  val){
            ans = m;
            r = m-1;
        }
    }
    return ans;
}

int main(){
    int n,m,c;
    cin >> n >> m >> c;
    vector<int> a(n+1);
            int cnt =  0;

    for(int i =1;i<=m;++i)
    {
        int x;
        cin >> x;
        if(x <= c/2){
            for(int i = 1;i<=n;++i){
                if(a[i] == 0 || a[i] > x){
                    cnt += (a[i]==0);
                    a[i] = x;
                    cout << i <<"\n";
                    fflush(stdout);
                    break;
                }
            }
        }
        else
        {
            for(int i = n;i>=1;--i){
                if(a[i] == 0 || a[i] < x){
                    cnt += (a[i]==0);
                    a[i] = x;
                    cout << i << "\n";
                    fflush(stdout);
                    break;
                }
            }
        }
        if(cnt == n) break;
    } 
    return 0;
}