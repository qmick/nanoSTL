#ifndef __ALGORITHM_HPP__
#define __ALGORITHM_HPP__

#include "iterator.hpp"
#include "utility.hpp"
#include "functional.hpp"
#include "nano/algo_base.hpp"
#include "nano/type_traits.hpp"

namespace nano {

//Non-modifying sequence operations

template< class InputIt, class UnaryFunction >
UnaryFunction for_each(InputIt first, InputIt last, UnaryFunction f)
{
	for (; first != last; ++first)
		f(*first);
	return f;
}


template< class InputIt, class T >
typename iterator_traits<InputIt>::difference_type
	count(InputIt first, InputIt last, const T &value)
{
	typename iterator_traits<InputIt>::difference_type result = 0;
	for (; first != last; ++first)
	{
		if (*first == value)
			++result;
	}
	return result;
}

template< class InputIt, class UnaryPredicate >
typename iterator_traits<InputIt>::difference_type
	count_if(InputIt first, InputIt last, UnaryPredicate p)
{
	typename iterator_traits<InputIt>::difference_type result = 0;
	for (; first != last; ++first)
	{
		if (p(*first))
			++result;
	}
	return result;
}

template< class InputIt1, class InputIt2 >
pair<InputIt1, InputIt2> 
mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2)
{
	while (first1 != last1 && *first1 == *first2)
	{
		++first1;
		++first2;
	}

	return make_pair(first1, first2);
}

template< class InputIt1, class InputIt2, class BinaryPredicate >
pair<InputIt1, InputIt2>
mismatch(InputIt1 first1, InputIt1 last1, InputIt2 first2,
BinaryPredicate p)
{
	while (first1 != last1 && p(*first1, *first2))
	{
		++first1;
		++first2;
	}

	return make_pair(first1, first2);
}

template< class InputIt1, class InputIt2 >
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
{
	for (; first1 != last1; ++first1, ++first2)
	{
		if (!(*first1 == *first2))
			return false;
	}
	return true;
}

template< class InputIt1, class InputIt2, class BinaryPredicate >
bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
{
	for (; first1 != last1; ++first1, ++first2)
	{
		if (!p(*first1, *first2))
			return false;
	}
	return true;
}

template< class InputIt, class T >
InputIt find(InputIt first, InputIt last, const T& value)
{
	for (; first != last; ++first)
	{
		if (*first == value)
			break;
	}
	return first;
}

template< class InputIt, class UnaryPredicate >
InputIt find_if(InputIt first, InputIt last, UnaryPredicate p)
{
	for (; first != last; ++first)
	{
		if (p(*first))
			break;
	}
	return first;
}

template< class ForwardIt1, class ForwardIt2 >
ForwardIt1 find_end(ForwardIt1 first, ForwardIt1 last,
	ForwardIt2 s_first, ForwardIt2 s_last)
{
	__find_end(first, last, s_first, s_last, 
		iterator_category(first), iterator_category(s_first));
}




template< class ForwardIt1, class ForwardIt2, class BinaryPredicate >
ForwardIt1 find_end(ForwardIt1 first, ForwardIt1 last,
	ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate p)
{
	__find_end(first, last, s_first, s_last, p, 
		iterator_category(first), iterator_category(s_first));
}

template< class ForwardIt1, class ForwardIt2 >
ForwardIt1 find_first_of(ForwardIt1 first, ForwardIt1 last,
	ForwardIt2 s_first, ForwardIt2 s_last)
{
	for (; first != last; ++first)
	{
		for (ForwardIt2 it = s_first; it != s_last; ++it)
		{
			if (*it == *first)
				return first;
		}
	}
}

template< class ForwardIt1, class ForwardIt2, class BinaryPredicate >
ForwardIt1 find_first_of(ForwardIt1 first, ForwardIt1 last,
	ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate p)
{
	for (; first != last; ++first)
	{
		for (ForwardIt2 it = s_first; it != s_last; ++it)
		{
			if (p(*it, *first))
				return first;
		}
	}
}

template< class ForwardIt >
ForwardIt adjacent_find(ForwardIt first, ForwardIt last)
{
	if (first == last)
		return first;
	ForwardIt it = first;
	++it;
	for (; first != last; ++first, ++it)
	{
		if (*first == *it)
			return first;
	}
	return last;
}

template< class ForwardIt, class BinaryPredicate>
ForwardIt adjacent_find(ForwardIt first, ForwardIt last, BinaryPredicate p)
{
	if (first == last)
		return first;
	ForwardIt it = first;
	++it;
	for (; first != last; ++first, ++it)
	{
		if (p(*first, *it))
			return first;
	}
	return last;
}

template< class ForwardIt1, class ForwardIt2 >
ForwardIt1 search(ForwardIt1 first, ForwardIt1 last,
	ForwardIt2 s_first, ForwardIt2 s_last)
{
	typedef typename type_traits<ForwardIt1>::difference_type difference_type;
	difference_type d1, d2;
	d1 = distance(first, last);
	d2 = distance(s_first, s_last);
	if (d1 < d2)
		return last;
	ForwardIt1 it = first;
	ForwardIt2 s_it = s_first;

	while (s_it != s_last)
	{
		if (*it == *s_it)
		{
			++it;
			++s_it; 
		}
		else
		{
			if (d1 == d2)
				return last;
			else
			{
				it = ++first;
				s_it = s_first;
				--d1;
			}
		}
	}
}

template< class ForwardIt1, class ForwardIt2, class BinaryPredicate >
ForwardIt1 search(ForwardIt1 first, ForwardIt1 last,
	ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate p)
{
	typename type_traits<ForwardIt1>::difference_type d1;
	typename type_traits<ForwardIt2>::difference_type d2;
	d1 = distance(first, last);
	d2 = distance(s_first, s_last);
	if (d1 < d2)
		return last;
	ForwardIt1 it = first;
	ForwardIt2 s_it = s_first;

	while (s_it != s_last)
	{
		if (p(*it, *s_it))
		{
			++it;
			++s_it;
		}
		else
		{
			if (d1 == d2)
				return last;
			else
			{
				it = ++first;
				s_it = s_first;
				--d1;
			}
		}
	}
}

template< class ForwardIt, class Size, class T >
ForwardIt search_n(ForwardIt first, ForwardIt last, Size count, const T& value)
{
	if (count <= 0)
		return first;
	else
	{
		first = find(first, last, value);
		while (first != last)
		{
			Size n = count - 1;
			ForwardIt i = first;
			++i;
			while (i != last && n != 0 && *i == value)
			{
				++i;
				--n;
			}
			if (n == 0)
				return first;
			else
				first = find(i, last, value);
		}
		return last;
	}
}

template< class ForwardIt, class Size, class T, class BinaryPredicate >
ForwardIt search_n(ForwardIt first, ForwardIt last, Size count, const T& value,
	BinaryPredicate p)
{
	if (count <= 0)
		return first;
	else
	{
		first = find(first, last, value, p);
		while (first != last)
		{
			Size n = count - 1;
			ForwardIt i = first;
			++i;
			while (i != last && n != 0 && p(*i, value))
			{
				++i;
				--n;
			}
			if (n == 0)
				return first;
			else
				first = find(i, last, value, p);
		}
		return last;
	}
}


//Modifying sequence operations
template< class InputIt, class OutputIt >
OutputIt copy(InputIt first, InputIt last, OutputIt d_first)
{
	if (distance(first, last) > 0)
		return __copy(first, last, d_first, iterator_category(first));
	else
		return d_first;
}

template< class BidIt1, class BidIt2 >
BidIt2 copy_backward(BidIt1 first, BidIt1 last, BidIt2 d_last)
{
	while (first != last) {
		*(--d_last) = *(--last);
	}
	return d_last;
}

template< class ForwardIt, class T >
void fill(ForwardIt first, ForwardIt last, const T& value)
{
	for (; first != last; ++first)
		*first = value;
}

template< class OutputIt, class Size, class T >
void fill_n(OutputIt first, Size count, const T& value)
{
	for (; count > 0; --count, ++first)
		*first = value;
}

template< class InputIt, class OutputIt, class UnaryOperation >
OutputIt transform(InputIt first, InputIt last, OutputIt d_first,
	UnaryOperation unary_op)
{
	for (; first != last; ++first, ++d_first)
		*d_first = unary_op(first);
	return d_first;
}

template< class InputIt1, class InputIt2, class OutputIt, class BinaryOperation >
OutputIt transform(InputIt1 first1, InputIt1 last, InputIt2 first2,
	OutputIt d_first, BinaryOperation binary_op)
{
	for (; first1 != last; ++first1, ++first2, ++d_first)
		*d_first = binary_op(first1, first2);
	return d_first;
}

template< class ForwardIt, class Generator >
void generate(ForwardIt first, ForwardIt last, Generator g)
{
	for (; first != last; ++first)
		*first = g();
}

template< class OutputIt, class Size, class Generator >
void generate_n(OutputIt first, Size count, Generator g)
{
	for (; count > 0; --count, ++first)
		first = g();
}

template< class ForwardIt, class T >
ForwardIt remove(ForwardIt first, ForwardIt last, const T& value)
{
	first = find(first, last, value);
	ForwardIt next = first;
	return first = last ? first : remove_copy(++next, last, first, value);
}

template< class ForwardIt, class UnaryPredicate >
ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPredicate p)
{
	first = find_if(first, last, p);
	ForwardIt next = first;
	return first = last ? first : remove_copy_if(++next, last, first, p);
}

template< class InputIt, class OutputIt, class T >
OutputIt remove_copy(InputIt first, InputIt last, OutputIt d_first,
	const T& value)
{
	for (; first != last; ++first)
	{
		if (*first != value)
		{
			*d_first = *first;
			++d_first;
		}
	}
	return d_first;
}

template< class InputIt, class OutputIt, class UnaryPredicate >
OutputIt remove_copy_if(InputIt first, InputIt last, OutputIt d_first,
	UnaryPredicate p)
{
	for (; first != last; ++first)
	{
		if (!p(*first))
		{
			*d_first = *first;
			++d_first;
		}
	}
}

template< class ForwardIt, class T >
void replace(ForwardIt first, ForwardIt last, const T& old_value, const T& new_value)
{
	for (; first != last; ++first)
	{
		if (*first == old_value)
			*first = new_value;
	}
}

template< class ForwardIt, class UnaryPredicate, class T >
void replace_if(ForwardIt first, ForwardIt last, UnaryPredicate p, const T& new_value)
{
	for (; first != last; ++first)
	{
		if (p(*first))
			*first = new_value;
	}
}

template< class InputIt, class OutputIt, class T >
OutputIt replace_copy(InputIt first, InputIt last, OutputIt d_first,
	const T& old_value, const T& new_value)
{
	for (; first != last; ++first, ++d_first)
	{
		*first = old_value ? new_value : *first;
		*d_first = *first;
	}
}

template< class InputIt, class OutputIt, class UnaryPredicate, class T >
OutputIt replace_copy_if(InputIt first, InputIt last, OutputIt d_first,
	UnaryPredicate p, const T& new_value)
{
	for (; first != last; ++first, ++d_first)
	{
		*first = p(*first) ? new_value : *first;
		*d_first = *first;
	}
}

template< class T >
void swap(T& a, T& b)
{
	T temp;
	temp = a;
	a = b;
	b = temp;
}

template< class ForwardIt1, class ForwardIt2 >
ForwardIt2 swap_ranges(ForwardIt1 first1, ForwardIt1 last, ForwardIt2 first2)
{
	for (; first1 != last; ++first1, ++first2)
		iter_swap(first1, first2);
}

template< class ForwardIt1, class ForwardIt2 >
void iter_swap(ForwardIt1 a, ForwardIt2 b)
{
	swap(*a, *b);
}

template< class BidIt >
void reverse(BidIt first, BidIt last)
{
	__reverse(first, last, iterator_category(first));
}

template< class BidIt, class OutputIt >
OutputIt reverse_copy(BidIt first, BidIt last, OutputIt d_first)
{
	while (first != last)
	{
		--last;
		*d_first = *last;
		++d_first;
	}
	return d_first;
}

template< class ForwardIt >
void rotate(ForwardIt first, ForwardIt middle, ForwardIt last)
{
	if (first == middle || middle == last) return;
	__rotate(first, middle, last, 
		difference_type(first), iterator_category(first));
}

template< class ForwardIt, class OutputIt >
OutputIt rotate_copy(ForwardIt first, ForwardIt middle,
	ForwardIt last, OutputIt d_first)
{
	return copy(first, middle, copy(middle, last, d_first));
}

template< class ForwardIt >
ForwardIt unique(ForwardIt first, ForwardIt last)
{
	first = adjacent_find(first, last);
	return unique_copy(first, last, first);
}

template< class ForwardIt, class BinaryPredicate >
ForwardIt unique(ForwardIt first, ForwardIt last, BinaryPredicate p)
{
	first = adjacent_find(first, last, p);
	return unique_copy(first, last, first, p);
}

template< class InputIt, class OutputIt >
OutputIt unique_copy(InputIt first, InputIt last, OutputIt d_first)
{
	typedef typename iterator_traits<InputIt>::value_type value_type;
	return __unique_copy(first, last, d_first, 
		less<value_type>(), iterator_category(first));
}

template< class InputIt, class OutputIt, class BinaryPredicate >
OutputIt unique_copy(InputIt first, InputIt last, 
	OutputIt d_first, BinaryPredicate p)
{
	return __unique_copy(first, last, d_first, p, 
		iterator_category(first));
}



//Partitioning operations
template< class BidIt, class UnaryPredicate >
BidIt partition(BidIt first, BidIt last, UnaryPredicate p)
{
	while (first < last)
	{
		while (first < last && p(*first))
			++first;
		if (first == last--) break;
		while (first < last && !p(*last))
			--last;
		if (first == last) break;
		iter_swap(first, last);
	}
	return first;
}

template< class BidIt, class UnaryPredicate >
BidIt stable_partition(BidIt first, BidIt last, UnaryPredicate p)
{
	//TODO	
}


//Sorting operations
template< class RanIt >
void sort(RanIt first, RanIt last)
{
	//TODO
}

template< class RanIt, class Compare >
void sort(RanIt first, RanIt last, Compare comp)
{
	//TODO
}

template< class RanIt >
void partial_sort(RanIt first, RanIt middle, RanIt last)
{
	//TODO
}

template< class RanIt, class Compare >
void partial_sort(RanIt first, RanIt middle, RanIt last, Compare comp)
{
	//TODO
}

template< class InputIt, class RanIt >
RanIt partial_sort_copy(InputIt first, InputIt last, RanIt d_first, RanIt d_last)
{
	//TODO
}

template< class InputIt, class RanIt, class Compare >
RanIt partial_sort_copy(InputIt first, InputIt last,
	RanIt d_first, RanIt d_last, Compare comp)
{
	//TODO
}

template< class RanIt >
void stable_sort(RanIt first, RanIt last)
{
	//TODO
}

template< class RanIt, class Compare >
void stable_sort(RanIt first, RanIt last, Compare comp)
{
	//TODO
}

template< class RanIt >
void nth_element(RanIt first, RanIt nth, RanIt last)
{
	//TODO
}

template< class RanIt, class Compare >
void nth_element(RanIt first, RanIt nth, RanIt last, Compare comp)
{
	//TODO
}


//Binary search operations(on sorted ranges)
template< class ForwardIt, class T >
ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T& value)
{
	typedef typename iterator_traits<ForwardIt>::difference_type difference_type;

	difference_type len, half;
	ForwardIt mid;

	len = distance(first, last);
	while (len > 0)
	{
		half = len >> 2;
		mid = first;
		advance(mid, half);
		if (*mid < value)
		{
			first = mid;
			++first;
			len = len - half - 1;
		}
		else
			len = half;
	}
	return first;
}

template< class ForwardIt, class T, class Compare >
ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T& value, Compare comp)
{
	//TODO
}

template< class ForwardIt, class T >
ForwardIt upper_bound(ForwardIt first, ForwardIt last, const T& value)
{
	//TODO
}

template< class ForwardIt, class T, class Compare >
ForwardIt upper_bound(ForwardIt first, ForwardIt last, const T& value, Compare comp)
{
	//TODO
}

template< class ForwardIt, class T >
bool binary_search(ForwardIt first, ForwardIt last, const T& value)
{
	//TODO
}

template< class ForwardIt, class T, class Compare >
bool binary_search(ForwardIt first, ForwardIt last, const T& value, Compare comp)
{
	//TODO
}

template< class ForwardIt, class T >
pair<ForwardIt, ForwardIt>
equal_range(ForwardIt first, ForwardIt last, const T& value)
{
	//TODO
}

template< class ForwardIt, class T, class Compare >
pair<ForwardIt, ForwardIt>
equal_range(ForwardIt first, ForwardIt last, const T& value, Compare comp)
{
	//TODO
}


//Set operations(on sorted ranges)
template< class InputIt1, class InputIt2, class OutputIt >
OutputIt merge(InputIt1 first1, InputIt1 last1,
	InputIt2 first2, InputIt2 last2, OutputIt d_first)
{
	//TODO
}

template< class InputIt1, class InputIt2, class OutputIt, class Compare>
OutputIt merge(InputIt1 first1, InputIt1 last1,
	InputIt2 first2, InputIt2 last2, OutputIt d_first, Compare comp)
{
	//TODO
}

template< class BidIt >
void inplace_merge(BidIt first, BidIt middle, BidIt last)
{
	//TODO
}

template< class BidIt, class Compare>
void inplace_merge(BidIt first, BidIt middle, BidIt last, Compare comp)
{
	//TODO
}

template< class InputIt1, class InputIt2 >
bool includes(InputIt1 first1, InputIt1 last1,
	InputIt2 first2, InputIt2 last2)
{
	//TODO
}

template< class InputIt1, class InputIt2, class Compare >
bool includes(InputIt1 first1, InputIt1 last1,
	InputIt2 first2, InputIt2 last2, Compare comp)
{
	//TODO
}

template< class InputIt1, class InputIt2, class OutputIt >
OutputIt set_difference(InputIt1 first1, InputIt1 last1,
	                    InputIt2 first2, InputIt2 last2,
	                    OutputIt d_first)
{
	//TODO
}

template< class InputIt1, class InputIt2,
class OutputIt, class Compare >
OutputIt set_difference(InputIt1 first1, InputIt1 last1,
	                    InputIt2 first2, InputIt2 last2,
	                    OutputIt d_first, Compare comp)
{
	//TODO
}

template< class InputIt1, class InputIt2, class OutputIt >
OutputIt set_intersection(InputIt1 first1, InputIt1 last1,
	                      InputIt2 first2, InputIt2 last2,
	                      OutputIt d_first)
{
	//TODO
}

template< class InputIt1, class InputIt2,
class OutputIt, class Compare >
OutputIt set_intersection(InputIt1 first1, InputIt1 last1,
	                      InputIt2 first2, InputIt2 last2,
	                      OutputIt d_first, Compare comp)
{
	//TODO
}

template< class InputIt1, class InputIt2, class OutputIt >
OutputIt set_symmetric_difference(InputIt1 first1, InputIt1 last1,
	                              InputIt2 first2, InputIt2 last2,
	                              OutputIt d_first)
{
	//TODO
}

template< class InputIt1, class InputIt2,
class OutputIt, class Compare >
OutputIt set_symmetric_difference(InputIt1 first1, InputIt1 last1,
	                              InputIt2 first2, InputIt2 last2,
	                              OutputIt d_first, Compare comp)
{
	//TODO
}

template< class InputIt1, class InputIt2, class OutputIt >
OutputIt set_union(InputIt1 first1, InputIt1 last1,
	               InputIt2 first2, InputIt2 last2,
	               OutputIt d_first)
{
	//TODO
}

template< class InputIt1, class InputIt2,
class OutputIt, class Compare >
OutputIt set_union(InputIt1 first1, InputIt1 last1,
	               InputIt2 first2, InputIt2 last2,
	               OutputIt d_first, Compare comp)
{
	//TODO
}

//Heap operations
template< class RanIt >
void make_heap(RanIt first, RanIt last)
{
	//TODO
}

template< class RanIt, class Compare >
void make_heap(RanIt first, RanIt last, Compare comp)
{
	//TODO
}

template< class RanIt >
void push_heap(RanIt first, RanIt last)
{
	//TODO
}

template< class RanIt, class Compare >
void push_heap(RanIt first, RanIt last, Compare comp)
{
	//TODO
}

template< class RanIt >
void pop_heap(RanIt first, RanIt last)
{
	//TODO
}

template< class RanIt, class Compare >
void pop_heap(RanIt first, RanIt last, Compare comp)
{
	//TODO
}

template< class RanIt >
void sort_heap(RanIt first, RanIt last)
{
	//TODO
}

template< class RanIt, class Compare >
void sort_heap(RanIt first, RanIt last, Compare comp)
{
	//TODO
}



//Minimum/maximum operations
template< class T >
const T& max(const T& a, const T& b)
{
	return a > b ? a : b;
}

template< class T, class Compare >
const T& max(const T& a, const T& b, Compare comp)
{
	return comp(a, b) ? a : b;
}

template< class ForwardIt >
ForwardIt max_element(ForwardIt first, ForwardIt last)
{
	//TODO
}

template< class ForwardIt, class Compare >
ForwardIt max_element(ForwardIt first, ForwardIt last, Compare cmp)
{
	//TODO
}

template< class T >
const T& min(const T& a, const T& b)
{
	//TODO
}

template< class T, class Compare >
const T& min(const T& a, const T& b, Compare comp)
{
	//TODO
}

template< class ForwardIt >
ForwardIt min_element(ForwardIt first, ForwardIt last)
{
	//TODO
}

template< class ForwardIt, class Compare >
ForwardIt min_element(ForwardIt first, ForwardIt last, Compare comp)
{
	//TODO
}

template< class InputIt1, class InputIt2 >
bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
	                         InputIt2 first2, InputIt2 last2)
{
	//TODO
}

template< class InputIt1, class InputIt2, class Compare >
bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
	                         InputIt2 first2, InputIt2 last2,Compare comp)
{
	//TODO
}

template< class BidIt >
bool next_permutation(BidIt first, BidIt last)
{
	//TODO
}

template< class BidIt, class Compare >
bool next_permutation(BidIt first, BidIt last, Compare comp)
{
	//TODO
}

template< class BidIt >
bool prev_permutation(BidIt first, BidIt last)
{
	//TODO
}

template< class BidIt, class Compare >
bool prev_permutation(BidIt first, BidIt last, Compare comp)
{
	//TODO
}


//Numeric operations
template< class InputIt, class T >
T accumulate(InputIt first, InputIt last, T init)
{
	//TODO
}

template< class InputIt, class T, class BinaryOperation >
T accumulate(InputIt first, InputIt last, T init, BinaryOperation op)
{
	//TODO
}

}

#endif
