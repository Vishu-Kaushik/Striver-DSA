#include <iostream>
#include <vector>
using namespace std;

vector<int> longestIncreasingSubsequence(int n, vector<int> &arr)
{
    vector<int> dp(n, 1);
    int maxi = 1;
    int lastIndex = 0;
    vector<int> hashIndex(n, 0);
    for (int i = 0; i < n; i++)
    {
        hashIndex[i] = i;
    }
    for (int ind = 0; ind < n; ind++)
    {
        for (int prev = 0; prev <= ind - 1; prev++)
        {
            if (arr[prev] < arr[ind] && 1 + dp[prev] > dp[ind])
            {
                dp[ind] = 1 + dp[prev];
                hashIndex[ind] = prev;
            }
        }
        if (dp[ind] > maxi)
        {
            maxi = dp[ind];
            lastIndex = ind;
        }
    }

    vector<int> ans;
    // ans.push_back(arr[i]);
    // cout<<"Vishu ";
    while (lastIndex != hashIndex[lastIndex])
    {
        ans.push_back(arr[lastIndex]);
        lastIndex = hashIndex[lastIndex];
    }
    ans.push_back(arr[lastIndex]);
    reverse(ans.begin(), ans.end());
    return ans;

    // ans.push_back(arr[lastIndex]);
    // while (lastIndex != hashIndex[lastIndex])
    // {
    //     lastIndex = hashIndex[lastIndex];
    //     ans.push_back(arr[lastIndex]);
    // }
}