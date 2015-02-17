#ifndef _UNINITIALIZED_HPP_
#define _UNINITIALIZED_HPP_

#include "type_traits.hpp"

namespace nano
{

template< class T >
T* __addressof(T& arg)
{
	return reinterpret_cast<T*>(
		&const_cast<char&>(
		reinterpret_cast<const volatile char&>(arg)));
}

//uninitialized_copy for POD
template< class InputIt, class ForwardIt >
ForwardIt __uninitialized_copy(InputIt first, InputIt last, ForwardIt d_first, true_type)
{
	typedef typename nano::iterator_traits<ForwardIt>::value_type Value;
	ForwardIt current = d_first;
	for (; first != last; first++, current++)
	{
		memmove(&*current, &*first, sizeof(Value));
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
		for (; first != last; first++, current++)
		{
			::new((void *) (&*current)) Value(*first);
		}
		return current;
	}
	catch (...)
	{
		for (; d_first != current; d_first++)
		{
			d_first->~Value();
		}
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
		memcpy(&*current, &value, sizeof(Value));
	}
}


template< class ForwardIt, class T >
//uninitialized_fill for non-POD
void __uninitialized_fill(ForwardIt first, ForwardIt last, const T& value, false_type)
{
	typedef typename nano::iterator_traits<ForwardIt>::value_type Value;
	ForwardIt current = first;
	try
	{
		for (; current != last; current++)
		{
			::new((void*) (&*current)) Value(value);
		}
	}
	catch (...)
	{
		for (; first != last; first++)
		{
			first->~Value();
		}
		throw;
	}
}


template< class ForwardIt, class Size, class T >
void __uninitialized_fill_n(ForwardIt first, Size count, const T& value, true_type)
{
	typedef typename nano::iterator_traits<ForwardIt>::value_type Value;
	ForwardIt current = first;
	for (; count > 0; count--, current++)
	{
		memcpy(&*current, &*value, sizeof(Value));
	}
}

template< class ForwardIt, class Size, class T >
void __uninitialized_fill_n(ForwardIt first, Size count, const T& value, false_type)
{
	typedef typename nano::iterator_traits<ForwardIt>::value_type Value;
	ForwardIt current = first;
	try
	{
		for (; count > 0; count--, current++)
		{
			::new ((void*) (&*current)) Value(value);
		}
	}
	catch (...)
	{
		for (; first != current; first++)
		{
			first->~Value();
		}
		throw;
	}
}


}

#endif