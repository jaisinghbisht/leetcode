/*
Count Subsets with Sum K
Problem statement
You are given an array 'arr' of size 'n' containing positive integers and a target sum 'k'.
Find the number of ways of selecting the elements from the array such that the sum of chosen elements is equal to the target 'k'.
Since the number of ways can be very large, print it modulo 10 ^ 9 + 7.
Example:
Input: 'arr' = [1, 1, 4, 5]
Output: 3
Explanation: The possible ways are:
[1, 4]
[1, 4]
[5]
Hence the output will be 3. Please note that both 1 present in 'arr' are treated differently.
Detailed explanation ( Input/output format, Notes, Images )
Sample Input 1 :
4 5
1 4 4 5
Sample Output 1 :
3
Explanation For Sample Output 1:
The possible ways are:
[1, 4]
[1, 4]
[5]
Hence the output will be 3. Please note that both 1 present in 'arr' are treated differently.
Sample Input 2 :
3 2
1 1 1
Sample Output 2 :
3
Explanation For Sample Output 1:
There are three 1 present in the array. Answer is the number of ways to choose any two of them.
Sample Input 3 :
3 40
2 34 5
Sample Output 3 :
0
Expected time complexity :
The expected time complexity is O('n' * 'k').
Constraints:
1 <= 'n' <= 100
0 <= 'arr[i]' <= 1000
1 <= 'k' <= 1000
Time limit: 1 sec
*/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int findWaysRecursiveHelper(int index, vector<int> &arr, int k)
{
    if (index == arr.size())
    {
        if (k == 0)
            return 1;
        return 0;
    }
    if (k < 0)
        return 0;
    return findWaysRecursiveHelper(index + 1, arr, k - arr[index]) + findWaysRecursiveHelper(index + 1, arr, k);
}

// Recursive approach
// Time Complexity: O(2^n)
// Space Complexity: O(n)
int findWaysRecursive(vector<int> &arr, int k)
{
    return findWaysRecursiveHelper(0, arr, k);
}

int findWaysMemoizationHelper(int index, vector<int> &arr, int k, vector<vector<int>> &dp)
{
    if (index == arr.size())
    {
        return (k == 0);
    }
    if (dp[index][k] != -1)
        return dp[index][k];
    int notTake = findWaysMemoizationHelper(index + 1, arr, k, dp);
    int take = 0;
    if (arr[index] <= k)
    {
        take = findWaysMemoizationHelper(index + 1, arr, k - arr[index], dp);
    }
    return dp[index][k] = (take + notTake) % MOD;
}

// Memoization approach
// Time Complexity: O(n*k)
// Space Complexity: O(n*k) + O(n) (for recursion stack)
int findWaysMemoization(vector<int> &arr, int k)
{
    vector<vector<int>> dp(arr.size(), vector<int>(k + 1, -1));
    return findWaysMemoizationHelper(0, arr, k, dp);
}

// Tabulation approach
// Time Complexity: O(n*k)
// Space Complexity: O(n*k)
int findWaysTabulation(vector<int> &arr, int k)
{
    int n = arr.size();
    vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
    dp[n][0] = 1;
    for (int idx = n - 1; idx >= 0; idx--)
    {
        for (int s = k; s >= 0; s--)
        {
            int notTake = dp[idx + 1][s];
            int take = 0;
            if (arr[idx] <= s)
            {
                take = dp[idx + 1][s - arr[idx]];
            }
            dp[idx][s] = (take + notTake) % MOD;
        }
    }
    return dp[0][k];
}

// Space Optimized Tabulation approach
// Time Complexity: O(n*k)
// Space Complexity: O(k)
int findWaysTabulationSpaceOptimized(vector<int> &arr, int k)
{
    int n = arr.size();
    vector<int> dp(k + 1, 0);
    dp[0] = 1;
    for (int idx = n - 1; idx >= 0; idx--)
    {
        for (int s = k; s >= arr[idx]; s--)
        {
            int notTake = dp[s];
            int take = 0;
            if (arr[idx] <= s)
            {
                take = dp[s - arr[idx]];
            }
            dp[s] = (take + notTake) % MOD;
        }
    }
    return dp[k];
}

int main()
{
    vector<int> arr = {1, 1, 4, 5};
    int k = 5;
    cout << findWaysTabulationSpaceOptimized(arr, k) << endl; // Output: 3
    arr = {1, 1, 1};
    k = 2;
    cout << findWaysTabulationSpaceOptimized(arr, k) << endl; // Output: 3
    arr = {2, 34, 5};
    k = 40;
    cout << findWaysTabulationSpaceOptimized(arr, k) << endl; // Output: 0
    return 0;
}
