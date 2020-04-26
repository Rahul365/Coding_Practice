#include<bits/stdc++.h>
using namespace std;
using ll = double long ;
// https://www.codechef.com/problems/MXMLCM

template<typename T>
T gcd(T a,T b){
    while(b){
        T t = a%b;
        a = b;
        b = t;
    }
    return a;
}
/*won't work for numbers more than n> 100 && 1 <= a[i] <= 1000000*/
template<typename T>
T LCM(T a,T b){
    return a /gcd(a,b) *b;
}

const int maxn = 10005;
vector<int> p(maxn);
int ans,res;
int maxi = 0;
void primefactors(int x){
    for(int i= 2;i <= sqrt(x);++i){
        if(x%i == 0){
           int cnt = 0;
            while(x%i == 0){
                x/=i;
            ++cnt;
            }
            p[i] = max(cnt,p[i]);
        }
    }
    if(x > 2){
        p[x] = max(p[x],1);
    }
}
/*here difference is compared with how many new prime factors are added to new lcm after using atmost one of the numbers from 1 to m*/
void primefactorsii(int x){
    int curr = x;

    for(int i= 2;i <= sqrt(x);++i){
        if(x%i == 0){
           int cnt = 0;
            while(x%i == 0){
                x/=i;
            ++cnt;
            }
            if(cnt > p[i])
            ans *= pow(i,cnt-p[i]);
        }
    }
    if(x > 2 && 1 > p[x]){
        ans *= pow(x,1-p[x]);   
    }
    if(ans > maxi)
    {
        maxi = ans;
        res = curr;
    }
   
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        
        int n , m;
        scanf("%d%d",&n,&m);
        vector<int> a(n);
        for(int i=0;i<n;++i){
            scanf("%d",&a[i]);
            primefactors(a[i]);
        }
    
        ans = 1;
        maxi = 0;
        res = 1;  
        for(int i = 1;i<=m;++i){
            ans = 1;
            primefactorsii(i);
        }
        printf("%d\n",res);
        fill(p.begin(),p.end(),0);
    }
}