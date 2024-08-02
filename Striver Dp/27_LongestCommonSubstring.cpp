#include <iostream>
#include <vector>
using namespace std;

// Using the Tabulation Solution of the longest common subsequence with slight modification
// TC = O(N*M)
int longestCommonSubstrTab(string S1, string S2, int n, int m)
{
    // your code here
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = 0;
    }
    for (int j = 0; j <= m; j++)
    {
        dp[0][j] = 0;
    }

    int ans = INT_MIN;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (S1[i - 1] == S2[j - 1])
            {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else
            { /* THis is the place where the condition was changed instead of
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);   */
                dp[i][j] = 0;
            }
            ans = max(ans, dp[i][j]);
        }
    }
    return ans;
}
// ---------------------------------------------------------------------------------

int longestCommonSubstrSpace(string S1, string S2, int n, int m)
{
    // your code here
    vector<int> prev(m + 1, 0), curr(m + 1, 0);

    int ans = INT_MIN;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (S1[i - 1] == S2[j - 1])
            {
                curr[j] = 1 + prev[j - 1];
            }
            else
            { /* THis is the place where the condition was changed instead of
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);   */
                curr[j] = 0;
            }
            ans = max(ans, curr[j]);
        }
        prev = curr;
    }
    return ans;
}