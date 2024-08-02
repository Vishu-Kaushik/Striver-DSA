#include <iostream>
#include <vector>
using namespace std;

// Recursion + Memoiation : TC = exponential and SC = O(length)
int solveRec(int ind, int prices[], int len, vector<vector<int>> &dp)
{
    if (ind == 0)
    {
        return len * prices[0];
    }
    if (dp[ind][len] != -1)
    {
        return dp[ind][len];
    }
    int notCut = solveRec(ind - 1, prices, len, dp);
    int cut = INT_MIN;
    int rod = ind + 1;
    if (len >= rod)
    {
        cut = prices[ind] + solveRec(ind, prices, len - rod, dp);
    }
    return dp[ind - 1][len] = max(cut, notCut);
}

int cutRodRec(int price[], int n)
{
    // int size = sizeof(price)/sizeof(price[1]);
    vector<vector<int>> dp(n, vector<int>(n + 1, -1));

    return solveRec(n - 1, price, n, dp);
}

//  ---------------------------------------------------------------------------------------------------------------------------------
// Tabulation :
int cutRodTab(int price[], int n)
{

    vector<vector<int>> dp(n, vector<int>(n + 1, 0));
    for (int i = 0; i <= n; i++)
    {
        dp[0][i] = i * price[0];
    }

    for (int i = 1; i < n; i++)
    {
        for (int len = 0; len <= n; len++)
        {
            int notCut = dp[i - 1][len];
            int cut = INT_MIN;
            int rod = i + 1;
            if (len >= rod)
            {
                cut = price[i] + dp[i][len - rod];
            }
            dp[i][len] = max(cut, notCut);
        }
    }
    return dp[n - 1][n];
}

// --------------------------------------------------------------------------------------------------------------------------------------------------------
// Space Optimization Can be done in the same manner by using 'prev' and 'curr' vectors
int cutRodSpace(int price[], int n)
{
    vector<int> prev(n + 1, 0), curr(n + 1, 0);
    for (int i = 0; i <= n; i++)
    {
        prev[i] = i * price[0];
    }

    for (int i = 1; i < n; i++)
    {
        for (int len = 0; len <= n; len++)
        {
            int notCut = prev[len];
            int cut = INT_MIN;
            int rod = i + 1;
            if (len >= rod)
            {
                cut = price[i] + curr[len - rod];
            }
            curr[len] = max(cut, notCut);
        }
        prev = curr;
    }
    return prev[n];
}

// // --------------------------------------------------------------------------------------------------------------------------------------------------------
// Space Optimization Can be done in the same manner by using 'prev' vector
int cutRodSpace1(int price[], int n)
{
    vector<int> prev(n + 1, 0);
    for (int i = 0; i <= n; i++)
    {
        prev[i] = i * price[0];
    }

    for (int i = 1; i < n; i++)
    {
        for (int len = 0; len <= n; len++)
        {
            int notCut = prev[len];
            int cut = INT_MIN;
            int rod = i + 1;
            if (len >= rod)
            {
                cut = price[i] + prev[len - rod];
            }
            prev[len] = max(cut, notCut);
        }
        }
    return prev[n];
}