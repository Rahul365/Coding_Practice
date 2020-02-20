#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;

const int MAXN = 1e6 + 11;

vector<int> f(MAXN, 0); //stores the fsum = SUM(gcd(x,n)) for x = 1 to n
vector<int> phi(MAXN);  //to store the totient value for each n

//euler totient [ phi(n) = n * (p-1)/p ] for all n%p == 0
void seive()
{
    //totient(n) = count of numbers x such that gcd(x,n) == 1
    for (int i = 1; i < MAXN; i++)
        phi[i] = i;

    for (int i = 2; i < MAXN; i++)
    {
        if (phi[i] == i)
        { //is is prime
            //compute for it's multiples
            for (int j = i; j < MAXN; j += i)
            {
                phi[j] *= (i - 1);
                phi[j] /= i;
            }
        }
    }

    //now computing pillai equation
    // f[x] = sum(gcd(x,n)) where 1<=x<=n
    // or f[x] =sum( d * phi(n/d) ) where n%d == 0 and d < n
    for (int i = 1; i < MAXN; i++)
    {
        //here i is divisor of all j which are multiple of it
        for (int j = i; j < MAXN; j += i)
        {
            f[j] = (f[j] + (i * phi[j / i])) % mod; //where i is divisor of j
            if (f[j] < 0)
                f[j] += mod;
        }
    }
}

int main()
{
    seive();
    for (int i = 1; i <= 11; i++)
    {
        cout << f[i] << " ";
    }
    cout << "\n";
    return 0;
}