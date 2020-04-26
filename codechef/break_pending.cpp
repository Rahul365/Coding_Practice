#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+1;
int s,n;
int a[maxn],b[maxn];
//for subtask1
bool solve1(){
    set<int> s;
    for(int i = 0;i<n;++i){
        if(s.empty()){
            s.insert(a[i]);
        }
        if(s.find(a[i]) == s.end())
            return false;//card not on the table
        if(a[i] >= b[i])//don't have strict defense
            return false;
        s.insert(a[i]);
        s.insert(b[i]);
    }
    return true;
}
//for subtask2 
bool solve2(){
    if(n == 2)
        return a[0] < b[1] && b[0] < a[1];
    
    if(a[0] == a[n-1] && a[0] >= b[n-1]){
        return false;
    }
    if(b[0] == b[n-1] && a[0] <= b[n-1]){
        return false;
    }
    map<int,int> freq;
    for(int i = 0;i<n;++i){
        ++freq[a[i]];
        ++freq[b[i]];
    }
    for(auto &v : freq){
            if(v.second > n) return false;
    }
    return true;
}

bool solve(){
    cin >> n;
    for(int i = 0;i<n;++i) a[i];
    for(int i = 0;i<n;++i) b[i];
    sort(a,a+n);
    sort(b,b+n);
    if(solve1()){
        return true;
    }
    else if(s==1){
        return false;
    }
    return solve2();
}

int main(){
    int t;
    cin >> t >> s;
    while(t--)
    {
        cout << (solve()?"YES":"NO") <<"\n";
    }
    return 0;
}