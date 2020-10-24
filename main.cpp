#include <iostream>
#include <vector>
#include <string>

using namespace std;

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

    return 0;
}