#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+11;
//Offline technique used
// https://www.geeksforgeeks.org/number-elements-less-equal-given-number-given-subarray/
class bit{
    public:
    vector<int> b;
    bit(){}
    bit(int _size){
        b = vector<int>(_size,0);
    }
    
    void update(int idx,int val){
        ++idx;
        while(idx <(int) b.size()){
            b[idx]+=val;
            idx += (idx & -idx);
        }
    }
    
    int read(int idx){
        ++idx;
        int sum = 0;
        while(idx > 0)
        {
            sum += b[idx];
            idx -= (idx & -idx);
        }
        return sum;
    }
    
    int sum(int l,int r){
        return read(r) - read(l-1);
    }
   
};

bit bitmin,bitmax;

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int n,q;
        scanf("%d%d",&n,&q);
        int maxi[n-1];
        int mini[n-1];
        bitmin = bit(n+1);
        bitmax = bit(n+1);
        int prev,curr;
        for(int i = 0;i<n;++i){
            scanf("%d",&curr);
            if(i){
                mini[i-1] = min(prev,curr);
                maxi[i-1] = max(prev,curr);
            }
            prev = curr;
        }
        vector<pair<int,int>> pmax(n-1),pmin(n-1);
        for(int i = 0;i<n-1;++i){
            pmax[i] = {maxi[i],i+2};
            pmin[i] = {mini[i],i+2};
        }
        
        int ans[q];
        vector<vector<int>> queries(q);
        for(int i = 0;i<q;++i){
            int x1,x2,y;
            scanf("%d%d%d",&x1,&x2,&y);
            queries[i] = {y,x1,x2,i};
        }
        sort(pmax.begin(),pmax.end(),greater<pair<int,int>>());//count the elements greater than equal to y in the rang[l:r]
        sort(pmin.begin(),pmin.end(),greater<pair<int,int>>());//count the elements greater than y in range[l : r]
        sort(queries.begin(),queries.end(),greater<vector<int>>());
        //O(n * logn)
        int idx = 0,idm = 0;
        curr = 0;
        int curr2 =  0;
        //O(q * klogn)
        for(int i = 0;i<q;++i){
            //cout << queries[i][0] <<"\n";
            while(pmax[curr].first >= queries[i][0] && curr < (int)pmax.size()){
                //cout << pmax[curr].second<<" ";
                bitmax.update(pmax[curr].second-1,1);
                ++curr;
            }
           // cout<<"\n";
            while(pmin[curr2].first > queries[i][0] && curr2 < (int)pmin.size()){
            //    cout << pmin[curr2].first<<" ";
                bitmin.update(pmin[curr2].second-1,1);
                ++curr2;
            }
          //  cout<<"\n";
            ans[queries[i][3]] = bitmax.sum(queries[i][1],queries[i][2]-1) - bitmin.sum(queries[i][1],queries[i][2]-1);
        }
        for(int i = 0;i<q;++i){
            printf("%d\n",ans[i]);
        }
    }
    return 0;
}