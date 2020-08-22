#include<bits/stdc++.h>
using namespace std;
// https://www.codechef.com/AUG20A/problems/SKMP
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        string p,s;
        cin >> s >> p;
        vector<int> cnt1(26,0);
        for(char c : s){
            cnt1[c-'a']++;
        }
        for(char c : p){
            cnt1[c-'a']--;
        }
        
        string r,ans = string(s.length(),'z'+1);
        for(int i = 0;i<26;++i){
            r += string(cnt1[i],char(i+'a'));
        }
        ans = r + p;
        for(int i = 0;i<r.length();++i){
            if(r[i] >= p[0]){
                int j = i;
                while(j < r.length() && r[j]<=p[0]){
                    ans = min(r.substr(0,j)+p+r.substr(j),ans);
                    ++j;
                }
                ans = min(r.substr(0,j)+p+r.substr(j),ans);
                break;
            }
        }
        cout << ans <<"\n";
    }
    return 0;
}