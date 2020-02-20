#include<bits/stdc++.h>
using namespace std;

void init(int n,int *p){
    for(int i = 0;i<n;i++)
           p[i] = i;
}

int main(){
    int n;
    cin>>n;
    int c[n];
    int k[n];
    int x[n],y[n];
    for(int i = 0;i<n;i++)
       cin>>x[i]>>y[i];
    for(int i = 0;i<n;i++)
       cin>>c[i];
    for(int i = 0;i<n;i++)
       cin>>k[i];
   
    int parent[n];
    init(n,parent);
    vector<int> power_plants;//cities where power plants are installed
    vector<pair<int,int>> edges;//connections built while connecting the cities
    long long mincost = 0;//mincost to build connections or install power plants
    vector<bool> vis(n,false);
    /**
     * Rest is apply prim's algorithm to find the minimum spanning tree 
     * And keep track of cities where power plant is installed and connections made between the cities
     * while minimum the cost to do so.
    */
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> q;
    for(int i = 0;i<n;i++)
        q.push({c[i],i});
    while(!q.empty()){
        int u = q.top().second;
        q.pop();
        if(vis[u]) continue;
        vis[u] = true;
        mincost += c[u];
        if(parent[u] == u)
            power_plants.push_back(u);
        else
            edges.push_back({min(parent[u],u),max(parent[u],u)});
       
        for(int v = 0 ;v<n;v++){
            if(v == u || vis[v]) continue;
            if((1LL * (k[u] + k[v]) * (abs(x[u]-x[v]) + abs(y[u]-y[v]))) < c[v]){
                c[v] = (k[u] + k[v]) * (abs(x[u]-x[v]) + abs(y[u]-y[v]));
                parent[v] = u;
                q.push({c[v],v});
            }
        }
    }
    cout<<mincost<<"\n";
    cout<<power_plants.size()<<"\n";
    for(int city : power_plants)
        cout<<city+1<<" ";
    cout<<"\n";
    cout<<edges.size()<<"\n";
    for(auto e  : edges)
         cout<<e.first+1<<" "<<e.second+1<<"\n";
   
    return 0;
}