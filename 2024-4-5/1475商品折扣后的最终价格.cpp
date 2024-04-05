#include<iostream>
#include<string>
#include<stack>
#include<vector>
#include<map>
using namespace std;

class Solution {
public:
    vector<int> finalPrices(vector<int>& prices) {
		vector<int> aft_prices;
		for (size_t i = 0; i < prices.size(); i++)
		{
			if (i + 1 < prices.size() ) {
				for (size_t j = i+1; j < prices.size(); j++)
				{
					if (prices[i + 1] < prices[i]) {
						aft_prices.push_back(prices[i] - prices[i + 1]);
						break;
					}
				}

			
			}
				
			else
				aft_prices.push_back(prices[i]);

		}
		return aft_prices;
    }
};