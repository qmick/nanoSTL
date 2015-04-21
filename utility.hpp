#ifndef __UTILITY_HPP__
#define __UTILITY_HPP__

namespace nano {

template< class T1, class T2>
struct pair
{
	//Member types
	typedef T1 first_type;
	typedef T2 second_type;

	//Member objects
	T1 first;
	T2 second;

	//member functions
	pair() {}
	pair(const T1& x, const T2& y)
		: first(x), second(y)
	{
	}

	template< class U1, class U2 >
	pair(const pair<U1, U2>& p)
		: first(p.first), second(p.second)
	{
		//TODO:pair constructor3
	}

	pair(const pair& p) = default;

};

template< class T1, class T2 >
pair<T1, T2> make_pair(T1 t, T2 u)
{
	//TODO:make_pair
}

}


#endif
