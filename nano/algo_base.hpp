#ifndef __ALGO_BASE_HPP__
#define __ALGO_BASE_HPP__

#include "../iterator.hpp"

namespace nano {

template< class BidIt1, class BidIt2 >
BidIt1 __find_end(BidIt1 first, BidIt1 last,
	BidIt2 s_first, BidIt2 s_last,
	bidirectional_iterator_tag, bidirectional_iterator_tag)
{
	typedef typename reverse_iterator<BidIt1> reviter1;
	typedef typename reverse_iterator<BidIt2> reviter2;

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
ForwardIt1 __find_end(ForwardIt1 first, ForwardIt1 last,
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
ForwardIt1 __find_end(BidIt1 first, BidIt1 last,
	BidIt2 s_first, BidIt2 s_last, BinaryPredicate p, 
	bidirectional_iterator_tag, bidirectional_iterator_tag)
{
	typedef typename reverse_iterator<BidIt1> reviter1;
	typedef typename reverse_iterator<BidIt2> reviter2;

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
ForwardIt1 __find_end(ForwardIt1 first, ForwardIt1 last,
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




}

#endif
