#include <iostream>
#include <vector>
using namespace std;

// THis is solution of the 0/1 Knapsack problem

// Recursive Solution --> TC: O(2^n) ans SC: O(N)
int solveRec(int w, int wt[], int val[], int n)
{
    // if(wt == 0)
    // {
    //     return 0;
    // }
    if (n == 0)
    {
        if (w >= wt[0])
        {
            return val[0];
        }
        else
        {
            return 0;
        }
    }

    int notTake = 0 + solveRec(w, wt, val, n - 1);
    int take = INT_MIN;
    if (wt[n] <= w)
    {
        take = val[n] + solveRec(w - wt[n], wt, val, n - 1);
    }
    return max(take, notTake);
}
int knapSackRec(int W, int wt[], int val[], int n)
{
    // Your code here
    //   Three parameters changing
    return solveRec(W, wt, val, n - 1);
}

//  --------------------------------------------------------------------------------

// Memoiation Solution --> TC:O(N*W) and SC: O(N*W) + O(N)
int solveMemo(int w, int wt[], int val[], int n, vector<vector<int>> &dp)
{
    // if(wt == 0)
    // {
    //     return 0;
    // }
    if (n == 0)
    {
        if (w >= wt[0])
        {
            return val[0];
        }
        else
        {
            return 0;
        }
    }
    if (dp[n][w] != -1)
    {
        return dp[n][w];
    }
    int notTake = 0 + solveMemo(w, wt, val, n - 1, dp);
    int take = INT_MIN;
    if (wt[n] <= w)
    {
        take = val[n] + solveMemo(w - wt[n], wt, val, n - 1, dp);
    }
    return dp[n][w] = max(take, notTake);
}

int knapSackMemo(int W, int wt[], int val[], int n)
{
    // Your code here
    //   Two parameters changing which are index and the weight
    vector<vector<int>> dp(n, vector<int>(W + 1, -1));
    return solveMemo(W, wt, val, n - 1, dp);
}

// Tabulation Solution : TC = O(N*W) and SC = O(N*W) where the auxiliary stack space is eliminated

int knapSackTab(int W, int wt[], int val[], int n)
{
    // Your code here
    //   Two parameters changing which are index and the weight
    vector<vector<int>> dp(n, vector<int>(W + 1, 0));
    // Base Cases :
    for (int j = wt[0]; j <= W; j++)
    {
        dp[0][j] = val[0];
    }

    for (int index = 1; index < n; index++)
    {
        for (int w = 0; w <= W; w++)
        {
            int notTake = dp[index - 1][w];
            int take = INT_MIN;

            if (wt[index] <= w)
            {
                take = val[index] + dp[index - 1][w - wt[index]];
            }
            dp[index][w] = max(take, notTake);
        }
    }
    return dp[n - 1][W];
}

// Space Optimization Using Two vectors which are prev and curr

int knapSackSpace1(int W, int wt[], int val[], int n)
{
    // Your code here
    //   Two parameters changing which are index and the weight
    vector<int> prev(W + 1, 0), curr(W + 1, 0);
    // Base Cases :
    for (int j = wt[0]; j <= W; j++)
    {
        prev[j] = val[0];
    }

    for (int index = 1; index < n; index++)
    {
        for (int w = 0; w <= W; w++)
        {
            int notTake = prev[w];
            int take = INT_MIN;

            if (wt[index] <= w)
            {
                take = val[index] + prev[w - wt[index]];
            }
            curr[w] = max(take, notTake);
        }
        prev = curr;
    }
    return prev[W];
}

// Space Optimization Using only One vector which is prev only
// Concept : https://youtube.com/watch?v=GqOmJHQZivw&list=PLgUwDviBIf0qUlt5H_kiKYaNSqJ81PMMY&index=22
int knapSackSpace2(int W, int wt[], int val[], int n)
{
    // Your code here
    //   Two parameters changing which are index and the weight
    vector<int> prev(W + 1, 0);
    // Base Cases :
    for (int j = wt[0]; j <= W; j++)
    {
        prev[j] = val[0];
    }

    for (int index = 1; index < n; index++)
    {
        for (int w = W; w >= 0; w--)
        {
            int notTake = prev[w];
            int take = INT_MIN;

            if (wt[index] <= w)
            {
                take = val[index] + prev[w - wt[index]];
            }
            prev[w] = max(take, notTake);
        }
    }
    return prev[W];
}