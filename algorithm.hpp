#ifndef __ALGORITHM__
#define __ALGORITHM__

#include "iterator.hpp"
#include "utility.hpp"
#include "nano/algo_base.hpp"

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
	//TODO
}

template< class ForwardIt1, class ForwardIt2 >
ForwardIt1 find_first_of(ForwardIt1 first, ForwardIt1 last,
	ForwardIt2 s_first, ForwardIt2 s_last)
{
	//TODO
}

template< class ForwardIt1, class ForwardIt2, class BinaryPredicate >
ForwardIt1 find_first_of(ForwardIt1 first, ForwardIt1 last,
	ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate p)
{
	//TODO
}

template< class ForwardIt >
ForwardIt adjacent_find(ForwardIt first, ForwardIt last)
{
	//TODO
}

template< class ForwardIt, class BinaryPredicate>
ForwardIt adjacent_find(ForwardIt first, ForwardIt last, BinaryPredicate p)
{
	//TODO
}

template< class ForwardIt1, class ForwardIt2 >
ForwardIt1 search(ForwardIt1 first, ForwardIt1 last,
	ForwardIt2 s_first, ForwardIt2 s_last)
{
	//TODO
}

template< class ForwardIt1, class ForwardIt2, class BinaryPredicate >
ForwardIt1 search(ForwardIt1 first, ForwardIt1 last,
	ForwardIt2 s_first, ForwardIt2 s_last, BinaryPredicate p)
{
	//TODO
}

template< class ForwardIt, class Size, class T >
ForwardIt search_n(ForwardIt first, ForwardIt last, Size count, const T& value)
{
	//TODO
}

template< class ForwardIt, class Size, class T, class BinaryPredicate >
ForwardIt search_n(ForwardIt first, ForwardIt last, Size count, const T& value,
	BinaryPredicate p)
{
	//TODO
}


//Modifying sequence operations
template< class InputIt, class OutputIt >
OutputIt copy(InputIt first, InputIt last, OutputIt d_first)
{
	//TODO
}

template< class BidirIt1, class BidirIt2 >
BidirIt2 copy_backward(BidirIt1 first, BidirIt1 last, BidirIt2 d_last)
{
	//TODO
}

template< class ForwardIt, class T >
void fill(ForwardIt first, ForwardIt last, const T& value)
{
	//TODO
}

template< class OutputIt, class Size, class T >
void fill_n(OutputIt first, Size count, const T& value)
{
	//TODO
}

template< class InputIt, class OutputIt, class UnaryOperation >
OutputIt transform(InputIt first1, InputIt last1, OutputIt d_first,
	UnaryOperation unary_op)
{
	//TODO
}

template< class InputIt1, class InputIt2, class OutputIt, class BinaryOperation >
OutputIt transform(InputIt1 first1, InputIt1 last1, InputIt2 first2,
	OutputIt d_first, BinaryOperation binary_op)
{
	//TODO
}

template< class ForwardIt, class Generator >
void generate(ForwardIt first, ForwardIt last, Generator g)
{
	//TODO
}

template< class OutputIt, class Size, class Generator >
void generate_n(OutputIt first, Size count, Generator g)
{
	//TODO
}

template< class ForwardIt, class T >
ForwardIt remove(ForwardIt first, ForwardIt last, const T& value)
{
	//TODO
}

template< class ForwardIt, class UnaryPredicate >
ForwardIt remove_if(ForwardIt first, ForwardIt last, UnaryPredicate p)
{
	//TODO
}

template< class InputIt, class OutputIt, class T >
OutputIt remove_copy(InputIt first, InputIt last, OutputIt d_first,
	const T& value)
{
	//TODO
}

template< class InputIt, class OutputIt, class UnaryPredicate >
OutputIt remove_copy_if(InputIt first, InputIt last, OutputIt d_first,
	UnaryPredicate p)
{
	//TODO
}

template< class ForwardIt, class T >
void replace(ForwardIt first, ForwardIt last, const T& old_value, const T& new_value)
{
	//TODO
}

template< class ForwardIt, class UnaryPredicate, class T >
void replace_if(ForwardIt first, ForwardIt last, UnaryPredicate p, const T& new_value)
{
	//TODO
}

template< class InputIt, class OutputIt, class T >
OutputIt replace_copy(InputIt first, InputIt last, OutputIt d_first,
	const T& old_value, const T& new_value)
{
	//TODO
}

template< class InputIt, class OutputIt, class UnaryPredicate, class T >
OutputIt replace_copy_if(InputIt first, InputIt last, OutputIt d_first,
	UnaryPredicate p, const T& new_value)
{
	//TODO
}

template< class T >
void swap(T& a, T& b)
{
	//TODO
}

template< class ForwardIt1, class ForwardIt2 >
ForwardIt2 swap_ranges(ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2)
{
	//TODO
}

template< class ForwardIt1, class ForwardIt2 >
void iter_swap(ForwardIt1 a, ForwardIt2 b)
{
	//TODO
}

template< class BidirIt >
void reverse(BidirIt first, BidirIt last)
{
	//TODO
}

template< class BidirIt, class OutputIt >
OutputIt reverse_copy(BidirIt first, BidirIt last, OutputIt d_first)
{
	//TODO
}

template< class ForwardIt >
void rotate(ForwardIt first, ForwardIt n_first, ForwardIt last)
{
	//TODO
}

template< class ForwardIt, class OutputIt >
OutputIt rotate_copy(ForwardIt first, ForwardIt n_first,
	ForwardIt last, OutputIt d_first)
{
	//TODO
}

template< class ForwardIt >
ForwardIt unique(ForwardIt first, ForwardIt last)
{
	//TODO
}

template< class ForwardIt, class BinaryPredicate >
ForwardIt unique(ForwardIt first, ForwardIt last, BinaryPredicate p)
{
	//TODO
}

template< class InputIt, class OutputIt >
OutputIt unique_copy(InputIt first, InputIt last, OutputIt d_first)
{
	//TODO
}

template< class InputIt, class OutputIt, class BinaryPredicate >
OutputIt unique_copy(InputIt first, InputIt last, OutputIt d_first, BinaryPredicate p)
{
	//TODO
}



//Partitioning operations
template< class BidirIt, class UnaryPredicate >
BidirIt partition(BidirIt first, BidirIt last, UnaryPredicate p)
{
	//TODO
}

template< class BidirIt, class UnaryPredicate >
BidirIt stable_partition(BidirIt first, BidirIt last, UnaryPredicate p)
{
	//TODO
}


//Sorting operations
template< class RandomIt >
void sort(RandomIt first, RandomIt last)
{
	//TODO
}

template< class RandomIt, class Compare >
void sort(RandomIt first, RandomIt last, Compare comp)
{
	//TODO
}

template< class RandomIt >
void partial_sort(RandomIt first, RandomIt middle, RandomIt last)
{
	//TODO
}

template< class RandomIt, class Compare >
void partial_sort(RandomIt first, RandomIt middle, RandomIt last, Compare comp)
{
	//TODO
}

template< class InputIt, class RandomIt >
RandomIt partial_sort_copy(InputIt first, InputIt last, RandomIt d_first, RandomIt d_last)
{
	//TODO
}

template< class InputIt, class RandomIt, class Compare >
RandomIt partial_sort_copy(InputIt first, InputIt last,
	RandomIt d_first, RandomIt d_last, Compare comp)
{
	//TODO
}

template< class RandomIt >
void stable_sort(RandomIt first, RandomIt last)
{
	//TODO
}

template< class RandomIt, class Compare >
void stable_sort(RandomIt first, RandomIt last, Compare comp)
{
	//TODO
}

template< class RandomIt >
void nth_element(RandomIt first, RandomIt nth, RandomIt last)
{
	//TODO
}

template< class RandomIt, class Compare >
void nth_element(RandomIt first, RandomIt nth, RandomIt last, Compare comp)
{
	//TODO
}


//Binary search operations(on sorted ranges)
template< class ForwardIt, class T >
ForwardIt lower_bound(ForwardIt first, ForwardIt last, const T& value)
{
	//TODO
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

template< class BidirIt >
void inplace_merge(BidirIt first, BidirIt middle, BidirIt last)
{
	//TODO
}

template< class BidirIt, class Compare>
void inplace_merge(BidirIt first, BidirIt middle, BidirIt last, Compare comp)
{
	//TODO
}

template< class InputIt1, class InputIt2 >
bool includes(InputIt1 first1, InputIt1 last1,
	InputIt2 first2, InputIt2 last2)
{
	//TODO
}

template< class InputIt1, class InputIt2 >
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
template< class RandomIt >
void make_heap(RandomIt first, RandomIt last)
{
	//TODO
}

template< class RandomIt, class Compare >
void make_heap(RandomIt first, RandomIt last, Compare comp)
{
	//TODO
}

template< class RandomIt >
void push_heap(RandomIt first, RandomIt last)
{
	//TODO
}

template< class RandomIt, class Compare >
void push_heap(RandomIt first, RandomIt last, Compare comp)
{
	//TODO
}

template< class RandomIt >
void pop_heap(RandomIt first, RandomIt last)
{
	//TODO
}

template< class RandomIt, class Compare >
void pop_heap(RandomIt first, RandomIt last, Compare comp)
{
	//TODO
}

template< class RandomIt >
void sort_heap(RandomIt first, RandomIt last)
{
	//TODO
}

template< class RandomIt, class Compare >
void sort_heap(RandomIt first, RandomIt last, Compare comp)
{
	//TODO
}



//Minimum/maximum operations
template< class T >
const T& max(const T& a, const T& b)
{
	//TODO
}

template< class T, class Compare >
const T& max(const T& a, const T& b, Compare comp)
{
	//TODO
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

template< class BidirIt >
bool next_permutation(BidirIt first, BidirIt last)
{
	//TODO
}

template< class BidirIt, class Compare >
bool next_permutation(BidirIt first, BidirIt last, Compare comp)
{
	//TODO
}

template< class BidirIt >
bool prev_permutation(BidirIt first, BidirIt last)
{
	//TODO
}

template< class BidirIt, class Compare >
bool prev_permutation(BidirIt first, BidirIt last, Compare comp)
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
