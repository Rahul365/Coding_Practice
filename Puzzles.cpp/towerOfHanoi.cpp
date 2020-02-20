#include <bits/stdc++.h>
#define move(d, from, to) cout << "Move disk " << d << " from " << from << " to " << to << "\n"
using namespace std;

void toh(int n, char from, char to, char aux)
{
    if (n == 1)
    {
        move(n, from, to);
        return;
    }
    toh(n - 1, from, aux, to);
    move(n, from, to);
    toh(n - 1, aux, to, from);
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;
        toh(n, 'A', 'B', 'C');
    }
    return 0;
}