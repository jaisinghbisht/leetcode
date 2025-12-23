/*
https://www.geeksforgeeks.org/problems/minimum-platforms-1587115620/1
Minimum Platforms
Given arrival arr[] and departure dep[] times of trains on the same day, find the minimum number of platforms needed so that no train waits. A platform cannot serve two trains at the same time; if a train arrives before another departs, an extra platform is needed.
Note: Time intervals are in the 24-hour format (HHMM) , where the first two characters represent hour (between 00 to 23 ) and the last two characters represent minutes (this will be <= 59 and >= 0). Leading zeros for hours less than 10 are optional (e.g., 0900 is the same as 900).
Examples:
Input: arr[] = [900, 940, 950, 1100, 1500, 1800], dep[] = [910, 1200, 1120, 1130, 1900, 2000]
Output: 3
Explanation: There are three trains during the time 9:40 to 12:00. So we need a minimum of 3 platforms.
Input: arr[] = [900, 1235, 1100], dep[] = [1000, 1240, 1200]
Output: 1
Explanation: All train times are mutually exclusive. So we need only one platform.
Input: arr[] = [1000, 935, 1100], dep[] = [1200, 1240, 1130]
Output: 3
Explanation: All 3 trains have to be there from 11:00 to 11:30
Constraints:
1 ≤ number of trains ≤ 50000
0000 ≤ arr[i] ≤ dep[i] ≤ 2359
*/

#include <bits/stdc++.h>
using namespace std;

// Time Complexity: O(n log n), Space Complexity: O(1)
// where n is the number of trains
int minPlatform(vector<int> &arr, vector<int> &dep)
{
    // consider ourselves as an observer at the platform, if more than one train arrives before any train departs, we need more platforms.
    // thus, the maximum number of trains at the platform at any time will be the answer.
    int n = arr.size();
    sort(arr.begin(), arr.end());
    sort(dep.begin(), dep.end());
    int count = 0, maxCount = 0;
    int a = 0, d = 0;
    while (a < n)
    {
        if (arr[a] <= dep[d])
        {
            count++;
            a++;
        }
        else
        {
            count--;
            d++;
        }
        maxCount = max(maxCount, count);
    }
    return maxCount;
}

int main()
{
    vector<int> arr = {900, 940, 950, 1100, 1500, 1800};
    vector<int> dep = {910, 1200, 1120, 1130, 1900, 2000};
    cout << minPlatform(arr, dep) << endl; // Output: 3
    arr = {900, 1235, 1100};
    dep = {1000, 1240, 1200};
    cout << minPlatform(arr, dep) << endl; // Output: 1
    arr = {1000, 935, 1100};
    dep = {1200, 1240, 1130};
    cout << minPlatform(arr, dep) << endl; // Output: 3
    return 0;
}