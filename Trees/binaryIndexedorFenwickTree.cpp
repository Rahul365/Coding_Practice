#include <bits/stdc++.h>
#define LSB(i) ((i) & (-i))
using namespace std;

int *binaryindextree;
int N;

void update(int pos, const int &val)
{
    int index = pos + 1;
    while (index <= N)
    {
        binaryindextree[index] += val;
        index += LSB(index);
    }
}

int get(int pos)
{
    int index = pos + 1;
    int sum = 0;
    while (index > 0)
    {
        sum += binaryindextree[index];
        index -= LSB(index);
    }
    return sum;
}

int rangesum(int l, int r)
{
    return get(r) - get(l - 1);
}

/**
 * Child node of binary indexed tree bit[x] of node bit[y] 
 * stores the sum of elements starting from y(inclusive) 
 * to x(exclusive)
 * 
*/

void buildFenwickTree(int *arr, int n)
{
    N = n + 1;
    binaryindextree = new int[N];
    for (int i = 0; i < N; i++)
    {
        binaryindextree[i] = 0;
    }
    for (int i = 0; i < n; i++)
    {
        update(i, arr[i]);
    }
}

int main()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int n = sizeof(arr) / sizeof(arr[0]);
    buildFenwickTree(arr, n);

    cout << rangesum(0, 0) << "\n";
    cout << rangesum(1, 5) << "\n";
    update(2, -10);
    cout << rangesum(1, 5) << "\n";
    return 0;
}