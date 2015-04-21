#ifndef __NANO_CONSTRUCT_HPP__
#define __NANO_CONSTRUCT_HPP__

namespace nano {

template< class T1, class T2 >
inline void construct(T1 *p, const T2 &value)
{
	new(p) T1(value);
}

template< class T1, class T2 >
inline void construct(T1 *p)
{
	new(p) T1();
}

template< class ForwardIt, class T >
//Construct range of elements
inline void construct(ForwardIt first, ForwardIt last, const T &value)
{
	typedef typename nano::iterator_traits<ForwardIt>::value_type Value;
	ForwardIt current = first;
	try
	{
		for (; current != last; ++current)
		{
			new((void*) (&*current)) Value(value);
		}
	}
	catch (...)
	{
		destroy(first, current);
		throw;
	}
}

template < class T >
inline void destroy(T *ptr)
{
	ptr->~T();
}


template< class ForwardIt >
//Destroy range of elements
inline void destroy(ForwardIt first, ForwardIt last)
{
	typedef typename iterator_traits<ForwardIt>::value_type Value;
	typedef typename type_traits<Value>::has_trivial_destructor has_trivial_destructor;
	__destroy(first, last, has_trivial_destructor());
}

template< class ForwardIt >
//Destroy POD data, do nothing
inline void __destroy(ForwardIt first, ForwardIt last, true_type) {}

template< class ForwardIt >
//Destroy non-POD data
inline void __destroy(ForwardIt first, ForwardIt last, false_type)
{
	typedef typename iterator_traits<ForwardIt>::value_type value_type;
	for (; first != last; ++first)
		first->~value_type();
}

}

#endif
