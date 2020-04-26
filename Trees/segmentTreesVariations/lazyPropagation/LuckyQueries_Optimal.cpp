#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e6 + 5;
string s;
struct stree{
    int n4,n7,n47,n74;
    bool to_update = false;
    void take(char ch)
    {
        if(ch == '4')
            n4 = n47  = n74 = 1;
        else
            n7 = n47 = n74 = 1;
    }
    
    void flip(){
        swap(n4,n7);
        swap(n47,n74);
    }
    
    void merge(stree &a,stree &b)
    {
        n4 = a.n4 + b.n4;
        n7 = a.n7 + b.n7;
        n47 = max({a.n4 + b.n7,a.n4 + b.n47,a.n47 + b.n7});
        n74 = max({a.n7 + b.n4,a.n74 + b.n4,a.n7 + b.n74});
    }
};
    
stree seg[4*maxn];
    
void build(int i,int l,int r)
{
    if(l == r)
    {
        seg[i].take(s[l]);
        return;
    }
    int m = l+((r-l)>>1);
    build(i+i+1,l,m);
    build(i+i+2,m+1,r);
    seg[i].merge(seg[i+i+1],seg[i+i+2]);
}
    
    
void updatelazy(int i,int l,int r,int L,int R){
    if(seg[i].to_update)
    {
        //swap number of 4 and 7
        //swap number of 47 and 74
        seg[i].flip();
        if(l!=r)
        {
            seg[i+i+1].to_update = !seg[i+i+1].to_update;
            seg[i+i+2].to_update = !seg[i+i+2].to_update;
        }
        seg[i].to_update = !seg[i].to_update;
    }
    if(r < L || R < l)
        return;
    if(L <=l && r<= R)
    {
        seg[i].flip();
        if(l!=r)
        {
            seg[i+i+1].to_update = !seg[i+i+1].to_update;
            seg[i+i+2].to_update = !seg[i+i+2].to_update;
        }
        return;
    }
    
    int m = l+((r-l)>>1);
    updatelazy(i+i+1,l,m,L,R);
    updatelazy(i+i+2,m+1,r,L,R);
    seg[i].merge(seg[i+i+1],seg[i+i+2]);
}
     
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n,m;
    cin >> n >> m;
    cin >> s;
    build(0,0,n-1);
    while(m--)
    {
        string q;
        cin >> q;
        if(q[0] == 's')
        {
            int l,r;
            cin >> l >> r;
            --l,--r;
            updatelazy(0,0,n-1,l,r);
        }
        else
            cout << seg[0].n47 <<"\n";
    }
    return 0;
}