#include<iostream>
#include<vector>
#include  <algorithm>
using namespace std;

bool cmp(int a, int b)
{
	return a < b;
}

//寻找数组中的目标值下标，若不存在则返回0
int binarySearch(vector<int>& nums, int target)
{
	int l = 0;
	int r = nums.size() - 1;
	while (l < r)
	{
		int mid = (l + r) >> 1;
		if (nums[mid] == target) return mid;
		else if (nums[mid] < target) l = mid + 1;
		else r = mid - 1;
	}
	if (nums[l] != target) return -1;
	return l;
}

//target的左边界，标准库中lower_bound表达同一个意思
int Lower_bound(vector<int>& nums, int target)
{
	int l = 0;
	int r = nums.size() - 1;
	while (l < r)
	{
		int mid = (l + r) >> 1;
		if (nums[mid] >= target) r = mid;
		else l = mid + 1;
	}
	return l;
}

//target的右边界，标准库中upper_bound是第一个大于target的数,两者差距为1
//注意当l与r的差值为1时，特别讨论，否则l不变
int Upper_bound(vector<int>& nums, int target)
{
	int l = 0;
	int r = nums.size() - 1;
	while (l + 1 < r)
	{
		int mid = (l + r) >> 1;
		if (nums[mid] <= target) l = mid;
		else r = mid - 1;
	}
	if (nums[r] <= target) return r;
	return l;
}


int main()
{
	
	vector<int> nums = { 0,1,2,5,5,5,7,8,9,10,11 };
	cout << Lower_bound(nums, 5) << endl;
	auto tmp1 = lower_bound(nums.begin(), nums.end(), 5, cmp);
	cout << tmp1 - nums.begin() << endl;
	cout << Upper_bound(nums, 5) << endl;
	auto tmp2 = upper_bound(nums.begin(), nums.end(), 5, cmp);
	cout << tmp2 - nums.begin() - 1 << endl;
	return 0;
}
