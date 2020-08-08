#include<bits/stdc++.h>
using namespace std;
// https://codeforces.com/problemset/problem/1166/A
int main(){
    int n;
    cin >> n;
    //given n students with n names
    //divide these students into two classrooms with goal to minimize the number of pairs of the students with the 
    //names that starts with the same letter
    //Best strategy is to divide the students whose name starts with the same letter into two classrooms evenly
    //then count the pairs from both the classes and add them to the answer
    //let m be number of students > 1
    //dividing will be (m/2 , m - (m/2))
    vector<int> cnt(26,0);
    for(int i = 0;i<n;++i){
        string s;
        cin >> s;
        ++cnt[s[0]-'a'];
    }
    auto count=[&](int x){ return (x*(x-1))>>1;};
    int ans = 0;
    for(int i = 0;i<26;++i)
            ans += count(cnt[i]>>1) +  count((cnt[i]>>1) + (cnt[i]%2));
    cout << ans <<"\n";
    return 0;
}