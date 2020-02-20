#include<bits/stdc++.h>
using namespace std;
const int N = 201;

map<string,vector<string>> g;
// map<string,int> dp;

int  dfs(string u,string par){
    int dp = 1;
    int mx = 0;
    for(string v : g[u]){
        if(v == par) continue;
        
        mx = max(mx,dfs(v,u));
    }
    return dp+mx;
}

int main(){
    freopen("input_522A.txt","r",stdin);
    freopen("output_522A.txt","w",stdout);
    int n;
    cin>>n;
    string name1;
    string reposts;
    string name2;
    for(int i =1;i<=n;i++){
        cin>>name1>>reposts>>name2;
        transform(name1.begin(),name1.end(),name1.begin(),::tolower);
        transform(name2.begin(),name2.end(),name2.begin(),::tolower);
        g[name2].push_back(name1);
    }

    string root = "polycarp";
   

    cout<<dfs(root,root)<<"\n";
    return 0;
}