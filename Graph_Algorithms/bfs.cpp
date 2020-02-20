#include<bits/stdc++.h>
using namespace std;
const int N = 1e5;
vector<int> g[N];
vector<bool> vis(N,false);

void bfs(int s){
    fill(vis.begin(),vis.end(),false);
    queue<int> q;
    q.push(s);
    vis[s] = true;
    while(!q.empty()){
        int u = q.front();
        cout<<u<<" ";
        q.pop();
        for(int v : g[u]){
            if(vis[v]) continue;
            vis[v] = true;
            q.push(v);
        }
    }

    cout<<"\n";
}

vector<pair<int,int>> gg[N];//g[u] = (v,w);  i.e weight(u,v)  = w(0 or 1);
vector<int> dist(N,0);
void bfs01(int s){
    fill(dist.begin(),dist.end(),INT_MAX);

    deque<int> q;
    q.push_back(s);
    dist[s] = 0;

    while(!q.empty()){
        int u = q.front();
        q.pop_front();

        for(pair<int,int> p: gg[u]){
            int v = p.first;
            if(dist[v] > dist[u] +  p.second){
                dist[v] = dist[u] + p.second;

                if(p.second == 0){
                    q.push_front(v);
                }
                else{
                    q.push_back(v);
                }
            }

        }
    }
    //dist of target resource from source s  = dist[target]
}

int main(){
    return 0;
}