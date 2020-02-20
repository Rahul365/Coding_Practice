#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6 + 1;
const int N = 1000;
int n;
vector<vector<int>> dishes(N);
int quality(int dish, int last_ing)
{
    if (dish == n)
        return 0;

    int ans = 0;
    int num_ing = dishes[dish].size();
    for (int i = 0; i < num_ing; i++)
    {
        ans = max(ans, (abs(last_ing - dishes[dish][i]) * dish) + quality(dish + 1, dishes[dish][(i + num_ing - 1) % num_ing]));
    }

    return ans;
}

void freespace()
{
    for (int i = 0; i < n; i++)
        dishes[i].clear();
    dishes.clear();
}

void bruteforcedp()
{
    cin >> n;
    dishes.resize(n);
    for (int i = 0; i < n; i++)
    {
        int m;
        cin >> m;
        dishes[i].clear();
        while (m--)
        {
            int x;
            cin >> x;
            dishes[i].push_back(x);
        }
    }

    int ans = 0;
    vector<vector<int>> quality(2); //dp table to store the quality of dist i when using jth ingredient as last ingredient
    //where 0<=i<n && 0 <= j < dishes[i].size()
    //if k is the first ingredient used in a dish
    //then { (k+dishes[i].size()-1) % dishes.size() } will be used as last ingredient for the next dish
    quality[(n - 1) % 2] = vector<int>(dishes[n - 1].size(), 0); //quality measured for each ingredient of last dish is 0
    for (int d = n - 2; d >= 0; d--)
    {                   //iterate from the second last dish
        int nd = d + 1; //next dish
        int ing_d = dishes[d].size();
        int ing_nd = dishes[nd].size();
        quality[d % 2] = vector<int>(ing_d, 0);

        for (int i = 0; i < ing_d; i++)
        {
            for (int j = 0; j < ing_nd; ++j)
            {
                quality[d % 2][i] = max(quality[d % 2][i], quality[nd % 2][(j + ing_nd - 1) % ing_nd] + abs(dishes[d][i] - dishes[nd][j]) * nd);
            }
            if (d == 0)
                ans = max(ans, quality[d % 2][i]);
        }
    }

    cout << ans << "\n";
}

void compmax(int &a, int b)
{
    a = max(a, b);
}
/**
 * Memory efficient
 * 
*/
void dpfromtop()
{
    cin >> n; //number of dishes
    //quality[i][j] => represents maximum quality of dish i when using j as the first ingradient for the (i-1)th dish
    int **dish = new int *[3];
    int **quality = new int *[3];
    int prev_m;
    int m;
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> m;

        int d = i % 3;        //current dish
        int pd = (i - 1) % 3; //previous dish
        if (i > 1)
            delete[] dish[(i - 2) % 3], delete[] quality[(i - 2) % 3];

        dish[d] = new int[m];
        quality[d] = new int[m];
        for (int j = 0; j < m; j++)
        {
            cin >> dish[d][j];
            quality[d][j] = 0;
        }

        if (i > 0)
        {
            for (int j = 0; j < m; j++)
            {
                //using j as the first ingredient of current dish
                for (int k = 0; k < prev_m; k++)
                {
                    //using k as the last ingredient of previous dish
                    compmax(quality[d][j], quality[pd][k] + abs(dish[pd][(k + prev_m - 1) % prev_m] - dish[d][j]) * d);
                }
                if (i == n - 1)
                    compmax(ans, quality[d][j]);
            }
        }
        prev_m = m;
    }

    cout << ans << "\n";
}

#include <bits/stdc++.h>
using namespace std;

void maxval(int &a, int b)
{
    a = max(a, b);
}

/*O(n*(|dish[i]|+|dish[i+1]|)) = O(n*m)*/
void solve()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        vector<int> dish[n];
        for (int i = 0; i < n; i++)
        {
            int m;
            cin >> m;
            while (m--)
            {
                int x;
                cin >> x;
                dish[i].push_back(x);
            }
        }

        vector<vector<int>> quality(n);
        quality[n - 1] = vector<int>(dish[n - 1].size(), 0);
        int ans = 0;
        for (int i = n - 2; i >= 0; i--)
        {
            int ni = i + 1; //next dish
            int m1 = dish[i].size();
            int m2 = dish[ni].size();
            quality[i] = vector<int>(dish[i].size(), 0);
            int maxB1 = INT_MIN;
            int maxB2 = INT_MIN;
            for (int f = 0; f < m2; ++f)
            {
                //considering f as the first ingredient for next dish (i+1)
                //we can know the maximum quality of ingredients for dish (i+1) when (f+m2-1)%m2 is used as the last ingredient
                maxval(maxB1, quality[ni][(f + m2 - 1) % m2] - ni * dish[ni][f]); //|a-b|*ni = ( a-b)*ni
                maxval(maxB2, quality[ni][(f + m2 - 1) % m2] + ni * dish[ni][f]); //|a-b|*ni = (-a+b)*ni
            }
            for (int l = 0; l < m1; l++) //use l as last ingredient of dish i
            {
                int A = ni * dish[i][l];
                quality[i][l] = max(A + maxB1, -A + maxB2);
                if (i == 0)
                    maxval(ans, quality[i][l]);
            }
        }

        cout << ans << "\n";
    }
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {

        // bruteforcedp();
        // dpfromtop();O(n^3)
        solve(); //O(n^2)
        //freespace();
    }
    return 0;
}