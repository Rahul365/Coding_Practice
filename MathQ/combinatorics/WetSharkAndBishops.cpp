#include<bits/stdc++.h>
using namespace std;

// https://codeforces.com/problemset/problem/621/B
int main(){
    int n;
    cin >> n;
    vector<vector<int>> mat(1001,vector<int>(1001));
    for(int i = 0;i < n;++i)
    {
        //mark the bishop positions
        int x,y;
        cin >> x >> y;
        mat[x-1][y-1] += 1;
    }

    long long int answer = 0;
    auto diagonal=[&](int r,int c,int dir){
        if(dir){
            //towards up right
            int cnt = 0;
            while(r >= 0 && c < 1000){
                cnt += mat[r][c];
                --r;
                ++c;
            }
            answer += (cnt *(cnt - 1))>>1;
        }
        else{
            //towards down right
            int cnt = 0;
            while(r < 1000 && c < 1000){
                cnt += mat[r][c];
                ++r;
                ++c;
            }
            answer += (cnt * (cnt-1))>>1;
        }
    };
    for(int  i = 0;i<1000;++i){
        //fixing the row
        diagonal(0,i,0);
        diagonal(0,i,1);
        //fixing the column
        if(i){
            diagonal(i,0,0);
            diagonal(i,0,1);
            //last row and second column
            diagonal(999,i,1);
        }
    }


    
    cout << answer <<"\n";
    return 0;
}