#include <iostream>
using namespace std;

void rearrange(long long *arr, int n)
{

    // Your code here
    // 	Idea --> If we can have(integrate) the value that we need to be and the value that was present here at the same
    // postion for a particular index
    // Logic : when integrating for the maximum value :
    //  arr[i] = arr[i]+(arr[high]%maxi)*maxi;
    // Logic : when integrating for the minimum value :
    //  arr[i] = arr[i]+(arr[low]%maxi)*maxi;
    int low = 0;
    int high = n - 1;
    long long maxi = arr[high] + 1;
    if (n == 1)
    {
        return;
    }
    int i = 0;
    while (low <= high)
    {
        if (i % 2 == 0) // the max element is at the even position
        {
            arr[i] = arr[i] + (arr[high] % maxi) * maxi;
            i++;
            high--;
        }
        else
        { // the min element is at the odd position
            arr[i] = arr[i] + (arr[low] % maxi) * maxi;
            i++;
            low++;
        }
    }
    for (int i = 0; i < n; i++)
    {
        arr[i] = arr[i] / maxi;
    }
}