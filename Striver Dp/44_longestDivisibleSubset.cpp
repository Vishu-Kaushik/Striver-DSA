#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

// Same as DP-42
vector<int> largestDivisibleSubset(vector<int> &nums)
{
    int n = nums.size();
    vector<int> dp(n, 1);
    vector<int> hashInd;
    for (int i = 0; i < n; i++)
    {
        hashInd.push_back(i);
    }
    int maxi = 1;
    int lastInd = 0;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (nums[i] % nums[j] == 0 && dp[i] < 1 + dp[j])
            {
                dp[i] = 1 + dp[j];
                hashInd[i] = j;
                // maxi = max(maxi,dp[i]);
            }
        }
        if (maxi < dp[i])
        {
            maxi = dp[i];
            lastInd = i;
        }
    }

    vector<int> ans;
    ans.push_back(nums[lastInd]);
    while (lastInd != hashInd[lastInd])
    {
        lastInd = hashInd[lastInd];
        ans.push_back(nums[lastInd]);
    }
    reverse(ans.begin(), ans.end());
    return ans;
}