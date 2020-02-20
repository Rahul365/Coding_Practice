#include <bits/stdc++.h>
using namespace std;
/**
 * Given a matrix (n*m) of 0's and non-zero integers(both +ve and -ve).
 * for a cell[i][j] with 0 value, fill it's and row and col with 0 also.
 * Return the modified matrix.
 * Do it in-place
 * Expected  Time : O(n*m)
 * Space Complexity : O(n*m),O(n) or O(m)
 * Expected Space Complexity : O(1)
 * 
*/
/**
 * using O((n*m)+(n*m) + (m*n)) time and O(n + m)space
 * 
*/
void setmatrixzeroesI(vector<vector<int>> &mat)
{
    int n = mat.size();
    if (!n)
        return;
    int m = mat[0].size();
    vector<bool> row(n, false);
    vector<bool> col(m, false);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            row[i] = col[j] = mat[i][j] == 0;

    //fill the rows
    for (int i = 0; i < n; i++)
    {
        if (row[i])
            for (int j = 0; j < m; j++)
                mat[i][j] = 0;
    }
    //fill the columns
    for (int j = 0; j < m; j++)
    {
        if (col[j])
            for (int i = 0; i < n; i++)
                mat[i][j] = 0;
    }
}

/**
 * Time : O(n*(m + m)) and space : O(m)
*/
void setmatrixzeroesII(vector<vector<int>> &mat)
{
    int n = mat.size();
    if (!n)
        return;
    int m = mat[0].size();
    vector<bool> cols(m, false); //to mark the column to be filled with zeroes
    for (int i = 0; i < n; i++)
    {
        bool found = false; //tells whether current row contains any zeroes
        for (int j = 0; j < m; j++)
            if (mat[i][j] == 0)
            {
                cols[j] = true;
                found = true;
            }

        if (found) //if there is a 0 ,then fill the row with zeroes
            for (int j = 0; j < m; j++)
            {
                mat[i][j] = 0;
            }
    }

    for (int j = 0; j < m; j++)
        if (cols[j]) //if column is to be filled with zeroes
            for (int i = 0; i < n; i++)
                mat[i][j] = 0;
}

/**
 * Time : O(m + (n*(m + m)) + (n*m))
 * Space : O(1)
*/
void setmatrixzeroesIII(vector<vector<int>> &mat)
{
    int n = mat.size();
    if (!n)
        return;
    int m = mat[0].size();
    //step 1)
    bool firstrow = false; //tells us at the end that whether to fill first row with zero
    for (int j = 0; j < m; j++)
        if (mat[0][j] == 0)
        {
            firstrow = true;
            break;
        }
    //we will use first row to mark which column is to be filled with zeroes or not
    for (int i = 1; i < n; i++)
    {
        bool found = false;
        for (int j = 0; j < m; j++)
            if (mat[i][j] == 0)
            {
                found = true;
                mat[0][j] = 0; //mark the jth column at first row with zero
            }
        if (found) //if the row contains any zero fill this row with 0 values
            for (int j = 0; j < m; j++)
                mat[i][j] = 0;
    }
    //step 2)
    //fill all those columns with zeroes which have value 0 in the firs row
    for (int j = 0; j < m; j++)
        if (mat[0][j] == 0)
            for (int i = 0; i < n; i++)
                mat[i][j] = 0;
    // //step 3)
    // //fill the first row with 0 values if there is any
    if (firstrow)
        for (int j = 0; j < m; j++)
            mat[0][j] = 0;
}

int main()
{
    return 0;
}