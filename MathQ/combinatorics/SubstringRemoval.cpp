#include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+11;
const long long int mod = 998244353;
using ll = long long int;
// https://codeforces.com/problemset/problem/1096/B
int main(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    // s = string(20000,'a');
    // n = s.length();
    /*
        Since we must remove exactly one substring and all the characters after removing substring must be equal
        So we have two options to consider:
        1) we can maintain string which contain all characters equal from left end and count the substrings from some left index till the end that we can remove to acheive our target string
        2) we can maintain string which contain all characters equal from right end and count the substrings to remove
        
        Cases to consider:
        1)either all the characters are same in the give string
        then answer = 2*n-1
        2)s[0]!=s[n-1] (last and first character don't match)
        In this case we consider both left and right part separately
        thus answer = (remove the whole string) + (remove the left substrings) + (remove right substrings)
        here remove left substring means that
        if we have s ="aaabbbbaaaa"  then we see that there are 3 'a' on left so we can remove s[1,n-1],s[2,n-1],s[3,n-1]
        3) s[0] == s[n-1] ,
         answer = (no.of choices of left end) * (no. of choices of right end)
    */
    vector<int> cnt(26,0);
    for(int i= 0;i <n;++i){
        ++cnt[s[i]-'a'];
    }
    long long int answer = 0;
    if(cnt[s[0]] == n){
        answer = (2*cnt[s[0]] - 1)%mod;
    }
    else{
        answer = 0;//empty substring
        ll left = 0;
        int i= 0;
        while(s[i]==s[0]){
            ++i;
            ++left;
        }
        ll right = 0;
        int j = n-1;
        while(s[j] == s[n-1]){
            ++right;
            --j;
        }
        
        
        if(s[0] == s[n-1]){
            if(i <= j){
                left += 1;
                right += 1;
            }
            answer += (left * right);
            answer %=mod;
        }
        else{
            answer = (1 + left + right)%mod;
        }
    }
    /*
        //Brute force
        for(int i = 0;i<n;++i){
            for(int j = i+1;j<=n;++j){
                int cnt = 0;
                for(int k = 0;k<26;++k)
                {
                    int toremove = dp[n][k] - (dp[j][k]-dp[i][k]);
                    // cerr << i<<" " <<j-1<<" "<<char(k+'a') <<" "<<dp[j][k] - dp[i][k] <<" \n"[k==25];
                    if(toremove && ++cnt>1) break;
                }
                if(cnt<=1) answer = (answer + 1)%mod;
            }
        }
    */
    cout << answer <<"\n";
    return 0;
}