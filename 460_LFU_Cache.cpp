/*
https://leetcode.com/problems/lfu-cache/
460. LFU Cache
Design and implement a data structure for a Least Frequently Used (LFU) cache.
Implement the LFUCache class:
LFUCache(int capacity) Initializes the object with the capacity of the data structure.
int get(int key) Gets the value of the key if the key exists in the cache. Otherwise, returns -1.
void put(int key, int value) Update the value of the key if present, or inserts the key if not already present. When the cache reaches its capacity, it should invalidate and remove the least frequently used key before inserting a new item. For this problem, when there is a tie (i.e., two or more keys with the same frequency), the least recently used key would be invalidated.
To determine the least frequently used key, a use counter is maintained for each key in the cache. The key with the smallest use counter is the least frequently used key.
When a key is first inserted into the cache, its use counter is set to 1 (due to the put operation). The use counter for a key in the cache is incremented either a get or put operation is called on it.
The functions get and put must each run in O(1) average time complexity.
Example 1:
Input
["LFUCache", "put", "put", "get", "put", "get", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [3], [4, 4], [1], [3], [4]]
Output
[null, null, null, 1, null, -1, 3, null, -1, 3, 4]
Explanation
// cnt(x) = the use counter for key x
// cache=[] will show the last used order for tiebreakers (leftmost element is  most recent)
LFUCache lfu = new LFUCache(2);
lfu.put(1, 1);   // cache=[1,_], cnt(1)=1
lfu.put(2, 2);   // cache=[2,1], cnt(2)=1, cnt(1)=1
lfu.get(1);      // return 1
                 // cache=[1,2], cnt(2)=1, cnt(1)=2
lfu.put(3, 3);   // 2 is the LFU key because cnt(2)=1 is the smallest, invalidate 2.
                 // cache=[3,1], cnt(3)=1, cnt(1)=2
lfu.get(2);      // return -1 (not found)
lfu.get(3);      // return 3
                 // cache=[3,1], cnt(3)=2, cnt(1)=2
lfu.put(4, 4);   // Both 1 and 3 have the same cnt, but 1 is LRU, invalidate 1.
                 // cache=[4,3], cnt(4)=1, cnt(3)=2
lfu.get(1);      // return -1 (not found)
lfu.get(3);      // return 3
                 // cache=[3,4], cnt(4)=1, cnt(3)=3
lfu.get(4);      // return 4
                 // cache=[4,3], cnt(4)=2, cnt(3)=3
Constraints:
1 <= capacity <= 104
0 <= key <= 105
0 <= value <= 109
At most 2 * 105 calls will be made to get and put.
*/

#include <bits/stdc++.h>
using namespace std;

// Double Linked List Node
class Node
{
public:
    Node *next;
    Node *prev;
    int key;
    int val;
    int freq;

    Node()
    {
        next = nullptr;
        prev = nullptr;
        key = -1;
        val = -1;
        freq = 1;
    }

    Node(int key, int val)
    {
        next = nullptr;
        prev = nullptr;
        this->key = key;
        this->val = val;
        freq = 1;
    }
};

// List of nodes for each frequency
class DLL
{
private:
    Node *head;
    Node *tail;

public:
    int size;

    DLL()
    {
        head = new Node();
        tail = new Node();
        head->next = tail;
        tail->prev = head;
        size = 0;
    }

    // Add node to the right (most recently used)
    void addNode(Node *node)
    {
        Node *prev = tail->prev;
        prev->next = node;
        node->prev = prev;
        node->next = tail;
        tail->prev = node;
        size++;
    }

    // Remove given node
    void removeNode(Node *node)
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        size--;
    }

    // Remove least recently used node (head's next)
    Node *removeLRU()
    {
        if (size == 0)
            return nullptr;
        Node *node = head->next;
        removeNode(node);
        return node;
    }
};

class LFUCache
{
private:
    unordered_map<int, Node *> keyNode; // key -> node
    unordered_map<int, DLL *> freqList; // list per freq -> {head, tail}
    int capacity;
    int minFreq;

public:
    LFUCache(int capacity)
    {
        keyNode.clear();
        freqList.clear();
        this->capacity = capacity;
        this->minFreq = 0;
    }

    // Time Complexity: O(1), Space Complexity: O(1)
    int get(int key)
    {
        if (keyNode.find(key) == keyNode.end())
            return -1;
        Node *node = keyNode[key];
        updateFreq(node);
        return node->val;
    }

    // Time Complexity: O(1), Space Complexity: O(1)
    void put(int key, int value)
    {
        if (capacity == 0)
            return;
        // Key already exists
        if (keyNode.find(key) != keyNode.end())
        {
            Node *node = keyNode[key];
            node->val = value;
            updateFreq(node);
            return;
        }
        // Cache is full, evict least frequently used node
        if (keyNode.size() == capacity)
        {
            Node *evict = freqList[minFreq]->removeLRU();
            keyNode.erase(evict->key);
            delete evict;
        }
        // Insert new node
        Node *node = new Node(key, value);
        minFreq = 1;
        if (freqList.find(minFreq) == freqList.end())
        {
            freqList[1] = new DLL();
        }
        freqList[1]->addNode(node);
        keyNode[key] = node;
    }

    // Update frequency of a node
    void updateFreq(Node *node)
    {
        int f = node->freq;
        // Remove node from current frequency list
        if (freqList.find(f) != freqList.end())
            freqList[f]->removeNode(node);
        // If current list is empty and f is minFreq, increment minFreq
        if (f == minFreq && freqList[f]->size == 0)
            minFreq++;
        // Add node to new frequency list
        (node->freq)++;
        if (freqList.find(node->freq) == freqList.end())
            freqList[node->freq] = new DLL();
        freqList[node->freq]->addNode(node);
    }
};

int main()
{
    LFUCache lfu(2);
    lfu.put(1, 1);              // cache=[1,_], cnt(1)=1
    lfu.put(2, 2);              // cache=[2,1], cnt
    cout << lfu.get(1) << endl; // return 1
                                // cache=[1,2], cnt(2)=1, cnt(1)=2
    lfu.put(3, 3);              // 2 is the LFU key because cnt(2)=1 is the smallest, invalidate 2.
                                // cache=[3,1], cnt(3)=1, cnt(1)=2
    cout << lfu.get(2) << endl; // return -1 (not found)
    cout << lfu.get(3) << endl; // return 3
                                // cache=[3,1], cnt(3)=2, cnt(1)=2
    lfu.put(4, 4);              // Both 1 and 3 have the same cnt, but 1 is LRU, invalidate 1.
                                // cache=[4,3], cnt(4)=1, cnt(3)=2
    cout << lfu.get(1) << endl; // return -1 (not found)
    cout << lfu.get(3) << endl; // return 3
    cout << lfu.get(4) << endl; // return 4
                                // cache=[4,3], cnt(4)=2, cnt(3)=3
    return 0;
}