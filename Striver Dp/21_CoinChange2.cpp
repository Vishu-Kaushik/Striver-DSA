#include <iostream>
#include <vector>
using namespace std;

/*
Question : You are given an infinite supply of coins of each of denominations D = {D0, D1, D2, D3, ...... Dn-1}. You need to figure out the total number of ways W,
in which you can make a change for value V using coins of denominations from D. Print 0, if a change isn't possible.
*/

// Memoiation solution --> TC: O(N*target) and SC:O(N*target)+O(target)
long solve(int ind, int value, int *denominations, vector<vector<long>> &dp)
{
    if (ind == 0)
    {
        return (value % denominations[0] == 0);
    }
    if (dp[ind][value] != -1)
    {
        return dp[ind][value];
    }
    long notTake = solve(ind - 1, value, denominations, dp);
    long take = 0;
    if (denominations[ind] <= value)
    {
        take = solve(ind, value - denominations[ind], denominations, dp);
    }
    return dp[ind][value] = (notTake + take);
}
long countWaysToMakeChange(int *denominations, int n, int value)
{
    vector<vector<long>> dp(n, vector<long>(value + 1, -1));
    return solve(n - 1, value, denominations, dp);
}

// ---------------------------------------------------------------------------------
// -----------------------------------------------------------------------------------

// Tabulation Solution : TC= O(N*value) and Sc = O(N*value)
long countWaysToMakeChangeTab(int *denominations, int n, int value)
{
    vector<vector<long>> dp(n, vector<long>(value + 1, 0));
    for (int t = 0; t <= value; t++)
    {
        dp[0][t] = (t % denominations[0] == 0);
    }
    for (int ind = 1; ind < n; ind++)
    {
        for (int t = 0; t <= value; t++)
        {
            long notTake = dp[ind - 1][t];
            long take = 0;
            if (denominations[ind] <= t)
            {
                take = dp[ind][t - denominations[ind]];
            }
            dp[ind][t] = take + notTake;
        }
    }
    return dp[n - 1][value];
}

// Space Optimization : using The prev and the curr rows
long countWaysToMakeChangeTab(int *denominations, int n, int value)
{
    // vector<vector<long>> dp(n, vector<long>(value + 1, 0));
    vector<long> prev(value + 1, 0);
    vector<long> curr(value + 1, 0);
    for (int t = 0; t <= value; t++)
    {
        prev[t] = (t % denominations[0] == 0);
    }
    for (int ind = 1; ind < n; ind++)
    {
        for (int t = 0; t <= value; t++)
        {
            long notTake = prev[t];
            long take = 0;
            if (denominations[ind] <= t)
            {
                take = curr[t - denominations[ind]];
            }
            curr[t] = take + notTake;
        }
        prev = curr;
    }
    return prev[value];
}
