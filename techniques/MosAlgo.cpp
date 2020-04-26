#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+1;
const int mod = 1e9 + 7;
int blocksize = 1000;
vector<int> val(maxn);
bool  compare(pair<pair<int,int>,int> &a, pair<pair<int,int>,int> &b){
    if(a.first.first/blocksize  != b.first.first/blocksize)
    return a.first.first/blocksize < b.first.first/blocksize;
    if(a.first.first/blocksize & 1) return a.first.second < b.first.second;
    return a.first.second > b.first.second;
}

void addto(int &result,int idx) {
//add some value to result
    result += val[idx];
    if(result>=mod){
        result -= mod;
    }
} 

void removefrom(int &result,int idx) {
    //remove some value from result
    result -= val[idx];
    if(result <= 0)
    result += mod;
}

vector<int> MosAlgo(vector<pair<pair<int,int>,int>> &queries){
    sort(queries.begin(),queries.end(),compare);
    int cl = 0;
    int cr = -1;
    int result = 0;
    vector<int> ans((int)queries.size());
    for(auto &q : queries){
        int l = q.first.first;
        int r = q.first.second;
        while(cr < r){
            ++cr;
            addto(result,cr);
        }
        while(cl  < l){
            removefrom(result,cl);
            ++cl;
        }
        while(cl > l){
            --cl;
            addto(result,cl);
        }
        while(cr > r){
            removefrom(result,cr);
            --cr;
        }
        ans[q.second] = result;
    }
    return ans;
}

/**
 * Range Sum query on an array  Using Mo's Offline algorithm such that there are no updates
 * Overall time : O(N * sqrt(N)) 
*/
int main(){
    int n;
    cin >> n;
    for(int i= 0;i<n;++i){
        cin >> val[i];
    }
    int q;
    cin >> q;
    vector<pair<pair<int,int>,int>> queries;
    for(int i= 0;i<q;++i){
        int x,y;
        cin >>x >> y;
        --x,--y;
        queries.push_back({{x,y},i});
    }
    vector<int> ans = MosAlgo(queries);
    for(int v : ans){
        cout << v << "\n";
    }
    return 0;
}   