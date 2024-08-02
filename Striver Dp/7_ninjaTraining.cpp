#include <iostream>
#include <vector>
using namespace std;

/*Problem statement:
Ninja is planing this ‘N’ days-long training schedule. Each day, he can perform any one of these three activities. (Running, Fighting Practice or Learning New Moves).
Each activity has some merit points on each day. As Ninja has to improve all his skills, he can’t do the same activity in two consecutive days. Can you help Ninja find
out the maximum merit points Ninja can earn?

You are given a 2D array of size N*3 ‘POINTS’ with the points corresponding to each day and activity. Your task is to calculate the maximum number of merit points that
Ninja can earn.

For Example
If the given ‘POINTS’ array is [[1,2,5], [3 ,1 ,1] ,[3,3,3] ],the answer will be 11 as 5 + 3 + 3.
*/

// Whenever the greedy fails we do try all possible ways i.e. we do recursion

/* Here two parameters are changing i.e day and last task perfomed therefore the dp array will be 2 dimensional and the day goes from (0 to n-1) and the last goes from (0 to 3 )
i.e. it goes till task+1 */

// Recursive Solution
int solve(int day, int last, vector<vector<int>> &points)
{
    if (day == 0)
    {
        int maxi = 0;
        for (int task = 0; task < 3; task++)
        {
            if (task != last)
            {
                maxi = max(maxi, points[0][task]);
            }
        }
        return maxi;
    }

    int maxi = 0;

    for (int task = 0; task < 3; task++)
    {
        if (task != last)
        {
            int point = points[day][task] + solve(day - 1, task, points);
            maxi = max(maxi, point);
        }
    }
    return maxi;
}

// Memoiation Technique ----> TC is O(N*4)*3 and the SC is O(N) + O(N*4)
int memoSolve(int day, int last, vector<vector<int>> &points, vector<vector<int>> &dp)
{
    if (day == 0)
    {
        int maxi = 0;
        for (int task = 0; task < 3; task++) // we can perform only three tasks i.e t0,t1,t2 but the extra t3 is when we are starting to perform task and
        // previously no task were perfomed (Running, Fighting Practice or Learning New Moves)
        {
            if (task != last)
            {
                maxi = max(maxi, points[0][task]);
            }
        }
        return maxi;
    }

    if (dp[day][last] != -1)
    {
        return dp[day][last];
    }

    int maxi = 0;

    for (int task = 0; task < 3; task++)
    {
        if (task != last)
        {
            int point = points[day][task] + memoSolve(day - 1, task, points, dp);
            maxi = max(maxi, point);
        }
    }
    return dp[day][last] = maxi;
}

int ninjaTechnique(int n, vector<vector<int>> &points)
{
    vector<vector<int>> dp(n, vector<int>(4, -1));
    // return solve(n - 1, 3, points); // recursive solve
    return memoSolve(n - 1, 3, points, dp);
}

//  --------------------------------------------------------------------------------------------------------------------------------

// Tabulation Technique Solution  ----> TC is O(N*4)*3 and the SC is  O(N*4)
int ninjaTabulation(int n, vector<vector<int>> &points)
{
    vector<vector<int>> dp(n, vector<int>(4, 0));

    // base Cases
    dp[0][0] = max(points[0][1], points[0][2]);
    dp[0][1] = max(points[0][0], points[0][2]);
    dp[0][2] = max(points[0][0], points[0][1]);
    dp[0][3] = max(points[0][0], max(points[0][1], points[0][2]));

    for (int day = 1; day < n; day++)
    {
        for (int last = 0; last < 4; last++)
        {
            int maxi = 0;
            for (int task = 0; task < 3; task++)
            {
                if (task != last)
                {
                    int point = points[day][task] + dp[day - 1][task];
                    maxi = max(maxi, point);
                }
            }
            dp[day][last] = maxi;
        }
    }
    return dp[n - 1][3];
}

// Sapce Optimized solution : Tc as O(N*4*3) and SC as O(4)
int ninjaSpaceOptimized(int n, vector<vector<int>> &points)
{
    vector<int> prev(4, 0);

    // base Cases
    prev[0] = max(points[0][1], points[0][2]);
    prev[1] = max(points[0][0], points[0][2]);
    prev[2] = max(points[0][0], points[0][1]);
    prev[3] = max(points[0][0], max(points[0][1], points[0][2]));

    for (int day = 1; day < n; day++)
    {
        vector<int> temp(4, 0);
        for (int last = 0; last < 4; last++)
        {
            temp[last] = 0;
            // int maxi = 0;
            for (int task = 0; task < 3; task++)
            {
                if (task != last)
                {
                    // int point = points[day][task] + prev[task];
                    // maxi = max(maxi, point);
                    temp[last] = max(temp[last], points[day][task] + prev[task]);
                }
            }
            // temp[last] = maxi;
        }
        prev = temp;
    }
    return prev[3];
}