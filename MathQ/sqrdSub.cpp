#include<bits/stdc++.h>
using namespace std;
using ll = long long int;

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int n;
        scanf("%d",&n);
        vector<pair<int,int>> even;
        vector<int> odd;
        for(int i = 0;i < n;++i){
            int num;
            scanf("%d",&num);
            if(num&1){
                odd.push_back(i);
            }
            else{
                even.push_back({num,i});
            }
        }
        ll cnt = 0;
        for(int i = 0;i<n;++i){
            ll p = 1LL;
            int pos = -1;
             int l = 0;
             int r = even.size()-1;
                while(l<=r){
                    int m = l+(r-l)/2;
                    if(even[m].second >= i){
                        pos = m;
                        if(even[m].second == i) break;
                        r = m-1;
                    }
                    else{
                        l = m+1;
                    }
                }
            if(pos!=-1)
            for(int j = pos;j < even.size();++j){
                p *= 1LL*even[j].first;
                if(p%4 == 0){
                    cnt += (n-even[j].second);
                    break;
                }
            }
        }
        
        
        ll ct = 1;//continuos count
        for(int i =1;i<=odd.size();++i){
            if(i < odd.size() && odd[i]-1 == odd[i-1])
            {
                ++ct;
            }
            else{
                ct = (ct*(ct + 1)/2);
                cnt += ct;
                ct = 1;
            }
        }
        printf("%lld\n",cnt);
    }
    return 0;
}