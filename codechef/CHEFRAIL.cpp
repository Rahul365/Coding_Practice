#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+1;
vector<int> spf(maxn);
//https://www.codechef.com/problems/CHEFRAIL
//Basic Geometry
void segseive(){
    for(int i = 1;i<maxn;++i)
        spf[i] = i;
    for(int i = 2;i*i<maxn;++i){
        if(spf[i] == i)
        {
            for(int j = i*2;j<maxn;j+=i)
                spf[j] = i;
        }
    }
}

// bool factors[maxn];
// void primefactors(long long  num){
//     for(long long i = 2;i*i<=num;++i){
//         if(num%i == 0){
//             while(num%i == 0){
                
//                 num /= i;
//             }
//             factors[i] = true;
//         }
//     }
//     if(num > 1)
//         factors[num] = true;
// }

int cord_x[2][maxn];
int cord_y[2][maxn];

void dfs(vector<pair<int,int>> &pf,vector<int> &f,int i = 0,long long x = 1LL){
    if(i >= pf.size() || x * pf[i].first > maxn-1)
    {
        f.push_back(x);
        return;
    }
    for(int j = 0;j<=2*pf[i].second && x <= maxn-1 ;x*=pf[i].first,++j)
        dfs(pf,f,i+1,x);
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
      segseive();
 //   primefactors(22);
  //  return 0;
    int t;
    cin >> t;
    while(t--){
        memset(cord_x,0,sizeof cord_x);
        memset(cord_y,0,sizeof cord_y);
        int n,m;
        cin >> n >> m;
        vector<int> x(n);
        vector<int> y(m);
        int xx = 0;
        int yy = 0;
        long long ans = 0;
        for(int &v : x){
            cin >> v;
            ++cord_x[v>=0][abs(v)];
            if(!v)
                --xx;
        }
        for(int &v : y){
            cin >> v;
            ++cord_y[v>=0][abs(v)];
            if(!v)
                --yy;
        }
        if(!xx ^ !yy)
            ans += 1LL * (n+xx) * (m+yy);
        for(int each_x : x){
            if(!each_x) continue;
            each_x = abs(each_x);
            vector<pair<int,int>> pf;
            int tx = each_x;
            while(tx >= 2){
                int c =0;
                int p  =spf[tx];
                while(tx%p == 0){
                   tx /=p;
                    ++c;
                }
                pf.push_back({p,c});
            }
            
            reverse(pf.begin(),pf.end());
            
            vector<int> f;
            dfs(pf,f);
            for(int fact : f){
                if((1LL * each_x * each_x)/fact < maxn){
                    ans += cord_y[1][fact]*cord_y[0][(1LL * each_x * each_x)/fact];
                }
            }
        }
        
        for(int each_y : y){
            if(!each_y) continue;
            each_y = abs(each_y);
            vector<pair<int,int>> pf;
            int ty = each_y;
            while(ty >= 2){
                int c =0;
                int p  =spf[ty];
                while(ty%p == 0){
                   ty /=p;
                    ++c;
                }
                pf.push_back({p,c});
            }
            
            reverse(pf.begin(),pf.end());
            
            vector<int> f;
            dfs(pf,f);
            for(int fact : f){
                if((1LL * each_y * each_y)/fact < maxn){
                    ans += cord_x[1][fact]*cord_x[0][(1LL * each_y * each_y)/fact];
                }
            }
        }
        cout << ans <<"\n";
    }
    return 0;
}