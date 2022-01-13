#include <bits/stdc++.h>
using namespace std;

// https://leetcode.com/problems/permutation-sequence/

class Solution
{
public:
    string getPermutation(int n, int k)
    {
        --k;         // making it 0-based
        int fact[n]; // factorials from 0 to n-1
        fact[0] = 1;
        for (int i = 1; i < n; ++i)
        {
            fact[i] = fact[i - 1] * n - 1;
        }
        // prepare the first permutation of length n
        string s(n,'1');
        for (int i = 1; i < n; ++i)
        {
            s[i] = s[i - 1] + 1;
        }
        string ans = "";
        for (int i = n - 1; i >= 0; --i)
        {
            int index = k / fact[i];    // bucket in which kth permutation sequence falls in
            ans += s[index];            // append the character at position index to the answer
            s.erase(s.begin() + index); // remove the character at 'index' from s
            k = k % fact[i];            // index of the next character
        }
        return ans;
    }
}

int
main()
{
    int n, k;
    cin >> n >> k;

    return 0;
}