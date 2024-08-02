#include <iostream>
#include <vector>
using namespace std;

// Brute Force Solution : Using Sorting Algorithm where TC=(NlogN)
// Better Solution : Keeping count variables of zeroes , ones and twos and then overwriting them in the Original array
// Best Solution : Using DNF algorithm ---> Dutch National Flag Algorithm

// DNF algorithm
void sortArray(vector<int> &arr, int n)
{
    // Write your code here
    int low = 0, mid = 0, high = n - 1;
    while (mid <= high)
    {
        if (arr[mid] == 0)
        {
            swap(arr[low], arr[mid]);
            low++;
            mid++;
        }
        else if (arr[mid] == 1)
        {
            mid++;
        }
        else
        {
            swap(arr[mid], arr[high]);
            high--;
        }
    }
}