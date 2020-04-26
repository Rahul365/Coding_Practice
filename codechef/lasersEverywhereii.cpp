#include<bits/stdc++.h>
using namespace std;
const int maxn  = 1e5+11;
using ll = long long;
vector<ll> points(maxn,0);

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        int n,q;
        cin >> n >> q;
        vector<int> pmax(n),pmin(n);
        //pmax[i] => max(point[i-1],point[i]) store the maximum y coordinate of a pair
        //pmin[i] => max(point[i-1],point[i]) store the minimum y coordinate of a pair
        for(int i = 1;i<=n;++i){
            cin >> points[i];
            if(i > 1){
                pmax[i] = max(points[i-1],points[i]);
                pmin[i] = min(points[i-1],points[i]);
            }
        }
        while(q--){
            int x1,x2;
            ll y;
            cin >> x1 >> x2 >> y;
            int ans = 0;
            //Max Number of line segment could be x2 - x1
            for(int i = x1+1 ; i<=x2;++i){
                //O(dist)
                //dist = x2 - x1
                //(l-1,points[l-1])  to (l,points[l])
                //Problem boils down to count the number of points from x1+1 to x2 
                //such that
                // (points[l-1] <= y <= points[l]) || (points[l] <= y <= points[l-1])
                // Number of such y's till x2  - Number of such y's till x1
                //1)
                // if((points[i-1] <= y && y <= points[i]) || (y >= points[i] && y <= points[i-1]))
                // {
                //     ++ans;
                // }
                if(pmin[i] <= y && y <= pmax[i]){
                    ++ans;
                }
            }
            cout << ans <<"\n";
        }
        fill(points.begin(),points.end(),0);
    }
    return 0;
}