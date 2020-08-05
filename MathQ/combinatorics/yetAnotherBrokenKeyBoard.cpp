#include<bits/stdc++.h>
using namespace std;
// https://codeforces.com/problemset/problem/1272/C
int main(){
    int n,k;
    cin >> n >> k;
    string s;
    cin >> s;
    vector<int> a(26,0);
    for(int i = 0;i<k;++i){
        char ch;
        cin >> ch;
        a[ch-'a'] = 1;
    }

    long long int answer = 0;
    long long int cnt = 0;
    for(int i = 0;i<n;++i){
        if(a[s[i]-'a']){
            ++cnt;
        }
        else{
            answer += (cnt *(cnt+1))>>1;
            cnt = 0;
        }
    }

    answer += (cnt *(cnt+1))>>1;
    cout << answer << "\n";
    return 0;
}