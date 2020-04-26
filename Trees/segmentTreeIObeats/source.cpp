#include<bits/stdc++.h>
using namespace std;
/**
 * 
 * Standard problem : Given an array of n integers. Perform q queries of 2 types on it.\
 * \\Query 1) x l r : minimize all the elements a[i] where l<=i<=r with 'x' i.e. a[i] = min(a[i],x)
 * \\Query 2) l r : return sum of elements from a[l] to a[r] i.e. return (a[l] + a[l+1]+ ...+a[r-1]+ a[r])
 * 
 * (lazy propagation will not work here (why?))
 * Segment trees will be used, but in advanced form
 * ALgorithm : 
 * Two values will maintained in each node for subarray it's holding, firstMax and secondMax 
 * nodeOfSegmenTree : (secondMax,firstMax,sum,cnt_max)
 * 1) for sum[l:r] => if(secondMax < x < firstMax) return sum -= (firstMax - x)*cnt_max;
 * 2) if(x >= firstMax) : do nothing
 * 3) if(x <= secondMax) : go recursively in the tree
 * 
*/
//(secondmax,firstmax,sum,cnt_first_max);
template<typename T>
class segmentTreeBeats{
    vector<T> tree;
    int n;//number of elements in the array
    public :
    segmentTreeBeats(int _n){
        tree = vector<T>(4*_n+1);
        n = _n;
    }

    T merge(T &a ,T &b);//method for defining how to merge two nodes from left and right side of the tree

    // template<>
    void build(const vector<int> &a,int i,int l,int r){
        if(l == r){
            //insert in the node
            tree[i] = {a[r],a[r],a[r],1};//(secondmax,firstmax,sum,cnt_first_max)
            return;
        }
        int m = l  +((r-l)>>1);
        build(a,i+i,l,m);
        build(a,i+i+1,m+1,r);
        tree[i] = merge(tree[i+i],tree[i+i+1]);
    }

    void update(int L,int R,T x){
         update(1,1,n,L,R,x);
    }
  

    T query(int L,int R){
            return query(1,1,n,L,R);
    }
    
    T query(int i,int l,int r,int L,int R);//utility
    void update(int i,int l ,int r,int L,int R,T x);//utililty
};

template<typename T>
T segmentTreeBeats<T>::merge(T &a,T &b){
    T res;
    return res;
}

template<typename T>
void segmentTreeBeats<T> ::update(int i,int l ,int r,int L,int R,T x){
    if(l > r || L > r || l > R){
        return;
    }

    if(L<= l  && r <= R){
        return;
    }

    int m = l +((r-l)>>1);
    update(i+i,l,m,L,R,x);
    update(i+i+1,m+1,r,L,R,x);
    tree[i] = merge(tree[i+i],tree[i+i+1]);
}


template<typename T>
T segmentTreeBeats<T>:: query(int i,int l,int r,int L,int R){
    if(l > r || L > r || l > R){
        return 0;//dummy value
    }

    if(L<=l && r <= R){
        return tree[i];
    }

    int m =  l + ((r-l)>>1);
    if(R <= m){
        return query(i+i,l,m,L,R);
    }
    else if(m < L){
        return query(i+i+1,m+1,r,L,R);
    }
    
    return merge(query(i+i,l,m,L,R),query(i+i+1,m+1,r,L,R));
}

int main(){
    vector<int> a = {0,1,2,5,8};
    int  n = a.size();
    segmentTreeBeats<vector<int>> seg(n);
    seg.build(a,1,1,n-1);
    return 0;
}