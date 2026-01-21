/*
https://leetcode.com/problems/minimum-falling-path-sum/description/
931. Minimum Falling Path Sum
Given an n x n array of integers matrix, return the minimum sum of any falling path through matrix.
A falling path starts at any element in the first row and chooses the element in the next row that is either directly below or diagonally left/right. Specifically, the next element from position (row, col) will be (row + 1, col - 1), (row + 1, col), or (row + 1, col + 1).
Example 1:
Input: matrix = [[2,1,3],[6,5,4],[7,8,9]]
Output: 13
Explanation: There are two falling paths with a minimum sum as shown.
Example 2:
Input: matrix = [[-19,57],[-40,-5]]
Output: -59
Explanation: The falling path with a minimum sum is shown.
Constraints:
n == matrix.length == matrix[i].length
1 <= n <= 100
-100 <= matrix[i][j] <= 100
*/

#include <bits/stdc++.h>
using namespace std;

int minFallingPathSumRecursiveHelper(int row, int col, const int m, const int n, vector<vector<int>> &matrix)
{
    if (row == m)
    {
        return 0;
    }
    if (row < 0 || row >= m || col < 0 || col >= n)
        return INT_MAX;
    int left = minFallingPathSumRecursiveHelper(row + 1, col - 1, m, n, matrix);
    int same = minFallingPathSumRecursiveHelper(row + 1, col, m, n, matrix);
    int right = minFallingPathSumRecursiveHelper(row + 1, col + 1, m, n, matrix);
    return matrix[row][col] + min(left, min(same, right));
}

// Recursive
// Time Complexity: O(3^(m*n))
// Space Complexity: O(m*n) for the recursion stack
// where m is the number of rows and n is the number of columns
int minFallingPathSumRecursive(vector<vector<int>> &matrix)
{
    int m = matrix.size(), n = matrix[0].size();
    int res = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        res = min(res, minFallingPathSumRecursiveHelper(0, i, m, n, matrix));
    }
    return res;
}

int minFallingPathSumMemoizationHelper(int row, int col, const int m, const int n, vector<vector<int>> &matrix, vector<vector<int>> &dp)
{
    if (row == m)
    {
        return 0;
    }
    if (row < 0 || row >= m || col < 0 || col >= n)
        return INT_MAX;
    if (dp[row][col] != INT_MAX)
        return dp[row][col];
    int left = minFallingPathSumMemoizationHelper(row + 1, col - 1, m, n, matrix, dp);
    int same = minFallingPathSumMemoizationHelper(row + 1, col, m, n, matrix, dp);
    int right = minFallingPathSumMemoizationHelper(row + 1, col + 1, m, n, matrix, dp);
    return dp[row][col] = matrix[row][col] + min(left, min(same, right));
}

// Memoization
// Time Complexity: O(m*n)
// Space Complexity: O(m*n) for the dp array + O(m*n) for the recursion stack
// where m is the number of rows and n is the number of columns
int minFallingPathSumMemoization(vector<vector<int>> &matrix)
{
    int m = matrix.size(), n = matrix[0].size();
    vector<vector<int>> dp(m, vector<int>(n, INT_MAX));
    int res = INT_MAX;
    for (int i = 0; i < n; i++)
    {
        res = min(res, minFallingPathSumMemoizationHelper(0, i, m, n, matrix, dp));
    }
    return res;
}

// Tabulation
// Time Complexity: O(m*n)
// Space Complexity: O(m*n) for the dp array
// where m is the number of rows and n is the number of columns
int minFallingPathSumTabulation(vector<vector<int>> &matrix)
{
    int n = matrix.size();
    vector<vector<int>> dp(n, vector<int>(n, INT_MAX));
    for (int i = 0; i < n; i++)
    {
        dp[0][i] = matrix[0][i];
    }
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j == 0 && j + 1 < n)
            {
                dp[i][j] = matrix[i][j] + min(dp[i - 1][j], dp[i - 1][j + 1]);
            }
            else if (j == n - 1)
            {
                dp[i][j] = matrix[i][j] + min(dp[i - 1][j], dp[i - 1][j - 1]);
            }
            else
            {
                dp[i][j] = matrix[i][j] + min(dp[i - 1][j], min(dp[i - 1][j - 1], dp[i - 1][j + 1]));
            }
        }
    }
    return *min_element(dp[n - 1].begin(), dp[n - 1].end());
}

// Tabulation with Space Optimization
// Time Complexity: O(m*n)
// Space Complexity: O(n) for the dp array
// where m is the number of rows and n is the number of columns
int minFallingPathSumTabulationOptimized(vector<vector<int>> &matrix)
{
    int n = matrix.size();
    vector<int> dp = matrix[0];
    for (int i = 1; i < n; i++)
    {
        vector<int> newDp(n);
        for (int j = 0; j < n; j++)
        {
            int best = dp[j];
            if (j > 0)
            {
                best = min(best, dp[j - 1]);
            }
            if (j < n - 1)
            {
                best = min(best, dp[j + 1]);
            }
            newDp[j] = matrix[i][j] + best;
        }
        dp = newDp;
    }
    return *min_element(dp.begin(), dp.end());
}

int main()
{
    vector<vector<int>> matrix = {{2, 1, 3}, {6, 5, 4}, {7, 8, 9}};
    cout << minFallingPathSumTabulationOptimized(matrix) << endl; // Output: 13
    matrix = {{-19, 57}, {-40, -5}};
    cout << minFallingPathSumTabulationOptimized(matrix) << endl; // Output: -59
    return 0;
}