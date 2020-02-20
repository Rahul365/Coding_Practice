#include<bits/stdc++.h>
using namespace std;
int r,p,s;
int n;
string sq;
//RPS
//R beats S
//S beats P
//P beats R
pair<bool,char> canCounter(char o){
    if(o == 'S' && r > 0){//rock beats scissors
        --r;
        return {true,'R'};
    }    
    else if(o == 'R' && p > 0){//paper beats rock
        --p;
        return {true,'P'};
    }
    else if(o == 'P' && s > 0){//scissors beats paper
        --s;
      return {true,'S'};
    }
    
    
    // if(r > 0) { --r; return {false,'R'};}
    // if(p > 0) { --p; return {false,'P'};}
    // if(s > 0) { --s; return {false,'S'};}
    return {false,'X'};
}

void solveI(){
    string t;
        int wins = 0;
        pair<bool,char> counter;
        int bound = ceil((double)n*0.5);
        for(int i= 0;i<n;i++){
            counter = canCounter(sq[i]);
            if(counter.first){
                wins++;
            }
            t+=counter.second;
           if(r==0 && p == 0 && s==0) break;
        }
      
        if(wins >= bound){
            cout<<"YES\n";
            
            for(int i = 0;i<n;i++){
                if(t[i] == 'X'){
                    if(r > 0){
                        --r,t[i] = 'R';
                    }
                    else if(p > 0){
                        --p,t[i] ='P';
                    }
                    else if(s > 0)
                    {
                        --s,t[i] ='S';
                    }
                }
            }
            cout<<t<<"\n";
        }
        else{
            cout<<"NO\n";
        }
}

void solveII(){
    int R = 0;
    int P = 0;
    int S = 0;
    for(int i = 0;i<n;i++){
        if(sq[i] == 'R') R++;
        else if(sq[i] == 'P') ++P;
        else ++S;
    }    
    int w = min(R,p) + min(P,s) + min(S,r);
    if(2*w < n) {cout<<"No\n"; return;}

    string t = "";

    for(int i = 0;i<n;i++){
        if(sq[i]=='R' && p > 0){
            t+='P'; --p;
        }
        else if(sq[i] == 'P' && s > 0){
            t+='S'; --s;
        }
        else if(sq[i] == 'S' && r > 0)
        {
            t+='R'; --r;
        }
        else t+='X';
    }
    for(int i = 0;i<n;i++)
    {   if(t[i] == 'X'){
            if(r > 0){
                --r,t[i]= 'R';
            }
            else if(p > 0){
                --p,t[i]='P';
            }
            else if(s > 0){
                --s,t[i]='S';
            }
        }
    }    
    cout<<"Yes\n";
    cout<<t<<"\n";
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int t;
    cin>>t;
    while(t--)
    {
        cin>>n;
        cin>>r>>p>>s;
        assert(r +p + s == n);
        cin>>sq;
        solveII();
    }
    return 0;
}