#include<bits/stdc++.h>
using namespace std;
const int inf = 1e9+7;
// https://codeforces.com/problemset/problem/1284/B
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    long long int answer = 0;
    int n;
    cin >> n;
    int cnt = 0;//to store the number of ascents so far
    vector<pair<int,int>> a;//refine : we can just use a[i] = {minimum value of the ith sequence}
    vector<int> b;//stores the maximum value of every sequence
    for(int i = 0;i<n;++i){
        int l;
        cin >> l;
        bool ok = false;
        int mn = inf;
        int mx = -inf;
        for(int j = 0;j<l;++j){
            int x;
            cin >> x;
            if(mn < x){ ok = true; }
            mn = min(mn,x);
            mx = max(mx,x);
        }
        if(ok){
            //my bug was here
            //Since every sequence being an ascent itself will make pairs with all sequences
            //for the very first ascent sequence(A) number of such sequences is (2*n)-1
            //But for second sequence(B) which is also ascent itself, will make pair with all the n sequences
            //Since we have already counted (A,B) && (B,A)
            //So for ascent B, we have (n-1) sequences to be paired with
            //Thus for every individually encountered ascent , number of ascent pairs made by it will 2*(n - (number of singleton ascents so far)) - 1
            answer+= 2*(n-cnt) - 1;
        }
        else{
            a.push_back({mn,mx});
            b.push_back(mx);
        }
        cnt += ok;
    }
 /*
    O(n^2) way to count the concatenated ascents
    where a[i] = {minimum value of the ith sequence, maximum value of the ith sequence}
    for(int i = 0;i<n;++i){
        for(int j = 0;j<n;++j){
            answer += a[i].first < a[j].second;
        }
    }

*/
    n = a.size();
    sort(b.begin(),b.end());
    // cerr << n << "\n";
    for(int i = 0;i<n;++i){
        int l = 0;
        int r = n-1;
        int pos = n;
        while(l <= r)
        {
            int m = l + ((r-l)>>1);
            if(b[m] > a[i].first){
                pos = m;
                r = m-1;
            }
            else{
                l = m+1;
            }
        }
        answer += (n-pos);
    }
    cout << answer <<"\n";
    return 0;   
}