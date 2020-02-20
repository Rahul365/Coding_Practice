#include <bits/stdc++.h>
#define ll long long int
using namespace std;
/**
 * Problem : Given two number a and b. Find the sum of digits of all the integers from a to b (inclusive).
 * constraints :
 *   1 <= a <= 10^18
 * e.g : a = 5 and b = 11
 * SUMOFDigits = 5 + 6 + 7 + 8 + 9 + (1 + 0) + (1 + 1) = 38
 * Solution : 
 *  Idea here is that a number can be represented as an array of it's digits
 *  e.g X = 1932 can be represented as array of digits
 *  digits[] = {2,3,9,1} where digits[0] is the rightmost digit of given X
 *  Now that we have the digit array of the given we can generate all numbers smaller than X
 *  
*/

int digitsum(ll a)
{
    ll ds = 0;
    while (a)
    {
        ds += a % 10;
        a /= 10;
    }
    return ds;
}

int bruteforce(ll a, ll b)
{
    int sum = 0;
    while (a <= b)
    {
        sum += digitsum(a);
        ++a;
    }
    return sum;
}

/**
 * Since the number are too large
 * It's not possible to do it linearly within expected time limit of (say 1 sec).
 * This is where digit dp comes into picture.
 * Key idea is to represent the given number X as array of digits.
 * Then we can generate the numbers smaller than X upto 1
 * while doing that, we will also compute the sum of digits of numbers from 1 to  X
 *
 * Also since the length maximum possible number of digits for number are 18
 * then Max digit sum for a number won't exceed (9*18 = 162)
*/

/**
 * generate digit array for given number
 */
void digitnum(ll num, vector<int> &digits)
{
    while (num)
    {
        digits.push_back(num % 10);
        num /= 10;
    }
}
/**
 * index : position of the current digit from the right
 * sum : stores the sum of digits from current position (index to 0)
*/
ll dp[20][200][2];

ll digitsumdp(int index, int sum, int tight, vector<int> &digits)
{
    if (index == -1)
        return sum;

    ll &ans = dp[index][sum][tight];
    if (ans != -1)
        return ans;
    ans = 0;
    int k = tight ? digits[index] : 9; //current digit can range from 0 to digit[index]
    //N = 1000
    //then digits[] = {0,0,0,1}
    //next digits[] = {9,9,9,0}
    //index = 3 , digits[index] = 1
    //i = 0 to 1

    for (int i = 0; i <= k; i++)
    {
        int newtight = digits[index] == i ? tight : 0;
        ans += digitsumdp(index - 1, sum + i, newtight, digits);
    }

    return ans;
}

ll digitsum(ll a, ll b)
{
    memset(dp, -1, sizeof(dp));
    vector<int> numA, numB;
    digitnum(a - 1, numA);
    digitnum(b, numB);
    ll sumA = digitsumdp(numA.size() - 1, 0, 1, numA);
    ll sumB = digitsumdp(numB.size() - 1, 0, 1, numB);
    return sumB - sumA;
}

int main()
{
    ll a, b;
    cin >> a >> b;
    cout << bruteforce(a, b) << "\n";
    cout << digitsum(a, b) << "\n";
    return 0;
}