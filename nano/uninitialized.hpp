#ifndef __NANO_UNINITIALIZED_HPP__
#define __NANO_UNINITIALIZED_HPP__

#include "type_traits.hpp"
#include "construct.hpp"
#include "../iterator.hpp"

namespace nano {


//uninitialized_copy for POD that is continuously stored 
template< class T >
inline T* __uninitialized_copy(T* first, T* last, T* d_first, true_type)
{
	typedef typename iterator_traits<T*>::value_type value_type;
	if (last > first)
		memmove(d_first, first, (last - first) * sizeof(value_type));
	return d_first + (last - first);
}

//uninitialized_copy for POD
template< class InputIt, class ForwardIt >
inline ForwardIt __uninitialized_copy(InputIt first, InputIt last, ForwardIt d_first, true_type)
{
	typedef typename nano::iterator_traits<ForwardIt>::value_type Value;
	ForwardIt current = d_first;
	for (; first != last; ++first, ++current)
	{
		*current = *first;
	}
	return current;
}

//uninitialized_copy for non-POD
template< class InputIt, class ForwardIt >
inline ForwardIt __uninitialized_copy(InputIt first, InputIt last, ForwardIt d_first, false_type)
{
	typedef typename nano::iterator_traits<ForwardIt>::value_type Value;
	ForwardIt current = d_first;
	try
	{
		for (; first != last; ++first, ++current)
		{
			::new((void *) (&*current)) Value(*first);
		}
		return current;
	}
	catch (...)
	{
		destroy(d_first, current);
	}
	return d_first;
}


template< class ForwardIt, class T >
//uninitialized_fill for POD
inline void __uninitialized_fill(ForwardIt first, ForwardIt last, const T& value, true_type)
{
	typedef typename nano::iterator_traits<ForwardIt>::value_type Value;
	ForwardIt current = first;
	for (; current != last; current++)
	{
		*current = value;
	}
}


template< class ForwardIt, class T >
//uninitialized_fill for non-POD
inline void __uninitialized_fill(ForwardIt first, ForwardIt last, const T& value, false_type)
{
	construct(first, last, value);
}


template< class ForwardIt, class Size, class T >
inline void __uninitialized_fill_n(ForwardIt first, Size count, const T& value, true_type)
{
	typedef typename iterator_traits<ForwardIt>::value_type Value;
	ForwardIt current = first;
	for (; count > 0; --count, ++current)
	{
		*current = value;
	}
}

template< class ForwardIt, class Size, class T >
inline void __uninitialized_fill_n(ForwardIt first, Size count, const T& value, false_type)
{
	typedef typename iterator_traits<ForwardIt>::value_type Value;
	ForwardIt current = first;
	try
	{
		for (; count > 0; --count, ++current)
		{
			::new ((void*) (&*current)) Value(value);
		}
	}
	catch (...)
	{
		destroy(first, current);
	}
}




}

#endif
