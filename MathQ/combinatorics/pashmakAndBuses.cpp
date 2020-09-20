#include<bits/stdc++.h>
using namespace std;
// https://codeforces.com/problemset/problem/459/C
int answer[1010][1010];
int main(){
    int n,k,d;
    cin >> n >> k >> d;
    /*
        We have n students labelled (1,2,3,.....,n)
        and k buses labelled (1,2,3,...,k)
        and d buses for d days (each bus got unlimited capcity)
        Two student can become close friends if they travel in the same buses in all d days.
        So we want to print all the arrangements of buses taken by n students on d days
        such that no two students become close friends.

        Each student have k^d choices of buses for d days.
        if(k^d  < n){
            then by Pigeon hole principle there are atleast two or more students who will share the same buses all d days
            print(-1)
        }
        else{
            print(first n d-digits  number in k base)
        }
    */
    long long int pwk = 1;
    for(int i =1;i<=d;++i){
        pwk *= k;
        if(pwk >= n){
             break;
        }
    }
    if(pwk < n) {
        cout  << -1 <<"\n";
        return 0; 
    }
    memset(answer,0,sizeof answer);
    //generating first n d-digits number
    for(int i = 1;i<n;++i){
        for(int j = 0 ;j  < d;++j){
            answer[i][j]  = answer[i-1][j];
        }
        for(int j = d-1; j >= 0 ;--j){
            answer[i][j] = (answer[i][j] + 1)%k;
            if(answer[i][j]) break;
        }
    }
    for(int i = 0;i < d;++i){
        for(int j = 0;j < n;++j){
            cout << answer[j][i]+1 <<" ";
        }
        cout <<"\n";
    }
    return 0;
}