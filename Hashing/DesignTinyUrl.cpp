#include<bits/stdc++.h>
using namespace std;
// https://leetcode.com/problems/encode-and-decode-tinyurl/
/*BASE = 26 + 26 + 10 = 62*/
char mp[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
string IDtoURL(int id){
    string url = "";
    while(id){
        url.push_back(mp[id%62]);
        id/=62;
    }
    return url;
}

int URLtoID(string url){
    int id= 0;
    for(int i = url.length()-1;i>=0;--i){
        if(url[i] >= 'a' && url[i]<='z'){
            id = id * 62 + url[i]-'a';
        }
        else if(url[i]>='A' && url[i]<='Z'){
            id = id * 62 + 26 + url[i]-'A';
        }
        else{
            id = id * 62 + 52 + url[i] -'0';
        }
    }
    return id;
}

int main(){
    string url_pref = "http://tinyurl.com/";
    string to_encode = "https://leetcode.com/problems/design-tinyurl";
    int ID = 12123;
    unordered_map<long long int,string> db;
    db[ID] = to_encode;
    string tinyurl = url_pref + IDtoURL(ID);
    cout << "TinyURL : "<<tinyurl <<"\n";
    cout << "OriginalURL : "<<db[URLtoID(tinyurl.substr(url_pref.length()))]<<"\n";
    return 0;
}