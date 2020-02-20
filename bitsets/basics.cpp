#include <bits/stdc++.h>
using namespace std;
const int N = 1e9 + 1;

//given sequence of 10^7 numbers  in the range [0,1e9]
//find the count of numbers which are not present in given sequence of numbers
void distinctCount()
{
    int n;
    cin >> n;
    bitset<N> b;
    for (int i = 0; i < n; ++i)
    {
        int x;
        cin >> x;
        b[x] = 1;
    }
    cout << (b.size() - b.count()) << "\n";
}

//given n <= 1000 items with weight wi <= 1000000
//find whether there exists a subset with sum value exactly equal to S
void knapsack()
{
    int n;
    cin >> n;
    //check if there is a subset of items that sum upto exactly S
    bitset<1000001> b;
    b[0] = true;

    for (int i = 0; i < n; ++i)
    {
        int x;
        cin >> x;
        b |= (b << x);
    }
    int S;
    cin >> S;

    cout << (b[S] ? "YES" : "NO") << "\n";
}

//given a graph with n vertices and m <= n(n-1)/2 edges
//count the number of triangles (a,b,c) such that a-b,b-c,a-c

void countTriangles()
{
    int n;
    cin >> n;
    const int nn = 12;
    bitset<nn> edges[n + 1];
    int m;
    cin >> m;
    //read edges
    for (int i = 0; i < m; ++i)
    {
        int x, y;
        cin >> x >> y;
        edges[x][y] = 1;
        edges[y][x] = 1;
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = i + 1; j <= n; ++j)
        {
            if (edges[i][j] == 0)
                continue;
            //since i and j are connected
            //now check if i and j have any common connection to a node x
            if ((edges[i] & edges[j]).count()) //
                ++ans;
        }
    }
    cout << (ans / 3) << "\n";
}

int main()
{
    countTriangles();
    return 0;
}