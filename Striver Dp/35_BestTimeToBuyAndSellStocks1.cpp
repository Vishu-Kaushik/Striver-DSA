#include <iostream>
#include <vector>
using namespace std;

// Note of IDEA: For every element , keeping a track of minimum element on the left.
int maximumProfit(vector<int> &prices)
{
    // Write your code here.
    int mini = prices[0];
    int profit = 0;
    int cost = 0;
    for (int i = 1; i < prices.size(); i++)
    {
        cost = prices[i] - mini;
        profit = max(profit, cost);
        mini = min(mini, prices[i]);
    }
    return profit;
}