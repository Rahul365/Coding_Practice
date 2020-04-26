#include<bits/stdc++.h>
using namespace std;
template<typename T>
    T cross(vector<T> &p,vector<T> &q,vector<T> &r){
        return p[0]*(q[1]-r[1]) + q[0] * (r[1] - p[1]) + r[0] * (p[1]-q[1]);
    }

class Solution {
public:
    
    bool cw(vector<int> &a,vector<int> &b,vector<int> &c){
        return (b[0]-a[0])*(c[1]-b[1]) - (c[0]-b[0])*(b[1]-a[1]) <= 0;
    }
    
    bool ccw(vector<int> &a,vector<int> &b,vector<int> &c){
        return (b[0]-a[0])*(c[1]-b[1]) - (c[0]-b[0])*(b[1]-a[1]) >= 0;
    }
    
    vector<vector<int>> outerTrees(vector<vector<int>>& points) {
        const int n = points.size();
        if(!n) return {{}};
        vector<vector<int>> res;
        sort(points.begin(),points.end());
        vector<int> p1 = points[0],p2 = points.back();
        vector<vector<int>> up,down;
        up.push_back(p1); down.push_back(p1);
        for(int i = 1 ;i<n;++i){
            if(i == n-1 || cross(p1,points[i],p2)>=0){//clockwise , (NOTE : replace '>=' with  '>' to avoid putting collinear points in the answer)
                while(up.size() >= 2 && cross(up[up.size()-2],up[up.size()-1],points[i])<0){
                    up.pop_back();
                }
                up.push_back(points[i]);
            }   
            if(i == n-1 || cross(p1,points[i],p2) < 0){//counterclockwise
                while(down.size() >= 2 
                      && cross(down[down.size()-2],down[down.size()-1],points[i]) > 0){
                    down.pop_back();
                }
                down.push_back(points[i]);
            }
        }
        
        for(auto &v : down)
            res.push_back(v);
        for(int i = up.size()-2;i>0;--i)
            res.push_back(up[i]);
        return res;
    }
};




vector<vector<int>> convexHull(vector<vector<int>> &points){
    const int n = points.size();
    if(!n) return {{}};
    vector<vector<int>> res,up,down;
    sort(points.begin(),points.end());
    vector<int> p1 = points[0],p2 = points.back();
    up.push_back(p1);
    down.push_back(p1);
    for(int i = 1 ; i < n;++i){
        if(i == n-1 || cross(p1,points[i],p2) > 0){
            while(up.size() >= 2 && cross(up[up.size()-2],up[up.size()-1],points[i]) <= 0){
                up.pop_back();
            }
            up.push_back(points[i]);
        }
        if(i == n-1 || cross(p1,points[i],p2) < 0){
            while(down.size() >= 2 && cross(down[down.size()-2],down[down.size()-1],points[i]) >= 0)
                down.pop_back();
            down.push_back(points[i]);
        }
    }
    for(auto &p : down) res.push_back(p);
    for(int i = up.size()-2;i > 0 ; --i)
        res.push_back(up[i]);
    return res;
}

void version2()
{
    //here we consider only the end points of the boundary
    //any point which is collinear to the boundary line and is not a endpoint will not be added to answer
    int t;
    cin >> t;
    while(t--){
        vector<vector<int>> points;
        int n;
        cin >> n;
        for(int i = 0; i <n;++i){
            int x,y;
            cin >> x >> y;
            points.push_back({x,y});
        }
        auto ans = convexHull(points);
        if((int)ans.size() < 3){
            cout <<-1<<"\n";
            continue;
        }
        sort(ans.begin(),ans.end());
        for(int i = 0 ;i<ans.size()-1;++i){
            cout << ans[i][0] << " "<<ans[i][1] <<", ";
        }
        cout << ans.back()[0] << " "<<ans.back()[1] <<"\n";
    }
}

int main(){
    // Input: [[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]] 
    // Output: [[1,1],[2,0],[4,2],[3,3],[2,4]] 
     
    vector<vector<int>> points = {{1,1},{2,2},{4,2},{2,0},{2,4},{3,3}};
    int n; cin >> n;
    points.clear();
    for(int i = 0;i<n;++i){
        int x,y;
        cin >> x >> y;
        points.push_back({x,y});
    }
    Solution sol;
    for(auto ans : sol.outerTrees(points)){
        cout << ans[0] << " " <<ans[1] <<"\n";
    }
    return 0;    
}







