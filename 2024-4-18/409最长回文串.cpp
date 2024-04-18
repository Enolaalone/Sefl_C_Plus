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
    int longestPalindrome(string s) {
		unordered_map<char, int>num_a;
		int k = 0,n=0;
		for (auto ch:s)
		{
			if (num_a.find(ch) == num_a.end()) {
				num_a[ch] = 1;
			}
			else num_a[ch]++;

		}

		for (auto itr = num_a.begin(); itr != num_a.end(); itr++) {
			if (!k && itr->second % 2)k++;
			n +=2*((itr->second) / 2);

		}
		return n + k;

    }
};

int main() {

	string s = "abccccdd";
	Solution solution;
	solution.longestPalindrome(s);
}