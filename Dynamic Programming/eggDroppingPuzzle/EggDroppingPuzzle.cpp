#include <bits/stdc++.h>
using namespace std;
/**
    Suppose you have N eggs and you want to determine from which floor in a K-floor building you can drop an 
    egg such that it doesn't break.You have to determine the minimum number of attempts you 
    need in order find the critical floor in the worst case while using the best strategy.
    There are few rules given below. 

    An egg that survives a fall can be used again.
    A broken egg must be discarded.
    The effect of a fall is the same for all eggs.
    If the egg doesn't break at a certain floor, it will not break at any floor below.
    If the eggs breaks at a certain floor, it will break at any floor above.

    
 *  If  egg is dropped from x floor, then there are two possibilities :
 *  1) if it breaks, we have n-1 eggs left with x-1 floors to try (1..x-1)
 *  2) if it doesn't break, we have n eggs left with k-x floors left to try (x+1 .....k)
*/

int mintrials(int n, int k)
{
    if (k == 0 || k == 1)
    {
        return k; //if building has only one floor or lesser then number of trials  = k
    }

    if (n == 1) //if there is only 1 egg then k trials are needed
        return k;

    int trials = INT_MAX;
    int res;
    for (int i = 1; i <= k; i++)
    {
        res = max(mintrials(n - 1, i - 1), mintrials(n, k - i));
        if (res < trials)
        {
            trials = res;
        }
    }
    return 1 + trials;
}

int numtrialsDP(int n, int k)
{
    int dp[n + 1][k + 1];

    for (int eggs = 0; eggs <= n; eggs++)
    {
        dp[eggs][1] = 1; //dropping eggs from 1st floor requires 1 trial
        dp[eggs][0] = 0; //dropping from 0th floor requires 0 trial
    }

    for (int floor = 1; floor <= k; ++floor)
    {
        dp[1][floor] = floor; //trials using 1 egg = number of floors
    }

    for (int i = 2; i <= n; i++)
    {
        for (int j = 2; j <= k; j++)
        {
            dp[i][j] = INT_MAX;
            for (int x = 1; x <= j; x++)
            {
                dp[i][j] = min(dp[i][j], 1 + max(dp[i - 1][x - 1], dp[i][j - x]));
            }
        }
    }
    return dp[n][k];
}

int main()
{
    int eggs = 10;
    int buildingFloors = 31;

    // cout<<mintrials(eggs,buildingFloors)<<"\n";
    cout << numtrialsDP(eggs, buildingFloors) << "\n";
    return 0;
}