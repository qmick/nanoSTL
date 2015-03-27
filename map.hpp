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
		  class Value,
		  class Compare = less<Key>, 
		  class Allocator = allocator<pair<const Key, Value> > >
class map
{
public:
#ifdef USE_AVL_TREE
	typedef AVL_tree<Key, Value, Compare, Allocator> search_tree;
#else
	typedef rb_tree<Key, Compare, Allocator> search_tree;
#endif
	typedef Key key_type;
	typedef Value mapped_type;
	typedef pair<const Key, Value> value_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef Compare key_compare;
	typedef Allocator allocator_type;
	typedef typename search_tree::reference reference;
	typedef typename search_tree::const_reference const_reference;
	typedef typename search_tree::pointer pointer;
	typedef typename search_tree::const_pointer const_pointer;
	typedef typename search_tree::iterator iterator;
	typedef typename search_tree::const_iterator const_iterator;
	typedef typename search_tree::rreverse_iterator reverse_iterator;
	typedef typename search_tree::const_reverse_iterator const_reverse_iterator;
	typedef map<Key, Value, Compare, Allocator> my_type;

public:
	map(){}

	template< class InputIt >
	map(InputIt first, InputIt last)
	{
		
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

	Value& operator[](const Key& key)
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
	Compare comp;
};

template< class Key, class Value, class Compare, class Alloc >
void swap(map<Key, Value, Compare, Alloc>& lhs,
	map<Key, Value, Compare, Alloc>& rhs)
{

}

}

#endif