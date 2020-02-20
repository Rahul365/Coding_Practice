#include <bits/stdc++.h>
#define ll long long int
using namespace std;
const int mod = 1e9 + 7;
map<string, ll> cnt; //map to store the number of ways to represent the sorted word
set<string> pool;    //pool to store the string
vector<ll> dp(4000);
int len, LIM;
string word; //word in the monster dictionary
/**
 * To get the sorted string for given word s
*/
string getword(string s)
{
    sort(s.begin(), s.end());
    return s;
}

ll get(int i)
{
    if (i == len)
        return 1;

    ll &ans = dp[i];
    if (ans != -1)
        return ans;

    ans = 0;
    int end = i + LIM + 1;
    end = min(end, len);
    string curr = "";
    for (int k = i; k < end; k++)
    {
        curr += word[k];
        curr = getword(curr);
        if (cnt[curr] > 0)
        { //we have a word from the dictionary
            ans += (cnt[curr] * get(k + 1)) % mod;
            if (ans >= mod)
                ans -= mod;
        }
    }
    return ans;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    // freopen("input.txt","r",stdin);
    // freopen("output.txt","w",stdout);

    int t;
    cin >> t;
    int z = 1;
    while (t--)
    {
        cout << "Case #" << z << ": ";
        int n, q; //size of monster vocabulary and number of enciphered messages
        cin >> n >> q;

        LIM = 0;
        pool.clear();
        cnt.clear();
        //read the monster vocabulary
        for (int i = 1; i <= n; i++)
        {
            cin >> word;
            LIM = max(LIM, (int)word.length());
            // pool.insert(word);
            word = getword(word);
            cnt[word]++;
        }

        while (q--)
        {
            cin >> word;
            len = word.length();
            for (int i = 0; i < len; i++)
            {
                dp[i] = -1;
            }
            cout << get(0) << " ";
        }
        cout << "\n";
        z++;
    }
    return 0;
}