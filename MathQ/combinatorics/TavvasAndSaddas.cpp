#include<bits/stdc++.h>
using namespace std;

vector<int> digits(int n){
    vector<int>  a;
    while(n){
        a.push_back(n%10);
        n/=10;
    }
    reverse(a.begin(),a.end());
    return a;
}

int main(){
    int n;
    cin >> n;
    vector<int> d = digits(n);
    const int k = d.size();
    // for(int v : d) cerr << v <<" "; cerr <<"\n";
    int index = (1<<k)-1;//number of elements with (k-1) digits = (2^(k))-1
    /*
        Since now we have to find the position of the current element with k digits
        Now to find the exact index
        iterate over the digits of the given number 
        if digit[i] == 7 ,
        then that means that number is (2^(k-i-1)) positions after the (k-1) digits last number
        So for each we add to index (2^(k-i-1)) which is just the number of values which comes before given number
        and after (444...upto (k-1)times) number
    */
    // cerr << index <<"\n";
    for(int i= 0;i<k;++i){
        if(d[i] == 7){
            index += (1<<(k-i-1));
        }
    }
    cout << index <<"\n";
    return 0;
}