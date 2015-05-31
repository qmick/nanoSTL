#ifndef __NANO_SKIPLIST_HPP_
#define __NANO_SKIPLIST_HPP_

#include "../iterator.hpp"
#include "../memory.hpp"
#include "../utility.hpp"
#include <cstddef>

namespace nano {

template< class Value >
struct skiplist_node
{
	skiplist_node<Value> *previous;
	skiplist_node<Value> *forward[1];
	Value value;
};

template< class Value, class Ref, class Ptr >
struct skiplist_iterator 
{
	typedef skiplist_node<Value>* node_ptr;
	typedef Value value_type;
	typedef Ref reference;
	typedef Ptr pointer;
	typedef ptrdiff_t difference_type;
	typedef skiplist_iterator<Value, Value&, Value*> iterator;
	typedef skiplist_iterator<Value, const Value&, const Value*> const_iterator;
	typedef skiplist_iterator<Value, Ref, Ptr> my_type;
};

template< class Key, class Value, class Compare, class Allocator >
class skiplist
{
public:
	//base type
	typedef skiplist_node<Key> list_node;
	typedef list_node* node_ptr;
	typedef Key key_type;
	typedef Value value_type;
	typedef Key* pointer;
	typedef const Key* const_pointer;
	typedef Key& reference;
	typedef const Key& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	//iterator
	typedef skiplist_iterator<value_type, reference, pointer> iterator;
	typedef skiplist_iterator<value_type, const_reference, const_pointer> const_iterator;
	typedef nano::reverse_iterator<iterator> reverse_iterator;
	typedef nano::reverse_iterator<const_iterator> const_reverse_iterator;

	//rebind allocator
	typedef typename Allocator::template rebind<list_node>::other node_allocator;
	typedef simple_allocator<list_node, node_allocator> list_allocator;

	typedef skiplist<Key, Value, Compare, Allocator> my_type;

public:
	skiplist(const Compare& comp = Compare())
	{
		//TODO
	}

	skiplist(const my_type& other)
	{
		//TODO
	}

	~skiplist()
	{
		//TODO
	}

	my_type& operator=(const my_type& other)
	{
		//TODO
	}

public:
	Compare value_comp() const
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
		//TODO
	}

	const_iterator end() const
	{
		//TODO
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}

	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(end());
	}

	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}

	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(begin());
	}

	iterator empty() const
	{
		//TODO
	}

	size_type size() const
	{
		//TODO
	}

	size_type max_size() const
	{
		return size_type(-1);
	}

	void swap(my_type& other)
	{
		//TODO
	}

public:
	pair<iterator, bool> insert_unique(const value_type& v)
	{
		//TODO
	}

	iterator insert_equal(const value_type& v)
	{
		//TODO
	}

	void erase(iterator pos)
	{
		//TODO
	}

	void erase(iterator first, iterator last)
	{
		//TODO
	}

	size_type erase(const value_type &x)
	{
		//TODO
	}

	pair<iterator, iterator> equal_range(const Key& key)
	{
		return pair<iterator, iterator>(lower_bound(key), upper_bound(key));
	}

	pair<iterator, iterator> equal_range(const Key& key) const
	{
		pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
	}

	iterator lower_bound(const Key& key)
	{
		//TODO
	}

	const_iterator lower_bound(const Key& key) const
	{
		//TODO
	}

	iterator upper_bound(const Key& key)
	{
		//TODO
	}

	const_iterator upper_bound(const Key& key) const
	{
		//TODO
	}

	size_type count(const Key& key) const
	{
		//TODO
	}

	iterator find(const Key& key)
	{
		//TODO
	}

	const_iterator find(const Key& key) const
	{
		//TODO
	}

	void clear()
	{
		//TODO
	}
};

}

#endif
