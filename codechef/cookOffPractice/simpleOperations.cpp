#include<bits/stdc++.h>
using namespace std;

int main(){
    int t;
    cin >> t;
    while(t--){
        string s,r;
        cin >> s>> r;
        vector<int> gaps;
        int k = 0;//number of intervals
        int len = 0;//sum of all the intervals length
        int l = -1;
        int pl = -1;
        for(int i = 0;i<=s.length();++i){
            if(i < s.length() && s[i]!=r[i]){
                if(l == -1) l = i;
            }
            else if(l!=-1 && (i==s.length() or s[i] == r[i])){
                len += (i-l);
                ++k;
                if(pl!=-1)
                gaps.push_back(l-pl-1);
                pl = i-1;
                l=-1;
            }
        }
        int ans = k * len;
        sort(gaps.begin(),gaps.end()); 
        for(int &g : gaps){
            --k;
            len += g;
            ans = min(ans,k * len);
        }
        cout << ans <<"\n";
    }
    return 0;
}