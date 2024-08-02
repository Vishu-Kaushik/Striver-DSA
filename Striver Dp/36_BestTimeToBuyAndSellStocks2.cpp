#include <iostream>
#include <vector>
using namespace std;

// ----------------- Recursive + Memoized Code ------------------------------
// TC = O(2^n) and SC = O(N) ---> Recursive
// TC = O(N*2) and SC = O(N*2) + O(N) ---> Memoization
long solveMemo(int ind, int buy, long values[], int n, vector<vector<long>> &dp)
{
    if (ind == n)
    {
        return 0;
    }
    if (dp[ind][buy] != -1)
    {
        return dp[ind][buy];
    }
    long profit = -1e9;
    if (buy)
    {
        profit = max(-values[ind] + solveMemo(ind + 1, 0, values, n, dp), solveMemo(ind + 1, 1, values, n, dp));
    }
    else
    {
        profit = max(values[ind] + solveMemo(ind + 1, 1, values, n, dp), solveMemo(ind + 1, 0, values, n, dp));
    }
    return dp[ind][buy] = profit;
}

long getMaximumProfit(long *values, int n)
{
    vector<vector<long>> dp(n, vector<long>(2, -1));
    int buy = 1;
    return (solveMemo(0, buy, values, n, dp));
}

// -------------- Tabulated Code ---------------------------------------------
long getMaximumProfit(long *values, int n)
{
    vector<vector<long>> dp(n + 1, vector<long>(2, 0));
    // Base Case:
    dp[n][0] = 0;
    dp[n][1] = 0;

    for (int ind = n - 1; ind >= 0; ind--)
    {
        for (int buy = 0; buy < 2; buy++)
        {
            long profit = 0;
            if (buy)
            {
                profit = max(-values[ind] + dp[ind + 1][0], dp[ind + 1][1]);
            }
            else
            {
                profit = max(values[ind] + dp[ind + 1][1], dp[ind + 1][0]);
            }
            dp[ind][buy] = profit;
        }
    }
    return dp[0][1];
}

// Space Optimized Code 1 : using ahead and curr array
long getMaximumProfitSpace1(long *values, int n)
{
    vector<long> ahead(2, 0), curr(2, 0);
    // Base Case:
    ahead[0] = 0;
    ahead[0] = 0;

    for (int ind = n - 1; ind >= 0; ind--)
    {
        for (int buy = 0; buy < 2; buy++)
        {
            long profit = 0;
            if (buy)
            {
                profit = max(-values[ind] + ahead[0], ahead[1]);
            }
            else
            {
                profit = max(values[ind] + ahead[1], ahead[0]);
            }
            curr[buy] = profit;
        }
        ahead = curr;
    }
    return ahead[1];
}

// Space Optimization 2: Using 4 variables
long getMaximumProfitSpace2(long *values, int n)
{
    long aheadNotBuy, aheadBuy, currBuy, currNotBuy;
    aheadNotBuy = 0;
    aheadBuy = 0;
    for (int ind = n - 1; ind >= 0; ind--)
    {
        currNotBuy = max(values[ind] + aheadBuy, aheadNotBuy);
        currBuy = max(-values[ind] + aheadNotBuy, aheadBuy);
        aheadNotBuy = currNotBuy;
        aheadBuy = currBuy;
    }
    return aheadBuy;
}