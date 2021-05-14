#include <iostream>
#include <vector>
using namespace std;

template <typename T>
void maxself(T &x, T y)
{
    x = max(x, y);
}

class Solution
{
public:
    int maxProduct(vector<int> &nums)
    {
        const int n = nums.size();
        int np = min(1, nums[0]); //if -ve,np < 0
        np = np == 0 ? 1 : np;
        int pp = max(1, nums[0]); //if +ve,pp > 0
        pp = pp == 0 ? 1 : pp;
        int ans = nums[0];
        for (int i = 1; i < n; ++i)
        {
            // cout << i << " " << pp << " "<< np <<"\n";
            int &v = nums[i];
            if (v > 0)
            {
                pp = max(pp * v, v);
                np = np * v;
                maxself(ans, pp);
            }
            else if (v < 0)
            {
                int tmp = pp;
                pp = max(v, max(pp * v, np * v)); //here pp could go negative
                np = min(v, min(np * v, tmp * v));
                maxself(ans, pp);
                pp = max(1, pp); //to avoid updating the answer with false +ve, update pp after updating the answer;
            }
            else
            {
                pp = 0;
                np = 1;
                maxself(ans, v);
            }
            // cout << i << " " << pp << " "<< np <<"\n";
        }
        return ans;
    }
};

int maxProductII(vector<int> &arr)
{
    const int n = arr.size();
    int pp = max(arr[0], 1); //positive max product ending here
    int np = min(arr[0], 1); //negative min product ending here
    int max_product = arr[0];
    for (int i = 1; i < n; ++i)
    {
        int v = arr[i];
        if (v > 0)
        {
            pp = pp * v;
            np = min(np * v, 1);
            maxself(max_product, pp);
        }
        else if (v < 0)
        {
            int tmp = pp;
            pp = np * v;
            np = tmp_pp * v;
            maxself(max_product, pp);
            maxself(pp, 1);
        }
        else
        {
            pp = np = 1;
            maxself(ans, 0);
        }
    }
    return max_product;
}
int main()
{
    return 0;
}