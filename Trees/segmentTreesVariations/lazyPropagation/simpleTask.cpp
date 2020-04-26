#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+1;
int tree[27][4*maxn],lazy[27][4*maxn];
int n,q;
char s[maxn];
int cnt[26];
void build(int i,int l,int r){
    if(l == r){
        tree[s[l]-'a'][i] = 1;//increment the count of character (s[l]) in it's segment tree
        for(int j = 0;j<26;++j){
            lazy[j][i] = -1;
        }
        return;
    }
    int m = l+(r-l)/2;
    build(i+i+1,l,m);
    build(i+i+2,m+1,r);
    for(int j = 0;j<26;++j){
        lazy[j][i] = -1;
        tree[j][i] = tree[j][i+i+1] + tree[j][i+i+2];
    }
}

void update(int i,int l,int r,int L,int R,int val,int whichone){
    if(lazy[whichone][i]!=-1){
        tree[whichone][i] = lazy[whichone][i]*(r-l+1);
        if(l!=r){
            lazy[whichone][i+i+1] = lazy[whichone][i];
            lazy[whichone][i+i+2] = lazy[whichone][i];
        }
        lazy[whichone][i]=-1;
    }
    if(L<=l && r<=R){
        tree[whichone][i] = val * (r-l+1);
        if(l!=r){
            lazy[whichone][i+i+1] = val;
            lazy[whichone][i+i+2] = val;
        }
        return;
    }
    if(l>r or L > R or r <L or R < l) return;
    int m = l+(r-l)/2;
    update(i+i+1,l,m,L,R,val,whichone);
    update(i+i+2,m+1,r,L,R,val,whichone);
    tree[whichone][i] = tree[whichone][i+i+1] + tree[whichone][i+i+2];
}


int query(int i,int l,int r,int L,int R,int whichone){
    if(lazy[whichone][i]!=-1){
        tree[whichone][i] = lazy[whichone][i] * (r-l+1);
        if(l!=r){
            lazy[whichone][i+i+1] = lazy[whichone][i];
            lazy[whichone][i+i+2] = lazy[whichone][i];
        }
        lazy[whichone][i] = -1;
    }
    if(L <=l && r<=R){
        return tree[whichone][i];
    }
    if(l > r or L > R or r < L or R < l){
        return 0;
    }
    int m = l+(r-l)/2;
    return query(i+i+1,l,m,L,R,whichone) + query(i+i+2,m+1,r,L,R,whichone);
}

void get(int i,int l,int r,int whichone){
    if(lazy[whichone][i]!=-1){
        tree[whichone][i] = lazy[whichone][i] * (r-l+1);
        if(l!=r){
            lazy[whichone][i+i+1] = lazy[whichone][i+i+2] = lazy[whichone][i];
        }
        lazy[whichone][i] = -1;
    }
    if(!tree[whichone][i]) return;
    if(l == r){
        s[l] = whichone + 'a';
        return;
    }
    if(l > r) return;
    int m = l+(r-l)/2;
    get(i+i+1,l,m,whichone);
    get(i+i+2,m+1,r,whichone);
}

int main(){
    scanf("%d %d",&n,&q);
    scanf("%s",s);
    // printf({"%s\n",s);
    build(0,0,n-1);
    while(q--){
        int x,y,up;
        scanf("%d%d%d",&x,&y,&up);
        --x,--y;

        for(int j = 0;j < 26;++j){
            /*query the count of each character from 0 to 26*/
            cnt[j] = query(0,0,n-1,x,y,j);
        }
        int curr = x;
        if(!up) curr = y;//non-increasing order
        for(int j = 0;j < 26;++j){
            if(!cnt[j]) continue;
            update(0,0,n-1,x,y,0,j);
            if(up){
                update(0,0,n-1,curr,curr+cnt[j]-1,1,j);
                curr+=cnt[j];
            }
            else{
                update(0,0,n-1,curr-cnt[j]+1,curr,1,j);
                curr-=cnt[j];
            }
        }

    }
    for(int i = 0;i < 26;++i){
        get(0,0,n-1,i);
    }
    printf("%s",s);
    return 0;
}   