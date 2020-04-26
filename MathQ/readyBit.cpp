#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e5+1;
using ll = long long int;
const ll mod = 998244353;
string s;
const vector<char> sym = {{'0','1','a','A'}};

template<typename T>
T power(T a,T b){
    T r = 1;
    while(b){
        if(b&1) r = (r*a)%mod;
        a = (a*a)%mod;
        b >>= 1;
    }
    return r;
}

ll dp[2][2]; // dp[x][y] => result  if G0 = x and G1 = y 
int n = 0;
ll total = 1LL;
int prec(char ch){
    if(ch == '&') return 3;
    if(ch == '^') return 2;
    return 1;
}

string intopost(){
    string post;
    stack<char> stk;
    for(char ch : s){
        if(ch == '#'){
            post += ch;
        }
        else if(ch=='('){
            stk.push(ch);
        }
        else if(ch == ')'){
            while(!stk.empty() && stk.top()!='(')
            {
                post += stk.top();
                stk.pop();
            }
            if(!stk.empty() && stk.top() == '(')
                stk.pop();
        }
        else{
            while(!stk.empty() && (stk.top()!='(' && prec(ch) <= prec(stk.top()))){
                post += stk.top();
                stk.pop();
            }
            stk.push(ch);
        }
    }
    while(!stk.empty())
    {
        post+=stk.top();
        stk.pop();
    }
    return post;
}

char convert(char ch ,int a_v){
    if(ch == 'a')
        ch = a_v?'1':'0';
    if(ch == 'A')
        ch = a_v?'0':'1';
    return ch;
}

//do operation
char doop(char x,char y,char opr){
    if(opr=='&')
    {
        if(x == y && x=='1') return '1';
    }
    if(opr == '|'){
        if(x=='1' or y=='1') return '1';
    }
    if(opr=='^'){
        if(x!=y) return '1';
    }
    return '0';
}


void evalpost(string post){
    stack<pair<char,char>> stk;//(a=0,a=1)
    for(char ch : post){
            char ch0 = convert(ch,0);
            char ch1 = convert(ch,1);
            if(ch == '&' or ch == '|' or ch =='^'){
                auto  A = stk.top(); stk.pop();
                auto  B = stk.top(); stk.pop();
                //let a = 0
                stk.push({doop(A.first,B.first,ch),doop(A.second,B.second,ch)});//a =  1
            }
            else{
                stk.push({ch0,ch1});
            }
    }
    //cerr <<post<< " : "<<  (stk.top().first-'0') << " "<<(stk.top().second-'0')<<"\n";
    ++dp[(stk.top().first-'0')][(stk.top().second-'0')];
}


void fillandsolve(string post,int pos){
    queue<pair<string,int>> q;
    q.push({post,0});
    while(!q.empty()){
        auto u = q.front();
        q.pop();
        while(u.second < (int)post.length() && u.first[u.second]!='#')
        {
            ++u.second;
        }
        if(u.second == (int)post.length()){
            evalpost(u.first);
            continue;
        }
        for(char ch : sym){
            u.first[u.second] = ch;
            q.push({u.first,u.second+1});
        }
    }
}

//to compute PQ^-1 % mod
template<typename T>
T compute(T P,T Q){
    Q = power(Q,mod-2);
    return (P*Q)%mod;
}

ll res(int i,int j){
    // cerr << dp[i][j] <<" ";
    return compute(dp[i][j],total);
}

ll mult(ll a,ll b)
{
    return (a%mod*b%mod)%mod;
}

ll add(vector<ll> arr){
    ll sum = 0;
    for(ll v : arr){ sum = (sum +v)%mod; if(sum < 0) sum += mod; }
    return sum;
}

void addself(ll &sum,vector<ll> arr){
    for(ll v : arr){
        sum = (sum + v)%mod;
    }
}

void countdp(string post){
    stack<pair<ll,vector<ll>>> stk; //pair(total number of # so far in the expression,{n(0,0),n(1,1),n(0,1),n(1,0)};
    for(char ch : post){
        if(ch == '&' or ch == '|' or ch=='^'){
            auto right = stk.top(); stk.pop();//right side
            auto left = stk.top(); stk.pop();//left side
            auto r = right.second;
            auto l = left.second; 
            vector<ll> res(4,0);
            ll lcnt = power(4LL,left.first)%mod;
            ll rcnt = power(4LL,right.first)%mod;
            if(ch == '&'){
                addself(res[0],{mult(lcnt,r[0]) , mult(l[0] , add({r[1],r[2],r[3]})) , mult(l[2],r[3]) , mult(l[3],r[2])});
                res[1] = mult(l[1],r[1]); 
                res[2] = res[3] = compute(add({mult(lcnt,rcnt),-res[0],-res[1]}),2LL);
            }
            else if(ch == '|')
            {
                res[0] = mult(l[0] , r[0]);
                addself(res[1],{mult(lcnt ,r[1]) ,mult(l[1], add({r[0] ,r[2],r[3]})) , mult(l[2],r[3]) , mult(l[3],r[2])});
                res[2] = res[3] = compute(add({mult(lcnt,rcnt),-res[0],-res[1]}),2LL);
            }
            else{
                res[0] = mult(l[0],r[0]) + mult(l[1],r[1]) + mult(l[2],r[2]) + mult(l[3],r[3]); 
                res[1] = mult(l[0],r[1]) + mult(l[1] , r[0]) + mult(l[2],r[3]) + mult(l[3],r[2]); 
                res[2] = res[3] = compute(add({mult(lcnt,rcnt),-res[0],-res[1]}),2LL);
            }
            stk.push({(left.first+right.first),res});
        }
        else{
            stk.push({1,{1,1,1,1}});
        }
    }
    auto res = stk.top().second;
    dp[0][0] = res[0]; 
    dp[1][1] = res[1];
    dp[0][1] = res[2];
    dp[1][0] = res[3];
}

int main(){
    int t;
    scanf("%d",&t);
    while(t--){
       cin >> s;
       total = 0;
       for(char ch  : s)
       {
           if(ch== '#')
              ++total;
       }
       total = power(4LL,total)%mod;
        //G0  when a = 0 and A = 1-a = 1
        //G1  when a = 1 and A = 1-a = 0
        // G0 = G1 = 1 ('1')
        // G0 = G1 = 0 ('0')
        // G0 = 0 , G1 = 1 ('a')
        // G0 = 1 , G1 = 0 ('A')
        memset(dp,0,sizeof dp);
        string post = intopost();
        //fillandsolve(post, 0);
        countdp(post);
        printf("%lld %lld %lld %lld\n",res(0,0),res(1,1),res(0,1),res(1,0));
        // cerr<<"\n";
    }
    return 0;
}