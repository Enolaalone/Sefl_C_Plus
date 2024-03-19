#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include < map >

using namespace std;

class Solution {
public:

    string shift(string s) {
        stack<char> str;
        int i;
        char letter,ch;
        string res;
        for ( i = 0;s[i] != '\0'; i++)
        {
            ch = s[i];
            if(ch==' ')
            {
                int j = 1;
                while (s[i+1] == ' ')
                {
                    i++;
                    j++;
                }
                if (j >= 3&&s[i+1]!='\0')
                res += "0#";
                
            }
            if (ch >= '0' && ch <= '9')
            {
                res += ch;

                while (s[i + 1] >= '0'&&s[i + 1] <= '9') {
                    i++;
                    res += s[i];

                }
                res += '#';
            }
            else if (ch == '(')
            {
                if (s[i + 1] == '-') {
                    res+="0#";
                }
                str.push(ch);
            }
            else if (ch == ')')
            {
                while (!str.empty())
                {
                    letter = str.top();
                    str.pop();
                    if (letter == '(')break;
                    res += letter;

                }
            }
            else if (ch == '-' || ch == '+')
            {
                while (!str.empty())
                {
                    letter = str.top();
                    str.pop();
                    if (letter == '(') {
                        str.push(letter);
                        break;
                    }
                    res += letter;

                }
                str.push(ch);
            }

            else if (ch == '*' || ch == '/')
            {
                while (!str.empty())
                {
                    letter = str.top();
                    str.pop();
                    if (letter == '(' || letter == '-' || letter == '+') {
                        str.push(letter);
                        break;
                    }
                    res += letter;

                }
                str.push(ch);
            }

        }

        while (!str.empty())
        {
            res += str.top();
            str.pop();
        }
        return res;

    }
    long long int calculate(string s) {
        string str = shift(s);
        stack<int> nums;
        long long int num = 0;
        int i, r, l;
        for ( i = 0; str[i]!='\0'; i++)
        {
            if (str[i] >= '0' && str[i] <= '9')
            {
                num = num * 10 + (long long int)(str[i] - '0');

                while (str[i + 1] !='#') {
                    i++;
                    num = num * 10 + (long long int)(str[i] - '0');

                }
                nums.push(num);
                num = 0;

            }
            else if (str[i] == '+') {
                r = nums.top();
                nums.pop();
                l = nums.top();
                nums.pop();

                nums.push(l + r);
            }
            else if (str[i] == '-') {

                if (nums.empty())
                nums.push(0);
                    
                r = nums.top();
                nums.pop();

                if (nums.empty())
                nums.push(0);
                l = nums.top();
                nums.pop();

                //while (str[i + 1] == '-') {
                //    i++;
                //    r = -r;
                //}




                nums.push(l - r);
            }
            else if (str[i] == '*') {
                r = nums.top();
                nums.pop();
                l = nums.top();
                nums.pop();

                nums.push(l * r);
            }
            else if (str[i] == '/') {
                r = nums.top();
                nums.pop();
                l = nums.top();
                nums.pop();

                nums.push(l / r);
            }
           
        }
        return nums.top();

    }
};

int main() {

    Solution solution;
    string str = "2-(   -6)";

    string s=solution.shift(str);
    for (auto ch: s)
    {
        cout << ch;
    }
    int k = solution.calculate(str);
    cout << endl << k;

}