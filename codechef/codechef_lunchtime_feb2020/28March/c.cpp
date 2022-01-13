#include<bits/stdc++.h>
using namespace std;


int main(){
    int t;
    cin >> t;
    
    while(t--){
        string s;
        cin >> s;
        int k,x;
        cin >> k >> x;
        int ans = 0;
        //10000 * 26
        vector<int> cnt(27,0);
        //subtask 1 when k = 0
        //a pefix is good when each character occurs at most k times
        for(char ch : s){
           ++cnt[ch-'a'];
           if(cnt[ch-'a'] == x+1 && k){
               --k;
               --cnt[ch-'a'];
               continue;
           }
           bool ok = true;
           for(int i = 0;i<26;++i){
               if(!cnt[i]) continue;
               if(cnt[i] <= x) continue;
               ok = false;
               break;
           } 
           if(ok){
               ++ans;
           }
        }
        cout << ans <<"\n";
    }   
    return 0;    
}