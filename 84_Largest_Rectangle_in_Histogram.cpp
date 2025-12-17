/*
https://leetcode.com/problems/largest-rectangle-in-histogram/
84. Largest Rectangle in Histogram
Given an array of integers heights representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.
Example 1:
Input: heights = [2,1,5,6,2,3]
Output: 10
Explanation: The above is a histogram where width of each bar is 1.
The largest rectangle is shown in the red area, which has an area = 10 units.
Example 2:
Input: heights = [2,4]
Output: 4
Constraints:
1 <= heights.length <= 105
0 <= heights[i] <= 104
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> findNSE(vector<int> &heights)
{
    int n = heights.size();
    vector<int> nse(n, n);
    stack<int> st;
    for (int i = n - 1; i >= 0; i--)
    {
        while (!st.empty() && heights[st.top()] >= heights[i])
        {
            st.pop();
        }
        if (!st.empty())
        {
            nse[i] = st.top();
        }
        st.push(i);
    }
    return nse;
}

vector<int> findPSE(vector<int> &heights)
{
    int n = heights.size();
    vector<int> nse(n, -1);
    stack<int> st;
    for (int i = 0; i < n; i++)
    {
        while (!st.empty() && heights[st.top()] >= heights[i])
        {
            st.pop();
        }
        if (!st.empty())
        {
            nse[i] = st.top();
        }
        st.push(i);
    }
    return nse;
}

// Time Complexity: O(n), Space Complexity: O(n)
// where n is the size of the array
int largestRectangleArea(vector<int> &heights)
{
    vector<int> nse = findNSE(heights);
    vector<int> pse = findPSE(heights);
    int area = 0;
    for (int i = 0; i < heights.size(); i++)
    {
        area = max(area, heights[i] * (nse[i] - pse[i] - 1));
    }
    return area;
}

// Time Complexity: O(n), Space Complexity: O(n)
// where n is the size of the array
int largestRectangleAreaOptimal(vector<int> &heights)
{
    stack<int> st;
    int n = heights.size(), area = 0;
    for (int i = 0; i < n; i++)
    {
        // we traverse the array and for each element, we pop elements from stack until we find a smaller element, maintaining a monotonic stack
        // this way we find both nse and pse in a single traversal
        while (!st.empty() && heights[st.top()] > heights[i])
        {
            int currElement = heights[st.top()];
            st.pop();
            int nse = i;
            int pse = st.empty() ? -1 : st.top();
            area = max(area, currElement * (nse - pse - 1));
        }
        st.push(i);
    }
    // clear remaining elements in stack
    while (!st.empty())
    {
        int currElement = heights[st.top()];
        st.pop();
        int nse = n;
        int pse = st.empty() ? -1 : st.top();
        area = max(area, currElement * (nse - pse - 1));
    }
    return area;
}

int main()
{
    vector<int> heights = {2, 1, 5, 6, 2, 3};
    cout << largestRectangleArea(heights) << endl;        // Output: 10
    cout << largestRectangleAreaOptimal(heights) << endl; // Output: 10
    heights = {2, 4};
    cout << largestRectangleArea(heights) << endl;        // Output: 4
    cout << largestRectangleAreaOptimal(heights) << endl; // Output: 4
    return 0;
}