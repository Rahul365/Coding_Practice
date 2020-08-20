#include<bits/stdc++.h>
using namespace std;
const int INF = 1e9+7;
/**
 * Edmond Karp Algorithm is just the implementation of Ford Fulkerson Idea to compute Max Flow
*/
int n;
vector<vector<int>> capacity;//at first it stores the actual capacity of every eges
//, but during the algorithm it stores the residual capacity = max capacity - flow value
vector<vector<int>> adj;//adjacency matrix to represent graph
vector<int> parent;

int bfs(int s,int t){
    fill(parent.begin(),parent.end(),-1);
    parent[s] = -2;
    queue<pair<int,int>> q;
    q.push({s,INF});
    while(!q.empty()){
        int curr = q.front().first;
        int flow = q.front().second;
        q.pop();
        for(int nxt : adj[curr]){
            if(parent[nxt]==-1 && capacity[curr][nxt])
            {   
                int new_flow = min(flow,capacity[curr][nxt]);
                parent[nxt] = curr;
                if(nxt == t)
                    return new_flow;
                q.push({nxt,new_flow});
            }
        }
    }
    return 0;
}

int getmaxflow(int s,int t){
    int new_flow = INF;
    parent = vector<int>(n);
    int flow = 0;
    while(new_flow = bfs(s,t)){
        flow += new_flow;
        int curr = t;
        while(curr!=s){
            int par = parent[curr];
            capacity[par][curr]-=new_flow;//residual capacity for the directed edge
            capacity[curr][par]+=new_flow;//residual capacity for the reverse edge
            curr = par;
        }
    }
    return flow;
}

int main(){
    return 0;
}