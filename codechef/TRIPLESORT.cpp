#include<bits/stdc++.h>
using namespace std;


int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        int n,k;
        scanf("%d%d",&n,&k);
        
        vector<int> a(n);
        set<pair<int,int>> b;
        
        for(int i =0 ;i < n;++i){
            scanf("%d",&a[i]);
            b.insert({a[i],i});
        }
        if(n&1){
            printf("-1\n");
            continue;
        }
        auto shift = [&](vector<int> &dd){
            swap(dd[0],dd[1]);
            reverse(dd.begin(),dd.end());
        };

        vector<vector<int>> ops;
        for(int i = 0;i<n-2 && k;++i){
            if(a[i] == b.begin()->first) {
                b.erase(b.begin());
                continue;
            }
            vector<int> val = {a[i],(*b.rbegin()).first,(*b.begin()).first};
            vector<int> pos = {i,(*b.rbegin()).second,(*b.begin()).second};
            ops.push_back(pos);
            for(int j = 0;j<3;++j){
                b.erase({val[j],pos[j]});
            }
            shift(val);
            for(int j = 0;j<3;++j){
                a[pos[j]] = val[j];
                b.insert({val[j],pos[j]});
            }
            
            b.erase(b.begin());
            --k;
        }
        
        auto ok = [&](){
            int last = n-b.size();
            while(b.size() && last < n && b.begin()->first == a[last]){
                b.erase(b.begin());
                ++last;
            }
            return !(b.size());
        };
        if(ok()){
                printf("%d\n",ops.size());
                for(auto line : ops){
                    for(int v : line){
                        printf("%d ",(v+1));
                    }
                    printf("\n");
                }
        }
        else{
            printf("-1\n");
        }
    }
    return 0;
}