/*
https://www.geeksforgeeks.org/problems/subset-sum-problem-1611555638/1
Subset Sum Problem
Given an array of positive integers arr[] and a value sum, determine if there is a subset of arr[] with sum equal to given sum.
Examples:
Input: arr[] = [3, 34, 4, 12, 5, 2], sum = 9
Output: true
Explanation: Here there exists a subset with target sum = 9, 4+3+2 = 9.
Input: arr[] = [3, 34, 4, 12, 5, 2], sum = 30
Output: false
Explanation: There is no subset with target sum 30.
Input: arr[] = [1, 2, 3], sum = 6
Output: true
Explanation: The entire array can be taken as a subset, giving 1 + 2 + 3 = 6.
Constraints:
1 <= arr.size() <= 200
1<= arr[i] <= 200
1<= sum <= 104
*/

#include <bits/stdc++.h>
using namespace std;

bool isSubsetSumRecursiveHelper(int index, vector<int> &arr, int sum)
{
    if (sum == 0)
    {
        return true;
    }
    if (sum < 0 || index == arr.size())
    {
        return false;
    }
    return isSubsetSumRecursiveHelper(index + 1, arr, sum - arr[index]) || isSubsetSumRecursiveHelper(index + 1, arr, sum);
}

// Recursive
// Time Complexity: O(2^n)
// Space Complexity: O(n) due to recursion stack
// where n is the size of the input array arr.
bool isSubsetSumRecursive(vector<int> &arr, int sum)
{
    return isSubsetSumRecursiveHelper(0, arr, sum);
}

bool isSubsetSumMemoizationHelper(int index, vector<int> &arr, int sum, vector<vector<int>> &dp)
{
    if (sum == 0)
    {
        return true;
    }
    if (sum < 0 || index == arr.size())
    {
        return false;
    }
    if (dp[index][sum] != -1)
    {
        return dp[index][sum];
    }
    return dp[index][sum] = isSubsetSumMemoizationHelper(index + 1, arr, sum - arr[index], dp) || isSubsetSumMemoizationHelper(index + 1, arr, sum, dp);
}

// Memoization
// Time Complexity: O(n*sum)
// Space Complexity: O(n*sum) for DP table + O(n) recursion stack
// where n is the size of the input array arr and sum is the target sum.
bool isSubsetSumMemoization(vector<int> &arr, int sum)
{
    vector<vector<int>> dp(arr.size(), vector<int>(sum + 1, -1));
    return isSubsetSumMemoizationHelper(0, arr, sum, dp);
}

// Tabulation
// Time Complexity: O(n*sum)
// Space Complexity: O(n*sum)
// where n is the size of the input array arr and sum is the target sum.
bool isSubsetSumTabulation(vector<int> &arr, int sum)
{
    // Steps to convert memoization to tabulation:
    int n = arr.size();
    // 1. Create dp array of size n+1 x sum+1 and initialize with false
    // we take n+1 because we are including the base case where index = n
    vector<vector<bool>> dp(n + 1, vector<bool>(sum + 1, 0));
    // 2. Analyze base cases and fill the dp array accordingly
    // Here, for all indices, when target sum is 0, we can always form the sum by taking no elements
    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = true;
    }
    // 3. Nested loops should be bottom up. Here, we have two states -> index and target sum.
    // for the first state (index), we go from n-1 to 0 (reverse of memoization function, which goes from 0 to n-1), making this bottom up.
    // i.e. Start from base case to original function call
    // for the second state (target sum), we iterate from 1 to sum
    // because smaller target values are required to compute larger ones.
    for (int index = n - 1; index >= 0; index--)
    {
        for (int target = 1; target <= sum; target++)
        {
            bool notTake = dp[index + 1][target];
            bool take = false;
            // we can only take the element if it does not exceed the target
            if (arr[index] <= target)
            {
                take = dp[index + 1][target - arr[index]];
            }
            dp[index][target] = take || notTake;
        }
    }
    return dp[0][sum];
}

// Tabulation Optimized
// Time Complexity: O(n*sum)
// Space Complexity: O(sum)
// where n is the size of the input array arr and sum is the target sum.
bool isSubsetSumTabulationOptimized(vector<int> &arr, int sum)
{
    int n = arr.size();
    vector<bool> dp(sum + 1, 0);
    dp[0] = true;
    for (int index = n - 1; index >= 0; index--)
    {
        for (int target = sum; target >= arr[index]; target--)
        {
            dp[target] = dp[target - arr[index]] || dp[target];
        }
    }
    return dp[sum];
}

int main()
{
    vector<int> arr = {3, 34, 4, 12, 5, 2};
    int sum = 9;
    cout << isSubsetSumTabulationOptimized(arr, sum) << endl; // Output: 1 (true)
    arr = {3, 34, 4, 12, 5, 2};
    sum = 30;
    cout << isSubsetSumTabulationOptimized(arr, sum) << endl; // Output: 0 (false)
    arr = {1, 2, 3};
    sum = 6;
    cout << isSubsetSumTabulationOptimized(arr, sum) << endl; // Output: 1 (true)
    return 0;
}