#include<bits/stdc++.h>
using namespace std;
/*Find the smallest possible multiple of given number n consisting of only 0s and 1s*/
string findmultiple(int n){
    if(n == 1) return "1";
    vector<string> dp(20001,"");
    queue<int> q;
    q.push(1);
    dp[1] = "1";
    while(!q.empty()){
        int r = q.front();
        q.pop();
        if(r == 0)
        {
            return dp[r];
        }
        else{
            for(int v : {0,1}){
                //0 is first value to be checked for ,since it's BFS 
                //and we want the smallest multiple value for given n
                int nr = 10 * r + v;
                nr %= n;
                if(dp[nr].empty()){
                    dp[nr] = dp[r] + (char)(v+'0'); 
                    q.push(nr);
                }
            }
        }
    }
    assert(false);
}

int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        cout << findmultiple(n) <<"\n";
    }
    return 0;
}