#include<bits/stdc++.h>
#define ll long long int
#define PII pair<ll,pair<int,int>>
using namespace std;


int getNumberofSubarraysWithSum(int *a,int n,int s){
        int ans = 0;
        unordered_map<int,int> map;
        map[0] = 1;
        int curr_sum = 0;
        for(int i = 0;i<n;i++){
            curr_sum += a[i];
            if(map.find(curr_sum-s)!=map.end()){
                ans += map[curr_sum-s];
            }
            
            map[curr_sum]++;
        }
        
        return  ans;
}

pair<int,int> getIndicesofSubarrayWithSum(int *a,int n,int s){
    pair<int,int> p = {-1,-1};
    if(n == 0) return p;
    unordered_map<int,int> map;
    int a_i = 0;
    int a_j = 0;
    int curr_sum = 0;
    while(a_j < n){
        curr_sum += a[a_j];
        if(curr_sum == s){
            p = {a_i,a_j};
            break;
        }
        if(map.find(curr_sum-s)!=map.end()){
            p = {map[curr_sum-s],a_j};
            break;
        }
        map[curr_sum] = a_j;
        a_j++;
    }
    return p;
}

int main()
{
    int t;
    cin>>t;
    while(t--){
        int n;
        int s;
        cin>>n;
        int a[n];
       
        for(int i = 0;i<n;i++){
            cin>>a[i];
        }
        cin>>s;
        cout<<getNumberofSubarraysWithSum(a,n,s)<<"\n";
        pair<int,int> p = getIndicesofSubarrayWithSum(a,n,s);
        cout<<p.first;
        if(p.second != -1){
            cout<<" "<<p.second;
        }
        cout<<"\n";
    }
	return 0;
}