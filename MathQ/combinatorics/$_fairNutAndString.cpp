#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
const ll mod = 1e9+7;
// https://codeforces.com/problemset/problem/1084/C
int main(){
    string s;
    cin >> s;
    string _s;
    for(char ch : s){
        if(_s.back() == 'b' && ch == 'b'){
            continue;
        }
        else if(ch == 'a'){
            _s.push_back('a');
        }
        else if(ch == 'b'){
            _s.push_back('b');
        }
    }
    if(_s.back()!='b') _s.push_back('b');
    /*
    Given a string s[]. Count the number of strictly increasing subsequences such that 
    A seq is strictly increasing if p1<p2<p3<..<pk. and it satisfy the conditions :
    1) 1<=i<=k, for every i  s[pi] = 'a'
    2) 1<=i<k,for every j, pi < j < pi+1 , s[j] ='b'

    Solution is as follows:
    1) First filter the string by removing every other character other than 'a' and 'b' and also keep  only one 'b' for every block of consecutive ('b')'s

    2) Now we have some blocks of a's separated by b's e.g. aabaaaba

    3) We can choose only 1 'a' from every block of a's to avoid voilating the 2nd condition.
      And also we have a choice of either choosing 'a' from this block or not.
      Let n(a) be the number of a's in the block.
      we can either choose 1 'a' from this block or don't choose from this block
      So there are n(a) + 1 ways to choose from this block
    4) Answer = (n(a[block_0] +1) * n(a[block_1]+1) * ......n(a[block_k])+1) - 1
       here (-1) indicates empty sequence that we can get
      Answer = (Answer+mod)%mod;
    */
    ll cnta = 1;
    ll answer = 1;
    for(char ch : _s){
        if(ch == 'b'){
            answer = (answer * cnta)%mod;
            cnta = 1;
        }
        else{
            ++cnta;
        }  
    }
    answer = ((answer - 1)%mod+mod)%mod;
    cout << answer <<"\n";
    return 0;
}