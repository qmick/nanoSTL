#ifndef __NANO_ALGO_BASE_HPP__
#define __NANO_ALGO_BASE_HPP__

#include "../iterator.hpp"
#include "type_traits.hpp"

namespace nano {

template< class BidIt1, class BidIt2 >
inline BidIt1 __find_end(BidIt1 first, BidIt1 last,
	BidIt2 s_first, BidIt2 s_last,
	bidirectional_iterator_tag, bidirectional_iterator_tag)
{
	typedef reverse_iterator<BidIt1> reviter1;
	typedef reverse_iterator<BidIt2> reviter2;

	reviter1 rlast(first);
	reviter2 rs_last(s_first);
	reviter1 rresult = search(reviter1(last), rlast, reviter2(s_last), rs_last);
	if (rresult == rlast)
		return last;
	else
	{
		BidIt1 result = rresult.base();
		advance(result, -distance(s_first, s_last));
		return result;
	}
}

template< class ForwardIt1, class ForwardIt2 >
inline ForwardIt1 __find_end(ForwardIt1 first, ForwardIt1 last,
	ForwardIt2 s_first, ForwardIt2 s_last,
	forward_iterator_tag, forward_iterator_tag)
{
	if (s_first == s_last)
		return s_first;
	else
	{
		ForwardIt1 result = last;
		while (1)
		{
			ForwardIt1 new_result = search(first, last, s_first, s_last);
			if (new_result == last)
				return result;
			else
			{
				result = new_result;
				first = new_result;
				++first;
			}
		}
		return result;
	}
}

template< class BidIt1, class BidIt2, class BinaryPredicate >
inline BidIt1 __find_end(BidIt1 first, BidIt1 last,
	BidIt2 s_first, BidIt2 s_last, BinaryPredicate p, 
	bidirectional_iterator_tag, bidirectional_iterator_tag)
{
	typedef reverse_iterator<BidIt1> reviter1;
	typedef reverse_iterator<BidIt2> reviter2;

	reviter1 rlast(first);
	reviter2 rs_last(s_first);
	reviter1 rresult = search(reviter1(last), rlast, reviter2(s_last), rs_last, p);
	if (rresult == rlast)
		return last;
	else
	{
		BidIt1 result = rresult.base();
		advance(result, -distance(s_first, s_last));
		return result;
	}
}

template< class ForwardIt1, class ForwardIt2, class BinaryPredicate >
inline ForwardIt1 __find_end(ForwardIt1 first, ForwardIt1 last,
	ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate p,
	forward_iterator_tag, forward_iterator_tag)
{
	if (s_first == s_last)
		return s_first;
	else
	{
		ForwardIt1 result = last;
		while (1)
		{
			ForwardIt1 new_result = search(first, last, s_first, s_last, p);
			if (new_result == last)
				return result;
			else
			{
				result = new_result;
				first = new_result;
				++first;
			}
		}
		return result;
	}
}

template< class RanIt, class OutputIt >
//Copy content pointed by random access iterator
inline OutputIt __copy(RanIt first, RanIt last, OutputIt d_first,
	random_access_iterator_tag)
{
	return __copy_r(first, last, d_first);
}

template< class InputIt, class OutputIt >
//Copy content pointed by input iterator
inline OutputIt __copy(InputIt first, InputIt last, OutputIt d_first,
	input_iterator_tag)
{
	for (; first != last; ++first, ++d_first)
		*d_first = *first;
}

template< class T >
//Copy content pointed by const pointer(continuous data)
inline T* __copy_r(const T *first, const T *last, T *d_first)
{
	typedef typename type_traits<T>::has_trivial_assignment_operator htao;
	return __copy_r_trivial(first, last, d_first, htao());
}

template< class T >
//Copy content pointed by pointer(continuous data)
inline T* __copy_r(T *first, T *last, T *d_first)
{
	typedef typename type_traits<T>::has_trivial_assignment_operator htao;
	return __copy_r_trivial(first, last, d_first, htao());
}

template< class RanIt, class OutputIt, class Distance >
//Copy content pointed by random access iterator but not pointer
inline OutputIt __copy_r(RanIt first, RanIt last, OutputIt d_first)
{
	for (Distance i = last - first; i > 0; --i, ++first, ++d_first)
		*d_first = *first;
	return d_first;
}

template< class T >
//Copy content pointed by pointer(continuous data) and has trivial assignment operator
inline T* __copy_r_trivial(const T *first, const T *last, T *d_first, true_type)
{
	memmove(d_first, first, sizeof(T) * (last - first));
	return d_first + (last - first);
}

template< class T >
//Copy content pointed by pointer(continuous data) but don't has trivial assignment operator
inline T* __copy_r_trivial(const T *first, const T *last, T *d_first, false_type)
{
	for (int i = last - first; i > 0; --i, ++first, ++d_first)
		*d_first = *first;
	return d_first;
}

template< class RanIt >
//Reverse for random access iterator
void __reverse(RanIt first, RanIt last, random_access_iterator_tag)
{
	for (; first < last; ++first, --last)
		iter_swap(first, last);
}

template< class BidirIt >
//Reverse for bidirectional iterator
void __reverse(BidirIt first, BidirIt last, bidirectional_iterator_tag)
{
	while (1)
	{
		if (first == last || first == --last)
			return;
		else
			iter_swap(first++, last);
	}
}

template< class RanIt, class Distance >
inline void __rotate(RanIt first, RanIt middle, RanIt last,
	Distance*, random_access_iterator_tag)
{
	typedef typename iterator_traits<RanIt>::value_type value_type;
	Distance n = __gcd(last - first, middle - first);
	while (n--)
	{
		__rotate_cycle(first, last, first + n, middle - first, value_type());
	}
}

template< class EuclideanRingElement >
EuclideanRingElement __gcd(EuclideanRingElement m, EuclideanRingElement n)
{
	while (n != 0)
	{
		EuclideanRingElement t = m % n;
		m = n;
		n = t;
	}
	return m;
}

template< class RanIt, class Dictance, class T, class Distance >
void __rotate_cycle(RanIt first, RanIt last, RanIt initial, Distance shift, T*)
{
	T value = *initial;
	RanIt ptr1 = initial;
	RanIt ptr2 = ptr1 + shift;
	while (ptr2 != initial)
	{
		*ptr1 = *ptr2;
		ptr1 = ptr2;
		if (last - ptr2 > shift)
			ptr2 += shift;
		else
			ptr2 = first + (shift - (last - ptr2));
	}
	*ptr1 = value;
}

template< class BidIt, class Distance >
inline void __rotate(BidIt first, BidIt middle, BidIt last,
	Distance*, bidirectional_iterator_tag)
{
	reverse(first, middle);
	reverse(middle, last);
	reverse(first, last);
}

template< class ForwardIt, class Distance >
inline void __rotate(ForwardIt first, ForwardIt middle, ForwardIt last,
	Distance*, forward_iterator_tag)
{
	for (ForwardIt i = middle;;)
	{
		iter_swap(first, i);
		++first;
		++i;
		if (first == middle)
		{
			if (i == last) return;
			middle = i;
		}
		else if (i == last)
			i = middle;
	}
}

template< class InputIt, class ForwardIt, class BinaryPredicate >
ForwardIt __unique_copy(InputIt first, InputIt last, ForwardIt d_first, 
	BinaryPredicate p, forward_iterator_tag)
{
	*d_first = *first;
	while (++first != last)
	{
		if (!p(*d_first, *first))
			*++d_first = *first;
	}
	return ++d_first;
}

template< class InputIt, class OutputIt, class BinaryPredicate, class T >
OutputIt __unique_copy(InputIt first, InputIt last, 
	OutputIt d_first, BinaryPredicate p, T*)
{
	T value = *first;
	*d_first = value;
	while (++first != last)
	{
		if (!p(value, *first))
		{
			value = *first;
			*++d_first = value;
		}
	}
	return ++d_first;
}

}

#endif
