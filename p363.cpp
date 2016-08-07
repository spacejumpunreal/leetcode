#include <vector>
#include <iostream>
#include <set>

using namespace std;


class Solution {
public:
	int maxSumSubmatrix(vector<vector<int>>& matrix, int k)
	{
		int rows = matrix.size();
		int cols = matrix[0].size();
		int nrows = rows;
		int ncols = cols;
		vector<vector<int>>* tm = nullptr;
		bool transposed = false;
		if (rows > cols)
		{
			transposed = true;
			nrows = cols;
			ncols = rows;
			tm = new vector<vector<int>>(nrows);
			for (int r = 0; r < nrows; r++)
			{
				(*tm)[r].resize(ncols);
				for (int c = 0; c < ncols; c++)
					(*tm)[r][c] = matrix[c][r];
			}
		}
		else
		{
			transposed = false;
		}
		vector<vector<int>>& m = transposed ? *tm : matrix;

		bool best_valid = false;
		int best = 0;
		for (int r = 0; r < nrows; r++)
		{
			auto csum = vector<int>(ncols, 0);
			for (int rr = r; rr < nrows; rr++)
			{
				for (int c = 0; c < ncols; c++)
				{
					csum[c] += m[rr][c];
				}
				set<int> left_sums;
				int left_sum = 0;
				for (int c = 0; c < ncols; c++)
				{
					left_sums.insert(left_sum);
					left_sum += csum[c];
					int ub = left_sum - k;
					auto itr = left_sums.lower_bound(ub);
					int v;
					if (itr == left_sums.end())
					{
						continue;	
					}
					else
					{
						v = *itr;
					}
					if (v == ub)
					{
						return k;
					}
					else
					{
						int r = left_sum - v;
						if ((!best_valid) || r > best)
						{
							best_valid = true;
							best = r;
						}
					}
				}
			}
		}
		return best;
	}
};


int main()
{
	vector<vector<int>> tm = {
		{ 1, 1 },
		{ 1, 1 },
	};
	auto s = Solution();
	auto r = s.maxSumSubmatrix(tm, 1);
	cout << r << endl;
	return 0;
}