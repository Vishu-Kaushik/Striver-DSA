#include <iostream>
#include <vector>
using namespace std;

// Recursive solution idea can be derived from the below solution
// Memoiation Solution : TC= O(N*N) and SC is O(N*N) + O(N)
int solve(int row, int col, int n, vector<vector<int>> &triangle, vector<vector<int>> &dp)
{
    if (row == n - 1)
    {
        return triangle[n - 1][col];
    }
    if (dp[row][col] != -1)
    {
        return dp[row][col];
    }

    int down = triangle[row][col] + solve(row + 1, col, n, triangle, dp);
    int diagonal = triangle[row][col] + solve(row + 1, col + 1, n, triangle, dp);

    return dp[row][col] = min(down, diagonal);
}
int minimizeSum(int n, vector<vector<int>> &triangle)
{
    vector<vector<int>> dp(n, vector<int>(n, -1));
    return solve(0, 0, n, triangle, dp);
}

// Tabulation Solution in which the recursion stack space will be eliminated
// TC : O(N*N) and SC is O(N*N)
int minimizeSumTab(int n, vector<vector<int>> &triangle)
{
    // Code here
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for (int j = 0; j < n; j++)
    {
        dp[n - 1][j] = triangle[n - 1][j];
    }

    for (int i = n - 2; i >= 0; i--)
    {
        for (int j = i; j >= 0; j--)
        {
            int down = triangle[i][j] + dp[i + 1][j];
            int diagonal = triangle[i][j] + dp[i + 1][j + 1];
            dp[i][j] = min(down, diagonal);
        }
    }
    return dp[0][0];
}

// Space optimization : TC : O(N*N) and SC is O(N)

int minimizeSumSpace(int n, vector<vector<int>> &triangle)
{
    // Code here
    vector<int> next(n, 0);
    for (int j = 0; j < n; j++)
    {
        next[j] = triangle[n - 1][j];
    }

    for (int i = n - 2; i >= 0; i--)
    {
        vector<int> curr(n, 0);
        for (int j = i; j >= 0; j--)
        {
            int down = triangle[i][j] + next[j];
            int diagonal = triangle[i][j] + next[j + 1];
            curr[j] = min(down, diagonal);
        }
        next = curr;
    }
    return next[0];
}
