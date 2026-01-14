/*
https://leetcode.com/problems/unique-paths-ii/description/
63. Unique Paths II
You are given an m x n integer array grid. There is a robot initially located at the top-left corner (i.e., grid[0][0]). The robot tries to move to the bottom-right corner (i.e., grid[m - 1][n - 1]). The robot can only move either down or right at any point in time.
An obstacle and space are marked as 1 or 0 respectively in grid. A path that the robot takes cannot include any square that is an obstacle.
Return the number of possible unique paths that the robot can take to reach the bottom-right corner.
The testcases are generated so that the answer will be less than or equal to 2 * 109.
Example 1:
Input: obstacleGrid = [[0,0,0],[0,1,0],[0,0,0]]
Output: 2
Explanation: There is one obstacle in the middle of the 3x3 grid above.
There are two ways to reach the bottom-right corner:
1. Right -> Right -> Down -> Down
2. Down -> Down -> Right -> Right
Example 2:
Input: obstacleGrid = [[0,1],[0,0]]
Output: 1
Constraints:
m == obstacleGrid.length
n == obstacleGrid[i].length
1 <= m, n <= 100
obstacleGrid[i][j] is 0 or 1.
*/

#include <bits/stdc++.h>
using namespace std;

int uniquePathsRecursiveHelper(int r, int c, const int m, const int n, vector<vector<int>> &obstacleGrid)
{
    if (r == m - 1 && c == n - 1)
        return 1;
    if (r > m - 1 || c > n - 1 || obstacleGrid[r][c])
        return 0;
    int right = uniquePathsRecursiveHelper(r + 1, c, m, n, obstacleGrid); // down
    int down = uniquePathsRecursiveHelper(r, c + 1, m, n, obstacleGrid);  // right
    return right + down;
}

// Recursive
// Time Complexity: O(2^(m+n)), where m is the number of rows and n is the number of columns.
// Space Complexity: O(m+n) for the recursion stack.
int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid)
{
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();
    if (obstacleGrid[m - 1][n - 1] == 1)
        return 0;
    return uniquePathsRecursiveHelper(0, 0, m, n, obstacleGrid);
}

int uniquePathsRecursiveHelper(int r, int c, const int m, const int n, vector<vector<int>> &obstacleGrid, vector<vector<int>> &dp)
{
    if (r == m - 1 && c == n - 1)
        return 1;
    if (r > m - 1 || c > n - 1 || obstacleGrid[r][c])
        return 0;
    if (dp[r][c] != -1)
        return dp[r][c];
    int right = uniquePathsRecursiveHelper(r + 1, c, m, n, obstacleGrid, dp); // down
    int down = uniquePathsRecursiveHelper(r, c + 1, m, n, obstacleGrid, dp);  // right
    return dp[r][c] = right + down;
}

// Memoization
// Time Complexity: O(m*n), where m is the number of rows and n is the number of columns.
// Space Complexity: O(m*n) for the dp array and O(m+n) for the recursion stack.
int uniquePathsWithObstaclesMemoization(vector<vector<int>> &obstacleGrid)
{
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();
    if (obstacleGrid[m - 1][n - 1] == 1)
        return 0;
    vector<vector<int>> dp(m, vector<int>(n, -1));
    return uniquePathsRecursiveHelper(0, 0, m, n, obstacleGrid, dp);
}

// Tabulation
// Time Complexity: O(m*n), where m is the number of rows and n is the number of columns.
// Space Complexity: O(m*n) for the dp array.
int uniquePathsWithObstaclesTabulation(vector<vector<int>> &obstacleGrid)
{
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();
    if (obstacleGrid[m - 1][n - 1] || obstacleGrid[0][0])
        return 0;
    vector<vector<int>> dp(m, vector<int>(n, 0));
    // start position
    dp[0][0] = 1;
    // first column
    for (int i = 1; i < m; i++)
    {
        if (obstacleGrid[i][0] == 0)
            dp[i][0] = dp[i - 1][0];
    }
    // first row
    for (int j = 1; j < n; j++)
    {
        if (obstacleGrid[0][j] == 0)
            dp[0][j] = dp[0][j - 1];
    }
    for (int i = 1; i < m; i++)
    {
        for (int j = 1; j < n; j++)
        {
            if (obstacleGrid[i][j] == 0)
            {
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
            }
        }
    }
    return dp[m - 1][n - 1];
}

// Tabulation Optimized
// Time Complexity: O(m*n), where m is the number of rows and n is the number of columns.
// Space Complexity: O(n) for the dp array.
int uniquePathsWithObstaclesTabulationOptimized(vector<vector<int>> &obstacleGrid)
{
    int m = obstacleGrid.size(), n = obstacleGrid[0].size();
    if (obstacleGrid[m - 1][n - 1] || obstacleGrid[0][0])
        return 0;
    vector<int> dp(n, 0);
    dp[0] = 1;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (obstacleGrid[i][j] == 1)
            {
                dp[j] = 0;
            }
            else if (j >= 1)
            {
                dp[j] = dp[j] + dp[j - 1];
            }
        }
    }
    return dp[n - 1];
}

int main()
{
    vector<vector<int>> obstacleGrid = {{0, 0, 0}, {0, 1, 0}, {0, 0, 0}};
    cout << uniquePathsWithObstaclesTabulationOptimized(obstacleGrid) << endl; // Output: 2
    obstacleGrid = {{0, 1}, {0, 0}};
    cout << uniquePathsWithObstaclesTabulationOptimized(obstacleGrid) << endl; // Output: 1
    return 0;
}