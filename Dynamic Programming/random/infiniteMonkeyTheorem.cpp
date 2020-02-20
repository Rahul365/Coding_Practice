#include<bits/stdc++.h>
using namespace std;

unordered_map<string,bool> favmap;//unordered map to check whether the string exists in the given array or not
int *dp;//dp array to stores the minimum number of spaces to be inserted the substr(pos,n-1)

int checkprefixes(string s,int pos,int n){
    if(pos == n) return 0;//base case

    int &ans = dp[pos];
    if(ans != -2) return ans;
    ans = INT_MAX;

    string curr;
    for(int j = pos;j<n;j++){
        curr += s[j];
        if(favmap[curr])//if the pattern is in the set 
        {
            int callcheck = checkprefixes(s,j+1,n);//check if the spaces can be inserted in the rest of the string
            if(callcheck!=-1) ans = min(ans,1 + callcheck);//update the minimum number spaces
        }
    }

    return ans  == INT_MAX?-1:ans;
}

int minspaces(string s,vector<string> &fav_strings,int N){
    favmap.clear();
    for(string x : fav_strings)
        favmap[x] = true;
    dp = new int[s.length()+1];
    memset(dp,-2,sizeof(dp));

    return checkprefixes(s,0,s.length());
}

int main(){
    string S;
    cin>>S;
    int N = S.length();
    int n;//number of elements in the set
    cin>>n;
    vector<string> fav_strings(n);
    for(int i = 0;i<N;i++){
        cin>>fav_strings[i];
    }

    cout<<minspaces(S,fav_strings,n)<<"\n";
    return 0;
}