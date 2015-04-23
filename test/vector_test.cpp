#include "../vector.hpp"
#include <cassert>

int main()
{
	using namespace nano;
	vector<vector<int> > v;
	vector<int> v1;

	
	for(int i = 0; i < 1000; ++i)
	{
		v1.push_back(i);
	}

	v.push_back(v1);
	
	for (size_t i = 0; i < v[0].size(); ++i)
	{
		assert(v[0][i] == i);
	}
	return 0;
}

