#include<bits/stdc++.h>
#define USE_FILE(i,o) freopen(i,"r",stdin); freopen(o,"w",stdout)
#define LOGS 0
using namespace std;
const int maxn = 1e5+1;
const int inf = 1e9+7;
int a[maxn];

template<typename T>
void minself(T &a,T b){
    a = min(a,b);
}
template<typename T>
void maxself(T &a,T b){
    a = max(a,b);
}


/**
 * 1)Minimize [l,r] with some x such that a[i] = min(a[i],x) for i belongs to [l,r]
 * 2)RangeSum from [l,r]
 * Solution  :  Armotized  O((n+q)logn)
 */
int seg[4*maxn][4];//(max,max2,sum,cntmax)
int push[4*maxn]={inf};



void printnode(int node){
    if(LOGS){
    cerr << "Node : "<<node<< " ";
    for(int i =0 ;i<4;++i) cerr << seg[node][i] <<" \n"[i==3];
    }
}

int* merge(int *a,int *b){
    int *c = new int[4];
    for(int i = 0;i<4;++i) c[i] = 0;
     c[1] = -inf;
     if(a[0] >= b[0]){
        c[0] = a[0];
        if(a[1]!=c[0]) maxself(c[1],a[1]);
        if(b[1]!=c[0]) maxself(c[1],b[1]);
        if(b[0]!=c[0]) maxself(c[1],b[0]);      
        c[3] = a[3] + (a[0] == b[0]?b[3]:0);  
    }
    else{
        c[0] = b[0];
        if(a[1]!=c[0]) maxself(c[1],a[1]);
        if(b[1]!=c[0]) maxself(c[1],b[1]);
        if(a[0]!=c[0]) maxself(c[1],a[0]);      
        c[3] = b[3];
    }
    c[2] = a[2] + b[2];//sum
    return c;
}

void buildseg(int i,int l,int r){
    if(l == r){
        seg[i][0] = seg[i][2] = a[l];
        seg[i][3] = 1;
        seg[i][1] = -inf;
        return;
    }
    int m =l+(r-l)/2;
    buildseg(i+i+1,l,m);
    buildseg(i+i+2,m+1,r);
    int *aux = merge(seg[i+i+1],seg[i+i+2]);
    for(int j=0;j<4;++j) seg[i][j] = aux[j];
    
}

void upintervalmin(int i,int l,int r,int L,int R,int x){
    if(push[i]!=inf){
        int &mx = seg[i][0];
        int &mx2 = seg[i][1];
        int &sum = seg[i][2];
        int &cntmx = seg[i][3];
        if(LOGS)
        cerr << "Pending push on node "<<i << " with value "<<push[i] <<" : ";
        if(!(push[i] >= mx)){
            if(l!=r){
                minself(push[i+i+1],push[i]);
                minself(push[i+i+2],push[i]);
            }
        }
        if(mx2 < push[i] && push[i] < mx){
            if(LOGS)
            cerr << sum << " to " << (sum-cntmx*(mx-push[i])) <<" ";
            sum -= cntmx * (mx-push[i]);
            mx = push[i];
        }
        if(LOGS)
        cerr <<"\n";
        printnode(i);
        push[i] = inf;
    }
    if(l > r || L > R || r < L || R < l){
        return;
    }
    int m = l+(r-l)/2;
    if(L<=l && r<= R){
        int &mx = seg[i][0];
        int &mx2 = seg[i][1];
        int &sum = seg[i][2];
        int &cntmx = seg[i][3];
        if(LOGS)
        cerr <<"Update "<<l << " "<< r<<" with value " << x;
        if(mx2 < x && x < mx){
            if(LOGS)
            cerr << sum << " to " << (sum-cntmx*(mx-x)) <<"\n";
            sum -= cntmx * (mx-x);
            mx = x;
            if(l!=r){
                if(LOGS)
                cerr << "push to child ["<<l<<" : " <<m <<"] ["<<m+1<<":"<<r<<"] "<<" with value "<<x<<"\n";
                minself(push[i+i+1],x);
                minself(push[i+i+2],x);
            }
        }
        else if(x <= mx2){
            if(l!=r){
                upintervalmin(i+i+1,l,m,L,R,x);
                upintervalmin(i+i+2,m+1,r,L,R,x);
                int *aux = merge(seg[i+i+1],seg[i+i+2]);
                for(int j=0;j<4;++j) seg[i][j] = aux[j];
            }
        }
        printnode(i);
        return;
    }
    // if(L <= m)
    upintervalmin(i+i+1,l,m,L,R,x);
    // if(m < R)
    upintervalmin(i+i+2,m+1,r,L,R,x);
    int *aux = merge(seg[i+i+1],seg[i+i+2]);
    for(int j=0;j<4;++j) seg[i][j] = aux[j];
    printnode(i);
}

int rangesum(int i,int l,int r,int L,int R){
    if(push[i]!=inf){
        int &mx = seg[i][0];
        int &mx2 = seg[i][1];
        int &sum = seg[i][2];
        int &cntmx = seg[i][3];
        if(LOGS)
        cerr << "Pending push on node "<<i << " with value "<<push[i] <<" : ";
        if(!(push[i] >= mx)){
            if(l!=r){
                minself(push[i+i+1],push[i]);
                minself(push[i+i+2],push[i]);
            }
        }
        if(mx2 < push[i] && push[i] < mx){
            if(LOGS)
            cerr << sum << " to " << (sum-cntmx*(mx-push[i])) <<" ";
            
            sum -= cntmx * (mx-push[i]);
            mx = push[i];

        }
        push[i] = inf;
        if(LOGS)
        cerr <<"\n";
        printnode(i);
    }

    if(l > r || L > R || r < L || R < l){
        return 0;
    }
    if(L<=l && r <= R){
        return seg[i][2];
    }
    int m = l+(r-l)/2;
    return rangesum(i+i+1,l,m,L,R) + rangesum(i+i+2,m+1,r,L,R);
}

int main(){
    USE_FILE("task2input.txt","task2output.txt");
    memset(seg,0,sizeof seg);
    for(int i = 0;i<4*maxn;++i) push[i] = inf;
    int n;
    cin >> n;
    for(int i= 0;i <n;++i){
        cin >> a[i];
    }
    buildseg(0,0,n-1);
    int q;
    cin >> q;
    while(q--){
        int t,l,r;
        cin >> t >> l >> r;
        if(t == 0){
            int x;
            cin >> x;
            upintervalmin(0,0,n-1,l,r,x);
        }
        else{
            
            cout << rangesum(0,0,n-1,l,r) <<"\n";
        }
    }
    return 0;
}