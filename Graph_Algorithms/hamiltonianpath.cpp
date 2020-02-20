/**
 * Hamiltonian Path in a directed or undirected graph is a path that visits each vertex exactly once.
 * The problem to check whether graph contains hamiltonian path or not is NP-complete,so is the problem of
 * finding all the hamiltonian paths in the graph.
 * 
 * There are three ways to check graph for hamiltonian paths :
 * 1) using permutations
 * 2) using dfs with in_stack,out_stack labels
 * 3) using dp with bitmasks
*/
#include <bits/stdc++.h>
using namespace std;
const int N = 100;
/**
 * Using permutations
*/
int adj[N][N];
int searchfromlast(int *p, int s, int e, int key)
{
    while (e >= s)
    {
        if (key < p[e])
            return e;
        --e;
    }
    return s;
}
void rev(int *p, int l, int r)
{
    while (l < r)
    {
        swap(p[l], p[r]);
        ++l, --r;
    }
}
//next greater permutation
bool ngepermutation(int *p, int n)
{
    bool flag = false;
    for (int i = n - 2; i >= 0; i--)
    {
        if (p[i] < p[i + 1])
        {
            flag = true;
            int id = searchfromlast(p, i + 1, n - 1, p[i]);
            swap(p[id], p[i]);
            rev(p, i + 1, n - 1);
            break;
        }
    }
    return flag;
}

bool checkHamiltonianPath(int n)
{
    int p[n];
    for (int i = 0; i < n; i++)
        p[i] = i;
    do
    {
        bool found = true;
        for (int i = 1; i < n; i++)
        {
            if (!adj[p[i - 1]][p[i]])
            {
                found = false;
                break;
            }
        }
        if (found)
            return true;
    } while (ngepermutation(p, n));
    return false;
}

/**
 * use dfs with in_stack out_stack labelling
*/
bool labels[N];
const int IN_STACK = 1;
const int OUT_STACK = 0;
bool dfs(int u, int instack_count, int n)
{
    if (instack_count == n)
        return true;
    for (int i = 0; i < n; i++)
    {
        if (labels[i] == OUT_STACK && adj[u][i] == true)
        {
            labels[i] = IN_STACK;
            if (dfs(i, instack_count + 1, n))
            {
                return true;
            }
            labels[i] = OUT_STACK;
        }
    }
    return false;
}

bool checkusingDFS(int n)
{
    memset(labels, OUT_STACK, sizeof(labels));

    for (int i = 0; i < n; i++)
    {
        labels[i] = IN_STACK;
        if (dfs(i, 1, n))
        {
            return true;
        }
        labels[i] = OUT_STACK;
    }

    return false;
}

/**
 * using dp with bitmasking
*/
const int MAXN = 100;
/*Time : O((1<<MAXN) * MAXN^2) */
bool check_using_dp(int n)
{
    bool dp[MAXN][(1 << MAXN)]; //tells there exists a path that visits each vertex exactly once and end at the same
    for (int i = 0; i < MAXN; ++i)
        for (int j = 0; j < (1 << MAXN); j++)
            dp[i][j] = false;

    for (int i = 0; i < n; i++)
    {
        dp[i][1 << i] = true;
    }

    for (int i = 0; i < (1 << n); ++i)
    {
        for (int j = 0; j < n; j++)
        {
            if (i & (1 << j))
            {
                for (int k = 0; k < n; k++)
                {
                    if (j != k && i & (1 << k) && adj[k][j] && dp[k][i ^ (1 << j)])
                    {
                        dp[j][i] = true;
                        break;
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        if (dp[i][(1 << n) - 1])
            return true;
    }
    return false;
}

int main()
{

    return 0;
}