#include "map.hpp"
#include <cassert>
int main()
{
	using namespace nano;
	map<int, int> a;
	for (int i = 0; i < 100; ++i)
		a.insert(pair<int, int>(i, i));


	map<int, int>::const_reverse_iterator it = a.rbegin();
	for (int i = 99; it != a.rend(); ++it, --i)
		assert((*it).second == i);

	return 0;
}
