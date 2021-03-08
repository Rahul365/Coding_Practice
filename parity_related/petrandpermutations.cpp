#include <bits/stdc++.h>
using namespace std;

int mergesort(int *arr, int l, int r)
{
    if (l < r)
    {
        int ans = 0;
        int m = l + (r - l) / 2;
        ans += mergesort(arr, l, m);
        ans += mergesort(arr, m + 1, r);
        int i = l;
        int j = m + 1;
        int tmp[r - l + 1];
        int index = 0;
        while (i <= m && j <= r)
        {
            if (arr[i] <= arr[j])
            {
                tmp[index++] = arr[i++];
            }
            else
            {
                ans += m - i + 1;
                tmp[index++] = arr[j++];
            }
        }
        while (i <= m)
            tmp[index++] = arr[i++];
        while (j <= r)
            tmp[index++] = arr[j++];
        for (int i = l; i <= r; ++i)
            arr[i] = tmp[i - l];
        return ans;
    }
    return 0;
}

int countinversions(int *arr, int n)
{
    return mergesort(arr, 0, n - 1);
}

// https://codeforces.com/problemset/problem/986/B
int main()
{
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; ++i)
        cin >> arr[i];
    // counting the inverions  and taking it's parity will give us the parity of number of swaps done to reach this permutation from identity permutation
    int inv_count = countinversions(arr, n) & 1;
/*
Both 3*n and 7*n + 1 will have different parities.
So we can just compare their parities with parity #of inversions and print the answer accordingly 
*/
    int p3n = (3 * n) & 1;
    int p7n = (7 * n + 1) & 1;

    if (inv_count == p3n)
        puts("Petr");
    else
        puts("Um_nik");
    return 0;
}