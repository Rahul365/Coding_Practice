#include<bits/stdc++.h>
using namespace std;

//use getline(cin,str_var) to read strings with spaces
int main(){
    int n;//number of strings to read
    
    cin>>n;
    
    getchar();//to read the newline character after reading the number of strings
    
    vector<string> names;
    
    string s;
    
    while(n--){
        getline(cin,s);
        names.push_back(s);
    }

    for(string name : names){
        cout<<name<<"\n";
    }
    return 0;
}