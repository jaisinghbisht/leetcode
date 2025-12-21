/*
https://www.geeksforgeeks.org/problems/-minimum-number-of-coins4426/1
Minimum number of Coins
Given an infinite supply of each denomination of Indian currency { 1, 2, 5, 10 } and a target value n. Find the minimum number of coins and/or notes needed to make the change for Rs n.
Examples:
Input: n = 39
Output: 6
Explaination: 39 can be formed using 3 coins of 10 rupees, 1 coin of 5 rupees and 2 coins of 2 rupees so minimum coins required are 6.
Input: n = 121
Output: 13
Explaination: 121 can be formed using 12 coins of 10 rupees and 1 coin of 1 rupees.
Constraints:
1 ≤ n ≤ 106
*/

#include <bits/stdc++.h>
using namespace std;

/*
Greedy rationale:
The given coin system {1, 2, 5, 10} is a canonical coin system.
This means that taking the largest possible denomination at each step
always leads to an optimal (minimum coin) solution.

Why greedy works:
- Every larger denomination is an exact multiple or can be optimally
  composed using smaller denominations.
- Replacing a larger coin with smaller ones never reduces the total
  number of coins (e.g., one 10 is always better than five 2s or ten 1s).
- Therefore, using as many large coins as possible minimizes the total
  number of coins needed.

At each step, we take the maximum number of the largest denomination
that does not exceed the remaining amount, reduce the amount, and repeat.
This locally optimal choice is also globally optimal for this coin system.
*/

// Time: O(n), Space: O(1)
int findMin(int n)
{
    int rupees[4] = {10, 5, 2, 1};
    int noOfCoins = 0, i = 0;
    while (i < 4 && n != 0)
    {
        noOfCoins += n / rupees[i];
        n %= rupees[i];
        i++;
    }
    return noOfCoins;
}

int main()
{
    int n = 39;
    cout << findMin(n) << endl; // Output: 6
    n = 121;
    cout << findMin(n) << endl; // Output: 13
    return 0;
}