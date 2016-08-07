#include <vector>
#include <iostream>
#include <map>

using namespace std;


class Solution {
public:
	int lengthOfLIS(vector<int>& nums) 
	{
		if (nums.size() == 0)
			return 0;
		int maxl = 1;
		map<int, int> l2v{make_pair(1, nums[0])};
		map<int, int> v2l{make_pair(nums[0], 1)};
		for (int n : nums)
		{
			auto i = v2l.lower_bound(n);
			if (i == v2l.end())
			{
				maxl++;
				l2v[maxl] = n;
				v2l[n] = maxl;
			}
			else if (i == v2l.begin())
			{
				auto pv = l2v[1];
				l2v.erase(1);
				v2l.erase(pv);
				l2v[1] = n;
				v2l[n] = 1;
			}
			else
			{
				auto pv = i->first;
				auto pl = i->second;
				l2v[pl] = n;
				v2l.erase(pv);
				v2l[n] = pl;
			}
		}
		return maxl;
	}
};


int main()
{
	auto s = Solution();
	auto r = 0;
	//vector<int> tv = {10,9,2,5,3,7,101,18};
	vector<int> tv = { 1 };
	r = s.lengthOfLIS(tv);
	cout << r << endl;
	return 0;
}