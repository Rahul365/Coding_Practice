#include<bits/stdc++.h>
using namespace std;

class MajorityChecker {
    unordered_map<int,vector<int>> pos;
    vector<int> arr;
    vector<int> seg;
    int n;
public:
    int upperbound(vector<int> &a,int key){
        int i= 0;
        int j = a.size()-1;
        int ans = j+1;
        while(i<=j)
        {
            int m = i+(j-i)/2;
            if(a[m] <= key){
                i = m+1;
            }
            else{
                ans = m;
                j = m-1;
            }
        }
        return ans;
    }
    
    int lowerbound(vector<int> &a,int key){
        int i = 0, j= a.size()-1;
        int ans = -1;
        while(i<=j){
            int m = i+(j-i)/2;
            if(a[m] >= key){
                ans = m;
                j = m-1;
            }
            else{
                i = m+1;
            }
        }
        return ans;
    }
    
    int countocc(int x,int l,int r){
        if(pos.count(x) == 0) return 0;
        auto left = lowerbound(pos[x],l); 
        if(left==-1) return 0;
        auto right = upperbound(pos[x],r);
        if(right==-1) return 0;
        return right-left;
    }
    
    void build(int i,int l,int r){
        if(l == r){
            seg[i] = arr[l];
            return;
        }
        int m = l+(r-l)/2;
        build(i+i+1,l,m);
        build(i+i+2,m+1,r);
        int left = seg[i+i+1]!=-1?countocc(seg[i+i+1],l,r):-1;
        int right = seg[i+i+2]!=-1?countocc(seg[i+i+2],l,r):-1;
        if(left!=-1 && 2*left > r-l+1){
            seg[i] = seg[i+i+1];
        }
        if(right!=-1 && 2*right > r-l+1){
            seg[i] = seg[i+i+2];
        }
    }
    
    pair<int,int> query(int i,int l,int r,int L,int R){
        if(R < l or r < L) return {-1,-1};
        if(L <= l && r <= R)
        {
            int count = countocc(seg[i],L,R);
            if(2*count > R-L+1){
                return {seg[i],count};
            }
            else{
                return {-1,-1};
            }
        }
        int m = l+(r-l)/2;
        auto left = query(i+i+1,l,m,L,R);
        auto right = query(i+i+2,m+1,r,L,R);
        if(left.first !=-1 ) return left;
        if(right.first!=-1) return right;
        return {-1,-1};
    }
    
    MajorityChecker(vector<int>& a) {
        this->arr = a;
        n = a.size();
        for(int i= 0;i<n;++i){
            pos[a[i]].push_back(i);//this will help in finding the occurences of element arr[i] in the range [left,right]
        }
        // for(int i= 0;i<n;++i){
        //     cout << countocc(a[i],0,n-1) <<" ";
        // }
        seg = vector<int>(4*n+1,-1);
        build(0,0,n-1);
    }
    
    int query(int left, int right, int threshold) {
       auto res = query(0,0,n-1,left,right);
       if(res.second >= threshold) return res.first;
       return -1;
    }
};

/**
 * Your MajorityChecker object will be instantiated and called as such:
 * MajorityChecker* obj = new MajorityChecker(arr);
 * int param_1 = obj->query(left,right,threshold);
 */

int main(){
    return 0;
}