#include <iostream>
#include <vector>
using namespace std;

// Naive Solution :
int peakNaive(int arr[], int n)
{
    if (n == 1)
    {
        return 0; // arr[0]
    }
    for (int i = 0; i < n; i++)
    {
        if ((i == 0 || arr[i] > arr[i - 1]) && (i == n - 1 || arr[i] > arr[i + 1]))
        {
            return i; // arr[i]
        }
    }
    return -1;
}

// Efficient SOlution :
int peakElementEfficient(int arr[], int n)
{
    // Your code here
    if (n == 1)
    {
        return 0;
    }
    if (arr[0] >= arr[1])
    {
        return 0;
    }
    else if (arr[n - 1] >= arr[n - 2])
    {
        return n - 1;
    }

    int low = 1;
    int high = n - 2;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        if (arr[mid] >= arr[mid + 1] && arr[mid] >= arr[mid - 1])
        {
            return mid;
        }
        //   Smaller than the left and greater than the right
        else if ((arr[mid - 1] > arr[mid] && arr[mid + 1] < arr[mid]))
        {
            high = mid - 1;
        }
        else if (arr[mid - 1] < arr[mid] && arr[mid + 1] > arr[mid])
        {
            low = mid + 1;
        }
        else
        {
            low = mid + 1;
        }
    }
    return -1;
}
