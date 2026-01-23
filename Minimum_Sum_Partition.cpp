/*
https://www.geeksforgeeks.org/problems/minimum-sum-partition3317/1
Minimum sum partition
Given an array arr[]  containing non-negative integers, the task is to divide it into two sets set1 and set2 such that the absolute difference between their sums is minimum and find the minimum difference.
Examples:
Input: arr[] = [1, 6, 11, 5]
Output: 1
Explanation:
Subset1 = {1, 5, 6}, sum of Subset1 = 12
Subset2 = {11}, sum of Subset2 = 11
Hence, minimum difference is 1.
Input: arr[] = [1, 4]
Output: 3
Explanation:
Subset1 = {1}, sum of Subset1 = 1
Subset2 = {4}, sum of Subset2 = 4
Hence, minimum difference is 3.
Input: arr[] = [1]
Output: 1
Explanation:
Subset1 = {1}, sum of Subset1 = 1
Subset2 = {}, sum of Subset2 = 0
Hence, minimum difference is 1.
Constraints:
1 ≤ arr.size()*|sum of array elements| ≤ 10^5
1 <= arr[i] <= 10^5
*/

#include <bits/stdc++.h>
using namespace std;

int minDifferenceRecursiveHelper(int index, int s1, vector<int> &arr, const int total)
{
    if (index == arr.size())
    {
        return abs(total - 2 * s1);
    }
    int take = minDifferenceRecursiveHelper(index + 1, s1 + arr[index], arr, total);
    int notTake = minDifferenceRecursiveHelper(index + 1, s1, arr, total);
    return min(take, notTake);
}

// Recursive approach
// Time Complexity: O(2^n)
// Space Complexity: O(n) for recursion stack
int minDifferenceRecursive(vector<int> &arr)
{
    int total = accumulate(arr.begin(), arr.end(), 0);
    return minDifferenceRecursiveHelper(0, 0, arr, total);
}

int minDifferenceMemoizationHelper(int index, int s1, vector<int> &arr, vector<vector<int>> &dp, int total)
{
    if (index == arr.size())
    {
        return abs(total - 2 * s1);
    }

    if (dp[index][s1] != -1)
        return dp[index][s1];

    int take = minDifferenceMemoizationHelper(index + 1, s1 + arr[index], arr, dp, total);
    int notTake = minDifferenceMemoizationHelper(index + 1, s1, arr, dp, total);

    return dp[index][s1] = min(take, notTake);
}

// Memoization approach
// Time Complexity: O(n*sum)
// Space Complexity: O(n*sum) + O(n) for recursion stack
int minDifferenceMemoization(vector<int> &arr)
{
    int total = accumulate(arr.begin(), arr.end(), 0);
    vector<vector<int>> dp(arr.size(), vector<int>(total + 1, -1));
    return minDifferenceMemoizationHelper(0, 0, arr, dp, total);
}

// Tabulation approach
// Time Complexity: O(n*sum)
// Space Complexity: O(n*sum)
int minDifferenceTabulation(vector<int> &arr)
{
    int n = arr.size();
    int sum = accumulate(arr.begin(), arr.end(), 0);
    int half = sum / 2;
    vector<vector<bool>> dp(n + 1, vector<bool>(half + 1, 0));
    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = true;
    }
    for (int index = n - 1; index >= 0; index--)
    {
        for (int target = 1; target <= half; target++)
        {
            bool notTake = dp[index + 1][target];
            bool take = false;
            if (arr[index] <= target)
            {
                take = dp[index + 1][target - arr[index]];
            }
            dp[index][target] = take || notTake;
        }
    }
    int res = INT_MAX;
    for (int s = 0; s <= half; s++)
    {
        if (dp[0][s] == true)
        {
            res = min(res, abs(sum - 2 * s));
        }
    }
    return res;
}

// Tabulation Optimized approach
// Time Complexity: O(n*sum)
// Space Complexity: O(sum)
int minDifferenceTabulationOptimized(vector<int> &arr)
{
    int n = arr.size();
    int sum = accumulate(arr.begin(), arr.end(), 0);
    int half = sum / 2;
    vector<bool> dp(half + 1, 0);
    dp[0] = true;
    for (int index = n - 1; index >= 0; index--)
    {
        for (int target = half; target >= arr[index]; target--)
        {
            dp[target] = dp[target] || dp[target - arr[index]];
        }
    }
    int res = INT_MAX;
    for (int s = 0; s <= half; s++)
    {
        if (dp[s])
        {
            res = min(res, sum - 2 * s);
        }
    }
    return res;
}

int main()
{
    vector<int> arr = {1, 6, 11, 5};
    cout << minDifferenceTabulationOptimized(arr) << endl; // Output: 1
    arr = {1, 4};
    cout << minDifferenceTabulationOptimized(arr) << endl; // Output: 3
    arr = {1};
    cout << minDifferenceTabulationOptimized(arr) << endl; // Output: 1
    return 0;
}