#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <math.h>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <algorithm>
#include <random>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class ParkingSystem {
public:
    int _big, _medium, _small;
    ParkingSystem(int big, int medium, int small) {
        _big = big;
        _medium = medium;
        _small = small;
    }
    
    bool addCar(int carType) {
        switch (carType)
        {
        case 1:
            if (_big > 0) _big--;
            else return false;
            break;
        case 2:
            if (_medium > 0) _medium--;
            else return false;
            break;
        case 3:
            if (_small > 0) _small--;
            else return false;
            break;
        }
        return true;
    }
};

class RandomizedCollection {
private:
    unordered_map<int, unordered_set<int>> index;
    vector<int> collection;
public:
    /** Initialize your data structure here. */
    RandomizedCollection() {

    }
    
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        collection.emplace_back(val);
        index[val].insert(collection.size()-1);
        return index[val].size()==1;
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        if (index.find(val) == index.end()) {
            return false;
        }
        int idx = *(index[val].begin());
        collection[idx] = collection.back();
        index[val].erase(idx);
        index[collection[idx]].erase(collection.size() - 1);
        if (idx < collection.size() - 1) {
            index[collection[idx]].insert(idx);
        }
        if (index[val].size() == 0) {
            index.erase(val);
        }
        collection.pop_back();
        return true;
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
        return collection[rand() % collection.size()];
    }
};

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
public:
    void popNode(TreeNode* node, vector <int> &nodeList)
    {
        if (node == nullptr) return;
        popNode(node -> left, nodeList);
        popNode(node -> right, nodeList);
        nodeList.push_back(node -> val);
    }

    vector<int> postorderTraversal(TreeNode* root) {
        vector <int> list {};
        popNode(root, list);
        return list;
    }

    int climbStairs(int n) {
        if (n == 0) return 1;
        if (n == 1) return 1;
        return climbStairs(n-1) + climbStairs(n-2);
    } // Space complexity O(n)

    int climbStairs2(int n) {
        int l = 0, c = 0, r = 1;
        for (int i = 0; i < n; i++)
        {
            l = c;
            c = r;
            r = l + c;
        }
        return r;
    } // Space complexity O(1)

    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if (t1 == nullptr) return t2;
        if (t2 == nullptr) return t1;
        t1->val = t1->val + t2->val;
        t1->left = mergeTrees(t1 -> left, t2 -> left);
        t1->right = mergeTrees(t1 -> right, t2 -> right);
        return t1;
    }

    // LC question 11

    int maxArea(vector <int> heights)
    {
        int ret {INT16_MIN}, lp{0}, rp;
        rp = heights.size()-1;
        while(lp <= rp)
        {
            ret = max(ret, min(heights[lp], heights[rp]) * (rp - lp));
            if (heights[lp] > heights[rp])
                rp -= 1;
            else
                lp += 1;
        }
        return ret;
    }
    // END - LC question 11

    int numJewelsInStones(string J, string S) {
        int count{0};
        unordered_set<char> gemSet;
        for (char gem : J) gemSet.insert(gem);
        for (char stone : S)
        {
            if (gemSet.count(stone)) count++;
        }
        return count;
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int> newVec{};
        int ptr1{0}, ptr2{0};
        while (ptr1 < nums1.size() || ptr2 < nums2.size())
        {
            if (ptr1 >= nums1.size())
            {
                newVec.push_back(nums2[ptr2]);
                ptr2 ++;
            }
            else if (ptr2 >= nums2.size())
            {
                newVec.push_back(nums1[ptr1]);
                ptr1 ++;
            }
            else if (nums1[ptr1] < nums2[ptr2])
            {
                newVec.push_back(nums1[ptr1]);
                ptr1 ++;
            }
            else
            {
                newVec.push_back(nums2[ptr2]);
                ptr2 ++;
            }
        }
        int size = newVec.size();
        if (size % 2 == 1) return (double) newVec[size / 2];
        return (double)newVec[size / 2] / 2 + newVec[size / 2 - 1] / 2;
    }

    vector<int> twoSum1(vector<int>& nums, int target) {
        unordered_map<int, int> hashtable;
        for (int i = 0; i < nums.size(); ++i) {
            auto it = hashtable.find(target - nums[i]);
            if (it != hashtable.end()) {
                return {it->second, i};
            }
            hashtable[nums[i]] = i;
        }
        return {};
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int a{0}, b{0}, fac{1};
        while (l1 != nullptr)
        {
            a += l1->val * fac;
            fac *= 10;
            l1 = l1->next;
        }
        fac = 1;
        while (l2 != nullptr)
        {
            b += l2->val * fac;
            fac *= 10;
            l2 = l2->next;
        }
        int summ = a + b;
        ListNode * rootNode;
        vector <ListNode> nodeList;
        while (summ != 0)
        {
            ListNode tempNode;
            tempNode.val = summ % 10;
            nodeList.push_back(tempNode);
        }
        return rootNode;
    }
    
    bool canPartition(vector<int>& nums) {
        int num_size = nums.size();
        if (num_size < 2) return false;
        int sum{0}, target{0}, maxNum{INT32_MIN};
        for (int n : nums) 
        {
            sum += n;
            maxNum = max(n, maxNum);
        }
        if (sum & 1) return false;
        target = sum / 2;
        if (maxNum > target) return false;
        vector <vector <bool>> dp(num_size, vector<bool>(target + 1, 0));
        for (int i = 0; i < num_size; i++) dp[i][0] = true;
        dp[0][nums[0]] = true;
        for (int i = 1; i < num_size; i++) 
        {
            int num = nums[i];
            for (int j = 1; j <= target; j++) 
            {
                if (j >= num)
                    dp[i][j] = dp[i - 1][j] | dp[i - 1][j - num];
                else
                    dp[i][j] = dp[i - 1][j];
            }
        }
        return dp[num_size - 1][target];
    }

    void dfs(TreeNode* root, int& pre, int& ans) {
        if (root == nullptr) return;
        dfs(root->left, pre, ans);
        if (pre == -1) {
            pre = root->val;
        } else {
            ans = min(ans, root->val - pre);
            pre = root->val;
        }
        dfs(root->right, pre, ans);
    }

    int getMinimumDifference(TreeNode* root) {
        int ans = INT32_MAX, pre{-1};
        dfs(root, pre, ans);
        return ans;
    }

    bool isValid(string s) {
        if (!s.size() % 2) return false;
        unordered_map <char, char> pair {
            {')', '('},
            {']', '['},
            {'}', '{'}
        };
        stack <char> stk;
        for (char c : s)
        {
            if (pair.count(c))
            {
                if (stk.empty() || stk.top() != pair[c]) return false;
                stk.pop();
            }
            else 
            {
                stk.push(c);
            }
        }
        return stk.empty();
    }

    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return head;
        ListNode* newHead = head->next;
        head->next = swapPairs(newHead->next);
        newHead->next = head;
        return newHead;
    }

    int rob(vector<int>& nums) {
        if (nums.size() == 0) return 0;
        vector<int> ret(nums.size(), 0);
        ret[0] = nums[0];
        if (nums.size() == 1) return ret[0];
        ret[1] = max(nums[0], nums[1]);
        for (int i = 2; i < nums.size(); i++)
            ret[i] = max(ret[i-2] + nums[i], ret[i-1]);
        return ret[nums.size()-1];
    }

    vector<string> commonChars(vector<string>& A) {
        unordered_map<char, int> table, comparTable;
        string cover{};
        for (char c : A[0])
        {
            if (!table.count(c)) 
            {
                pair<char, int> tempPair{c, 1};
                table.insert(tempPair);
            }
            else
                table[c] += 1;
        }
        for (int i=1; i<A.size(); i++)
        {
            comparTable = table;
            for (auto charCount : table) table[charCount.first] = 0;
            for (char c : A[i])
                if (table.count(c)) table[c]++;
            vector<char> keys{};
            for (auto c : table) keys.push_back(c.first);
            for (int i = 0; i < keys.size(); i++)
            {
                if (table[keys[i]] == 0)
                    table.erase(keys[i]);
                else
                    table[keys[i]] = min(table[keys[i]], comparTable[keys[i]]);
            }
        }
        vector <string> ret;
        for (auto charCount : table)
        {
            int cnt = charCount.second;
            for (int i=0; i < cnt; i++)
            {
                string temp{charCount.first};
                ret.push_back(temp);
            }
        }
        return ret;
    }

    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr) {
            return l2;
        } else if (l2 == nullptr) {
            return l1;
        } else if (l1->val < l2->val) {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        } else {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }

    Node* connect(Node* root) {
        if (root == nullptr) return nullptr;
        queue <Node*> nodeQueue;
        nodeQueue.push(root);
        while(!nodeQueue.empty())
        {
            int size = nodeQueue.size();
            for (int i=0; i<size; i++)
            {
                Node* node = nodeQueue.front();
                nodeQueue.pop();
                if (i < size-1)
                {
                    node->next = nodeQueue.front();
                }
                if (node->left != nullptr)
                {
                    nodeQueue.push(node->left);
                }
                if (node->right != nullptr)
                {
                    nodeQueue.push(node->right);
                }
            }
        }
        return root;
    }

    vector<int> sortedSquares(vector<int>& A) {
        int lptr {0};
        int rptr = A.size()-1;
        vector <int> ret(A.size(), 0);
        int i = A.size()-1;
        while (lptr <= rptr)
        {
            if (A[lptr] * A[lptr] > A[rptr] * A[rptr])
            {
                ret[i] = A[lptr] * A[lptr];
                lptr ++;
            } 
            else
            {
                ret[i] = A[rptr] * A[rptr];
                rptr --;
            }
            i--;
        }
        return ret;
    }

    int removeDuplicates(vector<int>& nums) {
        if (!nums.size()) return 0;
        int j{0};
        for (int i=0; i<nums.size(); i++)
        {
            if (nums[i] == nums[j]) continue;
            j++;
            nums[j] = nums[i];
        }
        return j+1;
    }
    int removeElement(vector<int>& nums, int val) {
        if (!nums.size()) return 0;
        int j{0};
        for (int i=0; i<nums.size(); i++)
        {
            if (nums[i] == val) continue;
            nums[j++] = nums[i];
        }
        return j++;
    }

    int maxProfit1(vector<int>& prices) {
        int size = prices.size();
        if (size == 0) return 0;
        int prof {0}, lowValue{prices[0]};
        for (int i = 0; i < size; i++)
        {
            int diff = prices[i] - lowValue;
            prof = diff > prof ? diff : prof;
            lowValue = diff < 0 ? prices[i] : lowValue;
        }
        return prof;
    }

    int maxProfit2(vector<int>& prices) {
        int size = prices.size();
        if (size == 0) return 0;
        int prof{0};
        for (int i = 1; i < size; i++)
            if (prices[i] > prices[i-1])
                prof += prices[i] - prices[i-1];
        return prof;
    }

    int maxProfit(vector<int>& prices) {
        int size = prices.size();
        if (size < 2) return 0;
        vector <vector <vector <int>>> dp(
                    size, vector<vector<int>>(
                    2, vector<int>(3, 0))); // #Days; 1-Holding, 0-Not Holding; #Trading.
        for (int i=0; i<3; i++) dp[0][1][i] = -prices[0];
        for (int i=1; i<size; i++)
        {
            dp[i][0][0] = 0;
            dp[i][0][1] = max((dp[i-1][0][1]), (dp[i-1][1][0]+prices[i]));
            dp[i][0][2] = max(dp[i-1][0][2], dp[i-1][1][1]+prices[i]);
            dp[i][1][0] = max(dp[i-1][1][0], dp[i-1][0][0]-prices[i]);
            dp[i][1][1] = max(dp[i-1][1][1], dp[i-1][0][1]-prices[i]);
            dp[i][1][2] = 0;
        }
        return max(dp[size-1][0][1], dp[size-1][0][2]);
    }

    bool backspaceCompare(string S, string T) {
        stack<char> a{}, b{};
        for (char c: S)
        {
            if (c!='#') a.push(c);
            else
            {
                if (!a.empty()) a.pop();
            }
        }
        for (char c: T)
        {
            if (c!='#') b.push(c);
            else
            {
                if (!b.empty()) b.pop();
            }
        }
        if (a.size() != b.size()) return false;
        int size = a.size();
        for (int i=0; i<size; i++)
        {
            if (a.top() != b.top()) return false;
            a.pop();
            b.pop();
        }
        return true;
    }

    int missingNumber(vector<int>& nums) {
        int size = nums.size();
        int lptr{0}, rptr{size-1};
        int mid{0};
        while (lptr <= rptr)
        {
            mid = (lptr + rptr)/2;
            if (nums[mid] == mid) lptr = mid+1;
            else rptr = mid-1;
        }
        return lptr;
    }

    vector<int> twoSum(vector<int>& numbers, int target) {
        int size = numbers.size();
        int lptr, rptr;
        for (lptr=0;lptr<size-1;lptr++)
        {
            int left{lptr+1}, right{size-1};
            while (left <= right)
            {
                rptr = (left + right) / 2;
                if (numbers[rptr] + numbers[lptr] == target) return {lptr+1, rptr+1};
                if (numbers[rptr] + numbers[lptr] > target) right = rptr - 1;
                if (numbers[rptr] + numbers[lptr] < target) left = rptr + 1;
            }
        }
        return {-1, 1};
    }

    void reorderList(ListNode* head) {
        if (head == nullptr) {
            return;
        }
        vector<ListNode*> reList;
        ListNode* temp = head;
        while (temp!=nullptr)
        {
            reList.emplace_back(temp);
            temp = temp->next;
        }
        int i = 0;
        int j = reList.size()-1;
        while (i < j)
        {
            reList[i]->next = reList[j];
            i++;
            if (i==j) break;
            reList[j]->next = reList[i];
            j--;
        }
        reList[i]->next =nullptr;
    }

    bool isLongPressedName(string name, string typed) {
        int i{0}, j{0};
        while (j < typed.size())
        {
            if (name[i] == typed[j])
            {
                i++;
                j++;
                continue;
            }
            if (typed[j] == name[i-1])
            {
                j++;
                continue;
            }
            return false;
        }
        return i == name.size() ? true : false;
    }

    string convertToTitle(int n) {
        string ret{};
        while (n>0)
        {
            n--;
            ret.push_back('A'+n%26);
            n /= 26;
        }
        reverse(ret.begin(), ret.end());
        return ret;
    }

    int titleToNumber(string s) {
        reverse(s.begin(), s.end());
        int ret{0};
        while(!s.empty())
        {
            ret *= 26;
            ret += (s.back() - 'A' + 1);
            s.pop_back();
        }
        return ret;
    }

    bool hasCycle1(ListNode *head) {
        unordered_set<ListNode*> set;
        ListNode *temp=head;
        while(temp!=nullptr)
            if (set.count(temp)) return true;
            set.insert(temp);
            temp = temp->next;
        return false;
    }

    bool hasCycle(ListNode *head) {
        if (head==nullptr || head->next==nullptr) return false;
        ListNode* slow = head;
        ListNode* fast = head->next;
        while(fast!=nullptr && fast->next!=nullptr)
        {
            if (slow == fast) return true;
            slow = slow->next;
            fast = fast->next->next;
        }
        return false;
    }

    int maximumProduct(vector<int>& nums) {
        int max1{INT32_MIN}, max2{INT32_MIN}, max3{INT32_MIN},
        min1{INT32_MAX}, min2{INT32_MAX};
        for (int i : nums)
        {
            if (i <= min1)
            {
                min2 = min1;
                min1 = i;
            }
            else if (i <= min2)
                min2 = i;
            if (i >= max1)
            {
                max3 = max2;
                max2 = max1;
                max1 = i;
            }
            else if (i >= max2)
            {
                max3 = max2;
                max2 = i;
            }
            else if (i >= max3)
                max3 = i;
        }
        return max(min1*min2*max1, max1*max2*max3);
    }

    ListNode* frontPointer;
    bool recursivelyCheck(ListNode* currentNode) {
        if (currentNode != nullptr) {
            if (!recursivelyCheck(currentNode->next)) {
                return false;
            }
            if (currentNode->val != frontPointer->val) {
                return false;
            }
            frontPointer = frontPointer->next;
        }
        return true;
    }

    bool isPalindrome(ListNode* head) {
        frontPointer = head;
        return recursivelyCheck(head);
    }

    // Problem solving # 14
    string longestCommonPrefix(vector <string> strs)
    {
        if (strs.size() == 0) return "";
        string prefix = strs[0];
        int longestPrefixIdx{INT32_MAX};
        for (int i=1; i<strs.size(); i++)
        {
            if (strs[i].length() == 0) return "";
            int ptr{0};
            for (;ptr<prefix.length() && ptr<strs[i].length();ptr++)
            {
                if (prefix[ptr] != strs[i][ptr]) break;
            }
            longestPrefixIdx = min(longestPrefixIdx, ptr);
        }
        string ret{};
        for (int i=0; i<longestPrefixIdx && i<prefix.length(); i++) ret.push_back(prefix[i]);
        return ret;
    }

    // Problem solving # 35
    int searchInsert(vector<int>& nums, int target) {
        int n = nums.size();
        int left = 0, right = n - 1, ans = n;
        while (left <= right) {
            int mid = ((right - left) >> 1) + left;
            if (target <= nums[mid]) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        return ans;
    }
    
    // Problem solving # 48
    /*
        instance: matrix 4 by 4
        (0, 0) -> (0, 3)    (1, 0) -> (0, 2)    (2, 0) -> (0, 1)    (3, 0) -> (0, 0)
        (0, 1) -> (1, 3)    (1, 1) -> (1, 2)    (2, 1) -> (1, 1)    (3, 1) -> (1, 0)
        (0, 2) -> (2, 3)    (1, 2) -> (2, 2)    (2, 2) -> (2, 1)    (3, 2) -> (2, 0)
        (0, 3) -> (3, 3)    (1, 3) -> (3, 2)    (2, 3) -> (3, 1)    (3, 3) -> (3, 0)

        conclusion : for n x n matrix,
            (i, j) -> (j, n-1-i)
    */
    void rotate(vector <vector<int>>& mat)
    {
        int size = mat.size();
        for (int i=0; i<size/2; i++)
            for (int j=i; j<size-i-1; j++)
            {
                int temp = mat[j][size-1-i];
                mat[j][size-1-i] = mat[i][j];
                mat[i][j] = mat[size-1-j][i];
                mat[size-1-j][i] = mat[size-1-i][size-1-j];
                mat[size-1-i][size-1-j] = temp;
            }
    }

    // Problem Solving # 1024
    int videoStitching(vector<vector<int>>& clips, int T) {
        int size = clips.size();
        vector <int> ret(T+1, -1);
        ret[0] = 0;
        for (int i=1; i<=T; i++)
            for (int j=0; j<size; j++)
                if (clips[j][0]<i && clips[j][1]>=i)
                    ret[i] = ret[i] == -1 ? ret[clips[j][0]] + 1 : min(ret[i], ret[clips[j][0]] + 1);
        return ret[T] ? ret[T] : -1;
    }

    // Problem Solving # 845
    int longestMountain(vector<int>& A) {
        int size = A.size();
        int lptr{0}, rptr{0};
        int ret{0};
        while (lptr < size - 2)
        {
            rptr = lptr + 1;
            if (A[lptr+1] > A[lptr])
            {
                while (rptr < size - 1 && A[rptr+1] > A[rptr])
                {
                    rptr++;
                }
                if (rptr < size - 1 && A[rptr+1] < A[rptr])
                {
                    while (rptr < size - 1 && A[rptr+1] < A[rptr])
                    {
                        rptr++;
                    }
                    ret = max(ret, rptr-lptr+1);
                }
            }
            lptr = rptr;
        }
        return ret;
    }

    // Problem # 1389
    vector<int> createTargetArray(vector<int>& nums, vector<int>& index) {
        vector<int> target;
        for(int i=0;i<index.size();i++)
        {
            target.insert(target.begin()+index[i],nums[i]);
        }
        return target;
    }

    // Problem # 1365
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
        vector <int> cnt(101, 0);
        for (int i : nums) cnt [i] ++;
        vector <int> ret{};
        for (int i : nums)
        {
            int count{0};
            for (int j=0; j<i; j++) count += cnt[j];
            ret.push_back(count);
        }
        return ret;
    }
    
    // Problem # 1313
    vector<int> decompressRLElist(vector<int>& nums) {
        vector <int> ret;
        for (int i=0, j=1; j<nums.size(); i+=2, j+=2)
        {
            for (int cnt=0; cnt<nums[i]; cnt++)
            {
                ret.push_back(nums[j]);
            }
        }
        return ret;
    }

    // Problem # 1290
    int getDecimalValue(ListNode* head) {
        int ret{0};
        ListNode* temp = head;
        while(temp != nullptr)
        {
            ret = ret*2 + temp->val;
            temp = temp->next;
        }
        return ret;
    }

    // Problem # 1588
    int sumOddLengthSubarrays(vector<int>& arr) {
        int sum{0};
        for (int n=1; n <= arr.size(); n+=2)
        {
            for (int i=0; i<arr.size(); i++)
            {
                int fac = min(i+1, n);
                fac = min((int)arr.size()-i, fac);
                fac = min((int)arr.size()+1-n, fac);
                sum += fac * arr[i];
            }
        }
        return sum;
    }

    // Problem # 144
    void preOrder(TreeNode* node, vector <int>& list)
    {
        if (node == nullptr) return;
        preOrder(node->left, list);
        list.push_back(node->val);
        preOrder(node->right, list);
    }
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> ret{};
        if (root == nullptr) return ret;
        stack<TreeNode*> speicher;
        TreeNode* node = root;
        while (!speicher.empty() || node != nullptr)
        {
            while (node != nullptr)
            {
                ret.emplace_back(node->val);
                speicher.emplace(node);
                node = node->left;
            }
            node = speicher.top();
            speicher.pop();
            node = node->right;
        }
        return ret;
    }

    int numberOfSteps (int num) {
        int ret{0};
        while (num > 0)
        {
            if (num % 2 == 0) num /=2;
            else num -= 1;
            ret ++;
        }
        return ret;
    }

    // Problem # 1480
    vector<int> runningSum(vector<int>& nums) {
        for (int i=1; i<nums.size(); i++)
            nums[i] += nums[i-1];
        return nums;
    }

    bool uniqueOccurrences(vector<int>& arr) {
        unordered_set<int> set;
        sort(arr.begin(), arr.end());
        int count{0}, rem{arr[0]};
        for (int i=0; i<arr.size(); i++)
        {
            if (arr[i] == rem) count++;
            else if (set.count(count))
                return false;
            else
            {
                set.insert(count);
                count = 1;
                rem = arr[i];
            }   
        }
        return !set.count(count);
    }

    // Problem # 94
    void inOrder(TreeNode* node, vector<int>& list)
    {
        if (node == nullptr) return;
        inOrder(node->left, list);
        inOrder(node->right, list);
        list.emplace_back(node->val);
    }
    vector<int> inorderTraversal(TreeNode* root) {
        vector <int> ret;
        stack <TreeNode*> stk;
        TreeNode* tmp = root;
        while (tmp != nullptr || !stk.empty())
        {
            if (tmp != nullptr)
            {
                stk.emplace(tmp);
                tmp = tmp->left;
            }
            else
            {
                tmp = stk.top();
                stk.pop();
                ret.emplace_back(tmp->val);
                tmp = tmp->right;
            }
        }
        return ret;
    }

    string reverseLeftWords(string s, int n) {
        string ret;
        for (int i=n; i<s.length(); i++) ret.push_back(s[i]);
        for (int i=0; i<n; i++) ret.push_back(s[i]);
        return ret;
    }

    vector<int> swapNumbers(vector<int>& numbers) {
        numbers[0] = numbers[1] ^ numbers[0];
        numbers[1] = numbers[0] ^ numbers[1];
        numbers[0] = numbers[1] ^ numbers[0];
        return numbers;
    }

    int diagonalSum(vector<vector<int>>& mat) {
        int ret{0};
        for (int i=0; i<mat.size()/2; i++)
        {
            int symIdx = mat.size()-i-1;
            ret += mat[i][i];
            ret += mat[i][symIdx];
            ret += mat[symIdx][i];
            ret += mat[symIdx][symIdx];
        }
        if (mat.size()%2==1) ret+=mat[mat.size()/2][mat.size()/2];
        return ret;
    }

    int numSquares(int n) {
        vector <int> dp(n+1, INT32_MAX);
        dp[0] = 0;
        for (int i=1; i<=n; i++)
        {
            for (int j=1; j<=sqrt(i); j++)
            {
                dp[i] = min(dp[i], dp[i-j*j]+1);
            }
        }
        return dp[n];
    }

    int dfsSN(TreeNode* node, int preSum)
    {
        if (node == nullptr) return 0;
        int sum = preSum*10 + node->val;
        if (node->left==nullptr && node->right==nullptr)
            return sum;
        else
            return dfsSN(node->right, sum) +  dfsSN(node->left, sum);
    }
    int sumNumbers(TreeNode* root) {
        return dfsSN(root, 0);
    }

    vector<ListNode*> listOfDepth(TreeNode* tree) {
        vector<ListNode*> ret;
        queue<TreeNode*> vNode;
        vNode.emplace(tree);
        while(!vNode.empty())
        {
            ListNode* head = nullptr, *temp=new ListNode();
            int loop = vNode.size();
            for (int i=0; i<loop; i++)
            {
                auto p = vNode.front();
                vNode.pop();
                if (p) 
                {
                    temp->next = new ListNode(p->val);
                    temp = temp->next;
                    if (head==nullptr) head = temp;
                    if (p->left)
                        vNode.emplace(p->left);
                    if (p->right)
                        vNode.emplace(p->right);
                }
            }
            ret.emplace_back(head);
        }
        return ret;
    }

    int islandPerimeter(vector<vector<int>>& grid) {
        int cnt{0};
        for (int i = 0; i < grid.size(); i++)
        {
            for (int j=0; j<grid[0].size(); j++)
            {
                if (j == 0 && grid[i][j]) cnt++;
                if (i == 0 && grid[i][j]) cnt++;
                if (j == grid[0].size()-1)
                {
                    if (grid[i][j]) cnt++;
                }
                else if (grid[i][j] - grid[i][j+1]) cnt++;
                if (i == grid.size()-1)
                {
                    if(grid[i][j]) cnt++;
                }
                else if (grid[i+1][j]-grid[i][j]) cnt++;
            }
        }
        return cnt;
    }

    bool isValidSudoku(vector<vector<char>>& board) {
        unordered_set<char> row, box1, box2, box3;
        vector<unordered_set<char>> cols(9);
        for (int i=0; i<9; i++)
        {
            for (int j=0; j<9; j++)
            {
                if (board[i][j] == '.') continue;
                if (cols[j].count(board[i][j])) return false;
                cols[j].insert(board[i][j]);
                if (j<3)
                {
                    if (box1.count(board[i][j])) return false;
                    box1.insert(board[i][j]);
                }
                else if (j<6)
                {
                    if (box2.count(board[i][j])) return false;
                    box2.insert(board[i][j]);
                }
                else if (j<9)
                {
                    if (box3.count(board[i][j])) return false;
                    box3.insert(board[i][j]);
                }
                if (row.count(board[i][j])) return false;
                    row.insert(board[i][j]);
            }
            row.clear();
            if (i == 2 || i==5)
            {box1.clear(); box2.clear(); box3.clear();}
        }
        return true;
    }


    int findRep(string s)
    {
        unordered_map<char, int> mp;
        for (char c : s)
        {
            if (!mp.count(c)) mp.insert(pair<char, int>(c, 1));
            else mp[c] ++;
        }
        int ret{INT32_MAX};
        for (auto t : mp) ret = min(ret, t.second);
        return ret;
    }
    vector<int> numSmallerByFrequency(vector<string>& queries, vector<string>& words) {
        vector <int> wdSet;
        for (string c : words) wdSet.emplace_back(findRep(c));
        vector <int> ret;
        for (string c : queries)
        {
            int cnt = findRep(c);
            int cont{0};
            for (int i : wdSet)
                if (cnt < i) cont ++;
            ret.emplace_back(cont);
        }
        return ret;
    }

    vector<int> constructArray(int n, int k) {
        vector<int> ret;
        ret.emplace_back(1);
        int fac = 1;
        for (int i=k; i>0; i--)
        {
            int val = ret.back()+fac*i;
            fac = -fac;
            ret.emplace_back(val);
        }
        for (int i=2+k; i<=n; i++) ret.emplace_back(i);
        return ret;
    }

    int countOdds(int low, int high) {
        return low%2==0? (high-low)/2+2 : (high-low)/2;
    }

    bool lemonadeChange(vector<int>& bills) {
        vector<int> wallet(2,0);
        for (int i: bills)
        {
            switch (i)
            {
            case 5:
                wallet[0]++;
                break;
            case 10:
                if (!wallet[0]) return false;
                wallet[1]++;
                wallet[0]--;
                break;
            case 20:
                if (!wallet[1])
                {
                    if (wallet[0]<3) return false;
                    wallet[0] -= 3;
                }
                else
                {
                    if (!wallet[0]) return false;
                    wallet[0]--;
                    wallet[1]--;
                }
                break;
            }
        }
        return true;
    }

    vector<int> nodeL;
    void traBST(TreeNode* node)
    {
        if (node==nullptr) return;
        nodeL.push_back(node->val);
        traBST(node->left);
        traBST(node->right);
    }
    int minDiffInBST(TreeNode* root) {
        traBST(root);
        sort(nodeL.begin(), nodeL.end());
        int diffMin{INT32_MAX};
        for (int i=0; i<nodeL.size()-1; i++) diffMin = min(diffMin, nodeL[i+1]-nodeL[i]);
        return diffMin;
    }

    vector<vector<int>> imageSmoother(vector<vector<int>>& M) {
        int m = M.size(), n = M.front().size();
        vector<vector<int>> result(m, vector<int>(n));
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
            {
                int num = 0, sum = 0;
                for (int _i = max(0, i-1); _i <= min(m-1, i+1); ++_i)
                    for (int _j = max(0, j-1); _j <= min(n-1, j+1); ++_j)
                    {
                        sum += M[_i][_j];
                        ++num;
                    }
                result[i][j] = sum / num;
            }
        return result;
    }

    int dayOfYear(string date) {
        vector <int> monthDays{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        int year{0}, month{0}, day{0};
        for (int i=0; i<4; i++)
            year = year*10 + (date[i] - '0');
        for (int i=5; i<7; i++)
            month = month*10 + (date[i] - '0');
        for (int i=8; i<10; i++)
            day = day*10 + (date[i] - '0');
        if (year%4 == 0 && year%100 != 0 || year%400 == 0) monthDays[1]++;
        for (int i=1; i<monthDays.size(); i++) monthDays[i] += monthDays[i-1];
        return month == 1 ? day : monthDays[month-2] + day;
    }
    
    // Problem # 394
    string decodeString(string s) {
        
    }

    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        unordered_set<int> set{}, inters{};
        for (int i: nums1) set.insert(i);
        for (int i : nums2)
            if (set.count(i))
                inters.insert(i);
        vector<int> ret;
        while (!inters.empty())
        {
            ret.emplace_back(*inters.begin());
            inters.erase(*inters.begin());
        }
        return ret;
    }
};

int main(int argc, char** argv)
{

    time_t t = clock();
    Solution s;
    // ====== test ==================================================

    cout << s.dayOfYear("2020-02-01") << endl;

    TreeNode h(71);
    h.left = new TreeNode(62);
    h.right = new TreeNode(84);
    h.left->left = new TreeNode(14);
    h.right->right = new TreeNode(88);
    int ans = s.minDiffInBST(&h);
 
    vector<vector<char>> a = {{'.','.','4', '.','.','.', '6','3','.'},
                              {'.','.','.', '.','.','.', '.','.','.'},
                              {'5','.','.', '.','.','.', '.','9','.'},

                              {'.','.','.', '5','6','.', '.','.','.'},
                              {'4','.','3', '.','.','.', '.','.','1'},
                              {'.','.','.', '7','.','.', '.','.','.'},

                              {'.','.','.', '5','.','.', '.','.','.'},
                              {'.','.','.', '.','.','.', '.','.','.'},
                              {'.','.','.', '.','.','.', '.','.','.'}};
    std::cout << "ans" << s.isValidSudoku(a) << endl;


    RandomizedCollection rc;
    bool r = rc.insert(1);
    r = rc.remove(1);
    r = rc.insert(1);
    cout << rc.getRandom() << ' ' << rc.getRandom() << ' ' << rc.getRandom() << endl;
    // ====== test ==================================================
    std::cout << endl << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
    return 0;
}