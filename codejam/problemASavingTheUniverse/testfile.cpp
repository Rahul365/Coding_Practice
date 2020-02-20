#include<bits/stdc++.h>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

int main(){
    string x;
    vector<string> ans;
    int n = 5;
    while(n--){
        getline(cin,x);
        ans.push_back(x);
    }
    int index = 0;
    for(string a : ans)
       cout<<(index++)<<":"<<a<<"\n";
    return 0;
}