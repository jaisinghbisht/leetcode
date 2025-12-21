/*
https://leetcode.com/problems/lemonade-change/
860. Lemonade Change
At a lemonade stand, each lemonade costs $5. Customers are standing in a queue to buy from you and order one at a time (in the order specified by bills). Each customer will only buy one lemonade and pay with either a $5, $10, or $20 bill. You must provide the correct change to each customer so that the net transaction is that the customer pays $5.
Note that you do not have any change in hand at first.
Given an integer array bills where bills[i] is the bill the ith customer pays, return true if you can provide every customer with the correct change, or false otherwise.
Example 1:
Input: bills = [5,5,5,10,20]
Output: true
Explanation:
From the first 3 customers, we collect three $5 bills in order.
From the fourth customer, we collect a $10 bill and give back a $5.
From the fifth customer, we give a $10 bill and a $5 bill.
Since all customers got correct change, we output true.
Example 2:
Input: bills = [5,5,10,10,20]
Output: false
Explanation:
From the first two customers in order, we collect two $5 bills.
For the next two customers in order, we collect a $10 bill and give back a $5 bill.
For the last customer, we can not give the change of $15 back because we only have two $10 bills.
Since not every customer received the correct change, the answer is false.
Constraints:
1 <= bills.length <= 105
bills[i] is either 5, 10, or 20.
*/

#include <bits/stdc++.h>
using namespace std;

/*
Greedy rationale:
We only care about how many $5 and $10 bills we have, since $20 bills are never
used to make change.

For a $10 customer, the only possible change is one $5, so we must give it.

For a $20 customer, we need $15 change. There are only two ways:
1) one $10 + one $5
2) three $5s

We greedily prefer option (1) when possible because $5 bills are more valuable
than $10 bills for future transactions:
- $5 bills are required to give change to $10 customers
- $10 bills are only useful for $20 customers

Using a $10 bill first preserves more $5 bills, maximizing flexibility for
future customers. If we cannot do either option, correct change is impossible.

Since each decision is locally optimal and never hurts future possibilities,
the greedy strategy works.
*/

// Time: O(n), Space: O(1)
bool lemonadeChange(vector<int> &bills)
{
    int five = 0, ten = 0;
    for (int &bill : bills)
    {
        if (bill == 5)
            five++;
        else if (bill == 10)
        {
            if (five == 0)
                return false;
            five--;
            ten++;
        }
        else
        {
            if (ten > 0 && five > 0)
            {
                ten--;
                five--;
            }
            else if (five >= 3)
                five -= 3;
            else
                return false;
        }
    }
    return true;
}

int main()
{
    vector<int> bills1 = {5, 5, 5, 10, 20};
    cout << (lemonadeChange(bills1) ? "true" : "false") << endl; // Output: true
    vector<int> bills2 = {5, 5, 10, 10, 20};
    cout << (lemonadeChange(bills2) ? "true" : "false") << endl; // Output: false
    return 0;
}