#include<bits/stdc++.h>
#define boost ios_base::sync_with_stdio(false)
#define ll long long int
using namespace std;

int N;
ll *bitree;
// IntelPentiumCore#365

void update(int index,ll val){
    //cout<<"update from "<<index<<"\n";
    while(index < N){
        bitree[index] += val;
        index += ((index) &(-index));
    }
}

ll get(int index){
    ll sum = 0;
    while(index > 0){
        sum += bitree[index];
        index -= ((index) & (-index));
    }
    return sum;
}

ll sum(int l,int r){
    return get(r) - get(l-1);
}

void buildfenwicktree(int n,ll val){
    N = n+1;
    bitree = new ll[N];
    for(int i =0;i<N;i++) bitree[i] = 0;
}

int main(){
    boost;
    int n,m;
    ll c;
    cin>>n>>m>>c;
    buildfenwicktree(n,c);
    
    char type;
    int u(-1),v(-1);
    ll k;
    int p;
    //range update and point query
    while(m--){
      do{
          cin>>type;
      }while(!(type == 'S' || type == 'Q'));
      
        if(type == 'Q'){
            cin>>p;
            ll ans = get(p) + c;
            cout<<ans<<"\n";
        }
        else{
            cin>>u>>v>>k;
            // while(u<=v) update(u++,k);
             update(u,k);
             update(v+1,-k);
         }
        
        // for(int i = 0;i<N;i++) cout<<bitree[i]<<" "; cout<<"\n";
    }
    return 0;
}