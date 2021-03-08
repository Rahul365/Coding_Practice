#include<bits/stdc++.h>
#define boost ios_base::sync_with_stdio(false); cin.tie(0);
using namespace std;
using ll = long long int;
// https://codeforces.com/contest/1043/problem/D

ll count(ll n){
    return (n*(n+1))>>1LL;
}

void brute(){
    int n,m;
    cin >> n >> m;
    vector<int> arr[m];
    vector<int> pos[m];
    for(int i = 0;i < m;++i){
        arr[i] = vector<int>(n);
        pos[i] = vector<int>(n+1,-1);
        for(int j = 0;j<n;++j){
            cin >> arr[i][j];
            pos[i][arr[i][j]] = j;
        }
    }
    ll answer = 0;
    for(int i = 0;i<n;){
        int min_length = INT_MAX;
        for(int j = 0;j<m;++j){
            // cerr << arr[0][i] << ": " << pos[j][arr[0][i]] <<"\n";
            int r = 0;
            for(int k = pos[j][arr[0][i]];k<n && i+r<n;++k){
                if(arr[0][i+r]!=arr[j][k]) break;
                ++r;
            }
            min_length = min(min_length,r);
        }
        // cerr << arr[0][i] << " " << min_length << " = " << count((ll)min_length)<<"\n";
        i+=min_length;
        answer += count((ll)min_length);
    }
    cout << answer <<"\n";
}

int main(){
    boost;
    int n,m;
    cin >> n >> m;
    vector<int> arr(n);
    vector<map<int,int>> next(n+1);
    for(int i = 0;i < m;++i){
        for(int j = 0;j<n;++j){
            cin >> arr[j];  
        }
        for(int j = 0;j<n-1;++j){
            if(next[arr[j]].size()==1 && next[arr[j]].count(arr[j+1])){
                next[arr[j]][arr[j+1]]+=1;
                continue;
            }
            next[arr[j]][arr[j+1]] = 1;
        }
    }
    ll answer = n;
    vector<bool> vis(n+1,false);
    vector<pair<int,int>> starts;
    for(int i = 1;i<=n;++i){
        if(vis[i] || next[i].size() != 1){
             continue;
        }
        int j = i;
        int len = 1;
        while(next[j].size() == 1  && next[j].begin()->second == m){
            vis[j] = true;
            ++len;
            j = next[j].begin()->first;
            // cerr <<j<<"\n";
        }
        starts.emplace_back(len,i);
    }
    fill(vis.begin(),vis.end(),false);
    sort(starts.rbegin(),starts.rend());
    for(auto &p : starts){
        int j = p.second;
        int len = 1;
        while(!vis[j]  && next[j].size() == 1  && next[j].begin()->second == m){
            vis[j] = true;
            ++len;
            j = next[j].begin()->first;
            // cerr <<j<<"\n";
        }
        if(len == p.first){
            answer += count((ll)len-1);
        }
    }
    cout << answer <<"\n";
    return 0;
}