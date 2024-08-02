#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
using namespace std;

// Question ----> We need to find the length of longest subarray with sum "K"

/*
Brute force -> With O(N^3) Time Complexity
*/

int subArrayLength(int arr[], int n, int k)
{
    int len = 0;
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
                len = max(len, j - i + 1);
            }
        }
    }
    return len;
}

/*
Brute force -> With O(N^2) Time Complexity
*/

int subArrayLength(int arr[], int n, int k)
{
    int len = 0;
    for (int i = 0; i < n; i++)
    {
        int sum = 0;
        for (int j = i; j < n; j++)
        {
            sum += arr[j];
            if (sum == k)
            {
                len = max(len, j - i + 1);
            }
        }
    }
    return len;
}

// This solution is the optimal solution for the array if it has positives and negatives only

// But here the array contains can contain positives and  zeroes and negatives
/* Better solution --> Using hashing

----------------------Time complexity:---------------------------
-----> Using ordered map :  O(N log(N))
-----> Using unorderded map : O(Nx1) but this if there are constraints that results in the collisions it will become O(N^2)

----------------------Space Complexity--------------------------
As we are storing the Prefix  Sum or preSum for every index it will be ----> O(N)

Note  --> i will look as left as possible for the sum of (x-k).
*/

// REfer to striver to video
int maxLenSubarrayWithSumK(vector<long long> nums, int k)
{
    int size = nums.size();
    map<long long, int> preSumMap; // map of type sum , index
    int maxLen = 0;
    long long sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += nums[i];
        if (sum == k)
        {
            maxLen = max(maxLen, i + 1);
        }
        long long rem = sum - k;
        if (preSumMap.find(rem) != preSumMap.end())
        {
            int len = i - preSumMap[rem];
            maxLen = max(maxLen, len);
        }

        if (preSumMap.find(sum) == preSumMap.end()) // this change is when the array contains the zero in it.
        {
            preSumMap[sum] = i;
        }
    }
    return maxLen;
}

/*
The Most Optimal solution uses two pointer algorithm
where both starts from the first element
But here the array contains  positives and zeroes only
*/

int maxLenSubarrayWithSumK(vector<long long> nums, int k)
{
    int n = nums.size();
    long long sum = nums[0];
    int maxLen = 0;

    // Declaring the two pointers
    int left = 0;
    int right = 0;
    while (right < n)
    {
        while (left <= right && sum > k)
        {
            sum -= nums[left];
            left++;
        }
        if (sum == k)
        {
            maxLen = max(maxLen, right - left + 1);
        }
        right++;
        if (right < n)
        {
            sum += nums[right];
        }
    }
    return maxLen;
}