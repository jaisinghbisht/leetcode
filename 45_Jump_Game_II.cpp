/*
https://leetcode.com/problems/jump-game-ii/
45. Jump Game II
You are given a 0-indexed array of integers nums of length n. You are initially positioned at index 0.
Each element nums[i] represents the maximum length of a forward jump from index i. In other words, if you are at index i, you can jump to any index (i + j) where:
0 <= j <= nums[i] and
i + j < n
Return the minimum number of jumps to reach index n - 1. The test cases are generated such that you can reach index n - 1.
Example 1:
Input: nums = [2,3,1,1,4]
Output: 2
Explanation: The minimum number of jumps to reach the last index is 2. Jump 1 step from index 0 to 1, then 3 steps to the last index.
Example 2:
Input: nums = [2,3,0,1,4]
Output: 2
Constraints:
1 <= nums.length <= 104
0 <= nums[i] <= 1000
It's guaranteed that you can reach nums[n - 1].
*/

#include <bits/stdc++.h>
using namespace std;

void recursive(int jump, int index, vector<int> &nums, int &maxJumps)
{
    if (index >= nums.size() - 1)
    {
        maxJumps = min(jump, maxJumps);
        return;
    }
    for (int i = 1; i <= nums[index]; i++)
    {
        recursive(jump + 1, index + i, nums, maxJumps);
    }
}
// Time Complexity: O(n^n) in the worst case
// Space Complexity: O(n) for the recursion stack
int jumpRecursive(vector<int> &nums)
{
    int maxJumps = INT_MAX;
    recursive(0, 0, nums, maxJumps);
    return maxJumps;
}

// Time Complexity: O(n), Space Complexity: O(1)
// where n is the size of the array
int jumpGreedy(vector<int> &nums)
{
    int jumps = 0, l = 0, r = 0, n = nums.size();
    while (r < n - 1)
    {
        int farthest = 0;
        for (int i = l; i <= r; i++)
        {
            farthest = max(i + nums[i], farthest);
        }
        l = r + 1;
        r = farthest;
        jumps++;
    }
    return jumps;
}

int main()
{
    vector<int> nums = {2, 3, 1, 1, 4};
    cout << jumpRecursive(nums) << endl; // Output: 2
    cout << jumpGreedy(nums) << endl;    // Output: 2
    nums = {2, 3, 0, 1, 4};
    cout << jumpRecursive(nums) << endl; // Output: 2
    cout << jumpGreedy(nums) << endl;    // Output: 2
    return 0;
}
