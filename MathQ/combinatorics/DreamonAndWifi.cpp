#include<bits/stdc++.h>
using namespace std;
// https://codeforces.com/problemset/problem/476/B
const int maxn =12;
long double fact[maxn];

int main(){
    fact[0] = 1.0;
    for(int i = 1;i<12;++i){ fact[i] = 1.0 * i * fact[i-1]; }
    string s;
    cin >> s;
    string d;
    cin >> d;
    double ans = 0;
    double fav = 0;
    double all = 0;
    int p = 0,m= 0;
    for(char ch : s){
        if(ch == '+') ++p; else ++m;
    }
    int qs = 0;
    for(char ch : d){
        if(ch == '?') ++qs;
        else if(ch == '+') --p;
        else --m;
    }

    if(m < 0 || p < 0)
    {
        cout << setprecision(10) <<fixed<<0<<"\n";
    }
    else{
        all = 1.0 *(1<<qs);//every ? can be replaced with {+,-}, so there are 2 possible to replace a 1 ?
        //thus total possible strings will be (2^count(?))
        fav = fact[p+m]/(fact[p]*fact[m]);//number of permutations of without repetitions (and with duplicates) of length (p+m) objects selected from (p+m)objects 
        //where + is repeated p times and - is repeated m times
        //cerr<<p<<" " << m << " "<< fav << " " <<all <<"\n";
        cout << setprecision(10) <<fixed<<(fav/all)<<"\n";//basic probability = (#of favorable outcomes/total # of possible outcomes)
    }
    return 0;
}