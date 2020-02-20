#include<bits/stdc++.h>
using namespace std;

vector<int> rabinkarpPatternMatch(string T,string P,int n,int m){
     vector<int> indexes;

     //compute hash of p using horner's rule
     //p  = P[m-1] + 10 *(P[m-2] + 10 * (P[m-3] + ..... + 10*(P[1] + 10*P[0])...));
    int p = 0;
    int t = 0;
    for(int i =0;i<m;i++)
    {
        p = p * 10;
        p = p + P[i];
        t = t * 10;
        t = t + T[i];
    }
    
    if(p == t) indexes.push_back(0);
    
    for(int i =1;i<=n-m;i++){
        t = 10 * (t - T[i-1]*pow(10,m-1)) + T[i+m-1];//compute next hash
        if(p == t) indexes.push_back(i);
    }
    return indexes;
}


//building finite automata
const int MAXC = 257;
int **FA = NULL;
void buildFA(string P,int m){
    FA = new int*[m+1];
    for(int i = 0;i<=m;i++){
        FA[i] = new int[MAXC];
        for(int j = 0;j<MAXC;j++){
            FA[i][j] = (i==m)?m:0;
        }
    }
    
    for(int i = 0;i<m;i++){
        FA[i][P[i]] = i+1;
    }
}

int transitionfunc(string T,int index){
    int state =0;
    while(FA[state][T[index]]!= state){
        state = FA[state][T[index++]];
    }
    return state;
}

vector<int> usingFA(string T,string P,int n,int m){
    buildFA(P,m);
    vector<int> ans;
    for(int i = 0;i<=n-m;i++)
    {
        int q = transitionfunc(T,i);
        if(q == m){
            ans.push_back(i);
        }
    }
    return ans;
}


//using KMP
int *F = NULL;
void precomputeF(string P,int m){
    F = new int[m];
    F[0] = 0;
    int i = 1,j=0;
    while(i<m){
        if(P[i] == P[j]){
            F[i] = j+1;
            i++;
            j++;
        }
        else if(j>0){
            j = F[j-1];
        }
        else{
            ++i;
        }
    }
}


vector<int> usingKMP(string T,string P,int n,int m){
    precomputeF(P,m);
    
    vector<int> ans;
    int i = 0;//for T;
    int j = 0;//for P;
    while(i<n){
        if(T[i] == P[j])
        {
            if(j == m-1){
                ans.push_back(i-j);
                if(m==1) i++;
                else j = F[j-1];
            }
            else{
                i++;
                j++;
            }
        }
        else if(j>0){
            j = F[j-1];
        }
        else{
            ++i;
        }
    }
    //free some memory
    delete(F);
    return ans;
}



void print(vector<int> ans){
     for(int i : ans) cout<<i<<" ";
    cout<<"\n";
}





int main(){
    string P = "ABABC";
    string T = "ABABABCABABABCABABABC";
    int n = T.length();
    int m = P.length();
    print(rabinkarpPatternMatch(T,P,n,m));
    print(usingFA(T,P,n,m));
    print(usingKMP(T,P,n,m));
    
    
    return 0;
}