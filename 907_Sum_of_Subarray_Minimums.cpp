/*
https://leetcode.com/problems/sum-of-subarray-minimums/description/
907. Sum of Subarray Minimums
Given an array of integers arr, find the sum of min(b), where b ranges over every (contiguous) subarray of arr. Since the answer may be large, return the answer modulo 109 + 7.
Example 1:
Input: arr = [3,1,2,4]
Output: 17
Explanation:
Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4].
Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.
Sum is 17.
Example 2:
Input: arr = [11,81,94,43,3]
Output: 444
Constraints:
1 <= arr.length <= 3 * 104
1 <= arr[i] <= 3 * 104
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity: O(n^2), Space Complexity: O(1)
// where n is the size of the array
// brute force approach
int sumSubarrayMinsBruteForce(vector<int> &arr)
{
    int res = 0;
    for (int i = 0; i < arr.size(); i++)
    {
        int minVal = INT_MAX;
        for (int j = i; j < arr.size(); j++)
        {
            minVal = min(minVal, arr[j]);
            res += minVal;
        }
    }
    return res;
}

/* --------------------------------------------------------- */
/* --------------------------------------------------------- */

vector<int> findNSE(vector<int> &arr)
{
    int n = arr.size();
    stack<int> st;
    vector<int> nse(n, -1);
    for (int i = n - 1; i >= 0; i--)
    {
        while (!st.empty() && arr[st.top()] >= arr[i])
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

vector<int> findPSEE(vector<int> &arr)
{
    int n = arr.size();
    stack<int> st;
    vector<int> psee(n, -1);
    for (int i = 0; i < n; i++)
    {
        // we want both previous and equal smaller elements, so we use '>' in comparison, not '>='
        // this is done to avoid double counting of elements as minimum in subarrays
        while (!st.empty() && arr[st.top()] > arr[i])
        {
            st.pop();
        }
        if (!st.empty())
        {
            psee[i] = st.top();
        }
        st.push(i);
    }
    return psee;
}

// Time Complexity: O(n), Space Complexity: O(n)
// where n is the size of the array
int sumSubarrayMinsOptimal(vector<int> &arr)
{
    int n = arr.size();
    const int MODULO = 1e9 + 7;
    vector<int> nextSmallerElement = findNSE(arr);
    // IMP : we need previous smaller and equal element for correct calculation, otherwise it could lead to duplicate counting
    // for e.g. consider arr = [3,1,2,4], for element '1', if we consider only previous smaller element, then for subarray [3,1],
    // '1' will be counted twice as minimum when we consider subarrays [3,1] and [1] separately.
    vector<int> previousSmallerAndGreaterElement = findPSEE(arr);
    long long total = 0;
    for (int i = 0; i < n; i++)
    {
        int prevSub = i - previousSmallerAndGreaterElement[i];
        // IMP : marking nse as n if -1 since it helps in calculation of nextSub
        // for e.g. when there is no smaller element on right side of current element,
        // then all elements to the right including current element will have current element as minimum
        if (nextSmallerElement[i] == -1)
            nextSmallerElement[i] = n;
        int nextSub = nextSmallerElement[i] - i;
        total = (total + (1LL * prevSub * nextSub * arr[i]) % MODULO) % MODULO;
    }
    return (int)total;
}

int main()
{
    vector<int> arr = {3, 1, 2, 4};
    cout << sumSubarrayMinsBruteForce(arr) << endl; // Output: 17
    cout << sumSubarrayMinsOptimal(arr) << endl;    // Output: 17
    vector<int> arr2 = {11, 81, 94, 43, 3};
    cout << sumSubarrayMinsBruteForce(arr2) << endl; // Output: 444
    cout << sumSubarrayMinsOptimal(arr2) << endl;    // Output: 444
    return 0;
}