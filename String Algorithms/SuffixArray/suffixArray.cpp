#include<bits/stdc++.h>
using namespace std;

void brute(string &s){
    vector<int> suffixArr;
    for(int i= 0;i<s.length();++i){
        suffixArr.push_back(i);
    }
    suffixArr.push_back(s.length());
    sort(suffixArr.begin(),suffixArr.end(),[&](int x,int y){
        return s.substr(x) <= s.substr(y);
    });
    
    for(int v : suffixArr){
        cout << v <<"\n";
    }
}



void countSort(vector<pair<int,int>> &a,int m){
    vector<int> cnt(10);
   // for(auto p : a) cout << p.second << " ";cout<<"\n";
    const int n = (int)a.size();
    for(int i = 0;i<n;++i){
        ++cnt[(a[i].first/m)%10];
    }
    
    for(int i = 1;i<10;++i) cnt[i]+=cnt[i-1];
    vector<pair<int,int>> res(n);
    
    for(int i = n-1;i>=0;--i){
        res[--cnt[(a[i].first/m)%10]] = a[i];
    }
    
    a = res;
}

void radixsort(vector<pair<pair<int,int>,int>> &arr){
    vector<pair<int,int>> a;//temp array to hold({key,position in the original array})
    vector<pair<pair<int,int>,int>> res;//second temp array to hold the sorted copy of original one
    int bound = 0;
    if(bound)
    {
        //first sort by the right half
        for(int i = 0;i<(int)arr.size();++i){
            a.push_back({arr[i].first.second,i});
            bound = max(bound,arr[i].first.second);
        }

        for(int m = 1;(bound/m);m*=10){
            //cout << m << "\n";
            countSort(a,m);
        }

        for(auto p : a)
            res.push_back(arr[p.second]);
        arr = res;
    }

    bound = 0;
    res.clear();
    a.clear();
    {
        //sort by the left half
        for(int i= 0;i<(int)arr.size();++i){
            a.push_back({arr[i].first.first,i});
            bound = max(bound,arr[i].first.first);
        }
        for(int m = 1;(bound/m);m*=10){
            //cout << m << "\n";
            countSort(a,m);
        }
        // for(auto p : a) cout << p.second << " "; cout<<"\n";
        for(auto p : a)
            res.push_back(arr[p.second]);
        arr = res;
    }
}



int main(){
    string s;
    cin >> s;
    // 0 1 2 3 4 5
    // a b a b b a
    //first we will make the length of the string as power of 2
    s+='$';
    int n = s.length();
    vector<int> order(n);
    vector<int> c(n);
    {
        //build equivalence classes of length = 1
        vector<pair<char,int>> a(n);
        for(int i = 0;i<n;++i) a[i] = {s[i],i};
        sort(a.begin(),a.end());
        c[a[0].second] = 0;
        for(int i = 1;i<n;++i){
            if(a[i-1].first == a[i].first) c[a[i].second] = c[a[i-1].second];
            else c[a[i].second] = 1 + c[a[i-1].second];
        }
        for(int i = 0;i<n;++i){
            order[i] = a[i].second;
        }
    }
    int k = 0;
    while((1<<k) < n){
        //starting points of the string of length 2^(k+1) are (i,(i+2^(k-1))%n)
        //so we'll start from k = 0
        //where for k = 0,we are currently looking at the substrings of length 2^(k+1)
        vector<pair<pair<int,int>,int>> data;
        {
            /*
            for(int i = 0;i<n;++i){
                data.push_back({{c[i],c[(i + (1<<k))%n]},i});
            }
            */
            /*To avoid doing the first phase of the radix sort*/
            for(int i = 0;i<n;++i){
                int id = order[i];
                data.push_back({{c[(id-(1<<k)+n)%n],c[id]},(id-(1<<k)+n)%n});
            }
        }
        //sort(data.begin(),data.end());
        /*My implementation of RADIX sort*/
        radixsort(data);//sort by second then first O(radix * n)
        for(int i = 0;i<n;++i) order[i] = data[i].second;
        c[data[0].second] =0;
        for(int i= 1;i<n;++i){
            if(data[i].first == data[i-1].first){
                c[data[i].second] = c[data[i-1].second];
            }
            else{
                c[data[i].second] = 1 + c[data[i-1].second];
            }
        }
        ++k;
    }
    //Time Complexity : O(n*(log(n))^2)
    //Time Complexity : O(n*log(n)) + O(log(n) * r * n) using Radix Sort = O(n*(1+r)*log(n))
    for(int &v : order) cout << v << " " << s.substr(v) <<"\n";
    return 0;
}