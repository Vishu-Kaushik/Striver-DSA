#include <iostream>
#include <vector>
using namespace std;

int f(vector<int> &nums, int goal)
{
    if (goal < 0)
    {
        return 0;
    }
    int l = 0, r = 0, count = 0, sum = 0;
    while (r <= nums.size())
    {
        sum += nums[r];
        while (sum > goal)
        {
            sum -= nums[l];
            l++;
        }
        count += (r - l + 1);
        r++;
    }
    return count;
}

int binarySum(vector<int> &nums, int goal)
{
    return f(nums, goal) - f(nums, goal - 1);
}