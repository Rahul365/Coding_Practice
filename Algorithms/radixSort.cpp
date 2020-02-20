#include <bits/stdc++.h>
using namespace std;

/*------------------RADIX SORT----------------------*/

int getLSD(int num, int lsd)
{
    while (lsd)
    {
        num /= 10;
        --lsd;
    }
    return num % 10;
}

void radixsortI(int *arr, int n)
{

    int cnt[10]; //for counting sort
    int res[n];
    bool allzero = false;
    int lsd = 0;
    while (!allzero)
    {
        allzero = true;
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < n; i++)
        {
            int x = getLSD(arr[i], lsd);
            if (x)
                allzero = false;
            cnt[x]++;
        }

        for (int i = 1; i < 10; i++)
            cnt[i] += cnt[i - 1];

        for (int i = n - 1; i >= 0; i--)
        {
            int x = getLSD(arr[i], lsd);
            res[cnt[x] - 1] = arr[i];
            cnt[x]--;
        }
        for (int i = 0; i < n; i++)
            arr[i] = res[i]; //upate the original array
        ++lsd;
    }
}

int getmax(int *arr, int n)
{
    int ans = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > ans)
            ans = arr[i];
    return ans;
}

void countsort(int *arr, int n, int exp)
{
    int res[n];
    int cnt[10];
    memset(cnt, 0, sizeof(cnt));
    for (int i = 0; i < n; i++)
    {
        cnt[(arr[i] / exp) % 10]++;
    }

    for (int i = 1; i < 10; i++)
        cnt[i] += cnt[i - 1];

    for (int i = n - 1; i >= 0; i--)
    {
        res[cnt[(arr[i] / exp) % 10] - 1] = arr[i];
        cnt[(arr[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++)
        arr[i] = res[i];
}

void radixsortII(int *arr, int n)
{
    int m = getmax(arr, n);
    //to find the ith least significant digit from an integer N
    //first cutoff the last (i-1) digits then return the last digit of new N
    // (NUM)%10 => gives the last digit
    // NUM = N/pow(10,i-1) => gives NUM with last (i-1) digits removed from it
    for (int exp = 1; m / exp > 0; exp *= 10)
    {
        countsort(arr, n, exp);
    }
}

int main()
{
    int arr[] = {170, 45, 75, 90, 802, 24, 2, 66};
    int n = sizeof(arr) / sizeof(arr[0]);
    radixsortII(arr, n);
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << "\n";
    return 0;
}