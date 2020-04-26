// https://codeforces.com/contest/1328/problem/B
#include<bits/stdc++.h>
using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int t;
    cin >> t;
    while(t--){
        
        int n,k;
        cin >> n >> k;
        
        //string s(n,'a');
        //each position i of rightmost b gives n-i positions to leftmost b
        //e.g/ s  = "aabaaaab" len = 8
        //          "01234567"
        //right most b at 2
        //left most b have (8-2-1) positions to move in from i=n-1 to i=(2+1)
        //permutation in group gets raised by (+1)
        //1 in first group (l = n-2) k = 1
        //2 in second group(l = n-3) k = 3
        //3 in third group (l = n-4) k = 6
        //4                          k = 10
        //5                          k = 15
        //6                          k = 26
        //till we have "bbaaaaaaaaaa......." //last string of the last group
        int p = 0;
        int r = n-1;
        int group=0;
        for(int  i =n-2;i>=0;--i){
            p +=(1 + group);//number of permutations in total so far
            ++group;//group number of permutation
            r = i;//position of rightmost 'b' in permutation
            if(p >= k)break;
        }
        // cerr<<p<<" " <<group<<" " <<k<<"\n";
        // string ans(n,'a');
        // ans[r] = 'b';
        // int pos = p - k;
        // ans[r + (p-k)+ 1] = 'b';
        // cout << ans <<"\n";
        for(int i = 0;i<n;++i){
            if(i == r or i == r+(p-k)+1){
                cout <<'b';
            }
            else{
                cout <<'a';
            }
        }
        cout <<"\n";
        /*
        //From editorial
        for(int i = n-2;i>=0;--i){
            if(k <= n-i-1){//kth permutation lies in current group
            //where leftmost b is at ith position
            //and rightmost b is at n-kth position
                s[i] = 'b';
                s[n-k] = 'b';
                cout << s <<"\n";
                break;
            }
            k-=(n-i-1);//move on to the next permutation group
        }
        */
    }
    return 0;
}