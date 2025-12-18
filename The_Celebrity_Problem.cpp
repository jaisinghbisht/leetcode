/*
https://www.geeksforgeeks.org/problems/the-celebrity-problem/1
The Celebrity Problem
A celebrity is a person who is known to all but does not know anyone at a party. A party is being organized by some people. A square matrix mat[][] of size n*n is used to represent people at the party such that if an element of row i and column j is set to 1 it means ith person knows jth person. You need to return the index of the celebrity in the party, if the celebrity does not exist, return -1.
Note: Follow 0-based indexing.
Examples:
Input: mat[][] = [[1, 1, 0],
                [0, 1, 0],
                [0, 1, 1]]
Output: 1
Explanation: 0th and 2nd person both know 1st person and 1st person does not know anyone. Therefore, 1 is the celebrity person.
Input: mat[][] = [[1, 1],
                [1, 1]]
Output: -1
Explanation: Since both the people at the party know each other. Hence none of them is a celebrity person.
Input: mat[][] = [[1]]
Output: 0
Constraints:
1 ≤ mat.size() ≤ 1000
0 ≤ mat[i][j] ≤ 1
mat[i][i] = 1
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity: O(n^2), Space Complexity: O(n)
// where n is the number of people at the party
int celebrityBruteForce(vector<vector<int>> &mat)
{
    int n = mat.size();
    vector<int> knowMe(n, 0), IKnow(n, 0);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (mat[i][j] == 1)
            {
                knowMe[j]++;
                IKnow[i]++;
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (knowMe[i] == n && IKnow[i] == 1)
            return i;
    }
    return -1;
}

// Time Complexity: O(n), Space Complexity: O(1)
// where n is the number of people at the party
int celebrity(vector<vector<int>> &mat)
{
    int n = mat.size();
    int top = 0, down = n - 1;
    while (top < down)
    {
        // top knows down, so top cannot be celebrity
        if (mat[top][down] == 1)
            top++;
        // down knows top, so down cannot be celebrity
        else if (mat[down][top] == 1)
            down--;
        // both don't know each other, so both cannot be celebrity (since one must be known by other)
        else
        {
            top++;
            down--;
        }
    }
    if (top > down)
    {
        return -1;
    }
    // verify if top is celebrity
    for (int i = 0; i < n; i++)
    {
        // diagonal element
        if (i == top)
            continue;
        // final row and column check
        if (mat[top][i] == 0 && mat[i][top] == 1)
            continue;
        else
            return -1;
    }
    return top;
}

int main()
{
    vector<vector<int>> mat1 = {
        {1, 1, 0},
        {0, 1, 0},
        {0, 1, 1}};
    cout << celebrityBruteForce(mat1) << endl; // Output: 1
    cout << celebrity(mat1) << endl;           // Output: 1
    vector<vector<int>> mat2 = {
        {1, 1},
        {1, 1}};
    cout << celebrityBruteForce(mat2) << endl; // Output: -1
    cout << celebrity(mat2) << endl;           // Output: -1
    vector<vector<int>> mat3 = {
        {1}};
    cout << celebrityBruteForce(mat3) << endl; // Output: 0
    cout << celebrity(mat3) << endl;           // Output: 0
    return 0;
}