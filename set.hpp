#ifndef __SET_HPP__
#define __SET_HPP__

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

template < class Key, class Compare = less<Key>, class Allocator = allocator<Key> >
class set
{
public:
#ifdef USE_AVL_TREE
	typedef AVL_tree<Key, Compare, Allocator> search_tree;
#else
	typedef rb_tree<Key, Compare, Allocator> search_tree;
#endif
	typedef Key key_type;
	typedef Key value_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef Compare key_compare;
    typedef Compare value_compare;	
	typedef Allocator allocator_type;
	typedef typename search_tree::const_reference reference;
	typedef typename search_tree::const_reference const_reference;
	typedef typename search_tree::const_pointer pointer;
	typedef typename search_tree::const_pointer const_pointer;
	typedef typename search_tree::const_iterator iterator;
	typedef typename search_tree::const_iterator const_iterator;
	typedef typename search_tree::const_reverse_iterator reverse_iterator;
	typedef typename search_tree::const_reverse_iterator const_reverse_iterator;
	typedef set<Key, Compare, Allocator> my_type;

	explicit set(Compare comp = Compare()) : tree(comp) {}

	template< class InputIt >
	set(InputIt first, InputIt last, const Compare& comp = Compare())
		: tree(comp)
	{
		for (; first != last; ++first)
			tree.insert_unique(*first);
	}

	~set() { tree.clear(); }

	my_type& operator=(const my_type& other)
	{
		tree = other.tree;
	}

	allocator_type get_allocator() const
	{
		return Allocator();
	}

	iterator begin() const
	{
		return tree.begin();
	}

	const_iterator begin() const
	{
		return tree.begin();
	}

	iterator end() const 
	{
		return tree.end();
	}

	const_iterator end() const
	{
		return tree.end();
	}

	reverse_iterator rbegin() const
	{
		return tree.rbegin();
	}	

	const_reverse_iterator rbegin() const
	{
		return tree.rbegin();
	}

	reverse_iterator rend() const
	{
		return tree.rend();
	}

	const_reverse_iterator rend() const
	{
		return tree.rend();
	}

	//Capacity
	void empty() const
	{
		return tree.empty();
	}
	
	size_type size() const
	{
		return tree.size();
	}

	size_type max_size() const
	{
		return tree.max_size();
	}

	//Modifiers
	void clear()
	{
		tree.clear();
	}

	pair<iterator, bool> insert(const value_type& value)
	{
		return tree.insert_unique(value);
	}

	iterator insert(iterator hint, const value_type& value)
	{
		return tree.insert_unique(value);
	}

	template< class InputIt>
	void insert(InputIt first, InputIt last)
	{
		for (; first != last; ++first)
			tree.insert_unique(*first);
	}

	void erase(iterator pos)
	{
		tree.erase(pos);
	}

	void erase(iterator first, iterator last)
	{
		tree.erase(first, last);
	}

	size_type erase(const key_type& key)
	{
		tree.erase(key);
	}
	
	void swap(my_type& other)
	{
		tree.swap(other.tree);
	}
	
	//Lookup
	size_type count(const Key& key) const
	{
		return tree.count();
	}

	iterator find(const Key& key)
	{
		return tree.find(key);
	}

	const_iterator find(const Key& key) const
	{
		return tree.find(key);
	}

	pair<iterator, iterator> equal_range(const Key& key)
	{
		return tree.equal_range(key);
	}

	pair<const_iterator, const_iterator> equal_range(const Key& key) const
	{
		return tree.equal_range(key);
	}

	iterator lower_bound(const Key& key)
	{
		return tree.lower_bound(key);
	}

	const_iterator lower_bound(const Key& key) const
	{
		return tree.lower_bound(key);
	}

	iterator upper_bound(const Key& key)
	{
		return tree.upper_bound(key);
	}

	const_iterator upper_bound(const Key& key) const
	{
		return tree.upper_bound(key);
	}

	//Observers
	key_compare key_comp() const
	{
		return Compare();
	}

	value_compare value_comp() const
	{
		return Compare();
	}

private:
	search_tree tree;
};



template < class Key, class Compare = less<Key>, class Allocator = allocator<Key> >
class multiset
{
public:
#ifdef USE_AVL_TREE
	typedef AVL_tree<Key, Compare, Allocator> search_tree;
#else
	typedef rb_tree<Key, Compare, Allocator> search_tree;
#endif
	typedef Key key_type;
	typedef Key value_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef Compare key_compare;
	typedef Compare value_compare;
	typedef Allocator allocator_type;
	typedef typename search_tree::const_reference reference;
	typedef typename search_tree::const_reference const_reference;
	typedef typename search_tree::const_pointer pointer;
	typedef typename search_tree::const_pointer const_pointer;
	typedef typename search_tree::const_iterator iterator;
	typedef typename search_tree::const_iterator const_iterator;
	typedef typename search_tree::const_reverse_iterator reverse_iterator;
	typedef typename search_tree::const_reverse_iterator const_reverse_iterator;
	typedef set<Key, Compare, Allocator> my_type;

	multiset(Compare comp = Compare()) : tree(comp) {}

	~multiset()
	{
		tree.clear();
	}

	my_type& operator=(const my_type& other)
	{
		tree = other.tree;
	}

	allocator_type get_allocator() const
	{
		return Allocator();
	}

	iterator begin() const
	{
		return tree.begin();
	}

	const_iterator begin() const
	{
		return tree.begin();
	}

	iterator end() const
	{
		return tree.end();
	}

	const_iterator end() const
	{
		return tree.end();
	}

	reverse_iterator rbegin() const
	{
		return tree.rbegin();
	}

	const_reverse_iterator rbegin() const
	{
		return tree.rbegin();
	}

	reverse_iterator rend() const
	{
		return tree.rend();
	}

	const_reverse_iterator rend() const
	{
		return tree.rend();
	}

	//Capacity
	void empty() const
	{
		return tree.empty();
	}

	size_type size() const
	{
		return tree.size();
	}

	size_type max_size() const
	{
		return tree.max_size();
	}

	//Modifiers
	void clear()
	{
		tree.clear();
	}

	pair<iterator, bool> insert(const value_type& value)
	{
		return tree.insert_equal(value);
	}

	iterator insert(iterator hint, const value_type& value)
	{
		return tree.insert_equal(value);
	}

	template< class InputIt>
	void insert(InputIt first, InputIt last)
	{
		for (; first != last; ++first)
			tree.insert_equal(*first);
	}

	void erase(iterator pos)
	{
		tree.erase(pos);
	}

	void erase(iterator first, iterator last)
	{
		tree.erase(first, last);
	}

	size_type erase(const key_type& key)
	{
		tree.erase(key);
	}

	void swap(my_type& other)
	{
		tree.swap(other.tree);
	}

	//Lookup
	size_type count(const Key& key) const
	{
		return tree.count();
	}

	iterator find(const Key& key)
	{
		return tree.find(key);
	}

	const_iterator find(const Key& key) const
	{
		return tree.find(key);
	}

	pair<iterator, iterator> equal_range(const Key& key)
	{
		return tree.equal_range(key);
	}

	pair<const_iterator, const_iterator> equal_range(const Key& key) const
	{
		return tree.equal_range(key);
	}

	iterator lower_bound(const Key& key)
	{
		return tree.lower_bound(key);
	}

	const_iterator lower_bound(const Key& key) const
	{
		return tree.lower_bound(key);
	}

	iterator upper_bound(const Key& key)
	{
		return tree.upper_bound(key);
	}

	const_iterator upper_bound(const Key& key) const
	{
		return tree.upper_bound(key);
	}

	//Observers
	key_compare key_comp() const
	{
		return Compare();
	}

	value_compare value_comp() const
	{
		return Compare();
	}

private:
	search_tree tree;
};



}

#endif
