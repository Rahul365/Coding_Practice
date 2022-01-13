#include<bits/stdc++.h>
using namespace std;



bool ispalindrome(string &s,int n){
    int m = n/2;
    if(n&1){
        for(int x = 0;m-x >=0 && m+x < n;++x){
            if(s[m-x] != s[m+x]) return false;
        }
    }
    else{
        for(int x = 0;m-x-1>=0 && m+x < n;++x){
            if(s[m-x-1]!=s[m+x]) return false;
        }
    }
    return true;
}



int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string s;
        cin >> s;
        int possible = 1;
        int operations = 0;
        bool left = true;
        bool right = true;
        for(int i = 0;i< n-i-1;++i){
            if(s[i]!=s[n-i-1]){
                if(s[i+1] == s[n-i-1] && left){
                    //swap right;
                    swap(s[i],s[i+1]);
                    ++operations;
                    left = false;
                    right = true;
                }
                else if(s[i] == s[n-i-2] && right){
                    //swap left;
                    ++operations;
                    swap(s[n-i-1],s[n-i-2]);
                    right = false;
                    left = true;
                }
                 if(s[i]!=s[n-i-1])
                {
                    possible = 0;
                    break;
                }
            }
            else{
                left =right = true;
            }
        }
        if(possible)
        {
            cout <<"YES\n";
            cout << operations <<"\n"; 
        }
        else{
            cout <<"NO\n";
        }
    
    }
    return 0;
}