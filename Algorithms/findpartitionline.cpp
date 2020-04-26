/**
 * Find a partition line parallel to Y-axis such that sum of values on left == sum of values on right
 * Given set of points(xi,yi) on cartesian plane such value(xi,yi) is vi.
 * Determine if there exists a line parallel to y-axis in the plane such that
 * sum of values of points to it's left  == sum of values of points to it's right.
 * 
 * Print "Yes" if such a partition is possible 
 * else  "No".
 * Note **: if a point itself is on such a partition line then that point is neither considered for the left nor for the right side.
 * 
 * e.g
 *  INPUT : X[] = {-3,5,8}
 *          Y[] = { 8,7,9}
 *          V[] = { 8,2,10}
 *          n = 3
 * OUTPUT : Yes
 *  for x = c where 5 < c < 8 is a good partition line where sum of values on left  == sum of values on right
*/


/**
 * Approach : 
 * 1)count the values at each x-coordinate. This means that if there are multiple points with the same x-cordinates.
 *   ,then they will be treated as single point and their values will be added.
 * 2)start iterating from minimum x-coordinate and check:
 *     .sum of values of 0 to i-1 points == sum of values of i+1 to n points 
 *     .sum of values of 0 to i-1 points == sum of values of i to n points
 *     .sum of values of 0 to i points  == sum of values of i+1 to n points
 *     print "Yes" and return if any of above condition becomes true for any x-coordinate
 * 3)print "No"
 * Time and space : O(sizeofmap or array to line sums)
*/

#include<bits/stdc++.h>
using namespace std;
/**
 * Using hashmap
*/
bool ispartitionpossible(int *x,int *y,int *v,int n){
    map<int,int> xvals;
    int total = 0;
    for(int i = 0;i<n;i++){
        xvals[x[i]]+=v[i];
        total += v[i];
    }
    //iterate through lines
    int sumsofar = 0;
    for(pair<int,int> p  : xvals){
        sumsofar += p.second;
        //sum(0..i-1) == sum(i+1..n-1)
        if(sumsofar - p.second == total - sumsofar){
            return true;
        }
        //sum(0...i) == sum(i+1..n-1)
        if(sumsofar == total - sumsofar){
            return true;
        }
        //sum(0...i-1) == sum(i..n-1)
        if(sumsofar - p.second == total - sumsofar + p.second){
            return true;
        }
    }
    return false;
}


/**
 * Using arrays
*/
const int MAX = 1000;
bool ispartition(int *x,int *y,int *v,int n){
    int size = 2*MAX + 1;
    //origin is shifted to MAX
    long long xvals[size] = {0};//to handle the negative x values e.g is x[i] = -1 then x[i]+MAX = -1 + 1000 = 999
    for(int i = 0;i<n;i++){
        xvals[x[i] + MAX]+=v[i];
    }

    for(int i = 1;i<size;i++){
        xvals[i] += xvals[i-1];
    }
    //if all the points add to zero then line can be drawn anywhere
    if(xvals[size-1] == 0) return true;
    //if the line is drawn touching the leftmost possible points
    if(xvals[size-1] - xvals[0] == 0){
        return true;
    }

    for(int i = 1;i<size;i++){
        //sum(0..i-1) == sum(i+1..size-1)
        if(xvals[i-1] == (xvals[size-1] - xvals[i])){
            return true;
        }
        //sum(0..i) == sum(i+1...size-1)
        if(xvals[i] == (xvals[size-1]-xvals[i])){
            return true;
        }
        //sum(0..i-1) == sum(i..size-1)
        if(xvals[i-1] == (xvals[size-1] - xvals[i-1])){
            return true;
        }
    }

    return false;
}

int  main(){
    int X[] = {-3,5,8};
    int Y[] = { 8,7,9};
    int V[] = { 8,2,10};
    int n = sizeof(V)/sizeof(V[0]);
    cout<<(ispartitionpossible(X,Y,V,n)?"Yes":"No")<<"\n";
    cout<<(ispartition(X,Y,V,n)?"Yes":"No")<<"\n";
    return 0;
}
