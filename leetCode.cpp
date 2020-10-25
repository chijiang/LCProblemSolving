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
};

int main(int argc, char** argv)
{
    time_t t = clock();
    Solution s;
    // ====== test ==================================================
    vector <int> A{1, 2, 3, 4, 5, 1};
    int longestM = s.longestMountain(A);
    cout << "Longest Mountain: " << longestM << endl;

    vector<vector<int>> a{{0, 2}, {4, 8}};
    int ans = s.videoStitching(a, 5);
    cout << ans;
    // ====== test ==================================================
    cout << endl << (double) (clock() - t) / CLOCKS_PER_SEC << endl;
    return 0;
}