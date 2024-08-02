#include <iostream>
#include <vector>
using namespace std;

// Memoiation and Recursive Approach : TC: exponential and SC: O(Weight)
int solveRec(int n, int w, int val[], int wt[], vector<vector<int>> &dp)
{
    if (n == 0)
    {
        int x = w / wt[0];
        return (x * val[0]);
    }
    if (dp[n][w] != -1)
    {
        return dp[n][w];
    }
    int notTake = 0 + solveRec(n - 1, w, val, wt, dp);
    int take = INT_MIN;
    if (w >= wt[n])
    {
        take = val[n] + solveRec(n, w - wt[n], val, wt, dp);
    }
    return dp[n][w] = max(take, notTake);
}
int knapSackRec(int N, int W, int val[], int wt[])
{
    vector<vector<int>> dp(N, vector<int>(W + 1, -1));
    return solveRec(N - 1, W, val, wt, dp);
}

// Tabulation Solution : TC= O(N*W) and SC: O(N*W)
int knapSackTab(int N, int W, int val[], int wt[])
{
    vector<vector<int>> dp(N, vector<int>(W + 1, 0));
    // Base Case:
    for (int i = 0; i <= W; i++)
    {
        dp[0][i] = (i / wt[0]) * val[0];
    }
    // Exploring the paths
    for (int ind = 1; ind < N; ind++)
    {
        for (int w = 0; w <= W; w++)
        {
            int notTake = dp[ind - 1][w];
            int take = INT_MIN;
            if (w >= wt[ind])
            {
                take = val[ind] + dp[ind][w - wt[ind]];
            }
            dp[ind][w] = max(take, notTake);
        }
    }
    return dp[N - 1][W];
}

// Space Optimization :  using two arrays
int knapSackSpace1(int N, int W, int val[], int wt[])
{
    // vector<vector<int>> dp(N, vector<int>(W + 1, 0));
    vector<int> prev(W + 1, 0), curr(W + 1, 0);

    // Base Case:

    for (int i = 0; i <= W; i++)
    {
        prev[i] = (i / wt[0]) * val[0];
    }
    // Exploring the paths
    for (int ind = 1; ind < N; ind++)
    {
        for (int w = 0; w <= W; w++)
        {
            int notTake = prev[w];
            int take = INT_MIN;
            if (w >= wt[ind])
            {
                take = val[ind] + curr[w - wt[ind]];
            }
            curr[w] = max(take, notTake);
        }
        prev = curr;
    }
    return prev[W];
}

// Space Optimization :  using One array
int knapSackSpace1(int N, int W, int val[], int wt[])
{

    vector<int> prev(W + 1, 0);

    // Base Case:

    for (int i = 0; i <= W; i++)
    {
        prev[i] = (i / wt[0]) * val[0];
    }
    // Exploring the paths
    for (int ind = 1; ind < N; ind++)
    {
        for (int w = 0; w <= W; w++)
        {
            int notTake = prev[w];
            int take = INT_MIN;
            if (w >= wt[ind])
            {
                take = val[ind] + prev[w - wt[ind]];
            }
            prev[w] = max(take, notTake);
        }
        // prev = curr;
    }
    return prev[W];
}
