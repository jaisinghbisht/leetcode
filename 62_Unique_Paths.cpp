/*
https://leetcode.com/problems/unique-paths/description/
62. Unique Paths
There is a robot on an m x n grid. The robot is initially located at the top-left corner (i.e., grid[0][0]). The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]). The robot can only move either down or right at any point in time.
Given the two integers m and n, return the number of possible unique paths that the robot can take to reach the bottom-right corner.
The test cases are generated so that the answer will be less than or equal to 2 * 109.
Example 1:
Input: m = 3, n = 7
Output: 28
Example 2:
Input: m = 3, n = 2
Output: 3
Explanation: From the top-left corner, there are a total of 3 ways to reach the bottom-right corner:
1. Right -> Down -> Down
2. Down -> Down -> Right
3. Down -> Right -> Down
Constraints:
1 <= m, n <= 100
*/

#include <bits/stdc++.h>
using namespace std;

int uniquePathsRecursiveHelper(int r, int c, const int m, const int n, vector<vector<int>> &visited)
{
    if (r == m - 1 && c == n - 1)
        return 1;
    if (r > m - 1 || c > n - 1 || visited[r][c])
        return 0;
    visited[r][c] = 1;
    int right = uniquePathsRecursiveHelper(r + 1, c, m, n, visited); // right
    int down = uniquePathsRecursiveHelper(r, c + 1, m, n, visited);  // down
    visited[r][c] = 0;
    return right + down;
}

// Recursive
// Time Complexity: O(2^(m+n)), where m is the number of rows and n is the number of columns.
// Space Complexity: O(m+n), for the recursion stack.
int uniquePathsRecursive(int m, int n)
{
    vector<vector<int>> visited(m, vector<int>(n, 0));
    return uniquePathsRecursiveHelper(0, 0, m, n, visited);
}

int uniquePathsMemoizationHelper(int r, int c, const int m, const int n,
                                 vector<vector<int>> &visited,
                                 vector<vector<int>> &dp)
{
    if (r == m - 1 && c == n - 1)
        return 1;
    if (r > m - 1 || c > n - 1 || visited[r][c])
        return 0;
    if (dp[r][c] != -1)
        return dp[r][c];
    visited[r][c] = 1;
    int right = uniquePathsMemoizationHelper(r + 1, c, m, n, visited, dp); // right
    int down = uniquePathsMemoizationHelper(r, c + 1, m, n, visited, dp);  // down
    visited[r][c] = 0;
    return dp[r][c] = right + down;
}

// Memoization
// Time Complexity: O(m*n), where m is the number of rows and n is the number of columns.
// Space Complexity: O(m*n) for the dp array + O(m+n) for the recursion stack.
int uniquePathsMemoization(int m, int n)
{
    vector<vector<int>> visited(m, vector<int>(n, 0));
    vector<vector<int>> dp(m, vector<int>(n, -1));
    return uniquePathsMemoizationHelper(0, 0, m, n, visited, dp);
}

// Tabulation
// Time Complexity: O(m*n), where m is the number of rows and n is the number of columns.
// Space Complexity: O(m*n) for the dp array.
int uniquePathsTabulation(int m, int n)
{
    // dp[i][j] will be storing the number of unique paths to reach cell (i, j)
    vector<vector<int>> dp(m, vector<int>(n, 1));
    for (int i = 1; i < m; i++)
    {
        for (int j = 1; j < n; j++)
        {
            dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }
    return dp[m - 1][n - 1];
}

// Tabulation Optimized
// Time Complexity: O(m*n), where m is the number of rows and n is the number of columns.
// Space Complexity: O(n) for the dp array.
int uniquePathsTabulationOptimized(int m, int n)
{
    // we only need the previous row to calculate the current row, not the entire matrix
    vector<int> dp(n, 1);
    for (int i = 1; i < m; i++)
    {
        for (int j = 1; j < n; j++)
        {
            dp[j] = dp[j] + dp[j - 1];
        }
    }
    return dp[n - 1];
}

int main()
{
    int m = 3, n = 7;
    cout << uniquePathsTabulationOptimized(m, n) << endl; // Output: 28
    m = 3, n = 2;
    cout << uniquePathsTabulationOptimized(m, n) << endl; // Output: 3
    return 0;
}