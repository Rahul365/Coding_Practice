#include <bits/stdc++.h>
using namespace std;

int X[2][2] = {
    {2, 1},
    {3, 0}};
/**
 * A[][] * B[][]
 */
void multiply(int A[2][2], int B[2][2])
{
    int a, b, c, d;
    a = A[0][0] * B[0][0] + A[0][1] * B[1][0];
    b = A[0][0] * B[0][1] + A[0][1] * B[1][1];
    c = A[1][0] * B[0][0] + A[1][1] * B[1][0];
    d = A[1][0] * B[0][1] + A[1][1] * B[1][1];

    A[0][0] = a;
    A[0][1] = b;
    A[1][0] = c;
    A[1][1] = d;
}

//recursive matrix exponentiation
void pow(int B[2][2], int n)
{
    if (n == 0 || n == 1)
        return;
    pow(B, n / 2);
    multiply(B, B);
    if (n & 1)
        multiply(B, X);
}

void powit(int B[2][2], int n)
{
    int r[][2] = {{1, 0}, {0, 1}};
    while (n != 0)
    {
        if (n & 1)
        {
            multiply(r, B);
        }
        n /= 2;
        multiply(B, B);
    }
    for (int i = 0; i < 2; i++)
    {
        B[i][0] = r[i][0];
        B[i][1] = r[i][1];
    }
}

int main()
{
    int B[2][2] = {{2, 1}, {3, 0}};
    int n = 3;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cout << B[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    powit(B, n);
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            cout << B[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}