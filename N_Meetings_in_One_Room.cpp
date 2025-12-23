/*
https://www.geeksforgeeks.org/problems/n-meetings-in-one-room-1587115620/1
N meetings in one room
Difficulty: EasyAccuracy: 45.3%Submissions: 375K+Points: 2Average Time: 20m
You are given timings of n meetings in the form of (start[i], end[i]) where start[i] is the start time of meeting i and end[i] is the finish time of meeting i. Return the maximum number of meetings that can be accommodated in a single meeting room, when only one meeting can be held in the meeting room at a particular time.
Note: The start time of one chosen meeting can't be equal to the end time of the other chosen meeting.
Examples :
Input: start[] = [1, 3, 0, 5, 8, 5], end[] =  [2, 4, 6, 7, 9, 9]
Output: 4
Explanation: Maximum four meetings can be held with given start and end timings. The meetings are - (1, 2), (3, 4), (5,7) and (8,9)
Input: start[] = [10, 12, 20], end[] = [20, 25, 30]
Output: 1
Explanation: Only one meetings can be held with given start and end timings.
Input: start[] = [1, 2], end[] = [100, 99]
Output: 1
Constraints:
1 ≤ n ≤ 105
0 ≤ start[i] < end[i] ≤ 106
*/

#include <bits/stdc++.h>
using namespace std;

static bool comp(const pair<int, int> &a, const pair<int, int> &b)
{
    return a.second < b.second;
}
// Time Complexity: O(n log n), Space Complexity: O(n)
// where n is the number of meetings
int maxMeetings(vector<int> &start, vector<int> &end)
{
    // {index, {startTime, endTime}}
    int n = start.size();
    vector<pair<int, int>> meetings;
    for (int i = 0; i < n; i++)
    {
        meetings.push_back({start[i], end[i]});
    }
    sort(meetings.begin(), meetings.end(), comp);
    int count = 1, nextAvailableTime = meetings[0].second;
    for (int i = 1; i < meetings.size(); i++)
    {
        if (nextAvailableTime < meetings[i].first)
        {
            nextAvailableTime = meetings[i].second;
            count++;
        }
    }
    return count;
}

int main()
{
    vector<int> start = {1, 3, 0, 5, 8, 5};
    vector<int> end = {2, 4, 6, 7, 9, 9};
    cout << maxMeetings(start, end) << endl; // Output: 4
    start = {10, 12, 20};
    end = {20, 25, 30};
    cout << maxMeetings(start, end) << endl; // Output: 1
    start = {1, 2};
    end = {100, 99};
    cout << maxMeetings(start, end) << endl; // Output: 1
    return 0;
}