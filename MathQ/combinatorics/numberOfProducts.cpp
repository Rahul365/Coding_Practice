#include<bits/stdc++.h>
using namespace std;
// https://codeforces.com/contest/1215/submission/85855036 2-DP solution By Im_Amartya
void solution_TLE(){
    int n;
    cin >> n;
    vector<int> a(n);
    long long int answer = 0;//number of pairs with negative product
    long long int total = n; total = (total*(total+1))/2;
    for(int i = 0;i<n;++i){ cin >> a[i]; a[i] = a[i] < 0 ? -1: 1;}
    /*
    //O(n^2)
    for(int i = 0;i<n;++i){
        int s = 1;
        for(int j = i;j<n;++j){
            s *= a[j];
            answer += s < 0;
        }
    }
    //is it possible to acheive linear time ?
    cout << answer << " " << (total - answer) <<"\n";/
    */
    /*
        -1 -1 -1 -1 -1
        5 + 3(length 3) + 1(length 5)
    */
    vector<int> pos;//stores the position of the negatives
    for(int i = 0;i<n;++i){
        if(a[i] < 0) pos.push_back(i);
    }
    const int m = pos.size();
    if(m < n-m && m!=0){
        for(int l = 1;l<=m;l+=2){
            for(int i = 0;i+l-1<m;++i){
                int j = i+l-1;
                int left = pos[i] - (i==0?-1:pos[i-1]);
                int right = (j+1>=m?n:pos[j+1]) - pos[j];
                // cerr << left << " " <<right <<"\n";
                answer += (long long int)(left*right);
            }
        }
        
         cout << answer << " " <<(total - answer) <<"\n";
    }
    else
    {
        //count plus
        // cerr << "count positive\n";
        int last = -1;
        for(int i = 0;i<=n;++i){
            if(i == n || a[i] < 0){
                long long int cnt = i - last - 1;
                answer += (cnt*(cnt+1))>>1;
                last = i;
            }
        }
        for(int l = 2;l<=m;l+=2){
            for(int i = 0;i+l-1<m;++i){
                int j = i+l-1;
                int left = pos[i] - (i==0?-1:pos[i-1]);
                int right = (j+1>=m?n:pos[j+1]) - pos[j];
                // cerr << left << " " <<right <<"\n";
                answer += (long long int)(left*right);
            }
        }
        cout << (total-answer) << " " << answer <<"\n";
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    long long int total = n; total = (total*(total+1))/2;
    for(int i = 0;i<n;++i){ cin >> a[i]; a[i] = a[i] < 0 ? -1: 1;}
   
    int cnt1 = 0;//number of elements such that there is even number of negative elements before them
    int cnt2 = -1;//number of elements such that there is odd number of negative elements before them 
    // (cnt2 intialize with -1 because there are no such elements before 
    // the first odd number such that there are odd number of negatives before them)
    //So just to cancel the count for first time, it is initialized accordingly
    //Solved by editorial--
    long long answer = 0;//number of segments with positive product
    int bal = 0;//number of negative integers so far
    for(int i= 0;i<n;++i){
        if(a[i] < 0){
            ++bal;
        }
        if(bal&1){
            //balance is odd
            //number of odds are negative
            ++cnt2;
            answer += cnt2;
        }
        else{
            //balance is even
            ++cnt1;
            answer += cnt1;
        }
    }
    cout << (total-answer) << " "<< answer <<"\n";
    return 0;
}