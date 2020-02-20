#include <bits/stdc++.h>
using namespace std;
const long double nax = 1e15L + 1;
const int MAXN = 3001;
long double dp[MAXN][1 + (MAXN + 1) / 2];
long double computeProb(long double *pheads, int n, int heads, int tails)
{
    long double &ans = dp[heads][tails];
    if (ans != nax)
        return ans;
    if (n == 0)
        return ans = heads > tails ? 1 : 0;

    ans = pheads[n - 1] * computeProb(pheads, n - 1, heads + 1, tails) + (1 - pheads[n - 1]) * computeProb(pheads, n - 1, heads, tails + 1);
    return ans;
}

int main()
{
    int n;
    scanf("%d", &n);
    long double ans = 0;
    long double phead[n]; //probability of getting head

    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= (n + 1) / 2; j++)
            dp[i][j] = nax;
    for (int i = 0; i < n; i++)
    {
        scanf("%Lf", &phead[i]);
    }
    ans = computeProb(phead, n, 0, 0);
    /*
    int heads = (n+1)/2;
    int tails = n - heads;
    while(heads <= n){
          string p = string(heads,'h') + string((n-heads),'t');
          do{
                long double pr3 = 1;
                for(size_t i =0 ;i<p.length();i++)
                {
                    pr3 *= (p[i]=='h'?phead[i]:(1-phead[i]));
                }
                ans += pr3;
          }while(next_permutation(p.begin(),p.end()));
          ++heads;
    }
    */

    printf("%1.10Lf\n", ans);
    return 0;
}