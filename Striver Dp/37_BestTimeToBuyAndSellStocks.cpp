#include <iostream>
#include <vector>
using namespace std;

//  Recursive + Memoization Solution: TC => O(n*ind*cap) , SC => O(n*ind*cap) + O(N)
int solveMemo(int ind, int buy, vector<int> &prices, int n, int cap, vector<vector<vector<int>>> &dp)
{
    if (cap == 0)
    {
        return 0;
    }
    if (ind == n)
    {
        return 0;
    }
    if (dp[ind][buy][cap] != -1)
    {
        return dp[ind][buy][cap];
    }
    int profit = -1e9;
    if (buy)
    {
        profit = max(-prices[ind] + solveMemo(ind + 1, 0, prices, n, cap, dp), solveMemo(ind + 1, 1, prices, n, cap, dp));
    }
    else
    { // sell case
        profit = max(prices[ind] + solveMemo(ind + 1, 1, prices, n, cap - 1, dp), solveMemo(ind + 1, 0, prices, n, cap, dp));
    }
    return dp[ind][buy][cap] = profit;
}

int maxProfit(vector<int> &prices)
{
    // Write your code here.
    int n = prices.size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(2, vector<int>(3, -1)));
    return solveMemo(0, 1, prices, n, 2, dp);
}

// Tabulation Solution : TC => O(n*ind*cap) , SC = O(n*ind*cap) using 3D dp
int maxProfitTab(vector<int> &prices)
{
    // Write your code here.
    int n = prices.size();
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>>(2, vector<int>(3, 0)));
    // tabulation Code:
    // Base case not necessary but writing for understanding
    // 1. cap =0
    for (int ind = 0; ind < n; ind++)
    {
        for (int buy = 0; buy < 2; buy++)
        {
            dp[ind][buy][0] = 0;
        }
    }

    // 2. ind == n
    for (int buy = 0; buy < 2; buy++)
    {
        for (int cap = 0; cap < 3; cap++)
        {
            dp[n][buy][cap] = 0;
        }
    }

    // changing parameters
    for (int ind = n - 1; ind >= 0; ind--)
    {
        for (int buy = 0; buy < 2; buy++)
        {
            for (int cap = 1; cap < 3; cap++)
            {
                int profit = 0;
                if (buy)
                {
                    profit = max(-prices[ind] + dp[ind + 1][0][cap], dp[ind + 1][1][cap]);
                }
                else
                {
                    profit = max(prices[ind] + dp[ind + 1][1][cap - 1], dp[ind + 1][0][cap]);
                }
                dp[ind][buy][cap] = profit;
            }
        }
    }

    return dp[0][1][2];
}

// SPace optimization :
int maxProfit(vector<int> &prices)
{
    // Write your code here.
    int n = prices.size();
    vector<vector<int>> ahead(2, vector<int>(3, 0));
    vector<vector<int>> curr(2, vector<int>(3, 0));
    // tabulation Code:
    // Base case not necessary but writing for understanding
    // 1. cap =0
    ahead[0][0] = 0;
    ahead[1][0] = 0;

    // 2. ind == n
    for (int buy = 0; buy < 2; buy++)
    {
        for (int cap = 0; cap < 3; cap++)
        {
            ahead[buy][cap] = 0;
        }
    }

    // changing parameters
    for (int ind = n - 1; ind >= 0; ind--)
    {
        for (int buy = 0; buy < 2; buy++)
        {
            for (int cap = 1; cap < 3; cap++)
            {
                int profit = 0;
                if (buy)
                {
                    profit = max(-prices[ind] + ahead[0][cap], ahead[1][cap]);
                }
                else
                {
                    profit = max(prices[ind] + ahead[1][cap - 1], ahead[0][cap]);
                }
                curr[buy][cap] = profit;
            }
        }
        ahead = curr;
    }

    return ahead[1][2];
}