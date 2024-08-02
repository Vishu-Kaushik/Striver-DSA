#include <iostream>
#include <vector>
using namespace std;

// ---------------------------------------------------------------------------------------------
// Recursive + Memoization Solution

bool solveMemo(string &s1, string &s2, int i, int j, vector<vector<int>> &dp)
{

    // base Cases
    if (i < 0 && j < 0)
    {
        return true;
    }
    if (i < 0 && j >= 0)
    {
        return false;
    }

    if (j < 0 && i >= 0)
    {
        for (int x = 0; x <= i; x++)
        {
            if (s1[x] != '*')
            {
                return false;
            }
        }
        return true;
    }

    if (dp[i][j] != -1)
    {
        return dp[i][j];
    }
    // Solving other cases
    if (s1[i] == s2[j] || s1[i] == '?')
    {
        return dp[i][j] = solveMemo(s1, s2, i - 1, j - 1, dp);
    }
    if (s1[i] == '*')
    {
        return dp[i][j] = solveMemo(s1, s2, i - 1, j, dp) || solveMemo(s1, s2, i, j - 1, dp);
    }
    return dp[i][j] = false;
}
int wildCardMemo(string pattern, string str)
{
    int pSize = pattern.length();
    int strSize = str.length();
    vector<vector<int>> dp(pSize, vector<int>(strSize, -1));
    if (solveMemo(pattern, str, pSize - 1, strSize - 1, dp))
    {
        return 1;
    }
    return 0;
}

// ---------------------------------------------------------------------------------------------------------------

// Memoized Solution After Shifting Of Index
bool solveMemo2(string &s1, string &s2, int i, int j, vector<vector<int>> &dp)
{

    // base Cases
    if (i == 0 && j == 0)
    {
        return true;
    }
    if (i == 0 && j >= 1)
    {
        return false;
    }

    if (j == 0 && i >= 1)
    {
        for (int x = 1; x <= i; x++) // note : Here Also changes are made
        {
            if (s1[x - 1] != '*')
            {
                return false;
            }
        }
        return true;
    }

    if (dp[i][j] != -1)
    {
        return dp[i][j];
    }
    // Solving other cases
    if (s1[i - 1] == s2[j - 1] || s1[i - 1] == '?')
    {
        return dp[i][j] = solveMemo2(s1, s2, i - 1, j - 1, dp);
    }
    if (s1[i - 1] == '*')
    {
        return dp[i][j] = solveMemo2(s1, s2, i - 1, j, dp) || solveMemo2(s1, s2, i, j - 1, dp);
    }
    return dp[i][j] = false;
}
int wildCardMemo2(string pattern, string str)
{
    int pSize = pattern.length();
    int strSize = str.length();
    vector<vector<int>> dp(pSize + 1, vector<int>(strSize + 1, -1));
    if (solveMemo2(pattern, str, pSize, strSize, dp))
    {
        return 1;
    }
    return 0;
}

// ---------------------------- Tabulation Solution -------------------------------------------------------
int wildCardTab(string pattern, string str)
{
    int pSize = pattern.length();
    int strSize = str.length();
    vector<vector<bool>> dp(pSize + 1, vector<bool>(strSize + 1, false));

    // Converting base Cases:
    dp[0][0] = true;
    for (int j = 1; j <= strSize; j++)
    {
        dp[0][j] = false;
    }
    for (int i = 1; i <= pSize; i++)
    {
        bool flag = true;
        for (int x = 1; x <= i; x++)
        {
            if (pattern[x - 1] != '*')
            {
                flag = false;
                break;
            }
        }
        // for every row you are assigning the 0th column's value
        dp[i][0] = flag;
    }

    // Comparisons
    for (int i = 1; i <= pSize; i++)
    {
        for (int j = 1; j <= strSize; j++)
        {
            if (pattern[i - 1] == str[j - 1] || pattern[i - 1] == '?')
            {
                dp[i][j] = dp[i - 1][j - 1];
            }
            else if (pattern[i - 1] == '*')
            {
                dp[i][j] = dp[i - 1][j] || dp[i][j - 1];
            }
            else
            {
                dp[i][j] = false;
            }
        }
    }
    if (dp[pSize][strSize])
    {
        return 1;
    }
    return 0;
}

// Space Optimized Code:
int wildCardSpace(string pattern, string str)
{
    int pSize = pattern.length();
    int strSize = str.length();
    vector<bool> prev(strSize + 1, -1), curr(strSize + 1, -1);

    // Converting base Cases:
    prev[0] = true;
    for (int j = 1; j <= strSize; j++)
    {
        prev[j] = false;
    }

    // Comparisons
    for (int i = 1; i <= pSize; i++)
    {
        // One of the base case
        // curr is the current row/s column and that cur's 0th row has to be assigned everytime
        bool flag = true;
        for (int x = 1; x <= i; x++)
        {
            if (pattern[x - 1] != '*')
            {
                flag = false;
                break;
            }
        }
        // for every row you are assigning the 0th column's value
        curr[0] = flag;

        for (int j = 1; j <= strSize; j++)
        {
            if (pattern[i - 1] == str[j - 1] || pattern[i - 1] == '?')
            {
                curr[j] = prev[j - 1];
            }
            else if (pattern[i - 1] == '*')
            {
                curr[j] = prev[j] || curr[j - 1];
            }
            else
            {
                curr[j] = false;
            }
        }
        prev = curr;
    }
    if (prev[strSize])
    {
        return 1;
    }
    return 0;
}
