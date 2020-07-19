#include<bits/stdc++.h>
using namespace std;
using  ll = long long int;
/**
 * Centroid Decomposition on Tree : 
 * In a tree of N nodes , a centroid of that tree is a node removing which will divide the tree into forests
 * each having number of nodes not more thant N/2
 * 
 * in other words,
 * A node is a centroid node in a tree,
 * if( max(N-s(u),s(v1),....s(vk)) <= N/2) where vi is ith children of node v
 * ans S(x) is size of subtree (number of nodes in the tree) rooted at node x
 * 
 * Algorithm :

    1) Select arbitrary node v
    2) Start a DFS from v, and setup subtree sizes
    3) Re-position to node v (or start at any arbitrary v that belongs to the tree)
    4) Check mathematical condition of centroid for v
        (4.1)If condition passed, return current node as centroid
        (4.2)Else move to adjacent node with ‘greatest’ subtree size, and back to step 4


 * int findcentroid(int node,int parent,int N){
 *      vis[node] = true;
 *      heavy_childe = -1;//child node with maximum number of nodes in its subtree
 *      is_centroid = true;//speculation that current node is centroid
 *      for(child : chilrens[node]){
 *          if(vis[child] || iscentroid[child]) continue;
 *          if(subtreesize[child] >  N/2) is_centroid = false;
 *          heavy_child = (heavy_child == -1?child : max(subtreesize[heavychild],subtreesize[child]));
 *      }
 *      if(is_centroid && N - subtreesize[node] <= N/2) return node;
 *      return findcentroid(heavychild,node,N);
 * }
 * 
 * void dfs(int node , int parent){
 *    ++subtreesize[node];
 *      vis[child] = true;
 *    for(child : childrens[node]){
 *      if(vis[child] || centroid[child]) continue;
 *      dfs(child,node);
 *      subtreesize[node] += subtreesize[child];
 *    }
 * }
 * 
 * 
 * int findcentroid(int node){
 *  for(each node ) vis[node] = false,subtreesize[node] = 0
 *  dfs(node,node);//compute the subtree sizes from node 
 *  N = subtree[node];//number of nodes in the tree rooted from node
 *  for(each node ) vis[node] = false;
 *  int centroid = findcentroid(node,node,N)
 *  iscentroid[centroid] =true;
 *  return centroid;
 *  }
 * 
 * int decmposeTree(node):
 *     centroidnode = findcentroid(node)
 *      for(child : childrens[centroidnode]){
 *          if(!iscentroid[child]){
 *              child_centroid = decomposeTree(child);
 *              addedge(centroitree,centroidnode,child_centroid);
*            }
 *        }
 *      }
 * return centroidnode
 * 
 * 
 * 
 * time Complexity : 
 * O(n) time for traversing all the nodes of the tree   
 */
const int maxn = 1e5+11;
vector<int> g[maxn];//adjacency list for original tree
vector<int> cg[maxn];//centroid decomposed tree from original tree
vector<int> subtree(maxn);//to store the size of the subtree rooted at node i
vector<bool> iscentroid(maxn,false);//to mark whether node is added to centroid decomposed tree or not
vector<bool> vis(maxn);//to mark the nodes in the tree as visited 
void dfs(int u,int p){
    ++subtree[u];
    vis[u] = true;
    for(int v : g[u]){
        if(v==p || vis[v] || iscentroid[v]) continue;
        dfs(v,u);
        subtree[u] += subtree[v];
    }
}
//max(N-subtree[u],subtree[{childrens of u}]) <= N/2
int findcentroid(int u,int N){
    int heavy_child = -1;
    bool ok = true;//current node u is centroid of the tree
    vis[u] = true;
    for(int v  : g[u]){
        if(vis[v] || iscentroid[v]) continue;
        if(heavy_child == -1 or subtree[heavy_child] < subtree[v]){
            heavy_child = v;
        }
        if(subtree[v]  > N/2) ok = false;
    }
    if(ok && N - subtree[u] <= N/2) return u;
    return findcentroid(heavy_child,N);
}

int findcentroid(int u){
    fill(vis.begin(),vis.end(),false);
    fill(subtree.begin(),subtree.end(),0);
    dfs(u,u); //to setup subtree sizes of each node rooted dowm from node u
    int N = subtree[u];// number of the nodes in the subtree rooted down from node u
    fill(vis.begin(),vis.end(),false);
    int centroid = findcentroid(u,N);
    iscentroid[centroid] = true;
    return centroid;
}

int decomposeTree(int u){
    int centroid = findcentroid(u);
    for(int child  : g[centroid]){
        if(!iscentroid[child]){
            int childCentroid = decomposeTree(child);
            cg[centroid].push_back(childCentroid);
            cg[childCentroid].push_back(centroid);
        }
    }
    return centroid;
}

void traversal(int u,int p,int depth){
    cout << u << "(" <<depth<< ") , ";
    for(int v : cg[u]){
        if(v == p) continue;
        traversal(v,u,depth+1);
    } 
}

void addEdge(int u,int v){
    g[u].push_back(v);
    g[v].push_back(u);
}

int main(){
    int n = 16;
    // addEdge(1, 4); 
    // addEdge(2, 4); 
    // addEdge(3, 4); 
    // addEdge(4, 5); 
    // addEdge(5, 6); 
    // addEdge(6, 7); 
    // addEdge(7, 8); 
    // addEdge(7, 9); 
    // addEdge(6, 10); 
    // addEdge(10, 11); 
    // addEdge(11, 12); 
    // addEdge(11, 13); 
    // addEdge(12, 14); 
    // addEdge(13, 15); 
    // addEdge(13, 16); 
    cin >> n;
    for(int i= 0;i<n-1;++i){
        int u,v;
        cin >> u >> v;
        addEdge(u,v);
    }
    int root = 1;
    cout << (root = decomposeTree(1)) <<"\n";
    traversal(root,root,0);
    return 0;
}