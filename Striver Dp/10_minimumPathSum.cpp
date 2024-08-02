#include <iostream>
#include <vector>
using namespace std;

// Recursive Solution : TC = O(N*M) and SC = O(N*M)
int solveRec(int i, int j, vector<vector<int>> &grid)
{
    if (i == 0 && j == 0)
    {
        return grid[i][j];
    }
    if (i < 0 || j < 0)
    {
        return 1e9;
    }
    int up = grid[i][j] + solveRec(i - 1, j, grid);
    int left = grid[i][j] + solveRec(i, j - 1, grid);
    return min(up, left);
}

int minSumPathRecursive(vector<vector<int>> &grid)
{
    int n = grid.size();
    int m = grid[0].size();
    return solveRec(n - 1, m - 1, grid);
}
// ------------------------------------------------------------------------------------------------------------
// Memoiation Based solution:
int solveMemo(int i, int j, vector<vector<int>> &grid, vector<vector<int>> &dp)
{
    if (i == 0 && j == 0)
    {
        return grid[i][j];
    }
    if (i < 0 || j < 0)
    {
        return 1e9;
    }
    if (dp[i][j] != -1)
    {
        return dp[i][j];
    }
    int up = grid[i][j] + solveMemo(i - 1, j, grid, dp);
    int left = grid[i][j] + solveMemo(i, j - 1, grid, dp);
    return dp[i][j] = min(up, left);
}
int minSumPath(vector<vector<int>> &grid)
{
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> dp(n, vector<int>(m, -1));
    return solveMemo(n - 1, m - 1, grid, dp);
}

// ------------------------------------------------------------------------------------------------------------
// Tabulation Based Solution
int minSumPathTab1(vector<vector<int>> &grid)
{
    int n = grid.size();
    int m = grid[0].size();
    vector<vector<int>> dp(n, vector<int>(m, 0));

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (i == 0 && j == 0)
            {
                dp[i][j] = grid[0][0];
            }
            else
            {

                int up = grid[i][j];
                if (i > 0)
                {
                    up += dp[i - 1][j];
                }
                else
                {
                    up += 1e9;
                }
                int left = grid[i][j];
                if (j > 0)
                {
                    left += dp[i][j - 1];
                }
                else
                {
                    left += 1e9;
                }
                dp[i][j] = min(up, left);
            }
        }
        return dp[n - 1][m - 1];
    }
}

// Space optimization Solution

int minSumPathTabOp(vector<vector<int>> &grid)
{
    int n = grid.size();
    int m = grid[0].size();
    // vector<vector<int>> dp(n, vector<int>(m, 0));
    vector<int> prev(m, 0);

    for (int i = 0; i < n; i++)
    {
        vector<int> cur(m, 0);
        for (int j = 0; j < m; j++)
        {
            if (i == 0 && j == 0)
            {
                cur[j] = grid[0][0];
            }
            else
            {

                int up = grid[i][j];
                if (i > 0)
                {
                    up += prev[j];
                }
                else
                {
                    up += 1000000007;
                }

                int left = grid[i][j];
                if (j > 0)
                {
                    left += cur[j - 1];
                }
                else
                {
                    left += 1e9;
                }
                cur[j] = min(up, left);
            }
        }
        prev = cur;
    }
    return prev[m - 1];
}