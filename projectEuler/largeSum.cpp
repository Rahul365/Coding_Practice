#include<bits/stdc++.h>
using namespace std;


string addTwoNumber(string a,string b){
    if(a.empty()) return b;
    if(b.empty()) return a;
    int n = a.length();
    int m = b.length();
    int carry = 0;
    string newsum = "";
    while(n>0 || m>0){
        int s = (n>0?(a[n-1]-'0'):0) + (m>0?(b[m-1]-'0'):0) + carry;
        carry = s/10;
        s = s%10;
        char ch = s + '0';
        newsum =  ch + newsum;
        if(n > 0) n--;
        if(m > 0) m--;
    }

    if(carry){
        char ch = carry+'0';
        newsum = ch + newsum;
    }
     return newsum;
}

int main(){
    freopen("largesum.txt","r",stdin);
    string s;
    string sum;
    for(int i=0;i<100;i++)
    {
        string x;
        cin>>x;
        sum = addTwoNumber(sum,x);
    }
    
    cout<<sum<<"\n";
    cout<<sum.substr(0,10)<<"\n";

    
    return 0;
}