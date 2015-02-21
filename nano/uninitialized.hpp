#ifndef _UNINITIALIZED_HPP_
#define _UNINITIALIZED_HPP_

#include "type_traits.hpp"

namespace nano {

template< class ForwardIt, class T >
void range_construct(ForwardIt first, ForwardIt last, const T &value)
{
	typedef typename nano::iterator_traits<ForwardIt>::value_type Value;
	ForwardIt current = first;
	try
	{
		for (; current != last; ++current)
		{
			::new((void*) (&*current)) Value(value);
		}
	}
	catch (...)
	{
		range_destroy(first, current);
		throw;
	}
}

template< class ForwardIt >
void range_destroy(ForwardIt first, ForwardIt last)
{
	typedef typename nano::iterator_traits<ForwardIt>::value_type Value;
	for (; first != last; ++first)
		first->~Value();
}

//uninitialized_copy for POD
template< class InputIt, class ForwardIt >
ForwardIt __uninitialized_copy(InputIt first, InputIt last, ForwardIt d_first, true_type)
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
ForwardIt __uninitialized_copy(InputIt first, InputIt last, ForwardIt d_first, false_type)
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
		range_destroy(d_first, current);
		throw;
	}
}


template< class ForwardIt, class T >
//uninitialized_fill for POD
void __uninitialized_fill(ForwardIt first, ForwardIt last, const T& value, true_type)
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
void __uninitialized_fill(ForwardIt first, ForwardIt last, const T& value, false_type)
{
	range_construct(first, last, value);
}


template< class ForwardIt, class Size, class T >
void __uninitialized_fill_n(ForwardIt first, Size count, const T& value, true_type)
{
	typedef typename nano::iterator_traits<ForwardIt>::value_type Value;
	ForwardIt current = first;
	for (; count > 0; --count, ++current)
	{
		*current = value;
	}
}

template< class ForwardIt, class Size, class T >
void __uninitialized_fill_n(ForwardIt first, Size count, const T& value, false_type)
{
	typedef typename nano::iterator_traits<ForwardIt>::value_type Value;
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
		range_destroy(first, current);
		throw;
	}
}




}

#endif