#include<bits/stdc++.h>
#define readint(x) scanf("%d",&x)
#define printint(x) printf("%d ",x)
#define readint64(x) scanf("%lld",&x)
#define sortvector(v) sort(v.begin(),v.end())
using namespace std;
using ll = long long int;



template<typename T>
T slope(T A,T B){
    T res = {B.second - A.second,B.first - A.first};
    return res;
}

//fraction comparison
//(a/b) > (c/d)  => if(a >= c && b <= d) (a/b) >= (c/d)
//(a/b) < (c/d)  => if(!(a >= c && b <= d)) (a/b) < (c/d)
//(a/b) == (c/d) => if(a == c && c == d) (a/b) == (c/d)
// where a = (a/gcd(a,b)) ,b = (b/gcd(a,b)) and so on...
//returns 0(!(A<B), 1(A < B)

//(a/b) < (c/d)
//(a*d) < (c*b)
int comparePoints(pair<ll,ll> &A,pair<ll,ll> &B){
    return A.first * B.second < B.first * A.second ? 1 : 0;
}



int main(){
    int t;
    readint(t);
    while(t--){
        int n,h;
        readint(h);
        readint(n);
        // map<pair<int,int>,int> cnt;
        vector<pair<ll,pair<ll,pair<int,int>>>> points;
        for(int i = 0;i<n;++i){
            int tt;
            readint(tt);
            ll x,a;
            readint64(x);
            readint64(a);
            // ++cnt[{x,a}];
            points.push_back({x,{a,{tt,i}}});
        }
        //sort points by their x coordinates
        sortvector(points);
        //Now for each point i , i want to count the number of other tower ends (excluding itself) which can be scene
        //without any interruption from it
        //By interruption , what we want to say is if a line is drawn from that point to the point for which we are checking it with
        //then there will no other tower touching or intersecting line connecting two points

        //Idea is to use slope of line here
        //what we know about slope of line of two points ? 
        // if two lines are parallel then their slopes are equal
        // if two lines are perpendicular then their slopes product = -1
        // if slope of line > 0 ,then angle made by that line with x,y plane is acute
        // if slope of line < 0 ,then angel made by that line with x,y plant is obtuse

        //Case I : point i is the type 0 
        //Case I.a : point j(>i) is the type 0(from ground)
        //Case I.b : point j(>i) is the type 1(from ceiling)
        
        //Case II : point i is the type 1 
        //Case II.a : point j(>i) is the type 0(from ground)
        //Case II.b : point j(>i) is the type 1(from ceiling)
        
        vector<int> ans(n);
        pair<ll,ll> d_cloud = {LLONG_MAX,LLONG_MAX};
        pair<ll,ll> d_ground = {LLONG_MIN,LLONG_MIN};
        pair<ll,ll> min_cloud = d_cloud;
        pair<ll,ll> max_ground = d_ground;
        for(int i = 0;i<n;++i){
            auto &p1 = points[i];
            int typei = p1.second.second.first;
            int id = p1.second.second.second;
            pair<ll,ll> pi  = {p1.first,p1.second.first};
            min_cloud = d_cloud;
            max_ground = d_ground;
            for(int j = i+1;j < n;++j){
                auto &p2 = points[j];
                int typej = p2.second.second.first;
                int idj = p2.second.second.second;
                pair<ll,ll> pj = {p2.first,p2.second.first};
                pair<ll,ll> m = slope<pair<ll,ll>>(pi,pj);
                //max_ground < m < min_cloud
                bool ok = true;
                if(min_cloud!=d_cloud && /*min_cloud > m*/comparePoints(m,min_cloud)!=1){
                        ok = false;
                }
                if(ok && max_ground!=d_ground && /*m > max_ground*/comparePoints(max_ground,m)!=1){
                        ok = false;
                }
        
                if(typej){
                    //update min_cloud
                    if(min_cloud==d_cloud || comparePoints(m,min_cloud))
                        min_cloud = m;
                }
                else{
                    //update max_ground
                    if(max_ground==d_ground || comparePoints(max_ground,m))
                       max_ground = m;
                }
                if(ok)//good point
                ++ans[id],++ans[idj];
            
                // else{
                //     cout << pi.first << " " << pi.second << ", "<<pj.first << " " <<pj.second<<" | ";
                //     cout << m.first << " " << m.second <<" | ";
                //     cout << min_cloud.first << " " <<min_cloud.second <<" , "<<max_ground.first << " "<<max_ground.second<<"\n";
                // }
            }
        }
        for(int i= 0;i<n;++i)
        {
            printint(ans[i]);
        }
        printf("\n");
    }
    return 0;
}