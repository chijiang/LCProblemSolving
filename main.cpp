#include <iostream>
#include <vector>
#include <string>

using namespace std;

class HashNode
{   
public:
    int val{NULL};
    int key{NULL};
    HashNode* next;
    HashNode(int _key, int _val) : key(_key), val(_val), next(nullptr){}
    HashNode() : key(NULL), val(NULL), next(nullptr){}
    HashNode(int _key, int _val, HashNode* _next) : key(_key), val(_val), next(_next) {}
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
};

int main(int argc, char** argv)
{
    Solution s;
    string str = "12336";
    cout << s.altBuildPalindrome(str) << endl;

    MyHashMap* my_map = new MyHashMap();
    my_map->put(1,1);
    my_map->put(10008,2);
    my_map->get(1);
    my_map->get(3);
    my_map->put(10008,1);
    my_map->get(2);
    my_map->remove(2);
    my_map->get(2);

    return 0;
}