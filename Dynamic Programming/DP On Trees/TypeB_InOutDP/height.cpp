#include<bits/stdc++.h>
using namespace std;
const int N = 1000;
vector<int> g[N];
/**
 * Given a tree of n nodes and m edges.
 * Print height of the tree for each node of the tree when considered as root of the tree.
 * 
*/
/**
 * Calculate the height of the tree for a given node u
*/
int dfs(int u,int p){
    int h = 0;
    for(int v : g[u]){
        if(v == p) continue;
        h = max(h,1 + dfs(v,u));
    }
    return h;
}
/*O(n*(n+m)) = O(n^2)*/
void bruteSolve(int n){
    int height[n+1];
    height[0] = -1;
    for(int i = 1;i<=n;i++){
        height[i] = dfs(i,0);
    }
    for(int i = 1;i<=n;i++)
        // cout<<"Height of tree when node "<<i<<" is root : "<<height[i]<<"\n";
        cout<<height[i]<<" ";
    cout<<"\n";
}


/**
 * O(N) approach 
 * Using In-Out DP
*/
int in[N];//in[NODE] stores the height of the subtree rooted at NODE
int out[N];//out[NODE] stores the height of the out-tree when neglecting the subtree rooted at NODE
/**
 * To compute the in[NODE] for all nodes with root node r
*/
void dfsI(int u,int p){
    in[u] = 0;
    for(int v : g[u]){
        if(v == p) continue;
        dfsI(v,u);
        in[u] = max(1 + in[v],in[u]);
    }
}
/**
 * Prequisites : out[parent] and in[siblings(u)] must already be computed
 * To compute the out[NODE] for all nodes 
 * out[NODE] = 1 + max(out[ParentOfNode],1 + mx);
 * where mx = in[v] such that v is siblings(u)
*/
void dfsII(int u,int p){
    int mx1(-1),mx2(-1);
    //find first two max in[Sibligs(v)] (why? see in the next for loop)
    for(int v : g[u]){
        if(v == p) continue;
        if(in[v] >= mx1){
            mx2 = mx1;
            mx1 = in[v];
        }
        else if(in[v] > mx2){
            mx2 = in[v];
        }
    }
    //u is the parent
    //v is the child
    //out[v] = max(1 + out[u],2 + use);
    for(int v : g[u]){
        if(v == p) continue;
        int use = mx1;//use the max sibling for node v
        
        if(use == in[v])//if max sibling is the node itself
            use = mx2;//use the second max sibling of node v

        out[v] = max(1 + out[u],2 + use);
        dfsII(v,u);
    }

}

void efficientSolve(int n){
    // memset(in,0,sizeof(in));
    // memset(out,0,sizeof(out));
    dfsI(1,0);
    dfsII(1,0);
    //finally height of tree rooted at node i  =  max(in[i],out[i])
    for(int i = 1;i<=n;i++){
        // cout<<"Height for root "<<i<<" : "<<max(in[i],out[i])<<"\n";
        cout<<max(in[i],out[i])<<" ";
    }cout<<"\n";
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int t;
    cin>>t;
    while(t--){
        int n,m;
        cin>>n>>m;
        int x,y;
        for(int i = 0;i<m;i++){
            cin>>x>>y;
            g[x].push_back(y);
            g[y].push_back(x);
        }
        bruteSolve(n);
        efficientSolve(n);
    }
    return 0;
}