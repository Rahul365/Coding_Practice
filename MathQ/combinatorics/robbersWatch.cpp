#include<bits/stdc++.h>
using namespace std;
//https://codeforces.com/problemset/problem/685/A
int main(){
    int n,m;
    cin >> n >> m;
    auto countReqPlaces = [&](int x){
       int answer = 1;
       while(x/7){
            answer += 1;
            x/=7;
       }
      return answer;
    };
    auto getNumber=[&](int x,vector<int> &arr){
        int N = arr.size();
        while(x/7){
            arr[--N] = x%7;
            x/=7;
        }
        arr[--N] = x;
    };
    int N = countReqPlaces(n-1);
    int M = countReqPlaces(m-1);
    //cerr << N << " " << M <<"\n";
    if(N+M > 7){
        /*Since the base is 7, by pigeonhole principle if the watch contains more than 7 pigeons, then there will be duplicates.*/
         cout << 0 <<"\n";
    }
    else{
        vector<vector<int>> a(n,vector<int>(N,0));
        vector<vector<int>> b(m,vector<int>(M,0));
        for(int i= 0;i<max(n,m);++i){
            if(i < n) getNumber(i,a[i]);
            if(i < m) getNumber(i,b[i]);
        }
        auto ok = [&](int i,int j){
            vector<int> cnt(10,0);
            for(int id = 0;id<a[i].size();++id) if(++cnt[a[i][id]]>1) return false;
            for(int id = 0;id<b[j].size();++id) if(++cnt[b[j][id]]>1) return false;
            return true;
        };
        int answer = 0;
        
        for(int i = 0;i<n;++i){
            for(int j = 0;j<m;++j){
                if(ok(i,j)) ++answer;
            }
        }
        cout << answer <<"\n";
    }
    return 0;
}