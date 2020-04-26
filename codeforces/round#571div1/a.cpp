#include<bits/stdc++.h>
using namespace std;
using ll = long long;

void print_(const vector<ll> &p){

    printf("%d\n",p.size());
    
    for(ll x : p){
        printf("%lld ",x);
    }
    printf("\n");
}

int main(){
    ll a,b;
    scanf("%lld%lld",&a,&b);
    ll sum = a+b;
    //vector<ll> ans;
    ll total = 0;
    ll i;
    for(i = 1;total <= sum ;++i){
        total += i;
        if(total > sum) break;
        //ans.push_back(i);
    }
    vector<ll> p,q;
    /*
    total -= i;
    
    
    sum = 0;
    for(int i = ans.size()-1;i>=0;--i){
        if(sum + ans[i] <= b){
            sum += ans[i];
            q.push_back(ans[i]);
            ans[i] = -1;
            if(sum == b) break;
        }
    }
    */
    for(ll v = i-1 ; v>0;--v){
        if(v <= a)
        {
            a-=v;
            p.push_back(v);
        }
        else{
            b-=v;
            q.push_back(v);
        }
    }
    /*
    for(ll xx : ans)
    {
        if(xx == -1) continue;
        p.push_back(xx);
    }
    */
    print_(p);
    print_(q);
    
    return 0;
}