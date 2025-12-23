/*
https://leetcode.com/problems/jump-game/description/
55. Jump Game
You are given an integer array nums. You are initially positioned at the array's first index, and each element in the array represents your maximum jump length at that position.
Return true if you can reach the last index, or false otherwise.
Example 1:
Input: nums = [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
Example 2:
Input: nums = [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum jump length is 0, which makes it impossible to reach the last index.
Constraints:
1 <= nums.length <= 104
0 <= nums[i] <= 105
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity: O(n), Space Complexity: O(1)
// where n is the size of the array nums
bool canJump(vector<int> &nums)
{
    int maxReach = 0, n = nums.size();
    for (int i = 0; i < n; i++)
    {
        if (i > maxReach)
            return false;
        maxReach = max(i + nums[i], maxReach);
        if (maxReach >= n - 1)
            return true;
    }
    return true;
}

int main()
{
    vector<int> nums = {2, 3, 1, 1, 4};
    cout << canJump(nums) << endl; // Output: 1 (true)
    nums = {3, 2, 1, 0, 4};
    cout << canJump(nums) << endl; // Output: 0 (false)
    return 0;
}