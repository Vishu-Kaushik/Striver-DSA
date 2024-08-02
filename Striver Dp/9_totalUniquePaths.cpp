#include <iostream>
#include <vector>
using namespace std;

// Recursive Solution -- > With TC = 2^(n*m) with the AS = O(path Length) = o((m-1)+(n-1))

int solveRecursive(int m, int n)
{
    // a= number of rows
    // b= number of columns
    if (m == 0 && n == 0)
    {
        return 1;
    }
    if (m < 0 || n < 0)
    {
        return 0;
    }
    int up = solveRecursive(m - 1, n);
    int left = solveRecursive(m, n - 1);
    return (up + left);
}

// Memoiation Solution --> TC = O(N*M) and the AS = O(path Length) + O(N*M)
int solveMemo(int m, int n, vector<vector<int>> &dp)
{
    if (m == 0 && n == 0)
    {
        return 1;
    }
    if (m < 0 || n < 0)
    {
        return 0;
    }
    if (dp[m][n] != -1)
    {
        return dp[m][n];
    }
    int up = solveMemo(m - 1, n, dp);
    int left = solveMemo(m, n - 1, dp);
    return dp[m][n] = (up + left);
}

// Tabulation Based Solution --> With TC as
int solveTabulation(int a, int b)
{
    // code here
    // a= number of rows
    // b= number of columns
    vector<vector<int>> dp(a, vector<int>(b, 0));
    dp[0][0] = 1;
    for (int i = 0; i < a; i++)
    {
        for (int j = 0; j < b; j++)
        {
            if (i == 0 && j == 0)
            {
                dp[i][j] = 1;
            }
            else
            {
                int up = 0;
                int left = 0;
                if (i > 0)
                {
                    up = dp[i - 1][j];
                }
                if (j > 0)
                {
                    left = dp[i][j - 1];
                }
                dp[i][j] = up + left;
            }
        }
    }
    return dp[a - 1][b - 1];
}

// Further Space Optimization
int solveSpaceOptimized(int a, int b)
{
    // code here
    vector<int> prev(b, 0);
    for (int i = 0; i < a; i++)
    {
        vector<int> temp(b, 0); // curr 
        for (int j = 0; j < b; j++)
        {
            if (i == 0 && j == 0)
            {
                temp[j] = 1;
            }
            else
            {
                int up = 0;
                int left = 0;
                if (i > 0)
                {
                    up = prev[j]; // last row same element above it
                }
                if (j > 0)
                {
                    left = temp[j - 1]; // current row last element
                }
                temp[j] = up + left;
            }
        }
        prev = temp;
    }
    return prev[b - 1];
}
int NumberOfPath(int a, int b)
{
    // code here
    // return solveRecursive(a - 1, b - 1);
    // a= number of rows
    // b= number of columns
    vector<vector<int>> dp(a, vector<int>(b, -1));
    return solveMemo(a - 1, b - 1, dp);
}