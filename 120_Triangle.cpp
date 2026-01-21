/*
https://leetcode.com/problems/triangle/
120. Triangle
Given a triangle array, return the minimum path sum from top to bottom.
For each step, you may move to an adjacent number of the row below. More formally, if you are on index i on the current row, you may move to either index i or index i + 1 on the next row.
Example 1:
Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
Output: 11
Explanation: The triangle looks like:
   2
  3 4
 6 5 7
4 1 8 3
The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined above).
Example 2:
Input: triangle = [[-10]]
Output: -10
Constraints:
1 <= triangle.length <= 200
triangle[0].length == 1
triangle[i].length == triangle[i - 1].length + 1
-104 <= triangle[i][j] <= 104
Follow up: Could you do this using only O(n) extra space, where n is the total number of rows in the triangle?
*/

#include <bits/stdc++.h>
using namespace std;

long long minimumTotalRecursiveHelper(int index, int row, vector<vector<int>> &triangle)
{
    if (row == triangle.size())
    {
        return 0;
    }
    if (index < 0 || index >= triangle[row].size())
        return INT_MAX;
    int down = minimumTotalRecursiveHelper(index, row + 1, triangle);
    int right = minimumTotalRecursiveHelper(index + 1, row + 1, triangle);
    return triangle[row][index] + min(down, right);
}

// Recursive Approach
// Time Complexity: O(2^n), where n is the number of rows in the triangle.
// Space Complexity: O(n) for the recursion stack.
int minimumTotalRecursive(vector<vector<int>> &triangle)
{
    return (int)minimumTotalRecursiveHelper(0, 0, triangle);
}

long long minimumTotalMemoizationHelper(int index, int row, vector<vector<int>> &triangle, vector<vector<long long>> &dp)
{
    if (row == triangle.size())
        return 0;
    if (dp[row][index] != LLONG_MAX)
        return dp[row][index];
    int down = minimumTotalMemoizationHelper(index, row + 1, triangle, dp);
    int right = minimumTotalMemoizationHelper(index + 1, row + 1, triangle, dp);
    return dp[row][index] = triangle[row][index] + min(down, right);
}

// Memoization Approach
// Time Complexity: O(n^2), where n is the number of rows in the triangle
// Space Complexity: O(n^2) for the dp array + O(n) for the recursion stack.
int minimumTotalMemoization(vector<vector<int>> &triangle)
{
    vector<vector<long long>> dp(triangle.size());
    for (int i = 0; i < triangle.size(); i++)
    {
        dp[i] = vector<long long>(triangle[i].size(), LLONG_MAX);
    }
    return (int)minimumTotalMemoizationHelper(0, 0, triangle, dp);
}

// Tabulation Approach
// Time Complexity: O(n^2), where n is the number of rows in the triangle
// Space Complexity: O(n^2) for the dp array
int minimumTotalTabulation(vector<vector<int>> &triangle)
{
    int n = triangle.size();
    vector<vector<int>> dp(n);
    for (int i = 0; i < n; i++)
    {
        dp[i] = vector<int>(triangle[i].size(), INT_MAX);
    }
    dp[0][0] = triangle[0][0];
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < triangle[i].size(); j++)
        {
            if (j == 0)
            {
                dp[i][j] = triangle[i][j] + dp[i - 1][j];
            }
            else if (j == triangle[i].size() - 1)
            {
                dp[i][j] = triangle[i][j] + dp[i - 1][j - 1];
            }
            else
            {
                dp[i][j] = triangle[i][j] + min(dp[i - 1][j], dp[i - 1][j - 1]);
            }
        }
    }
    int ans = INT_MAX;
    for (int val : dp[n - 1])
    {
        ans = min(ans, val);
    }
    return ans;
}

// Tabulation Optimized Approach
// Time Complexity: O(n^2), where n is the number of rows in the triangle
// Space Complexity: O(n) for the dp array
int minimumTotalTabulationOptimized(vector<vector<int>> &triangle)
{
    int n = triangle.size();
    vector<long long> dp(n, LLONG_MAX);
    dp[0] = triangle[0][0];
    for (int i = 1; i < n; i++)
    {
        for (int j = triangle[i].size() - 1; j >= 0; j--)
        {
            if (j == 0)
            {
                dp[j] += triangle[i][j];
            }
            else if (j == triangle[i].size() - 1)
            {
                dp[j] = dp[j - 1] + triangle[i][j];
            }
            else
            {
                dp[j] = min(dp[j], dp[j - 1]) + triangle[i][j];
            }
        }
    }
    return *min_element(dp.begin(), dp.end());
}

int main()
{
    vector<vector<int>> triangle = {{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}};
    cout << minimumTotalTabulationOptimized(triangle) << endl; // Output: 11
    triangle = {{-10}};
    cout << minimumTotalTabulationOptimized(triangle) << endl; // Output: -10
}