#include <bits/stdc++.h>
using namespace std;

// https://leetcode.com/problems/permutation-sequence/

class Solution
{
public:
    string getPermutation(int n, int k)
    {
        --k;          // making it 0-based
        int fact = 1; // factorials from 0 to n-1
        for (int i = 1; i < n; ++i)
        {
            fact = fact * i;
        }
        // prepare the first permutation of length n
        vector<int> s(n);
        iota(s.begin(), s.end(), 1);
        string ans = "";
        for (int i = n - 1; i >= 0; --i)
        {
            int index = k / fact;            // bucket in which kth permutation sequence falls in
            ans.append(to_string(s[index])); // append the character at position index to the answer
            s.erase(s.begin() + index);      // remove the character at 'index' from s
            k = k % fact;
            fact /= max(i, 1); // index of the next character
        }
        return ans;
    }
};

int main()
{
    int n, k;
    cin >> n >> k;
    Solution s;
    cout << s.getPermutation(n, k) << "\n";
    return 0;
}