#include<bits/stdc++.h>
using namespace std;
/**
 * https://code.google.com/codejam/contest/32013/dashboard#s=p1
 * Problem A
*/
string readstring(){
        char ch;
        string s;
        while((ch=getchar())!='\n'){
            s += ch;
        }
        return s;
}

int main(){
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    int cases;
    int n;//number of engines
    int q;
    cin>>cases;
    for(int c = 1;c <= cases;++c){
        // map<string,int> engines;
       
        cin>>n;

        string e;
        // getline(cin,e);//to read newline character
        getchar();
        for(int i = 0;i<n;i++)
        {
            getline(cin,e);
            //cout<<i<<" "<<e<<"\n";
            // engines[e] = i+1;
        }

        set<string> useengine;
        
        cin>>q;

        int ans = 0;//number of switches
        // getline(cin,e);//to read new line character
        getchar();
        while(q--){
            getline(cin,e);

            useengine.insert(e);

            if(useengine.size() == n){
                ans++;
                useengine.clear();
            }
            useengine.insert(e);
        }

        cout<<"Case #"<<c<<": "<<ans<<"\n";
    }
    return 0;
}