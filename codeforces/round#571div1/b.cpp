#include<bits/stdc++.h>
using namespace std;
const int maxn = 2005;
const int INF = 4e6+11;
int dp[maxn][maxn];//dp[i][j] => minimum number of character needed to change to get to this cell(i,j)
char grid[maxn][maxn];

void min_self(int &a,int b){
    a = min(a,b);
}

void max_self(int &a,int b){
    a = max(a,b);
}


int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    for(int i = 0;i<n;++i){
        for(int j = 0;j<n;++j){
           cin >> grid[i][j];
            dp[i][j] = INF;
        }
    }
    //compute dp[i][j];
    dp[0][0] = 0;
    for(int i =0 ;i<n;++i){
        for(int j = 0;j<n;++j){
            if(i!=0){
                min_self(dp[i][j],dp[i-1][j]);//from up
            }
            if(j!=0){
                min_self(dp[i][j],dp[i][j-1]);//from left
            }
            if(grid[i][j]!='a')
                ++dp[i][j];
        }        
    }
    int max_pref = 0;
    //if i am at cell [i][j] => maximum path length i can cover upto this cell from [0][0] is (i + j + 1)
    //as we are allowed to go to either right or down from any cell [i][j] => (cell[i+1][j],cell[i][j+1])
    for(int i = 0;i<n;++i){
        for(int j = 0;j<n;++j){
            if(dp[i][j] <=k){
                max_pref = max(max_pref,i+j+1);
            }
        }
    }
    vector<pair<int,int>> list;
    for(int i = 0;i<n;++i){
        for(int j = 0;j<n;++j){
            if(dp[i][j] <= k && i+j+1 == max_pref){
                    list.emplace_back(i,j);
            }
        }
    }
    auto inside =[&](int i,int j){
        return i>=0 && i < n && j>=0 && j<n;
    };

    string ans(max_pref,'a');
    if(list.empty())
    {
        ans += grid[0][0];
        list.emplace_back(0,0);
    }
    while(!list.empty()){
        char best_next = 'z';
        vector<pair<int,int>> new_list;
        for(auto p : list){
            for(int d_r : {0,1}){
                int d_c = 1 - d_r;
                int r = p.first + d_r;
                int c = p.second + d_c;
                if(!inside(r,c)) continue;
                if(best_next >= grid[r][c]){
                    if(grid[r][c] < best_next)
                        new_list.clear();
                    best_next = grid[r][c];
                    new_list.emplace_back(r,c);
                }
            }
        }
        if(new_list.empty()) break;
        ans += best_next;
        list = new_list;
        //remove duplicate cells to avoid retraversing the same
        sort(list.begin(),list.end());
        list.resize(unique(list.begin(),list.end())-list.begin());
    }

    cout << ans <<"\n";
    return 0;
}