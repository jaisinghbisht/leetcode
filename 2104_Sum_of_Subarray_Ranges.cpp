/*
https://leetcode.com/problems/sum-of-subarray-ranges/
2104. Sum of Subarray Ranges
You are given an integer array nums. The range of a subarray of nums is the difference between the largest and smallest element in the subarray.
Return the sum of all subarray ranges of nums.
A subarray is a contiguous non-empty sequence of elements within an array.
Example 1:
Input: nums = [1,2,3]
Output: 4
Explanation: The 6 subarrays of nums are the following:
[1], range = largest - smallest = 1 - 1 = 0
[2], range = 2 - 2 = 0
[3], range = 3 - 3 = 0
[1,2], range = 2 - 1 = 1
[2,3], range = 3 - 2 = 1
[1,2,3], range = 3 - 1 = 2
So the sum of all ranges is 0 + 0 + 0 + 1 + 1 + 2 = 4.
Example 2:
Input: nums = [1,3,3]
Output: 4
Explanation: The 6 subarrays of nums are the following:
[1], range = largest - smallest = 1 - 1 = 0
[3], range = 3 - 3 = 0
[3], range = 3 - 3 = 0
[1,3], range = 3 - 1 = 2
[3,3], range = 3 - 3 = 0
[1,3,3], range = 3 - 1 = 2
So the sum of all ranges is 0 + 0 + 0 + 2 + 0 + 2 = 4.
Example 3:
Input: nums = [4,-2,-3,4,1]
Output: 59
Explanation: The sum of all subarray ranges of nums is 59.
Constraints:
1 <= nums.length <= 1000
-109 <= nums[i] <= 109
*/

#include <bits/stdc++.h>
using namespace std;

vector<int> findNSE(vector<int> &nums)
{
    int n = nums.size();
    stack<int> st;
    vector<int> nse(n, -1);
    for (int i = n - 1; i >= 0; i--)
    {
        while (!st.empty() && nums[st.top()] >= nums[i])
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

vector<int> findPSEE(vector<int> &nums)
{
    int n = nums.size();
    stack<int> st;
    vector<int> pse(n, -1);
    for (int i = 0; i < n; i++)
    {
        // we want both previous and equal smaller elements, so we use '>' in comparison, not '>='
        // this is done to avoid double counting of elements as minimum in subarrays
        while (!st.empty() && nums[st.top()] > nums[i])
        {
            st.pop();
        }
        if (!st.empty())
        {
            pse[i] = st.top();
        }
        st.push(i);
    }
    return pse;
}

vector<int> findNGE(vector<int> &nums)
{
    int n = nums.size();
    stack<int> st;
    vector<int> nse(n, -1);
    for (int i = n - 1; i >= 0; i--)
    {
        while (!st.empty() && nums[st.top()] <= nums[i])
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

vector<int> findPGEE(vector<int> &nums)
{
    int n = nums.size();
    stack<int> st;
    vector<int> pse(n, -1);
    for (int i = 0; i < n; i++)
    {
        // we want both previous and equal greater elements, so we use '<' in comparison, not '<='
        // this is done to avoid double counting of same elements as maximum in subarrays
        while (!st.empty() && nums[st.top()] < nums[i])
        {
            st.pop();
        }
        if (!st.empty())
        {
            pse[i] = st.top();
        }
        st.push(i);
    }
    return pse;
}

// Time Complexity: O(n), Space Complexity: O(n)
// where n is the size of the array
long long subArrayRanges(vector<int> &nums)
{
    int n = nums.size();
    vector<int> nextSmallerElement = findNSE(nums);
    vector<int> previousSmallerAndGreaterElement = findPSEE(nums);
    vector<int> nextGreaterElement = findNGE(nums);
    vector<int> previousGreaterElement = findPGEE(nums);
    long long total = 0;
    for (int i = 0; i < n; i++)
    {
        int prevSmaller = i - previousSmallerAndGreaterElement[i];
        // IMP : marking nse as n if -1 since it helps in calculation of nextSub
        // for e.g. when there is no smaller element on right side of current element,
        // then all elements to the right including current element will have current element as minimum
        if (nextSmallerElement[i] == -1)
        {
            nextSmallerElement[i] = n;
        }
        int nextSmaller = nextSmallerElement[i] - i;

        int prevGreater = i - previousGreaterElement[i];
        // IMP : marking nse as n if -1 since it helps in calculation of nextSub
        // for e.g. when there is no greater element on right side of current element,
        // then all elements to the right including current element will have current element as maximum
        if (nextGreaterElement[i] == -1)
        {
            nextGreaterElement[i] = n;
        }
        int nextGreater = nextGreaterElement[i] - i;

        long long curr = nums[i] * (1LL * prevGreater * nextGreater - prevSmaller * nextSmaller);
        total += curr;
    }
    return total;
}

int main()
{
    vector<int> nums = {1, 2, 3};
    cout << subArrayRanges(nums) << endl; // Output: 4
    nums = {1, 3, 3};
    cout << subArrayRanges(nums) << endl; // Output: 4
    nums = {4, -2, -3, 4, 1};
    cout << subArrayRanges(nums) << endl; // Output: 59
    return 0;
}