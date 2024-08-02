#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Approach 1 : using new technique to solve it
int solve(int i, int j, string A, vector<vector<int>> &dp)
{
    if (i == j)
    {
        return 1;
    }
    if (i > j)
    {
        return 0;
    }
    if (dp[i][j] != -1)
    {
        return dp[i][j];
    }

    if (A[i] == A[j])
    {
        return dp[i][j] = 2 + solve(i + 1, j - 1, A, dp);
    }
    return dp[i][j] = max(solve(i + 1, j, A, dp), solve(i, j - 1, A, dp));
}
int longestPalinSubseq(string A)
{
    // code here
    int len = A.length();
    vector<vector<int>> dp(len, vector<int>(len, -1));
    return solve(0, len - 1, A, dp);
}

// -------------------------------------------------- End of approach 1 ----------------------------------------------------

// ---------- Approach 2 : Using the idea of the LCS problem
// But there is only one string given to us so We have to find the other string
// 1. First Stirng is The given string
// 2. Second string is the reverse of the given string
// Then after finding the two strings we can apply the code of LCS for this problem.

// Recursive Solution 1 : without shifting of indexes ------------------------------------------------------------
int solveRec1(int i, int j, string A, string B)
{
    if (i < 0 || j < 0)
    {
        return 0;
    }

    if (A[i] == B[j])
    {
        return 1 + solveRec1(i - 1, j - 1, A, B);
    }
    return max(solveRec1(i - 1, j, A, B), solveRec1(i, j - 1, A, B));
}
int longestPalinSubseqRec1(string A)
{
    // code here
    int len = A.length();
    string B = A;
    reverse(B.begin(), B.end());
    return solveRec1(len - 1, len - 1, A, B);
}
// --------------------------------------------------------------------------------------------------------------------------------------------------------

// ------------------------------------------ Recursive Solution 2 : using the shifting of indexes -------------------------------------------------------------------------------------

int solveRec2(int i, int j, string A, string B)
{
    if (i == 0 || j == 0)
    {
        return 0;
    }

    if (A[i - 1] == B[j - 1])
    {
        return 1 + solveRec2(i - 1, j - 1, A, B);
    }
    return max(solveRec2(i - 1, j, A, B), solveRec2(i, j - 1, A, B));
}
int longestPalinSubseqRec(string A)
{
    // code here
    int len = A.length();
    string B = A;
    reverse(B.begin(), B.end());
    return solveRec2(len, len, A, B);
}

// ------------------------------------------ End of Recursive Solution 2 : using the shifting of indexes ----------------------------------------------------

// ----------------------------------------Memoiation Solution : using the shifting of index -------------------------------------------------------------------------
int solveMemo1(int i, int j, string A, string B, vector<vector<int>> &dp)
{
    if (i == 0 || j == 0)
    {
        return 0;
    }
    if (dp[i][j] != -1)
    {
        return dp[i][j];
    }

    if (A[i - 1] == B[j - 1])
    {
        return dp[i][j] = 1 + solveMemo1(i - 1, j - 1, A, B, dp);
    }
    return dp[i][j] = max(solveMemo1(i - 1, j, A, B, dp), solveMemo1(i, j - 1, A, B, dp));
}
int longestPalinSubseqMemo(string A)
{
    // code here
    int len = A.length();
    string B = A;
    reverse(B.begin(), B.end());
    vector<vector<int>> dp(len + 1, vector<int>(len + 1, -1));
    return solveMemo1(len, len, A, B, dp);
}

// -------------------------------------------- End of Memoiation Solution----------------------------------------------------------------------------------

// ------------------ Tabulation SOlution : using shifting of index _--------------------------------------------------------------------------------------
int lcsTab(int n, int m, string s1, string s2)
{
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
    // Base Cases
    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = 0;
    }
    for (int j = 0; j <= m; j++)
    {
        dp[0][j] = 0;
    }

    // Wrting the nested loops
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
int longestPalinSubseqTab(string A)
{
    // code here
    int len = A.length();
    string B = A;
    reverse(B.begin(), B.end());
    // vector<vector<int>> dp(len+1,vector<int>(len+1,-1))
    return lcsTab(len, len, A, B);
}

// ---------------------------- End of tabulation Solution -----------------------------------------
// We can also do space optimization in the same manner as we did in the LCS problem