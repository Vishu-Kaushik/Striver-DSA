#include <iostream>
#include <vector>
using namespace std;

// IDEA : making a dp of ind which is day and transaction (which is complete when you buy and sell a stock )

// Recursive + memoized code
int solveMemo(int ind, int tran, vector<int> &prices, int n, int maxTran, vector<vector<int>> &dp)
{
    if (ind == n || tran == maxTran)
    {
        return 0;
    }
    if (dp[ind][tran] != -1)
    {
        return dp[ind][tran];
    }
    int profit = 0;
    // even operation --> it is buy
    if (tran % 2 == 0) // buy
    {
        profit = max(-prices[ind] + solveMemo(ind + 1, tran + 1, prices, n, maxTran, dp), solveMemo(ind + 1, tran, prices, n, maxTran, dp));
    }
    // odd operation --> it is sell
    else
    {
        profit = max(prices[ind] + solveMemo(ind + 1, tran + 1, prices, n, maxTran, dp), solveMemo(ind + 1, tran, prices, n, maxTran, dp));
    }
    return dp[ind][tran] = profit;
}
int maxProfitMemo(vector<int> &prices)
{
    // method of ind,transaction
    int n = prices.size();
    // So for transaction we did make it 4 becoz --> buy sell buy sell --> makes two complete allowed transactions
    // so it does 4 operations that's why we make it 4
    vector<vector<int>> dp(n, vector<int>(4, -1));
    return solveMemo(0, 0, prices, n, 4, dp);
}

// Tabulation Code:
int maxProfitTab(vector<int> &prices)
{
    // method of ind,transaction
    int n = prices.size();
    vector<vector<int>> dp(n + 1, vector<int>(5, 0));

    // No need to write the base cases becoz we initialize those with 0 only.
    // Directly writing the changing parameters and there for loops as well as recurence

    for (int ind = n - 1; ind >= 0; ind--)
    {
        for (int tran = 3; tran >= 0; tran--)
        {
            int profit = 0;
            if (tran % 2 == 0)
            {
                profit = max(-prices[ind] + dp[ind + 1][tran + 1], dp[ind + 1][tran]);
            }
            else
            {
                profit = max(prices[ind] + dp[ind + 1][tran + 1], dp[ind + 1][tran]);
            }
            dp[ind][tran] = profit;
        }
    }
    return dp[0][0];
}

// Space Optimization :
int maxProfitSpace(vector<int> &prices)
{
    // method of ind,transaction
    int n = prices.size();
    vector<int> after(5, 0), curr(5, 0);

    for (int ind = n - 1; ind >= 0; ind--)
    {
        for (int tran = 3; tran >= 0; tran--)
        {
            int profit = 0;
            if (tran % 2 == 0)
            {
                profit = max(-prices[ind] + after[tran + 1], after[tran]);
            }
            else
            {
                profit = max(prices[ind] + after[tran + 1], after[tran]);
            }
            curr[tran] = profit;
        }
        after = curr;
    }
    return after[0];
}