#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <math.h>
#include <unordered_set>

using namespace std;

struct HashNode
{   
public:
    int val{NULL};
    int key{NULL};
    HashNode* next;
    HashNode(int _key, int _val) : key(_key), val(_val), next(nullptr){}
    HashNode() : next(nullptr){}
};
class MyHashMap {
private:
    vector <HashNode*> bucket;
    const int BUCKET_SIZE = 10007;
public:
    /** Initialize your data structure here. */
    MyHashMap() {
        bucket = vector <HashNode*>(BUCKET_SIZE, nullptr);
    }
    
    /** value will always be non-negative. */
    void put(int key, int value) {
        int index = key % BUCKET_SIZE;
        if (bucket[index] == nullptr) bucket[index] = new HashNode(key, value);
        else
        {
            HashNode* temp = bucket[index];
            while (temp->next != nullptr) 
            {
                if (temp->key == key) 
                {
                    temp->val = value;
                    return;
                }
                temp = temp->next;
            }
            if (temp->key == key) temp->val = value;
            else temp->next = new HashNode(key, value);
        }
    }
    
    /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
    int get(int key) {
        int index = key % BUCKET_SIZE;
        HashNode* temp = bucket[index];
        while (temp != nullptr)
        {
            if (temp->key == key) return temp->val;
            temp->next = temp;
        }
        return -1;
    }
    
    /** Removes the mapping of the specified value key if this map contains a mapping for the key */
    void remove(int key) {
        int index = key % BUCKET_SIZE;
        HashNode* temp = bucket[index];
        while (temp != nullptr)
        {
            if (temp->key == key)
            {
                temp->val = -1;
                break;
            }
            temp->next = temp;
        }
    }
};

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
public:
    int sum_methods(int n)
    {
        if (n < 0) return 0;
        if (n == 0 || n == 1 || n == 2) return 1;
        return sum_methods(n - 1) + sum_methods(n - 3) + sum_methods(n - 4);
    }

    int triTiling_D(int n)
    {
        if (n == 2) return 3;
        if (n <= 1) return 0;
        return triTiling_D(n-2) + triTiling_A(n-1) * 2;
    }

    int triTiling_A(int n)
    {
        if (n <= 0) return 0;
        if (n == 1) return 1;
        return triTiling_D(n-1) + triTiling_C(n-1);
    }

    int triTiling_C(int n)
    {
        if (n <= 1) return 0;
        return triTiling_A(n-1);
    }

    int findLCS(string x, string y)
    {
        vector<vector<int>> result(x.size()+1, vector<int>(y.size()+1, 0));
        for (int i = 0; i <= x.size(); ++i) result[i][0] = 0;
        for (int j = 0; j <= y.size(); ++j) result[0][j] = 0;
        for (int i = 1; i <= x.size(); ++i)
            for (int j = 1; j <= y.size(); ++j)
            {
                if (x[i] == y[j])
                    result[i][j] = result[i - 1][j - 1] + 1;
                else
                    result[i][j] = max(result[i-1][j], result[i][j-1]);
            }
        int ret {0};
        for (vector<int> s : result)
            for (int t : s)
                ret = max(ret, t);
        return ret;
    }

    int recFindLCS(string x, string y)
    {
        if (x.size() == 0 || y.size() == 0) return 0;
        if (x[x.size()-1] == y[y.size() -1])
        {
            x.pop_back();
            y.pop_back();
            return 1 + recFindLCS(x, y);
        }
        else
        {
            string xcp = x;
            string ycp = y;
            xcp.pop_back();
            ycp.pop_back();
            return max(recFindLCS(x, ycp), recFindLCS(xcp, y));
        }
        
    }

    int buildPalindrome(string str)
    {
        if (str.size() <= 1) return 0;
        if (str[0] == str[str.size() - 1])
            return buildPalindrome(str.replace(0, 1, "").replace(str.size()-1, 1, ""));
        else
        {
            string cutHead, cutTail; 
            cutHead = str;
            cutTail = str;
            cutHead.replace(0, 1, "");
            cutTail.replace(cutTail.size()-1, 1, "");
            return 1 + min(buildPalindrome(cutHead), 
                            buildPalindrome(cutTail));
        }  
    }

    int altBuildPalindrome(string str)
    {
        string revStr;
        for (int i = str.size() - 1; i >= 0; i--) revStr.push_back(str[i]);
        return str.size() - recFindLCS(str, revStr);
    }

    vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
        vector <vector <int>> ret;
        int new_start{newInterval[0]}, new_end{newInterval[1]}, i{0};
        for (; i<intervals.size(); i++)
        {
            vector<int> ori_interval = intervals[i];
            if (ori_interval[1] < newInterval[0])
                ret.emplace_back(ori_interval);
            else if (ori_interval[0] > newInterval[1])
                break;
            else
            {
                new_start = min(new_start, ori_interval[0]);
                new_end = max(ori_interval[1], new_end);
            }
        }
        vector<int> new_interval{new_start, max(new_end, newInterval[1])};
        ret.emplace_back(new_interval);
        for (; i<intervals.size(); i++) ret.emplace_back(intervals[i]);
        return ret;
    }

    static int countOnes(int num)
    {
        int ret{0};
        while (num > 0)
        {
            ret += num % 2;
            num /= 2;
        }
        return ret;
    }
    static bool comp(int a, int b)
    {
        int numa = countOnes(a), numb = countOnes(b);
        return numa != numb ? numa < numb : a < b;
    }
    vector <int> sortByBit(vector <int> &arr)
    {
        sort(arr.begin(), arr.end(), comp);
        return arr;
    }

    // Prob solving # 5
    string longestPalindrome(string s)
    {
        string ret;
        size_t size = s.size();
        // Create a matrix to save the palindromes checking results, 
        // in which, (i, j) indicates the starting pos and 
        // the end pos.
        vector<vector<bool>> dp(size, vector<bool>(size)); 
        // Retr the different length of the sub string.
        for (int length = 0; length < size; length ++)
        {
            // Finding the starting and ending pos index
            for (int i = 0; i + length < size ; i ++)
            {
                int j = i + length;
                // When the substring has a length of 1 (Param@length = 0)
                if (length == 0) dp[i][j] = 1;
                // If the substring contains two letters, comp them.
                else if (length == 1) dp[i][j] = s[i] == s[j];
                else
                {
                    // If the first letter and the last letter are the same,
                    // the checking result of the substring should be identical
                    // to its substring, which removes a single head and 
                    // a single tail letter.
                    dp[i][j] = s[i] == s[j] && dp[i+1][j-1];
                }
                // Update the result.
                if (dp[i][j] && length + 1 > ret.size())
                {
                    ret = s.substr(i, length+1);
                }
            }
        }
        return ret;
    }

    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        unordered_map <int, vector<vector<int>>> pSet;
        vector<int> minDis;
        for (auto point : points)
        {
            int dis = point[0]*point[0] + point[1]*point[1];
            minDis.emplace_back(dis);
            pSet[dis].emplace_back(point);
        }
        sort(minDis.begin(), minDis.end());
        vector <vector<int>> ret;
        for (int i=0; ret.size() < K; i++)
        {
            for (auto point : pSet[minDis[i]])
                ret.emplace_back(point);
        }
        return ret;
    }

    int countVowelStrings(int n) {
        vector <vector <int>> dp(n+1, vector<int>(5));
        for (int i = 0; i < 5; i++) dp[1][i] = 1;
        for (int i = 2; i<n+1; i++)
        {
            dp[i][0] = dp[i-1][0] + dp[i-1][1] + dp[i-1][2] + dp[i-1][3] + dp[i-1][4]; // ended with letter "u";
            dp[i][1] = dp[i-1][1] + dp[i-1][2] + dp[i-1][3] + dp[i-1][4]; // ended with letter "o";
            dp[i][2] = dp[i-1][2] + dp[i-1][3] + dp[i-1][4]; // ended with letter "i";
            dp[i][3] = dp[i-1][3] + dp[i-1][4]; // ended with letter "e";
            dp[i][4] = dp[i-1][4]; // ended with letter "a";
        }
        return dp[n][0] + dp[n][1] + dp[n][2] + dp[n][3] + dp[n][4];
    }

    vector<int> countBits(int num) {
        vector<int> ret;
        ret.emplace_back(0);
        for (int i=1; i < num+1; i++)
        {
            if (i%2) 
            {
                ret.emplace_back(ret[i-1]+1);
            }
            else
            {
                ret.emplace_back(ret[i/2]);
            }
        }
        return ret;
    }

    ListNode* oddEvenList(ListNode* head) {
        if (!head) return head;
        ListNode* evenHead = head->next;
        ListNode* oddNode = head, *evenNode = evenHead;
        for (;evenNode && evenNode->next;)
        {
            oddNode->next = evenNode->next;
            oddNode = oddNode->next;
            evenNode->next = oddNode->next;
            evenNode = evenNode->next;
        }
        oddNode->next = evenHead;
        return head;
    }

    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        unordered_map<int, int> rank;
        for (int i=0; i < arr2.size(); i++) rank[arr2[i]] = i-arr2.size();
        sort(arr1.begin(), arr1.end(), [&](int x, int y){
            return (rank.count(x) ? rank[x] : x) < (rank.count(y) ? rank[y] : y);
        });
        return arr1;
    }

    int maxDepth(TreeNode* root) {

    }
};

int main(int argc, char** argv)
{
    Solution s;
    string str = "12336";
    cout << s.altBuildPalindrome(str) << endl;

    vector<vector<int>> list {{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
    vector<int> bd{4, 8};
    vector <vector <int>> ans = s.insert(list, bd);

    MyHashMap* my_map = new MyHashMap();
    my_map->put(1,1);
    my_map->put(10008,2);
    my_map->get(1);
    my_map->get(3);
    my_map->put(10008,1);
    my_map->get(2);
    my_map->remove(2);
    my_map->get(2);


    vector <int> abc {1, 2, 3, 4, 5, 6, 7};
    abc.insert(abc.begin()+1, 100);
    for (int i : abc) cout << i << " ";
    cout << endl;

    vector <int> sBBinput {1, 2, 3, 4, 5};
    vector <int> ans1 = s.sortByBit(sBBinput);
    for (int z : ans1) cout << z << " ";
    cout << endl;

    cout << s.longestPalindrome("cdbsbd") << endl;

    vector <int> testS = s.countBits(64);
    for (int i: testS) cout << i << " ";
    cout << endl;
    return 0;
}