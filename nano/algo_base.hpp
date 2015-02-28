#ifndef __ALGO_BASE_HPP__
#define __ALGO_BASE_HPP__

#include "../iterator.hpp"

namespace nano {

template< class ForwardIt1, class ForwardIt2 >
ForwardIt1 __find_end(ForwardIt1 first, ForwardIt1 last,
	ForwardIt2 s_first, ForwardIt2 s_last,
	bidirectional_iterator_tag, bidirectional_iterator_tag)
{
	
}

template< class ForwardIt1, class ForwardIt2 >
ForwardIt1 __find_end(ForwardIt1 first, ForwardIt1 last,
	ForwardIt2 s_first, ForwardIt2 s_last,
	forward_iterator_tag, forward_iterator_tag)
{

}

}

#endif
