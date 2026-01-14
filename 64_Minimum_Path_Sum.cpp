/*
https://leetcode.com/problems/minimum-path-sum/description/
64. Minimum Path Sum
Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right, which minimizes the sum of all numbers along its path.
Note: You can only move either down or right at any point in time.
Example 1:
Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
Output: 7
Explanation: Because the path 1 → 3 → 1 → 1 → 1 minimizes the sum.
Example 2:
Input: grid = [[1,2,3],[4,5,6]]
Output: 12
Constraints:
m == grid.length
n == grid[i].length
1 <= m, n <= 200
0 <= grid[i][j] <= 200
*/

#include <bits/stdc++.h>
using namespace std;

long long minPathSumHelperRecursive(int r, int c, const int m, const int n, vector<vector<int>> &grid)
{
    if (r == m - 1 && c == n - 1)
        return grid[r][c];
    if (r > m - 1 || c > n - 1)
        return INT_MAX;
    int right = minPathSumHelperRecursive(r + 1, c, m, n, grid); // down
    int down = minPathSumHelperRecursive(r, c + 1, m, n, grid);  // right
    return grid[r][c] + min(right, down);
}

// Recursive Approach
// Time Complexity: O(2^(m+n)), where m is the number of rows and n is the number of columns.
// Space Complexity: O(m+n) for the recursion stack.
int minPathSumRecursive(vector<vector<int>> &grid)
{
    int m = grid.size(), n = grid[0].size();
    return (int)minPathSumHelperRecursive(0, 0, m, n, grid);
}

long long minPathSumHelperMemoization(int r, int c, const int m, const int n, vector<vector<int>> &grid, vector<vector<int>> &dp)
{
    if (r == m - 1 && c == n - 1)
        return dp[r][c] = grid[r][c];
    if (r > m - 1 || c > n - 1)
        return INT_MAX;
    if (dp[r][c] != -1)
        return dp[r][c];
    int right = minPathSumHelperMemoization(r + 1, c, m, n, grid, dp); // down
    int down = minPathSumHelperMemoization(r, c + 1, m, n, grid, dp);  // right
    return dp[r][c] = grid[r][c] + min(right, down);
}

// Memoization Approach
// Time Complexity: O(m*n), where m is the number of rows and n is the number of columns.
// Space Complexity: O(m*n) for the dp array + O(m+n) for the recursion stack.
int minPathSumMemoization(vector<vector<int>> &grid)
{
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> dp(m, vector<int>(n, -1));
    return (int)minPathSumHelperMemoization(0, 0, m, n, grid, dp);
}

// Tabulation Approach
// Time Complexity: O(m*n), where m is the number of rows and n is the number of columns.
// Space Complexity: O(m*n) for the dp array.
int minPathSumTabulation(vector<vector<int>> &grid)
{
    int m = grid.size(), n = grid[0].size();
    vector<vector<int>> dp(m, vector<int>(n));
    dp[0][0] = grid[0][0];
    for (int i = 1; i < m; i++)
    {
        dp[i][0] = dp[i - 1][0] + grid[i][0];
    }
    for (int j = 1; j < n; j++)
    {
        dp[0][j] = dp[0][j - 1] + grid[0][j];
    }
    for (int i = 1; i < m; i++)
    {
        for (int j = 1; j < n; j++)
        {
            dp[i][j] = grid[i][j] + min(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[m - 1][n - 1];
}

// Tabulation Approach - Space Optimized
// Time Complexity: O(m*n), where m is the number of rows and n is the number of columns.
// Space Complexity: O(n) for the dp array.
int minPathSumTabulationOptimized(vector<vector<int>> &grid)
{
    int m = grid.size(), n = grid[0].size();
    vector<int> dp(n);
    dp[0] = grid[0][0];
    for (int j = 1; j < n; j++)
    {
        dp[j] = dp[j - 1] + grid[0][j];
    }
    for (int i = 1; i < m; i++)
    {
        // we can only come from above in the first column
        dp[0] += grid[i][0];
        for (int j = 1; j < n; j++)
        {
            dp[j] = grid[i][j] + min(dp[j], dp[j - 1]);
        }
    }
    return dp[n - 1];
}

int main()
{
    vector<vector<int>> grid = {{1, 3, 1}, {1, 5, 1}, {4, 2, 1}};
    cout << "Minimum Path Sum: " << minPathSumTabulationOptimized(grid) << endl; // Output: 7
    grid = {{1, 2, 3}, {4, 5, 6}};
    cout << "Minimum Path Sum: " << minPathSumTabulationOptimized(grid) << endl; // Output: 12
    return 0;
}