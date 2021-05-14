#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    Solution()
    {
    }
    int superEggDrop(int k, int n)
    {
        /**
         moves[floor][eggsleft] => minimum number of moves 
         to determine whether egg will break if it is dropped from current floor
         moves[0][0,..,n] = 1
        possibilies when egg is dropped from ith floor when we have e eggs
        1) eggs breaks then we have (e-1) eggs to test(i-1) floors
        2) eggs doesn't break then we have (e) eggs to test on (totalFloors - i) floors to test on ,Since egg won't break for any floor  <= i;
        **/
        int **dp = new int *[k + 1];
        for (int i = 0; i <= k; ++i)
        {
            dp[i] = new int[n + 1];
            for (int j = 0; j <= n; ++j)
                dp[i][j] = -1;
        }
        function<int(int, int)> rec = [&](int eggs, int floors) -> int {
            if (floors <= 1)
            {
                return floors;
            }
            if (eggs == 1)
            {
                return floors; //minimum trials is the number of floors we have
            }
            int &ret = dp[eggs][floors];
            if (ret != -1)
                return ret;
            ret = INT_MAX;
            for (int floor = 1; floor <= floors; ++floor)
            {
                ret = min(ret, max(rec(eggs - 1, floor - 1), rec(eggs, floors - floor)));
            }
            ret += 1; //? +1 for the current trial
            return ret;
        };
        //for 0 eggs and n floors;
        for (int e = 0; e <= k; ++e)
        {
            dp[e][1] = 1;
            dp[e][0] = 0;
        }
        //for 1 egg and n floors;
        for (int f = 1; f <= n; ++f)
        {
            dp[1][f] = f;
        }
        for (int f = 1; f <= n; ++f)
        {
            for (int e = 2; e <= k; ++e)
            {
                dp[e][f] = INT_MAX;
                /*
                    Binary search over floor numbers
                    Decision to reduce search space ?
                    if(result(egg_break at floor m) > result(egg_do_not_break at floor m)){
                        Now we can test on m-1 floors with totaleggs-1
                        move search space to right;
                        r = m-1;
                    }
                    else{
                        Since egg doesn't break at mth floor,
                        so move to higher floors i.e. remaining number of floors (Total floors - mfloors)
                        with total eggs left.
                        l = m+1;
                    }
                */
                int l = 1;
                int r = f;
                while (l <= r)
                {
                    int m = l + (r - l) / 2;
                    int egg_breaks = dp[e - 1][m - 1];   //egg break when dropped from mth floor
                    int egg_do_not_break = dp[e][f - m]; //egg doesn't break when dropped from  mth floor
                    dp[e][f] = min(dp[e][f], max(egg_breaks, egg_do_not_break));
                    if (egg_breaks > egg_do_not_break)
                    {
                        r = m - 1;
                    }
                    else
                    {
                        l = m + 1;
                    }
                }
                dp[e][f] += 1;
            }
        }
        // return rec(k,n);
        int ans = dp[k][n];
        for (int i = 0; i <= k; ++i)
        {
            delete[] dp[i];
        }
        delete[] dp;
        return ans;
    }
};

int main()
{
    // superEggDrop(NumberOfeggs,NumberOffloors);
    std::cout << (new Solution())->superEggDrop(100 /*Number Of floors*/, 10000 /*Number Of floors*/);
    return 0;
}