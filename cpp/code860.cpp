/*
860. 柠檬水找零
在柠檬水摊上，每一杯柠檬水的售价为 5 美元。

顾客排队购买你的产品，（按账单 bills 支付的顺序）一次购买一杯。

每位顾客只买一杯柠檬水，然后向你付 5 美元、10 美元或 20 美元。你必须给每个顾客正确找零，也就是说净交易是每位顾客向你支付 5 美元。

注意，一开始你手头没有任何零钱。

如果你能给每位顾客正确找零，返回 true ，否则返回 false 。

示例 1：

输入：[5,5,5,10,20]
输出：true
解释：
前 3 位顾客那里，我们按顺序收取 3 张 5 美元的钞票。
第 4 位顾客那里，我们收取一张 10 美元的钞票，并返还 5 美元。
第 5 位顾客那里，我们找还一张 10 美元的钞票和一张 5 美元的钞票。
由于所有客户都得到了正确的找零，所以我们输出 true。
示例 2：

输入：[5,5,10]
输出：true
示例 3：

输入：[10,10]
输出：false
示例 4：

输入：[5,5,10,10,20]
输出：false
解释：
前 2 位顾客那里，我们按顺序收取 2 张 5 美元的钞票。
对于接下来的 2 位顾客，我们收取一张 10 美元的钞票，然后返还 5 美元。
对于最后一位顾客，我们无法退回 15 美元，因为我们现在只有两张 10 美元的钞票。
由于不是每位顾客都得到了正确的找零，所以答案是 false。
 

提示：

0 <= bills.length <= 10000
bills[i] 不是 5 就是 10 或是 20 
*/
#include<iostream>
#include<stdlib.h>
#include<sstream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
    int _cnt_bill_5 = 0;    // 当前5美元张数
    int _cnt_bill_10 = 0;   // 当前10美元张数
    int _cnt_bill_20 = 0;   // 当前20美元张数
public:
    bool lemonadeChange(vector<int>& bills) {
        for(vector<int>::iterator it = bills.begin(); it != bills.end(); ++it){
            if(5 == *it){
                // 5美元的时候，直接接收
                ++ _cnt_bill_5;
                continue;
            }
            if(10 == *it){
                // 10美元的时候，找零5美元
                if(0 == _cnt_bill_5) 
                    return false;
                ++ _cnt_bill_10;
                -- _cnt_bill_5;    
                continue;
            }
            if(20 == *it){
                ++ _cnt_bill_20;
                // 20美元的时候，找零3张5美元或者一张5美元加一张10美元
                if(0 < _cnt_bill_10 && 0 < _cnt_bill_5){
                    -- _cnt_bill_10;
                    -- _cnt_bill_5;
                    continue;
                }
                if(2 < _cnt_bill_5){
                    _cnt_bill_5 -= 3;
                    continue;
                }
                return false;
            }
        }
        return true;
    }
};

void trimLeftTrailingSpaces(string &input) {
    input.erase(input.begin(), find_if(input.begin(), input.end(), [](int ch) {
        return !isspace(ch);
    }));
}

void trimRightTrailingSpaces(string &input) {
    input.erase(find_if(input.rbegin(), input.rend(), [](int ch) {
        return !isspace(ch);
    }).base(), input.end());
}

vector<int> stringToIntegerVector(string input) {
    vector<int> output;
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    stringstream ss;
    ss.str(input);
    string item;
    char delim = ',';
    while (getline(ss, item, delim)) {
        output.push_back(stoi(item));
    }
    return output;
}

string boolToString(bool input) {
    return input ? "True" : "False";
}

int main() {
    string line;
    while (getline(cin, line)) {
        vector<int> bills = stringToIntegerVector(line);
        
        bool ret = Solution().lemonadeChange(bills);

        string out = boolToString(ret);
        cout << out << endl;
    }
    system("pause");
    return 0;
}