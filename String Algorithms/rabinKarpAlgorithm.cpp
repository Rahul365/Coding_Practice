#include<bits/stdc++.h>
using namespace std;
const int MAXN = 257;
/**
 * Given a string T (text) of length n and string P of length m.
 * Find all the starting indexes of pattern P in T.
 */

/**
 * Using Rabin Karp algorithm to find the pattern P in T.
*/
vector<int> rabinkarpPatternMatcher(string T,string P,int n,int m){
    vector<int> indexes;
    
    //to calculate hash of substring of length m
    //use horner's rule:
    // hashvalue = P[m-1] + 10 *(P[m-2] + 10 * (P[m-3] +.......+10*(P[1] + 10 * P[0]) ... ))
    int p = 0;//hash value of Pattern P
    int t = 0;//hash value of substring T[i,.....,i+m-1]

    for(int i = 0;i<m;i++){
        p = p * 10; t = t * 10;
        p = p + P[i]; t = t + T[i];
    }

    if(p == t) indexes.push_back(0);

    for(int i = 1;i<=n-m;i++){
        t = 10 * (t - pow(10,m-1)*T[i-1]) + T[i+m-1];
        if(p == t) {
            indexes.push_back(i);
        }
    }
    return indexes;
}


/**
 * Using  finite Automata
*/
vector<vector<int>> FA(1000,vector<int>(MAXN,0));//FA[state][condition] = nextstate;
/**
 * Time : O(m*MAXN) = O(m) where MAXN = 256 constant
 * space : O(m*MAXN)
*/
void buildfiniteautomata(string P,int m){
    for(int i = 0;i<MAXN;i++){
        FA[m][i] = m;//FA[goalstate][condition] = goalstate;
    }
    for(int state = 0;state<m;state++){
        FA[state][P[state]] = state+1;
    }
}

int transitionfunc(string T,int index){
    int state = 0;
    while(FA[state][T[index]]!=state){
        state = FA[state][T[index]];
        index++;
    }
    return state;
}

vector<int> finiteautomataPatternMatching(string T,string P,int n,int m){
    vector<int> indexes;
    buildfiniteautomata(P,m);

    for(int i =0;i<=n-m;i++){
        int q = transitionfunc(T,i);
        if(q == m){
            //reached goal state
            indexes.push_back(i);
        }
    }

    return indexes;   
}

int main(){
    string a = "hello world! find me";
    string b = "d";
    vector<int> ans_rabin = rabinkarpPatternMatcher(a,b,a.length(),b.length());
    for(int x : ans_rabin) cout<<x<<" ";
    cout<<"\n";

    vector<int> ans_fa = finiteautomataPatternMatching(a,b,a.length(),b.length());
    for(int x : ans_fa) cout<<x<<" ";
    cout<<"\n";
    
    return 0;
}