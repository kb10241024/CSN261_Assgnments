#include <bits/stdc++.h>
using namespace std;

// Driver Code
int main()
{
    double time = 0.0;
    clock_t starting = clock();

    ///Taking Inputs
    cout << "Enter the number of elements for array" << endl;
    int n;
    cin >> n;
    int *arr = new int[n];
    cout << "Enter elements" << endl;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    int k;
    cout << "Enter k : " << endl;
    cin >> k;

    int begin = 0, end = 0;

    // unordered_map 'um' implemented
    // as hash table
    unordered_map<int, int> um;
    int sum = 0, maxLen = 0;

    // traverse the given array
    for (int i = 0; i < n; i++)
    {
        // accumulate sum
        sum += arr[i];

        // when subarray starts from index '0'
        if (sum == k)
        {
            maxLen = i + 1;
            begin = 0;
            end = i;
        }

        // make an entry for 'sum' if it is
        // not present in 'um'
        if (um.find(sum) == um.end())
            um[sum] = i;

        // check if 'sum-k' is present in 'um'
        // or not
        if (um.find(sum - k) != um.end())
        {

            // update maxLength
            if (maxLen < (i - um[sum - k]))
            {
                maxLen = i - um[sum - k];
                begin = um[sum - k] + 1;
                end = i;
            }
        }
    }
    cout << "Length of longest subarray is " << maxLen << endl;
    cout << "Index from " << begin << " to " << end << endl;

    clock_t ending = clock();
    time += (double)(ending - starting) / CLOCKS_PER_SEC;
    printf("\nTotal Execution time is : %f (sec)\n", time);

    return 0;
}
