#include<bits/stdc++.h>
using namespace std;

class PatternMatch{
    private:
      int *F;//longest prefix which is also suffix
      string T,P;
      int n,m;
      void precomputeF(){
          int i = 1;
          int j = 0;
          F[0] = 0;
          while(i < m){
              if(P[i] == P[j]){
                  F[i] = j+1;
                  i++;
                  j++;
              }
              else if(j > 0){
                  j = F[j-1];
              }
              else{
                  ++i;
              }
          }
      }

    public:
      PatternMatch(string T,string P){
          this->T = T;
          this->P = P;
          n = T.length();
          m = P.length();
          F = new int[m];
      }


     vector<int> findPatternUsingKMP(){
         precomputeF();//compute LPS  for pattern P
         vector<int> ans;
         int i = 0;//iterator for string T
         int j = 0;//iterator for string P

         while(i < n){
             if(T[i] == P[j]){
                 if(j == m-1){
                     ans.push_back(i-j);
                     if(m == 1) i++; // if the pattern is of length 1
                     else
                      j = F[j-1];
                 }
                 else{
                     i++;
                     j++;
                 }
             }
             else if(j > 0){
                 j = F[j-1];
             }
             else{
                 ++i;
             }
         }
         return ans;
     }
    
};


int main(){
    string T = "abcbdbbbddssgasdga";
    string P = "bb";
    PatternMatch p(T,P);
    vector<int> indexes = p.findPatternUsingKMP();
    for(int index : indexes){
        cout<<index<<" ";
    }
    cout<<"\n";
    return 0;
}