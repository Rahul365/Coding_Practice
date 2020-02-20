#include<bits/stdc++.h>
#define left 2*i+1
#define right 2*i+2
#define mid l + ((r-l)>>1)
using namespace std;
const int N = 1e5;
int seg[2*N];
int arr[] = {2,3,-1,5,-2,4,8,10};//array of elements
int n = sizeof(arr)/sizeof(arr[0]);//number of elements in the array
/**
 * To build the segment tree
*/
void buildTree(int i,int l,int r){
    if(l == r){
        seg[i] = arr[l];
    }
    else{
        buildTree(left,l,mid);
        buildTree(right,mid+1,r);
        seg[i] = seg[left]  + seg[right];
    }
}
/**
 * Find the sum for RANGE [s,e)
*/
int query(int i,int l,int r,int s,int e){
    if(l > r || r < s || e < l)
        return 0;
    if(s <= l && r <= e){
        return seg[i];
    }
    else{//if the part of the current segment (l,r) overlaps with queried range
    //then return the sum obtain from overlapping sections
        return query(left,l,mid,s,e) + query(right,mid+1,r,s,e);
    }
}

void update(int i,int l,int r,int data,int pos){
    if(l == r && pos == l){
        arr[pos] = data;
        seg[i] = data;
    }
    else{
        if(pos <= mid)//update on the left
            update(left,l,mid,data,pos);
        else if(pos > mid)//update on the right
            update(right,mid+1,r,data,pos);
        seg[i] = seg[left] + seg[right];
    }
}

int main(){
    //height of the segment tree
    int x = ceil(log2(n))+1;
    //number of nodes in the segment tree
    int MAX_SIZE = 2*pow(2,x) - 1;
    memset(seg,0,sizeof(seg));
    buildTree(0,0,n-1);
    
    //                   0(0,7)
    //                  /     \
    //                 1(0,3)  2(3,7)
    //                /\       /\
    //               3  4     5  6
    cout<<query(0,0,n-1,0,4)<<"\n";
    // cout<<query(0,0,n-1,3,6)<<"\n";
    update(0,0,n-1,2,2);
    cout<<query(0,0,n-1,0,4)<<"\n";
    return 0;
}