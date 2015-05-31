#include "../vector.hpp"
#include <cstdio>
#include <cassert>

int main()
{
	using namespace nano;

	//test construct
	vector<int> v1;
	vector<int> v2(100);
	vector<int> v3(100, 7);
	vector<int> v4 = v3;
	vector<int> v5(v3.begin(), v3.end());

	vector<int> v6;
	v6 = v3;

	vector<int> v7;
	v7.assign(100, 7);
	
	vector<int> v8;
	v8.assign(v7.begin(), v8.end());

	int temp = v8.at(3);

	temp = v8[3];

	temp = v8.front();
	temp = v8.back();

	vector<int>::iterator it = v8.begin();
	for(; it != v8.end(); ++it)
	{
		printf("%d", *it);
	}

	vector<int>::const_iterator cit = v8.begin();

	for(; cit != v8.end(); cit++)
	{
		printf("%d", *cit);
	}


	vector<int>::reverse_iterator rit = v8.rbegin();
	for(; rit != v8.rend(); ++rit)
	{
		printf("%d", *rit);
	}

	vector<int>::const_reverse_iterator crit = v8.rbegin();
	for(; crit != v8.rend(); ++crit)
	{
		printf("%d", *crit);
	}

	v8.reserve(1000);

	v1.insert(v1.begin(), 11);
	v1.insert(v1.begin(), 100, 11);
	v1.insert(v1.begin(), v8.begin(), v8.end());
	v1.erase(v1.begin());
	v1.erase(v1.begin(), v1.end());	

	v1.push_back(11);
	v1.pop_back();
	v1.resize(100, 8);
	v1.swap(v8);
	
	return 0;
}

