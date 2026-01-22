/*
https://leetcode.com/problems/partition-equal-subset-sum/description/
416. Partition Equal Subset Sum
Given an integer array nums, return true if you can partition the array into two subsets such that the sum of the elements in both subsets is equal or false otherwise.
Example 1:
Input: nums = [1,5,11,5]
Output: true
Explanation: The array can be partitioned as [1, 5, 5] and [11].
Example 2:
Input: nums = [1,2,3,5]
Output: false
Explanation: The array cannot be partitioned into equal sum subsets.
Constraints:
1 <= nums.length <= 200
1 <= nums[i] <= 100
*/

#include <bits/stdc++.h>
using namespace std;

bool canPartitionRecursiveHelper(int index, vector<int> &nums, int sum)
{
    if (sum == 0)
    {
        return true;
    }
    if (sum < 0 || index == nums.size())
    {
        return false;
    }
    return canPartitionRecursiveHelper(index + 1, nums, sum - nums[index]) || canPartitionRecursiveHelper(index + 1, nums, sum);
}

// Recursive
// Time Complexity: O(2^n)
// Space Complexity: O(n) due to recursion stack
// where n is the size of the input array nums.
bool canPartitionRecursive(vector<int> &nums)
{
    int sum = accumulate(nums.begin(), nums.end(), 0);
    if (sum % 2 != 0)
        return false;
    return canPartitionRecursiveHelper(0, nums, sum / 2);
}

bool canPartitionMemoizationHelper(int index, vector<int> &nums, int sum, vector<vector<int>> &dp)
{
    if (sum == 0)
    {
        return true;
    }
    if (sum < 0 || index == nums.size())
    {
        return false;
    }
    if (dp[index][sum] != -1)
    {
        return dp[index][sum];
    }
    return dp[index][sum] =
               canPartitionMemoizationHelper(index + 1, nums,
                                             sum - nums[index], dp) ||
               canPartitionMemoizationHelper(index + 1, nums, sum, dp);
}

// Memoization
// Time Complexity: O(n*sum)
// Space Complexity: O(n*sum) for DP table + O(n) recursion stack
// where n is the size of the input array nums and sum is the target sum.
bool canPartitionMemoization(vector<int> &nums)
{
    int sum = accumulate(nums.begin(), nums.end(), 0);
    vector<vector<int>> dp(nums.size(), vector<int>(sum / 2 + 1, -1));
    return (sum % 2 != 0) ? false : canPartitionMemoizationHelper(0, nums, sum / 2, dp);
}

// Tabulation
// Time Complexity: O(n*sum)
// Space Complexity: O(n*sum)
// where n is the size of the input array nums and sum is the target sum.
bool canPartitionTabulation(vector<int> &nums)
{
    // Step 1: Calculate total sum of the array
    int sum = accumulate(nums.begin(), nums.end(), 0);
    // If total sum is odd, it cannot be partitioned into two equal subsets
    if (sum % 2 != 0)
        return false;
    // We now need to check if there exists a subset with sum = totalSum / 2
    sum /= 2;
    int n = nums.size();
    // dp[index][target] =
    // true if we can form 'target' using elements from index to n-1
    vector<vector<bool>> dp(n + 1, vector<bool>(sum + 1, false));
    // Base case:
    // Target sum 0 can always be formed by choosing no elements
    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = true;
    }
    // Fill the DP table bottom-up
    // index goes from n-1 down to 0 (reverse of recursion)
    for (int index = n - 1; index >= 0; index--)
    {
        // target represents the remaining sum we want to form
        for (int target = 1; target <= sum; target++)
        {
            // Option 1: Do not take the current element
            bool notTake = dp[index + 1][target];
            // Option 2: Take the current element (only if it does not exceed target)
            bool take = false;
            if (nums[index] <= target)
            {
                take = dp[index + 1][target - nums[index]];
            }
            // If either option is true, we can form this target
            dp[index][target] = take || notTake;
        }
    }
    // Final answer: can we form sum using all elements starting from index 0?
    return dp[0][sum];
}

// Space Optimized Tabulation
// Time Complexity: O(n*sum)
// Space Complexity: O(sum)
bool canPartitionTabulationOptimized(vector<int> &nums)
{
    int sum = accumulate(nums.begin(), nums.end(), 0);
    if (sum % 2 != 0)
        return false;
    sum /= 2;
    int n = nums.size();
    vector<bool> dp(sum + 1, 0);
    dp[0] = true;
    for (int index = n - 1; index >= 0; index--)
    {
        for (int target = sum; target >= nums[index]; target--)
        {
            dp[target] = dp[target - nums[index]] || dp[target];
        }
    }
    return dp[sum];
}

int main()
{
    vector<int> nums = {1, 5, 11, 5};
    cout << canPartitionTabulationOptimized(nums) << endl; // Output: 1 (true)
    nums = {1, 2, 3, 5};
    cout << canPartitionTabulationOptimized(nums) << endl; // Output: 0 (false)
    return 0;
}