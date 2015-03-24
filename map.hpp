#ifndef __MAP_HPP__
#define __MAP_HPP__


#include "memory.hpp"
#include "iterator.hpp"
#include "utility.hpp"
#include "functional.hpp"

#ifdef USE_AVL_TREE
#include "nano/AVL_tree.hpp"
#else
#include "nano/rb_tree.hpp"
#endif

namespace nano
{

template< class Key,
		  class T,
		  class Compare = less<Key>, 
		  class Allocator = allocator<pair<const Key, T> > > 
class map
{
public:
#ifdef USE_AVL_TREE
	typedef AVL_tree<Key, T, Compare, Allocator> search_tree;
#else
	typedef rb_tree<Key, T, Compare, Allocator> search_tree;
#endif
	typedef Key key_type;
	typedef T mapped_type;
	typedef pair<const Key, T> value_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef Compare key_compare;
	typedef Allocator allocator_type;
	typedef typename Allocator::reference reference;
	typedef typename Allocator::const_reference const_reference;
	typedef typename Allocator::pointer pointer;
	typedef typename Allocator::const_pointer const_pointer;
	typedef nano::iterator<bidirectional_iterator_tag, T> iterator;
	typedef nano::iterator<bidirectional_iterator_tag, T, const T*, const T&> const_iterator;
	typedef nano::reverse_iterator<iterator> reverse_iterator;
	typedef nano::reverse_iterator<const_iterator> const_reverse_iterator;
	typedef map<Key, T, Compare, Allocator> my_type;

public:
	map(){}

	template< class InputIt >
	map(InputIt first, InputIt last)
	{
		//TODO
	}

	map(const my_type& other)
	{

	}

	my_type& operator=(const my_type& other)
	{
		//TODO
	}

	allocator_type get_allocator() const
	{
		return Allocator();
	}

	T& operator[](const Key& key)
	{
		//TODO
	}

	iterator begin()
	{
		//TODO
	}

	const_iterator begin() const
	{
		//TODO
	}

	iterator end()
	{

	}
	const_iterator end() const
	{

	}

	reverse_iterator rbegin()
	{

	}
	const_reverse_iterator rbegin() const
	{

	}

	reverse_iterator rend()
	{

	}
	const_reverse_iterator rend() const
	{

	}

	bool empty() const
	{

	}

	size_type size() const
	{

	}

	size_type max_size() const
	{

	}

	void clear()
	{

	}

	pair<iterator, bool> insert(const value_type& value)
	{

	}

	iterator insert(iterator hint, const value_type& value)
	{

	}

	template< class InputIt >
	void insert(InputIt first, InputIt last)
	{

	}

	void erase(iterator pos)
	{

	}

	void swap(map& other)
	{

	}

	size_type count(const Key& key) const
	{

	}

	iterator find(const Key& key)
	{

	}
	const_iterator find(const Key& key) const
	{

	}

	pair<iterator, iterator> equal_range(const Key& key)
	{

	}

	pair<const_iterator, const_iterator> equal_range(const Key& key) const
	{

	}

	iterator lower_bound(const Key& key)
	{

	}

	const_iterator lower_bound(const Key& key) const
	{

	}

	iterator upper_bound(const Key& key)
	{

	}

	const_iterator upper_bound(const Key& key) const
	{

	}

	key_compare key_comp() const
	{

	}

private:
	search_tree tree;
};

template< class Key, class T, class Compare, class Alloc >
void swap(map<Key, T, Compare, Alloc>& lhs,
	map<Key, T, Compare, Alloc>& rhs)
{

}

}

#endif