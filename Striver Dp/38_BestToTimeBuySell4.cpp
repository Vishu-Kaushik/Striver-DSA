#include <iostream>
#include <vector>
using namespace std;

/*
You are given an integer array prices where prices[i] is the price of a given stock on the ith day, and an integer k.

Find the maximum profit you can achieve. You may complete at most k transactions: i.e. you may buy at most k times and sell at most k times.

Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the stock before you buy again).


*/
int maximumProfit(vector<int> &prices, int n, int k)
{

    vector<vector<int>> ahead(2, vector<int>(k + 1, 0));
    vector<vector<int>> curr(2, vector<int>(k + 1, 0));
    // changing parameters
    for (int ind = n - 1; ind >= 0; ind--)
    {
        for (int buy = 0; buy < 2; buy++)
        {
            for (int cap = 1; cap <= k; cap++)
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

    return ahead[1][k];
}