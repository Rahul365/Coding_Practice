#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <set>
#define pii pair<int,int>
#define min_pqueue priority_queue<pii,vector<pii>,greater<pii>>
using namespace std;
const int maxn = 1e5+5;
const int INF = 1e5;
const int LN = 18;
bool ERROR_LOG = false;
int n;
vector<int> g[maxn];
set<pair<int,int>> Q[maxn];
bool color[maxn];
/**Finding lca and distance between two nodes in O(log n)******/
int pr[maxn][LN];
int level[maxn];
int findlca(int u,int v){
    if(level[u] < level[v]) swap(u,v);
    int lg = 0;
    while((1<<lg) <= level[u]){
        ++lg;
    }
    --lg;
    for(int i = lg;i>=0;--i){
        if(level[u] - (1<<i) >= level[v]) u = pr[u][i];
    }
    if(u == v){
    //   if(ERROR_LOG)
    //   cerr << "lca : "<<u<<"\n"; 
      return u;
    }
    for(int i = lg;i>=0;--i){
        if(pr[u][i]!=-1 && pr[u][i] != pr[v][i]){
            u = pr[u][i];
            v = pr[v][i];
        }
    }
    // if(ERROR_LOG)
    // cerr << "lca : "<<pr[u][0]<<"\n"; 
    return pr[u][0];
}

int dist(int u,int v){
    // if(ERROR_LOG)
    // cerr <<u << ", "<<v<<" ";
    return level[u] + level[v] - 2*level[findlca(u,v)];
}

void dfs(int u,int p){
    level[u] = 1 + level[p];
    pr[u][0] = p;
    for(int v : g[u]){
        if(v == p) continue;
        dfs(v,u);
    }
}
/**-------------****/

int cpar[maxn];//Populated via using Centroid Decomposition On Trees
/***----Centroid Decomposition on tree------------****/
struct CDP{
    int subtree[maxn];
    bool centroid[maxn],vis[maxn];
    void dfs(int u,int p){
        subtree[u] = 1;
        for(int v : g[u]){
            if(v == p || centroid[v]) continue;
            dfs(v,u);
            subtree[u] += subtree[v];
        }
    }

    int findcentroid(int u,int p,int N){
        int hc = -1;
        bool ok = true;
        for(int v : g[u]){
            if(v == p ||  centroid[v]) continue;
            ok &= !(2*subtree[v] > N);
            hc = hc==-1 || subtree[hc] < subtree[v] ? v : hc;
        }
        if(ok && !(2*(N - subtree[u])>N)) return u;
        return findcentroid(hc,u,N);
    }


    int decomposeTree(int u){
        dfs(u,u);
        int cu = findcentroid(u,pr[u][0],subtree[u]);
        centroid[cu] = true;
        for(int v : g[cu]){
            if(!centroid[v]){
                int cv = decomposeTree(v);
                cpar[cv] = cu;
            }
        }
        return cu;
    }

    void init(int r){
        memset(cpar,0,sizeof cpar);
        memset(centroid,false,sizeof centroid);
        r = decomposeTree(r);
    }

}CD0;
/*******------------------------***************/
/**-----------------*/
const int MAXN = maxn;
struct CentroidDecomposition{
  vector<int> L[MAXN];
  int subsize[MAXN];

  void dfsii(int cur, int p){
    subsize[cur] = 1;

    for(int i = 0;i < L[cur].size();++i){
      int to = L[cur][i];

      if(to != p && cpar[to] == -1){
        dfsii(to,cur);
        subsize[cur] += subsize[to];
      }
    }
  }

  void centroid_decomposition(int cur, int p, int n, int prevc){
    for(int i = 0;i < L[cur].size();++i){
      int to = L[cur][i];

      if(to != p && cpar[to] == -1 && 2 * subsize[to] > n){
        centroid_decomposition(to,cur,n,prevc);
        return;
      }
    }

    cpar[cur] = prevc;

    for(int i = 0;i < L[cur].size();++i){
      int to = L[cur][i];

      if(cpar[to] == -1){
        dfsii(to,-1);
        centroid_decomposition(to,cur,subsize[to],cur);
      }
    }
  }

  void init(int start){
    memset(cpar,-1,sizeof cpar);
    dfsii(start,-1);
    centroid_decomposition(start,-1,subsize[start],-2);
  }
}CD;
//-------------------


void init(){
    for(int i = 0;i<=n;++i){
        color[i] = false;
        level[i] = 0;
        cpar[i] = -1;
        for(int l = 0; l < LN;++l){
            pr[i][l] = -1;
        }
    }
}

int closestW(int node)
{
    auto  &qq = Q[node];
    if(!qq.empty()){
        return qq.begin()->first;
    }
    return INF;
}

#define USE_FILE 1
int main(){
    if(USE_FILE){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    }
    scanf("%d",&n);
    init();
    for(int i= 0;i<n-1;++i){
        int u,v;
        scanf("%d%d",&u,&v);
        g[u].push_back(v);
        g[v].push_back(u);
        CD.L[u].push_back(v);
        CD.L[v].push_back(u);
    }
    // CD.init(1); //AC
    CD0.init(1); // AC 
    dfs(1,1);//to compute LCA and distance ,build sprase parent matrix
    for(int l = 1;l<LN;++l){
    for(int i=1;i<=n;++i){
            if(pr[i][l-1]!=-1){
                pr[i][l] = pr[pr[i][l-1]][l-1];
            }
        }
    }
   
    int q;
    scanf("%d",&q);

    while(q--){
        int t,x;
        scanf("%d%d",&t,&x);
        if(t){
            //find the closest white
            int ans = INF;
            int node = x;
            while(node > 0){
                ans = min(ans,dist(x,node) + closestW(node));
                node = cpar[node];
            }
            printf("%d\n",ans >= INF?-1:ans);
        }
        else{
            //flip the color
            color[x] = !color[x];
            int node = x;
            while(node > 0){
                if(color[x])
                Q[node].insert({dist(x,node),x});
                else
                Q[node].erase({dist(x,node),x});
                node = cpar[node];
            }
        }
    }
    return 0;
}