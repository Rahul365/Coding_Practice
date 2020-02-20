#include <bits/stdc++.h>
#define ll long long int
using namespace std;
// https://www.codechef.com/JAN20B/problems/ISBIAS
int main()
{
    int n, q;
    cin >> n >> q;
    ll arr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    int incr[n];
    int decr[n];
    incr[0] = 0; //increasing ends at 0
    decr[0] = 0; //decreasing ends at 0
    for (int i = 1; i < n; i++)
    {
        incr[i] = (arr[i] > arr[i - 1]);
        decr[i] = (arr[i] < arr[i - 1]);
    }
    for (int i = 0; i < n - 1; i++)
    {
        if (incr[i] && incr[i] == incr[i + 1])
            incr[i] = 0;
        else if (decr[i] && decr[i] == decr[i + 1])
            decr[i] = 0;
    }
    int cinc[n + 1], cdec[n + 1];
    cinc[0] = cdec[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        cinc[i] = incr[i - 1] + cinc[i - 1];
        cdec[i] = decr[i - 1] + cdec[i - 1];
    }
    // for(int i = 0;i<n;i++) cout<<cinc[i+1]<<" "; cout<<"\n";
    //for(int i = 0;i<n;i++) cout<<cdec[i+1]<<" "; cout<<"\n";
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        int i = cinc[r] - cinc[l - 1] + (!incr[r - 1] && r >= 2 && arr[r - 2] < arr[r - 1]) - incr[l - 1];
        int d = cdec[r] - cdec[l - 1] + (!decr[r - 1] && r >= 2 && arr[r - 2] > arr[r - 1]) - decr[l - 1];
        //cout<<i<<" "<<d<<"\n";
        if (r - l > 1 && i && i == d)
            cout << "YES";
        else
            cout << "NO";
        cout << "\n";
    }

    return 0;
}