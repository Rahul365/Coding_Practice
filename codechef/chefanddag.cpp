#include<bits/stdc++.h>
using namespace std;
const int NIL = 0;
const int INF = 1 << 28;
const int maxn = 1e5 + 11;
vector<int> g[maxn];
int n, m, p;
vector<int> dist(maxn);
vector<int> match(maxn);
bool vis[maxn];

int dfs(int u){
    vis[u] = true;
    for(int v : g[u])
    {
        if(match[v]==NIL or !vis[match[v]] && dfs(match[v])){
            match[v] = u;
            return 1;
        }
    }
    return 0;
}

int main() {
	int t;
	cin >> t;
	while (t--) {
		int k;
		scanf("%d%d", &n, &k);
		for (int i = 1; i <= n; ++i) {
			g[i].clear();
			match[i] = NIL;
			dist[i] = NIL;
		}
		vector<vector<int>> edge(n+1, vector<int>(n+1,0));
		for (int i = 0; i < k; ++i) {
			vector<int> perm(n);
			for (int j = 0; j < n; ++j) {
				scanf("%d", &perm[j]);
				for (int l = 0; l < j; ++l) {
					++edge[perm[l]][perm[j]];
				}
			}
		}

		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (i == j or edge[i][j] != k) continue;
				g[j].push_back(i);
			}
		}
		int flow = 0;
        for(int i = 1;i<=n;++i){
            memset(vis,false,sizeof vis);
            flow+=dfs(i);
        }
		printf("%d\n",n - flow);
		for (int i = 1; i <= n; ++i) {
			printf("%d ", match[i]);
		}
		printf("\n");
	}
	return 0;
}