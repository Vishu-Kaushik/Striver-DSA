#include <iostream>
#include <vector>
using namespace std;

// Given a ‘N’ * ’M’ maze with obstacles, count and return the number of unique paths to reach the right-bottom cell from the top-left cell. A cell in the given
// maze has a value '-1' if it is a blockage or dead-end, else 0. From a given cell, we are allowed to move to cells (i+1, j) and (i, j+1) only. Since the answer
// can be large, print it modulo 10^9 + 7.

// Memoiation solution
int solve(int n, int m, vector<vector<int>> &mat, vector<vector<int>> &dp)
{
    if (n >= 0 && m >= 0 && mat[n][m] == -1)
    {
        return 0;
    }
    if (n == 0 && m == 0)
    {
        return 1;
    }

    else if (n < 0 || m < 0)
    {
        return 0;
    }
    if (dp[n][m] != -1)
    {
        return dp[n][m];
    }

    int up = 0;
    int left = 0;

    up = solve(n - 1, m, mat, dp);

    left = solve(n, m - 1, mat, dp);

    return dp[n][m] = (up + left) % 1000000007;
}

int mazeObstacles(int n, int m, vector<vector<int>> &mat)
{
    vector<vector<int>> dp(n, vector<int>(m, -1));
    return solve(n - 1, m - 1, mat, dp);
}

// Tabulation solution
int mazeObstaclesTab(int n, int m, vector<vector<int>> &mat)
{
    vector<vector<int>> dp(n, vector<int>(m, -1));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (mat[i][j] == -1)
            {
                dp[i][j] = 0;
            }
            else if (i == 0 && j == 0)
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
                dp[i][j] = (up + left) % 1000000007;
            }
        }
    }
    return dp[n - 1][m - 1];
}

// Also we can space optimize it with the same concept as done in the ninja training question