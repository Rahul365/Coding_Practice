#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    void maxdiv(int &a,int b){
        while(a%b == 0 && a >= b){
            a/=b;
        }
    }
    
    bool isUgly(int num) {
        maxdiv(num,2);
        maxdiv(num,3);
        maxdiv(num,5);
        return num==1;
    }
    
    int nthUglyNumber(int n) {
        vector<int> ugly(n+1);
        ugly[0] = 1;
        int next_ugly;
        int min_multiple_2 = 2;
        int min_multiple_3 = 3;
        int min_multiple_5 = 5;
        int i2 = 0;
        int i3 = 0;
        int i5 = 0;
        for(int i = 1;i<n;++i){
            next_ugly = min({min_multiple_2 , min_multiple_3,min_multiple_5});
            ugly[i] = next_ugly;
            if(next_ugly == min_multiple_2){
                i2 = i2 + 1;
                min_multiple_2 = ugly[i2]*2;//next multiple of 2
            }
            if(next_ugly == min_multiple_3){
                i3 = i3 + 1;
                min_multiple_3 = ugly[i3]*3;//next multiple of 3
            }
            if(next_ugly == min_multiple_5){
                i5 = i5 + 1;
                min_multiple_5 = ugly[i5]*5;//next multiple of 5
            }
        }
        return ugly[n-1];
    }
};

int main(){
    Solution sol;
    cout << sol.nthUglyNumber(1690) <<"\n";
    return 0;
}