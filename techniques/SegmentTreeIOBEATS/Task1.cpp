#include<bits/stdc++.h>
using namespace std;
#define USE_FILE(i,o) freopen(i,"r",stdin); freopen(o,"w",stdout)

const int maxn = 1e5+1;
int a[maxn],b[maxn],c[maxn];
int seg[4*maxn],push[4*maxn],cnt[4*maxn];
int segsum[4*maxn];

/*
     Task 1. There are two kinds of operations:

     For all i in [l,r], change A[i] to max(A[i], x)
     Query for the sum of A[i] where i in [l, r]

     --Yet to be solved--
*/

void buildseg(int i,int l,int r){
    if(l == r){
        seg[i] = segsum[i] = a[l];
        cnt[i] = 1;
        return;
    }
    int m = l+(r-l)/2;
    buildseg(i+i+1,l,m);
    buildseg(i+i+2,m+1,r);
    seg[i] = max(seg[i+i+1],seg[i+i+2]);
    cnt[i] = (seg[i] == seg[i+i+1]?cnt[i+i+1]:0) + (seg[i]==seg[i+i+2]?cnt[i+i+2]:0);
    segsum[i] = segsum[i+i+1] + segsum[i+i+2];
}

int rangemax(int i,int l,int r,int L,int R){
    if(l > r || L > R || r < L ||R <l) return 0;
    if(push[i]!=-1){
        segsum[i] += max(0,cnt[i]*(push[i] - seg[i]));
        seg[i] = max(seg[i],push[i]);
        if(l!=r){
            push[i+i+1] = max(push[i+i+1],push[i]);
            push[i+i+2] = max(push[i+i+2],push[i]);
        }
        push[i] = -1;
    }
    if(L<=l && r<=R) return seg[i];
    int m = l+(r-l)/2;
    return max(rangemax(i+i+1,l,m,L,R),rangemax(i+i+2,m+1,r,L,R));
}

int rangesum(int i,int l,int r,int L,int R){
    if(l > r || L > R || r < L || R <l){
        return 0;
    }
    if(push[i]!=-1){
        seg[i] = max(seg[i],push[i]);
        if(l!=r){
            push[i+i+1] = max(push[i+i+1],push[i]);
            push[i+i+2] = max(push[i+i+2],push[i]);
        }
        push[i] = -1;
    }
    if(L<=l && r<=R){
        return segsum[i];
    }
    int m = l+(r-l)/2;
    return rangesum(i+i+1,l,m,L,R) + rangesum(i+i+2,m+1,r,L,R);
}


void upintervalmax(int i,int l,int r,int L,int R,int val){
    if(l > r || L > R || r < L || R < l) return;
    if(push[i]!=-1){
        seg[i] = max(seg[i],push[i]);
        if(l!=r){
            push[i+i+1] = max(push[i+i+1],push[i]);
            push[i+i+2] = max(push[i+i+2],push[i]);
        }
        push[i] = -1;
    }

    if(L<=l && r<=R){
        seg[i] = max(seg[i],val);
        cerr << "update " << L << " : "<< R <<" with "<<val<<"\n";
        if(l!=r){
            push[i+i+1] = max(push[i+i+1],val);
            push[i+i+2] = max(push[i+i+2],val);
        }
        return;
    }
    int m = l+(r-l)/2;
    upintervalmax(i+i+1,l,m,L,R,val);
    upintervalmax(i+i+2,m+1,r,L,R,val);
    seg[i] = max(seg[i+i+1],seg[i+i+2]);
}

int main(){
    USE_FILE("task1input.txt","task1output.txt");
    memset(seg,0,sizeof seg);
    memset(push,-1,sizeof push);
    memset(cnt,0,sizeof cnt);
    memset(segsum,0,sizeof segsum);
    int n;
    cin >> n;
    for(int i = 0 ;i < n;++i){
        cin >> a[i];
        b[i] = a[i];
        c[i] = 0;
    }
    buildseg(0,0,n-1);
    int q;
    cin >> q;
    //update queries
    //and range max queries
    while(q--){
        int t,l,r;
        cin >> t >> l >> r;
        if(t == 0){
            //update
            int x;
            cin >> x;
            upintervalmax(0,0,n-1,l,r,x);
        }
        else if(t == 1){
            //rangemax
            cout << rangemax(0,0,n-1,l,r) <<"\n";
        }
        else if(t == 2){
            cout << rangesum(0,0,n-1,l,r) <<"\n";
        }
    }

    return 0;
}