#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
// https://codeforces.com/problemset/problem/1036/C
int countnz(int num){
    int answer = 0;
    while(num){
        answer += num%10!=0;
        num/=10;
    }
    return answer;
}


vector<int> tovect(ll num)
{
    vector<int> ans;
    while(num){
        ans.push_back(num%10);
        num/=10;
    }
    reverse(ans.begin(),ans.end());
    return ans;
}

//dp[pos][cnt][bound]

ll dp[50][11][11];

ll count(int pos,const vector<int> &num,bool bound,int cnt){
    if(pos == num.size()){
        return cnt > 0 && cnt <= 3;
    }
    int lim = bound? num[pos]:9;
    ll &ret = dp[pos][cnt][bound];
    if(ret!=-1) return ret;
    ret = 0LL;
    if(cnt > 3) return ret = 0LL;
    if(cnt == 3) return ret = 1LL;
    
    for(int v = 0;v <= lim;++v){
            bool next = (num[pos] == v?bound:false);
            ret += count(pos+1,num,next,cnt+(v!=0));
    }
    return ret;
}

ll getcount(ll num){
    if(num <= 0) return 0LL;
    for(int i = 0;i<50;++i)for(int j =0 ;j<10;++j) for(int k=0;k<10;++k) dp[i][j][k] = -1LL;
    vector<int> arr = tovect(num);
    ll answer = count(0,arr,true,0);
    return answer;
}

ll c[20][20];
ll p9[4];
void build(){
    p9[0] = 1;
    
    for(int i= 1;i<4;++i) p9[i] = 9 * p9[i-1];
    memset(c,0,sizeof c);
    
    c[0][0] = 1;

    for(int i = 1;i<20;++i){
        c[i][0] = c[i-1][0];
        for(int j = 1;j<=i;++j){
            c[i][j] = c[i-1][j] + c[i-1][j-1];
        }
    }
}

ll countN(ll N){
    if(N <= 0) return 0LL;
    vector<int> num = tovect(N);
    int n = num.size();
    ll answer = 0;
    int curr = 3;//max number of non-zero digits
    for(int i = 0 ;i<n && curr >= 0;++i){
        if(num[i] == 0) continue;
        ll A = 0;
        for(int p = 0;p <= curr;++p){
            A += (p < 0 || p > n-i-1?0LL:c[n-i-1][p]) * p9[p];
        }
        answer += A;
        --curr;
        A = 0;
        for(int p = 0;p<=curr;++p)
        A += (p < 0 || p > n-i-1?0LL:c[n-i-1][p]) * p9[p] *(num[i]-1);
        answer += A;
    }
    return answer;
}   

void solveUsingCombinatorics(ll L,ll R){
    ll answer = countN(R+1) - countN(L);
    cout << answer <<"\n";
}
/*Solved using Digit DP*/
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    build();
    int T;
    cin >> T;
    while(T--){
        ll L,R;
        cin >> L >> R;
        solveUsingCombinatorics(L,R);
        // ll answer = getcount(R) - getcount(L-1);
        // cout << answer <<"\n";
    }
    return 0;
}