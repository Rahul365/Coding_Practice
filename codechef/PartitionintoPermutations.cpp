#include <bits/stdc++.h>
using namespace std;

int main()
{

    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        int remove = 0; //element whose value exceeds 2*n+1 if max value in  arr[0] goes upto 100 and n = 20 and arr[maxindex] = 100
        //then to make permutations split possible for such value
        //all the missing number in array of size 20 which are less than 100 must be inserted
        //so array length will be > 100
        //suppose arr[] = {1,1,3,2,4,100};
        //sort  arr[] = {1,1,2,3,4,100};
        //Now for val = 100 , we don't have any value 100-1 in the array
        //so add (100-1) = 99 then we don't have 99-1 = 98 so add that ,now we don't have 97 ....
        //this addition operation will go from 99 to 5
        //So total additions here will 100-5 = 95 numbers were inserted here
        //so we have a permutations (1,2,3,........,100) , (1) At the cost = 96 insertions
        //So if we don't include 100 here remove(100)
        //operations = 1
        //then permutations are (1,2,3,4),(1) At the cost  = 1
        //Thus minimum possible operation = 1 i.e remove 100
        //Observations  here :
        // Freq(x) >= Freq(x+1) so that permutation of x with x+1 will be (Freq(x+1))
        //e.g {1,1,1,2,2,3} => here permutations are (1,2,3) , (1,2) , (1)
        vector<int> occ(2 * n + 1, 0); //to store the occurences of the elements given such that element <= 2*n+1
        for (int i = 0; i < n; i++)
        {
            int x;
            cin >> x;
            if (x >= 2 * n + 1)
            {
                ++remove;
            }
            else
            {
                occ[x]++;
            }
        }

        vector<int> dp(2 * n + 1);

        for (int value = 1; value <= 2 * n; value++)
        {
            vector<int> dp2(2 * n / value + 1);
            int suffix = dp.back();
            for (int i = dp.size() - 1; i >= 0; i--)
            {
                suffix = min(suffix, dp[i]);
                if (i < dp2.size())
                {
                    dp2[i] = suffix + abs(i - occ[value]);
                }
            }
            dp = dp2;
        }

        int answer = INT_MAX;
        for (int a : dp)
        {
            answer = min(answer, a);
        }
        cout << (answer + remove) << "\n";
    }
    return 0;
}