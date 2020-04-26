#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+11;
using ll = long long;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        int n,q;
        cin >> n >> q;
        vector<vector<int>> segments;
        int prev = 0;
        int point = 0;
        for(int i = 1;i<=n;++i){
            cin >> point;
            if(i > 1){
                segments.push_back({i-1,prev,i,point});
            }
            prev = point;
        }

        while(q--){
            int x1,x2, y;
            cin >> x1 >> x2 >> y;
            /**
             * find all the points whose x coordinates are in [x1,x2]
            */
        //    vector<vector<int>> filter_byxy;
           int ans = 0;
           for(vector<int> seg : segments){
                if(x1 <= seg[0] && seg[2] <= x2 &&  ((y >= seg[3] && y <= seg[1])||(seg[1] <= y && y <= seg[3]))){
                    if(make_pair(seg[0],seg[1]) == make_pair(x2,y)) continue;
                    if(make_pair(seg[2],seg[3]) == make_pair(x1,y)) continue;
                    // filter_byxy.push_back(seg);
                    ++ans;
                }
           }
            cout << ans <<"\n";
        }
    }
    return 0;
}