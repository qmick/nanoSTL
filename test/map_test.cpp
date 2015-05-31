#include "../map.hpp"
#include "functional.hpp"
#include <cstdio>
#include <cassert>

int main()
{
	using namespace nano;

	typedef map<int, int> Mii;
	typedef pair<int, int> Pii;

	Mii m1;
	Mii m2(less<int>());
	
	for(int i = 0; i < 100; ++i)
	{
		m1.insert(Pii(i, 89));
	}	

	Mii m3(m1.begin(), m1.end());
	Mii m4 = m1;

	m1[3] = 11;
	
	Mii::iterator it = m1.begin();
	for(; it != m1.end(); ++it)
	{
		printf("%d", (*it).second);
	}

	Mii::const_iterator cit = m1.begin();
	for(; cit != m1.end(); it++)
	{
		printf("%d", (*cit).second);
	}

	Mii::reverse_iterator rit = m1.rbegin();
	for(; rit != m1.rend(); ++rit)
	{
		printf("%d", (*rit).second);
	}

	Mii::const_reverse_iterator crit = m1.rbegin();\
	for(; crit != m1.rend(); ++crit)
	{
		printf("%d", (*crit).second);
	}
	
	m1.clear();

	for(int i = 0; i < 100; ++i)
	{
		m1.insert(Pii(i, 11));
	}

	Mii m5;

	m5.insert(m1.begin(), m1.end());
	m5.erase(m5.begin());
	m5.erase(m5.begin(), m5.end());
	m5.swap(m1);

	m5.count(4);
	m5.find(11);
	m5.equal_range(6);
	m5.lower_bound(15);
	m5.upper_bound(17);

	
	return 0;
}
