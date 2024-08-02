#include <iostream>
#include <vector>
using namespace std;

// using the code of .... LONGEST PALINDROMIC SUBSEQUENCE ....
// So the answer will be only the number of characters which are not included in the LONGEST PALINDROMIC SUBSEQUENCE and then we will have to insert them at the correct
// position

// Tabulation Solution : Same Analysis
int solve(string &s1, string &s2, int len)
{
    // becoz of shifting of Indexing
    vector<vector<int>> dp(len + 1, vector<int>(len + 1, 0));
    for (int i = 0; i <= len; i++)
    {
        dp[i][0] = 0;
    }
    for (int j = 0; j <= len; j++)
    {
        dp[0][j] = 0;
    }

    for (int i = 1; i <= len; i++)
    {
        for (int j = 1; j <= len; j++)
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
    return dp[len][len];
}
int countMin(string str)
{
    // complete the function here
    string str2 = str;
    reverse(str2.begin(), str2.end());
    int len = str.length();
    int ans = solve(str, str2, len);
    return len - ans;
}
