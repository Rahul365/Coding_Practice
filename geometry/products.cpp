#include<bits/stdc++.h>
using namespace std;
/*
    Template for points in 2d
*/
template<typename T>
class point2d{
    public:
    T x;
    T y;
    point2d(){};
    point2d(T _x,T _y):x(_x),y(_y){};

    point2d& operator+=(point2d b){
        x += b.x;
        y += b.y;
        return *this;
    }
    point2d& operator-=(point2d b){
        x -= b.x;
        y -= b.y;
        return *this;
    }

    point2d& operator*=(T c){
        x *= c;
        y *= c;
        return *this;
    }

    point2d& operator/=(T c){
        x/=c;
        y/=c;
        return *this;
    }

    point2d& operator+(point2d b) const{
        return point2d(*this)+=b;
    }

    point2d& operator-(point2d b) const{
        return point2d(*this) -=b;
    }

    point2d& operator*(T c) const{
        return point2d(*this)*=c;
    }

    point2d& operator/(T c) const{
        return point2d(*this)/=c;
    }
};


/*
    Template for points in 3d
*/
template<typename T>
class point3d{
    public:
    T x;
    T y;
    T z;
    point3d(){};
    point3d(T _x,T _y,T _z):x(_x),y(_y),z(_z){};

    point3d& operator+=(point3d b){
        x += b.x;
        y += b.y;
        z += b.z;
        return *this;
    }
    point3d& operator-=(point3d b){
        x -= b.x;
        y -= b.y;
        z -= b.z;
        return *this;
    }

    point3d& operator*=(T c){
        x *= c;
        y *= c;
        z *= c;
        return *this;
    }

    point3d& operator/=(T c){
        x/=c;
        y/=c;
        z/=c;
        return *this;
    }

    point3d& operator+(point3d b) const{
        return point3d(*this)+=b;
    }

    point3d& operator-(point3d b) const{
        return point3d(*this) -=b;
    }

    point3d& operator*(T c) const{
        return point3d(*this)*=c;
    }

    point3d& operator/(T c) const{
        return point3d(*this)/=c;
    }
};

/**
 * For dot product of 2d and 3d points
 * A.B = |A||B|cos(0);
 * For cross product of 2d and 3d points
 * AxB = |A||B|sin(0);
*/

template<typename T>
T dot(point2d<T> A,point2d<T> B){
    return A.x * B.x + A.y * B.y;
}

template<typename T>
T dot(point3d<T> A,point3d<T> B){
    return A.x * B.x + A.y*B.y + A.z * B.z;
}

template<typename T>
T cross(point2d<T> A,point2d<T> B){
    return A.x * B.y - A.y*B.x;
}

template<typename T>
T cross(point2d<T> A,point2d<T> B,point2d<T> C){
    return cross(B-A,C-B);
    //return A.x * (B.y - C.y) + B.x * (C.y - A.y) + C.x * (A.y - B.y);
    //return (B.x-A.x) * (C.y - B.y) - (C.x-B.x)*(B.y-A.y);
}

/**
 * To determine the orientation of three points connected in order(A,B,C)
 * line(A,B) ,line(B,C) => (A->B->C)
 * if(signofCrossproduct(AB,BC) < 0) => Anticlockwise
 * else if(signofCrossproduct(AB,BC) > 0) => Clockwise
 * else => collinear
*/
template<typename T>
T orientation(point2d<T> A,point2d<T> B,point2d<T> C){
    int p = cross(A,B,C);
    if(p == 0){
        return 0;//collinear
    }
    else if(p < 0){
        return -1;//counter-clockwise
    }
    return 1;//clockwise
}

int main(){ 
    point2d<int> p1(1,2);
    point2d<int> p2(1,1);
    point2d<int> p3(1,4);
    cout << cross(p1,p2,p3) <<"\n";
    int orient = orientation(p1,p2,p3);
    if(orient < 0){
        cout << "CounterClockWise\n";
    }
    else if(orient > 0){
        cout << "ClockWise\n";
    }
    else{
        cout << "Collinear\n";
    }
    return 0;
}