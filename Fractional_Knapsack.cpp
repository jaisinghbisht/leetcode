/*
https://www.geeksforgeeks.org/problems/fractional-knapsack-1587115620/1
Fractional Knapsack
Given two arrays, val[] and wt[] , representing the values and weights of items, and an integer capacity representing the maximum weight a knapsack can hold, determine the maximum total value that can be achieved by putting items in the knapsack. You are allowed to break items into fractions if necessary.
Return the maximum value as a double, rounded to 6 decimal places.
Examples :
Input: val[] = [60, 100, 120], wt[] = [10, 20, 30], capacity = 50
Output: 240.000000
Explanation: By taking items of weight 10 and 20 kg and 2/3 fraction of 30 kg. Hence total price will be 60+100+(2/3)(120) = 240
Input: val[] = [500], wt[] = [30], capacity = 10
Output: 166.670000
Explanation: Since the item’s weight exceeds capacity, we take a fraction 10/30 of it, yielding value 166.670000.
Constraints:
1 ≤ val.size = wt.size ≤ 105
1 ≤ capacity ≤ 109
1 ≤ val[i], wt[i] ≤ 104
*/

#include <bits/stdc++.h>
using namespace std;

struct Item
{
    int val;
    int wt;
};
class Solution
{
public:
    static bool cmp(const Item &a, const Item &b)
    {
        double r1 = 1.0 * a.val / a.wt;
        double r2 = 1.0 * b.val / b.wt;
        return r1 > r2;
    }
    double fractionalKnapsack(vector<int> &val, vector<int> &wt, int capacity)
    {
        int n = val.size();
        vector<Item> items(n);
        for (int i = 0; i < n; i++)
        {
            items[i].val = val[i];
            items[i].wt = wt[i];
        }
        sort(items.begin(), items.end(), cmp);
        double totalValue = 0;
        int usedWt = 0, i = 0;
        while (i < n && usedWt + items[i].wt <= capacity)
        {
            totalValue += items[i].val;
            usedWt += items[i].wt;
            i++;
        }
        if (i < n && usedWt < capacity)
        {
            totalValue += 1.0 * items[i].val * (capacity - usedWt) / items[i].wt;
        }
        return totalValue;
    }
};

int main()
{
    Solution sol;
    vector<int> val = {60, 100, 120};
    vector<int> wt = {10, 20, 30};
    int capacity = 50;
    double result = sol.fractionalKnapsack(val, wt, capacity);
    cout << fixed << setprecision(6) << result << endl; // Output: 240.000000
    val = {500};
    wt = {30};
    capacity = 10;
    result = sol.fractionalKnapsack(val, wt, capacity);
    cout << fixed << setprecision(6) << result << endl; // Output: 166.670000
    return 0;
}