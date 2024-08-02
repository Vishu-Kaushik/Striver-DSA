#include <iostream>
#include <vector>
using namespace std;

// Recursive + Memoiation solution
// TC = O(N*M) and SC = O(N*M) + O(N)
int solve(int row, int col, int N, vector<vector<int>> Matrix, vector<vector<int>> &dp)
{
    if (col < 0 || col >= N)
    {
        return -1e9;
    }
    if (row == 0)
    {
        return Matrix[0][col];
    }
    if (dp[row][col] != -1)
    {
        return dp[row][col];
    }
    int up = Matrix[row][col] + solve(row - 1, col, N, Matrix, dp);
    int ld = Matrix[row][col] + solve(row - 1, col - 1, N, Matrix, dp);
    int rd = Matrix[row][col] + solve(row - 1, col + 1, N, Matrix, dp);

    return dp[row][col] = max(up, max(ld, rd));
}
int maximumPath(int N, vector<vector<int>> Matrix)
{
    // code here
    int maxi = -1e9;
    vector<vector<int>> dp(N, vector<int>(N, -1));
    for (int i = 0; i < N; i++)
    {
        maxi = max(maxi, solve(N - 1, i, N, Matrix, dp));
    }
    return maxi;
}

// Tabulation Solution --> TC = O(N*M) and SC = O(N*M)

int maximumPathTab(int N, vector<vector<int>> Matrix)
{
    // code here

    vector<vector<int>> dp(N, vector<int>(N, 0));
    for (int i = 0; i < N; i++)
    {
        dp[0][i] = Matrix[0][i];
    }
    for (int i = 1; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            int up = INT_MIN;
            int ld = INT_MIN;
            int rd = INT_MIN;

            up = Matrix[i][j] + dp[i - 1][j];
            if (j > 0)
            {
                ld = Matrix[i][j] + dp[i - 1][j - 1];
            }
            if (j < N - 1)
            {
                rd = Matrix[i][j] + dp[i - 1][j + 1];
            }
            dp[i][j] = max(up, max(ld, rd));
        }
    }
    int maxi = -1e8;
    for (int i = 0; i < N; i++)
    {
        maxi = max(maxi, dp[N - 1][i]);
    }
    return maxi;
}

// Space Optimized solution -- > TC = O(N*M) and SC = O(M)
int maximumPathSpace(int N, vector<vector<int>> Matrix)
{
    // code here

    vector<int> prev(N, 0);
    for (int i = 0; i < N; i++)
    {
        prev[i] = Matrix[0][i];
    }
    for (int i = 1; i < N; i++)
    {
        vector<int> curr(N, 0);
        for (int j = 0; j < N; j++)
        {
            int up = INT_MIN;
            int ld = INT_MIN;
            int rd = INT_MIN;

            up = Matrix[i][j] + prev[j];
            if (j > 0)
            {
                ld = Matrix[i][j] + prev[j - 1];
            }
            if (j < N - 1)
            {
                rd = Matrix[i][j] + prev[j + 1];
            }
            curr[j] = max(up, max(ld, rd));
        }
        prev = curr;
    }
    int maxi = -1e8;
    for (int i = 0; i < N; i++)
    {
        maxi = max(maxi, prev[i]);
    }
    return maxi;
}