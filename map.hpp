#ifndef __MAP_HPP__
#define __MAP_HPP__

#include "memory.hpp"
#include "iterator.hpp"
#include "utility.hpp"

namespace nano
{

template< class Key,
		  class T,
		  class Compare, 
		  class Allocator = nano::allocator<nano::pair<const Key, T> > > 
class map
{
public:
	typedef Key key_type;
	typedef T mapped_type;
	typedef nano::pair<const Key, T> value_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef Compare key_compare;
	typedef Allocator allocator_type;
	typedef typename Allocator::reference reference;
	typedef typename Allocator::const_reference const_reference;
	typedef typename Allocator::pointer pointer;
	typedef typename Allocator::const_pointer const_pointer;
	typedef nano::iterator<nano::bidirectional_iterator_tag, T> iterator;
	typedef nano::iterator<nano::bidirectional_iterator_tag, T, const T*, const T&> const_iterator;
	typedef nano::reverse_iterator<iterator> reverse_iterator;
	typedef nano::reverse_iterator<const_iterator> const_reverse_iterator;

};

}

#endif