#include<bits/stdc++.h>
using namespace std;

int tonum(string s){
    int a = 0;
    for(char ch : s){
        a = a*10 + (ch-'0');
    }
    return a;
}

int sum(string a,string b,int i,int j){
    swap(a[i],b[j]);
    return tonum(a) + tonum(b);
}

int main(){
    int t;
    cin >> t;
    while(t--){
        string a,b;
        cin >> a >> b;
        int curr = tonum(a) + tonum(b);
        //100 * 100 * 2 * 2 
        for(int i = 0;i<a.length();++i){
            for(int j = 0;j<b.length();++j){
                curr = max(curr,sum(a,b,i,j));
            }
        }
        cout << curr<<"\n";
    }
    return 0;    
}