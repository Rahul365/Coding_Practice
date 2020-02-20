#include<bits/stdc++.h>
using namespace std;

/**
 * Given a string.
 * Find the length of the longest palindromic substring in the given string.
 */

int bruteForce(string s,int n){
    int maxlength = 0;
    string result = "";
    for(int i = 0;i<n-1;i++)
    {
        for(int j = i+1;j<n;j++){
            int a = i;
            int b = j;
            string left = "";
            string right = "";
            int len = 0;
            while(a < b){
               if(s[a] != s[b])
               {
                   len = 0;
                   break;
               }
               left = left+s[a];
               right = s[b] + right;
               len+=2;
               a++,b--;
            }
            if(a == b){
                len+=1;
            }
           if(len > maxlength){
               maxlength = len;
               result = left + right;
           }
        }
    }
    cout<<result<<"\n";
    return maxlength;
}

/*
    time complexity : O(n^2)
*/
int maxlength(string s,int n){
    bool l[n][n];
    for(int i = 0;i<n;i++)
        for(int j = 0;j<n;j++)
            l[i][j] = (i == j)?true:false;
    
    int ans = 1;
    int st = 0;
    for(int len = 2;len <= n;++len){
        for(int i = 0;i<n-len+1;i++){
            int j = i + len -1;
            if(s[i] == s[j]){
                if(len == 2 || l[i+1][j-1]){
                    l[i][j] = true;
                    if(len > ans)
                        st = i;//get the start position of the substring which is palindromic
                    ans = max(ans,len);//update the length of the substring 
                }
            }
            else{
                l[i][j] = false;
            }
        }
    }
    /*
        stringobj.substr(starting_position,number_of_characters_to_copy)
    */
    cout<<s.substr(st,ans)<<"\n";
    return ans;
}


void longestPalindromicsubstring(string s,int n){
    int maxlen = 0;
    string lps;
    int startindex = 0;
    bool l[n][n];
    for(int i = 0;i<n;i++)
        for(int j = 0;j<n;j++)
            l[i][j] = (i==j);
        
    for(int len = 2;len<=n;len++){
        for(int i = 0;i<n-len+1;i++){
            int j = i+len-1;
        
            if(s[i] == s[j] && (len == 2 || l[i+1][j-1])){
                l[i][j] = true;
                if(len > maxlen)
                {
                    maxlen = len;
                    startindex = i;
                }
            }
            
        }
    }
    cout<<"length : "<<maxlen<<"\n";
    cout<<"LPS : "<<s.substr(startindex,maxlen)<<"\n";
}

int main(){
    string s = "aaaabbaa";
    int n = s.length();
    cout<<bruteForce(s,n)<<"\n";
    cout<<maxlength(s,n)<<"\n";
    return 0;
}