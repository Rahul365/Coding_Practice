#include<bits/stdc++.h>
using namespace std;
using ll = long long int;

void buildlps(int *&f,string s){
    int n = s.length();
    f = new int[n];//f[i]=>length of the longest common prefix which is also suffix of this string 's'
    for(int i = 0;i<n;++i) f[i] = 0;
    int i = 1,j=0;
    while(i < n){
        if(s[i] == s[j]){
            f[i] = ++j;
            ++i;
        }
        else if(j){
            j = f[j-1];
        }
        else{
            ++i;
        }
    }
}

void buildlps(int *&f,int *p,string s){
    int n = s.length();
    f = new int[n];
    for(int i = 0;i<n;++i) f[i] = 0;
    int i = 1,j=0;
    while(i < n){
        if(s[i] == s[j]){
            ++j;
            if(2*j > i+1){
                j = p[j-1];
            }
            f[i] = j;
            ++i;
        }
        else if(j){
            j = p[j-1];
        }
        else{
            ++i;
        }
    }
}

int main(){
    int t;
    cin >> t;
    while(t--){
        string s;
        cin >> s;
        int n = s.length();
        int *f1 = NULL;
        int *f2 = NULL;
        buildlps(f1,s);
        int *p = f1;
        f1 = NULL;
        buildlps(f1,p,s);
        reverse(s.begin(),s.end());
        buildlps(f2,s);
        p = f2;
        f2 = NULL;
        buildlps(f2,p,s);
        ll ans = 0;
        for(int i = 1;i<n-2;i+=2){
            if(2*f1[i] >= (i+1) && 2*f2[n-i-2] >= (n-i-1))
             ++ans;
        }
        cout << ans <<"\n";
    }
    return 0;
}