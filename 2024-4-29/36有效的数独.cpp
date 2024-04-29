#include<iostream>
#include<string>
#include<cstdbool>
#include<stack>
#include<vector>
#include<map>
#include <algorithm>
#include <queue>
#include<unordered_set>
#include<unordered_map>
using namespace std;

class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {

        for (size_t i = 1; i <=board.size()* board.size()/9; i++)
        {   
            unordered_set<char>num;
            for (size_t j = 0; j < 3; j++)
            {
                for (size_t k = 0; k < 3; k++)
                {
                    if (num.find(board[j * (i+2)/3][k * i]) == num.end()) {
                        num.insert(board[j * (i + 2)/3][k * i]);
                    }
                    else
                    {
                        return false;
                    }
                }

            }

        }

        for (size_t i = 1; i <= board.size(); i++)
        {
            unordered_set<char>num;
            for (size_t j = 0; j < 9; j++)
            {
                if (num.find(board[i][j]) == num.end()&& board[i][j]!='.') {
                    num.insert(board[i][j]);
                }
                else if(num.find(board[i][j]) != num.end() && board[i][j] != '.')
                {
                    return false;
                }
            }


        }

        for (size_t i = 1; i <= board.size(); i++)
        {
            unordered_set<char>num;
            for (size_t j = 0; j < 9; j++)
            {
                if (num.find(board[j][i]) == num.end() && board[j][i] != '.') {
                    num.insert(board[j][i]);
                }
                else if(num.find(board[i][j]) != num.end() && board[i][j] != '.')
                {
                    return false;
                }
            }


        }



        return true;
    }
};


class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {


        int row[9][10] = {0};
        int col[9][10] = {0};
        int box[9][10] = {0};
        for (size_t i = 0; i < 9; i++)
        {
            for (size_t j = 0; j < 9; j++)
            {
                if (board[i][j] == '.')continue;
                int num = (int)(board[i][j] - '0');
                if (row[j][num])return false;
                if (col[i][num])return false;
                if (box[(i/3)*3+(j/3)][num])return false;


                row[j][num] = 1;
                col[i][num] = 1;
                box[(i / 3) * 3 + (j / 3)][num] = 1;


            }

        }
        return true;


    }

}