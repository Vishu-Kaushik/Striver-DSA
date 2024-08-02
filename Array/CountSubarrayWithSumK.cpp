#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

// Method 1 --> Brute force --> to create the all the subarrays and then check for the sum
// Tc will be O(N^3)

int subArrayCount(int arr[], int n, int k)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            int sum = 0;
            for (int k = i; k <= j; k++)
            {
                sum += arr[k];
            }
            if (sum == k)
            {
                count++;
            }
        }
    }
    return count;
}

/* Better Solution
Method 2 -- > O(N^2)
*/

int subArrayCount(int arr[], int n, int k)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        int sum = 0;
        for (int j = i; j < n; j++)
        {
            sum += arr[j];
            if (sum == k)
            {
                count++;
            }
        }
    }
    return count;
}

/*
Optimal solution --> Using hashing

----------------------Time complexity:---------------------------
-----> Using ordered map :  O(N log(N))
-----> Using unorderded map : O(Nx1) but this if there are constraints that results in the collisions it will become O(N^2)

----------------------Space Complexity--------------------------
As we are storing the Prefix  Sum or preSum for every index it will be ----> O(N)

Note  --> i will look as left as possible for the sum of (x-k).
*/

int countSubarrayswithSumK(vector<int> nums, int k)
{
    map<int, int> mp;
    mp[0] = 1; // of great significance
    int preFixSum = 0;
    int count = 0;

    for (int i = 0; i < nums.size(); i++)
    {
        preFixSum += nums[i];
        int remove = preFixSum - k;
        if (mp.find(remove) != mp.end())
        {
            count += mp[remove];
        }
        mp[preFixSum] += 1;
    }
    return count;
}