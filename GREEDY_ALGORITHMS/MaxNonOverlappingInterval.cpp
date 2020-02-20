#include<bits/stdc++.h>
using namespace std;

bool comp(pair<int,int> &p1,pair<int,int> &p2){
    return p1.second <= p2.second;
}

int main(){
    int n;
    cin>>n;
    pair<int,int> requests[n];
    for(int i = 0;i<n;i++){
        int s,f;
        cin>>s>>f;
        requests[i] = {s,f};
    }
    //sort the intervals according to their finishing time
    sort(requests,requests+n,comp);
    
    //for(int i = 0;i<n;i++){
      //  cout<<requests[i].first<<"  "<<requests[i].second<<"\n";
    //}
   int i=0;
   int cnt=0;//count of nonoverlapping intervals
    while(i<n){
        ++cnt;
        cout<<requests[i].first<<"  "<<requests[i].second<<"\n";
        int j = i+1;
        while(j < n && requests[i].second > requests[j].first){
            ++j;
        } 
        i = j;
    }
    
    return 0;
}