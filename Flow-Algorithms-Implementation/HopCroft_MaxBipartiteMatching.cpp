/*
  Problem : CHEF AND DAG , https://www.codechef.com/MARCH20A/problems/CHEFDAG
*/
#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+11;
const int NIL = 0;
const int INF = 1<<28;
vector<int> G[maxn],g[maxn];
int dist[maxn];
int match[maxn];
int n;
void init(){
  for(int i = 1;i< maxn;++i){
    G[i].clear();
    g[i].clear();
    dist[i] = INF;
    match[i] = NIL;
  }
}


bool bfs(){
  queue<int> q;
  for(int u =1;u<=n;++u){
    if(match[u] == NIL){
      q.push(u);
      dist[u] = 0;
    }
    else{
      dist[u] = INF;
    }
  }
  dist[NIL] = INF;
  while(!q.empty()){
    int u = q.front();
    q.pop();
    if(u==NIL) continue;
    for(int v : G[u]){
      if(dist[match[v]] == INF){
        dist[match[v]] = dist[u] + 1;
        q.push(match[v]);
      }
    }
  }
  
  return dist[NIL]!=INF;
}

bool dfs(int u){
  if(u == NIL) return true;
  for(int v : G[u]){
    if(dist[match[v]] == dist[u] + 1 && dfs(match[v])){
          match[u] = v;
          match[v] = u;
          return true;
    }
  }
  dist[u] = INF;
  return false;
}

int hopcroft_maxbipartite_matching(){
  int matching = 0;
  while(bfs()){
    for(int u = 1;u<=n;++u){
      if(match[u] == NIL && dfs(u))
      {
        ++matching;
      }
    }
  }
  return matching;
}


int main(){
    int t;
    cin >> t;
    while(t--){
        int k;
        cin >> n >> k;
        init();
        int edge[n+1][n+1];
        for(int i = 1;i<=n;++i)
            for(int j = 1;j<=n;++j)
                edge[i][j]= 0;
        for(int i = 0 ;i<k;++i){
            vector<int> p(n);
            for(int j = 0; j<n;++j){
                cin >> p[j];
                for(int l = 0;l<j;++l)
                    ++edge[p[l]][p[j]];
            }
        }
        vector<int> indeg(n+1,0);
        for(int i = 1;i<=n;++i){
            for(int j = 1;j<=n;++j){
                if(i ==j || edge[i][j] != k) continue;
                g[i].push_back(j);
                ++indeg[j];
            }
        }
        
        vector<int> outv;
        vector<int> inv;
        for(int i = 1;i<=n;++i)
        {
            if(g[i].size() != 0)
                outv.push_back(i);
            if(indeg[i]!=0)
                inv.push_back(i);
        }
        if(outv.size() == 0){
            cout << n << "\n";
            for(int i = 0;i<n;++i)
                cout << 0 <<" \n"[i==n-1];
            continue;
        }
        
        //build a bipartite graph
        unordered_map<int,int> outid,inid,pos;
        for(int i = 1;i<=outv.size();++i){
            outid[i] = outv[i-1];
        }
        for(int i = 1;i<=inv.size();++i){
            inid[i+outv.size()] = inv[i-1];
            pos[inv[i-1]] = i + outv.size();
        }
        for(int i = 1;i<=outv.size();++i){
            for(int v : g[outv[i-1]]){
                G[i].push_back(pos[v]);
            }
        }
        
        int N = n;
        n = outv.size();
        //hopcroft_maxbipartite_matching
        cout << N - hopcroft_maxbipartite_matching() <<"\n";
        
        vector<int> ans(N+1,0);
        for(int i= 1;i<=n;++i){
            ans[outid[i]] = inid[match[i]];
        }
        for(int i = 1;i<=N;++i)
            cout << ans[i] << " \n"[i==N];
           
    }
    return 0;
}
