#include <iostream>
#include <vector>
using namespace std;

// Tabulation Solution of the LONGEST COMMON SUBSEQUENCE

/* Question : Given two strings str1 and str2. The task is to remove or insert the minimum number of characters from/in str1 so as to transform it into str2.
It could be possible that the same character needs to be removed/deleted from one point of str1 and inserted to some another point.*/
int solve(int n, int m, string &s1, string &s2)
{
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = 0;
    }
    for (int j = 0; j <= m; j++)
    {
        dp[0][j] = 0;
    }

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
            {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][m];
}
int minOperations(string str1, string str2)
{
    // Your code goes here
    int n = str1.length();
    int m = str2.length();
    int partial = solve(n, m, str1, str2);
    int ans = n - partial + m - partial;
    return ans;
}
