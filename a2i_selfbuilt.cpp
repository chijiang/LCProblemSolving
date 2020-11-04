#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int myAtoi(string str) {
        while (1)
        {
            if (str[0] != ' ') break;
            str.replace(0, 1, "");
        }
        char firstc = str[0];
        if (firstc == '-' || firstc == '+')
            if (str[1] != '.' && (str[1] < '0' || str[1] > '9'))
                return 0;
        if (firstc != '-'
            && firstc != '+'
            && ( firstc < '0'
            || firstc > '9')) return 0;
        int sign = firstc == '-' ? -1 : 1;
        if (firstc == '+' || firstc == '-')
            str.replace(0, 1, "");
        size_t ret {0};
        for (int i = 0; i < str.size(); i++)
        {
            char c = str[i];
            if (c < '0' || c > '9') break;
            ret *= 10;
            ret += (size_t) c - 48;
            if (ret > INT32_MAX) break;
        }
        if (sign < 0)
            return ret == (int)ret ? (int)ret * sign : INT32_MIN;
        return ret == (int)ret ? (int)ret * sign : INT32_MAX;
    }
};

int main(int argc, char** argv)
{
    Solution s;
    string str {"4882"};
    cout << s.myAtoi(str) << endl;
}