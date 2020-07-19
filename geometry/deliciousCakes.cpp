#include<bits/stdc++.h>
using namespace std;
using ll = long long int;

inline int sign(ll v){
    if(v == 0LL) return 0;
    return v>0LL?1:-1;
}

struct Point{
    ll x,y;
    Point(ll _x=0,ll _y=0):x(_x),y(_y){};
    
    pair<ll,ll> mp(){
        return {x,y};
    }

    Point& operator+(Point b){
        x += b.x;
        y += b.y;
        return *this;
    }

    Point& operator-(Point b){
        x -= b.x;
        y -= b.y;
        return *this;
    }
    
    Point& operator/(ll d){
        x /= d;
        y /= d;
        return (*this);
    }

    Point& operator/=(ll d){
        return Point(*this)/d;
    }

    Point& operator*(ll c){
        x *= c;
        y *= c;
        return *this;
    }

    Point& operator*=(ll c){
        return Point(*this)*c;
    }

    Point& operator-=(Point b){
        return Point(*this)-b;
    }

    Point& operator+=(Point b){
        return Point(*this)+b;
    }

};

ll cross2(Point A,Point B){
    return A.x*B.y - A.y*B.x;
}

ll dot(Point A,Point B){
    return A.x * B.x + B.y * A.y;
}

ll sqrLen(Point A,Point B){
    return (A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y);
}

ll cross3(Point A,Point B,Point C){
    return cross2(B-A,C-B);
}

bool lexcomp(Point a,Point b){
    return a.x < b.x || (a.x == b.x && a.y > b.y);
}

vector<vector<Point>> layers;
vector<vector<Point>> seqLayers;
map<pair<ll,ll>,int> id;
vector<int> LayerNum;

void preprocessLayers(){
    seqLayers.clear();
    for(auto layer : layers){
        vector<Point> points = layer;
        int n = (int)points.size();
        int pos = 0;
        for(int i = 1;i<n;++i)
            if(lexcomp(points[i],points[pos]))
                pos = i;
        rotate(points.begin(),points.begin()+pos,points.end());
        seqLayers.push_back(points);
    }
}

vector<Point> convexHull(vector<Point> &points){
    vector<Point> res;
    const int n = (int)points.size();
    if(n < 3) return res;
    Point p0 = points[0];
    Point pn = points.back();
    vector<Point> upper,lower;
    upper.push_back(p0);
    lower.push_back(p0);
    for(int i = 1;i<n;++i){
        ll cw = sign(cross3(p0,points[i],pn));
        if(i == n-1 || cw <= 0){
            //clockwise
            int m = (int)upper.size();
            while(m >= 2 && sign(cross3(upper[m-2],upper[m-1],points[i]))>0)
            {
                upper.pop_back();
                --m;
            }
            upper.push_back(points[i]);
        }
        if(i == n-1 || cw >= 0){
            //anticlockwise
            int m = (int)lower.size();
            while(m >= 2 && sign(cross3(lower[m-2],lower[m-1],points[i]))<0)
            {
                lower.pop_back();
                --m;
            }
            lower.push_back(points[i]);
        }
    }
    res = lower;
    for(int i = (int)upper.size()-2;i;--i){
        res.push_back(upper[i]);
    }
    return res;
}

void buildlayers(vector<Point> &points){
    //identifiers for points
    sort(points.begin(),points.end(),[&](Point &a,Point &b){
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    });
    id.clear();
    layers.clear();
    LayerNum.clear();
    int ID = -1;
    for(auto p : points) id[p.mp()] = ++ID;
    LayerNum = vector<int>((int)points.size(),-1);
    int lnum = 0;
    while(true)
    {
        vector<Point> sp;//set of point for the next layer
        for(auto p : points) if(LayerNum[id[p.mp()]]==-1) sp.push_back(p);//points which are not already in prev layer
        vector<Point> res = convexHull(sp);//getting the outer layer
        if(res.empty()) break;
        ++lnum;//next layer Number
        for(auto p : res) LayerNum[id[p.mp()]]=lnum; //assigning to each point it's layer number
        layers.push_back(res);//append to layer
    }
}

/*Naive Approach to Check points inside a polygon O(N) worst Case*/
bool insideLayer(int pos,Point p){
    vector<Point> &cvx = seqLayers[pos];
    const int n = (int)cvx.size();
    if(sign(cross3(cvx.back(),cvx[0],p)) <= 0) return false;
    for(int i = 0; i < n-1;++i){
        if(sign(cross3(cvx[i],cvx[i+1],p)) <= 0) return false;
    }
    return true;
}

bool inTriangle(Point A,Point B,Point C,Point D){
    ll T = abs(cross3(A,B,C));
    ll T3 = abs(cross3(A,B,D));
    ll T2 = abs(cross3(A,C,D));
    ll T1 = abs(cross3(B,C,D));
    return  T == (T1 + T2 + T3);
}

int orientation(Point A,Point B,Point C){
    int val = sign((B.y-A.y)*(C.x-B.x)-(C.y-B.y)*(B.x-A.x));
    if(val == 0) return 0;
    return val > 0 ? 1 : -1;
    //1->clockwise
    //-1->AntiClockwise
}
/*O(logN)*/
int insidePolygon(int pos,Point p){
    vector<Point> &cvx = layers[pos];
    const int n = (int)cvx.size();
    Point p0 = cvx[0];
    if(!(orientation(p0,cvx[1],p)<=0 && orientation(cvx.back(),p0,p)<=0)) return -1;
    if(orientation(p0,cvx.back(),p) == 0)
    {
        if(sqrLen(p0,cvx.back())>=sqrLen(p0,p)) return 2;
        return -1;
    }
    if(orientation(p0,cvx[1],p) == 0){
        if(sqrLen(p0,cvx[1])>=sqrLen(p0,p)) return 2;
        return -1;
    }
    int l = 1;
    int r = n-1;
    while(l<=r){
        int m = l +(r-l)/2;
        if(orientation(p0,cvx[m],p)<0){
            pos = m;
            l = m+1;
        }
        else{
            r = m-1;
        }
    }
    // cout << cvx[pos].x << " " <<cvx[pos].y<<"\n";
    if(pos == n-1){
        if(sqrLen(p0,cvx[pos])>=sqrLen(p0,p)) return 2;
        return -1;
    }
    if(orientation(cvx[pos],cvx[pos+1],p)==0) return 2;
    return inTriangle(p0,cvx[pos],cvx[pos+1],p)?1:-1;
    //return (orientation(cvx[pos],cvx[pos+1],p)<0 && orientation(p0,cvx[pos],p)<=0 && orientation(cvx[pos+1],p0,p)<=0)?1:-1;
}

int getans2(Point p){
    for(int i = (int)layers.size();i>=1;--i){
        int resp = insidePolygon(i-1,p);
        if(resp == -1) continue;
        return i-(resp==2);
    }    
    return 0;
}

int getans(Point p){
   int ans = 0;
   for(int i= 1;i<=layers.size();++i){
       if(!insideLayer(i-1,p)) break;
       ++ans;
   }
   return ans;
}

void printlayers(){
    for(auto l : layers){
        for(auto p :l){
            cout <<" ( "<< p.x << " " <<p.y <<") , ";
        }
        cout <<"\n";
    }
}

void printprocessedlayers()
{
    for(auto l : seqLayers){
        for(auto p : l){
            cout <<"("<<p.x << " "<< p.y << ") , ";
        }
        cout <<"\n";
    }
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int n,q;
        scanf("%d%d",&n,&q);
        vector<Point> points(n);
        for(int i = 0;i<n;++i){
            scanf("%lld%lld",&points[i].x,&points[i].y);
        }
        buildlayers(points);
        // for(Point p : points){
        //     printf("(%lld,%lld) = %d\n",p.x,p.y,LayerNum[id[p.mp()]]);
        // }
        // printf("\n");
        // printlayers();
        preprocessLayers();//for O(logN) check of point inside polygon
        // printprocessedlayers();
        Point qp[1];
        while(q--){
            scanf("%lld%lld",&qp[0].x,&qp[0].y);
            printf("%d\n",getans2(qp[0]));
        }
    }   
    return 0;
}