#include <iostream>
#include <vector>
using namespace std;

int minDifference(int arr[], int n)
{
    // Using the solution of the Subset sum problem

    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        sum += arr[i];
    }

    vector<vector<bool>> dp(n, vector<bool>(sum + 1, false));

    // Writing the base cases
    for (int i = 0; i < n; i++)
    {
        dp[i][0] = true;
    }
    dp[0][arr[0]] = true;

    // Exploring all the paths
    for (int ind = 1; ind < n; ind++)
    {
        for (int target = 1; target <= sum; target++)
        {
            bool notTake = dp[ind - 1][target];

            bool take = false;
            if (arr[ind] <= target)
            {
                take = dp[ind - 1][target - arr[ind]];
            }

            dp[ind][target] = take || notTake;
        }
    }

    int mini = INT_MAX;
    for (int i = 0; i <= sum / 2; i++)
    {
        int s1 = i;
        if (dp[n - 1][s1])
        {
            int s2 = sum - i;
            if (dp[n - 1][s2])
            {
                mini = min(mini, abs(s1 - s2));
            }
        }
    }
    return mini;
}