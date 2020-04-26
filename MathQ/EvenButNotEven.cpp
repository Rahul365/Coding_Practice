#include<bits/stdc++.h>
using namespace std;


int main(){
    ios_base :: sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n; // number of digits in the given number
        string num;

        cin >> num;
        /**
         * Given a number num. 
         * Check whether it's an even but not even number(ebne) or not.
         * if(!ebne && it is possibe to make it ebne)
         *      print the ebne
         * else
         *      print -1
         * ebne(even but not even) : a number with the even sum of it's digit but itself is odd.
         * 
         * Now this is an Observation problem:
         * Question to ask oneself here is : 
         *      What makes the sum even ? 
         *         -sum is obtained by adding two or more values 
         *         -In way of even or odd, a number can be even or odd (can't be both at a time)
         *         BASICS : 
         *          Odd + Odd = even
         *          EVEN + ODD = ODD
         *          EVEN - EVEN = EVEN
         *          ODD - ODD = EVEN
         *          Now if we have more than 1 odd digits present in our number
         *          then we can have a 'ebne' number such that sum of it's digits is even and number if odd itself
         *          Otherwise
         *          Such number is never possible (if SUM is even ,it's last digit needs to be odd)
         *          
        */
        string ans;
        int cnt = 0;
        for(int i = 0;i<n;++i){
            if((int)(num[i]-'0') & 1){
                ans += num[i];
                ++cnt;
            }
            if(cnt == 2)
                break;
        }
        if(cnt == 2){
            cout << ans <<"\n";
        }
        else
        {
           cout << "-1\n";
        }
        

    }
    return 0;
}