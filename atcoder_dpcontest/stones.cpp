#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    vector<int> a(n);
    for (int &x : a)
        scanf("%d", &x);

    vector<bool> dp(k + 1, false);
    //Game Theory : NIM game
    //here dp[k] => true if the player who starts first is the winner
    //if k == 0, dp[0] =false => player who will end up in this state will lose because he can't take any turn from this point
    // and the player who is in state dp[k + x] where k = 0 , can win the game
    // i.e if(dp[i-x] == false){
    //       /*this means the second player will lose his shit*/
    //       dp[i] = true;//player which is playing this turn wins
    //   }
    for (int stones = 0; stones <= k; stones++)
    {
        for (int v : a)
        {
            if (stones >= v && !dp[stones - v])
                dp[stones] = true;
        }
    }

    puts(dp[k] ? "First" : "Second");
    return 0;
}