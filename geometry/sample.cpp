#include<bits/stdc++.h>
using namespace std;
// BAD SCCORE _ AC

void query(int r1,int c1,int r2,int c2){
    cout << 1 << " "<< r1<<" "<<c1<<" " <<r2<<" "<<c2<<"\n"; fflush(stdout);
}

int mat[100][100];
void fillrow(int c,int &Q,int row,int l,int r){
    if(c <= 0) return;
    if(l == r){
        if(c){
            mat[row][l] = 1;
        }
        return;
    }
    if(r-l+1 == c){
        while(l<=r){
            mat[row][l++] = 1;
        }
        return;
    }
    int m = l +(r-l)/2;
    query(row,l,row,m);
    --Q;
    int v;
    cin >> v;
    fillrow(v,Q,row,l,m);
    fillrow(c-v,Q,row,m+1,r);
}

int main(){
    int t;
    cin >> t;
    while(t--){
        int n,p;
        cin >> n >> p;
        int q = 5*n*n;
        vector<int> cnt(n+1);
        for(int i = 1;i<=n;++i){
            for(int j = 1;j<=n;++j){
                mat[i][j] = 0;
            }
        }
        for(int i = 1;i<=n && q;++i)
        {
            --q;
            query(i,1,i,n);
            cin >> cnt[i];
            assert(cnt[i]!=-1);
            if(cnt[i]){
                fillrow(cnt[i],q,i,1,n);
            }
        }
        
        cout << 2 <<"\n";
        fflush(stdout);
        for(int i= 1;i<=n;++i){
            for(int j = 1;j<=n;++j)
            {
                    cout << mat[i][j] <<" ";fflush(stdout);
            }
            cout <<"\n"; fflush(stdout);
        }   
        int verdict;
        cin >> verdict;
        if(verdict == -1){
            exit(0);
        }
    }
    return 0;
}