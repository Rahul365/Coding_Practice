#include <bits/stdc++.h>
using namespace std;
// x = 123
// y = 2123
// a = 3 2 1
// b = 3 2 1 2
// c = 6 4 2 2
int getdigit(char a)
{
    return a - '0';
}

string add(string a, string b)
{
    if (!a.length())
        return b;
    if (!b.length())
        return a;
    int carry = 0;
    string c;
    char *aa = &a[0];
    char *bb = &b[0];
    while (*aa || *bb)
    {
        int sum = (*aa ? getdigit(*aa) : 0) + (*bb ? getdigit(*bb) : 0) + carry;
        carry = sum / 10;
        sum = sum % 10;
        c += (char)(sum + '0');
        if (*aa)
            ++aa;
        if (*bb)
            ++bb;
    }
    if (carry)
        c += (char)(carry + '0');
    return c;
}

void printreverse(string x)
{
    char *a = &x[x.length() - 1];
    while (*a)
    {
        cout << (*a);
        --a;
    }
    cout << ",";
}

int main()
{
    //x = 4321
    // y=  341
    // ans= 4662
    string a = "1";
    string b = "1";
    unsigned long long int pos = 0;
    string c;
    while (c.length() != 1000)
    {
        c = add(a, b);
        //printreverse(c);
        a = b;
        b = c;
        ++pos;
    }
    printreverse(c);
    cout << "END\nIndex : " << (pos + 2) << "\n";
    return 0;
}