#include <bits/stdc++.h>
using namespace std;

int kthElement(int arr1[], int arr2[], int n, int m, int k)
{
    if (n > m)
    {
        return kthElement(arr2, arr1, m, n, k);
    }
    int l = max(0, k - m);
    int r = min(k, n);
    int f = k;
    while (l <= r)
    {
        int m1 = l + (r - l) / 2;
        int m2 = k - m1;
        if ((m1 > 0 && m2 < m) && arr1[m1 - 1] > arr2[m2])
        {
            // arr1 is too much on the right
            r = m1 - 1;
        }
        else if ((m2 > 0 && m1 < n) && arr2[m2 - 1] > arr1[m1])
        {
            l = m1 + 1;
        }
        else
        {
            // cout << m1 << ":" << m2 <<"\n";
            return max(m1 > 0 ? arr1[m1 - 1] : INT_MIN, m2 > 0 ? arr2[m2 - 1] : INT_MIN);
        }
    }

    return -1;
}

int main()
{
    int n = 5;
    int m = 7;
    int arr1[] = {1, 3, 5, 10};
    int arr2[] = {2, 6, 7, 8, 11, 13, 14};
    int k = 7;
    //find and print the value of the 7th sorted element from the two sorted arrays 
    cout << kthElement(arr2, arr1, n, m, k);
    return 0;
}