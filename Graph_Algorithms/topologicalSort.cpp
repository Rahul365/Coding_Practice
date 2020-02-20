#include<bits/stdc++.h>
#define print(a) for(int x : a) cout<<x<<" "; cout<<"\n"
using namespace std;
const int N = 1e5;
int V,E;
vector<int> g[N];
vector<int> indegree(N,-1);
int last = -1;

vector<int> topologicalsort(){
    queue<int> q;
    //push the vertices which have indegree[v] == 0 in queue
    for(int v = 1;v <= last;++v)
        if(indegree[v] == 0)
            q.push(v);

    vector<int> ans;//stores the topological sorting
    while(!q.empty()){
        int u = q.front();
        q.pop();
        ans.push_back(u);
        // cout<<u<<" ";
        // sort(g[u].begin(),g[u].end());
        for(int v : g[u]){
            if(--indegree[v] == 0){//push the adjacent vertices in the queue when indegree of it becomes 0
                q.push(v);
            }
        }
    }
    // cout<<"\n";
    print(ans);
    
    if(ans.size() == V)
        return ans;
    return {-1};
}

int main(){
    cin>>V>>E;
    int x,y;
    int e = E;
    while(e--){
        cin>>x>>y;
        if(indegree[x]==-1) indegree[x] = 0;
        if(indegree[y]==-1) indegree[y] = 0;
        indegree[y]++;
        g[x].push_back(y);
        last = max(max(x,y),last);
    }
    topologicalsort();
    return 0;
}