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

	typedef Key key_type;
	typedef Value mapped_type;
	typedef pair<const Key, Value> value_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef Compare key_compare;
	typedef Allocator allocator_type;

	//Compare two pairs according to their first element
	struct comp_pair
	{
		Compare compare;
		comp_pair(Compare comp = Compare())
			: compare(comp) {}
		bool operator()(const value_type& lhs, const value_type& rhs) const
		{
			return compare(lhs.first, rhs.first);
		}
	};

#ifdef USE_AVL_TREE
	typedef AVL_tree<Key, Value, Compare, Allocator> search_tree;
#else
	typedef rb_tree<value_type, comp_pair, Allocator> search_tree;
#endif

	typedef typename search_tree::reference reference;
	typedef typename search_tree::const_reference const_reference;
	typedef typename search_tree::pointer pointer;
	typedef typename search_tree::const_pointer const_pointer;
	typedef typename search_tree::iterator iterator;
	typedef typename search_tree::const_iterator const_iterator;
	typedef typename search_tree::reverse_iterator reverse_iterator;
	typedef typename search_tree::const_reverse_iterator const_reverse_iterator;
	typedef map<Key, Value, Compare, Allocator> my_type;
	
	

public:
	explicit map(const Compare &comp = Compare()) 
		: tree(comp_pair(comp)) {}

	template< class InputIt >
	map(InputIt first, InputIt last, const Compare &comp = Compare())
		: tree(comp)
	{
		for (; first != last; ++first)
			tree.insert_unique(*first);
	}

	map(const my_type& other) : tree(other.tree) {}

	~map() { tree.clear(); }

	my_type& operator=(const my_type& other)
	{
		tree = other.tree;
		return *this;
	}

	allocator_type get_allocator() const
	{
		return Allocator();
	}

	mapped_type& operator[](const key_type& key)
	{
		return (*(tree.insert_unique(value_type(key, mapped_type())).first)).second;
	}

	iterator begin()
	{
		return tree.begin(); 
	}

	const_iterator begin() const
	{
		return tree.begin();
	}

	iterator end()
	{
		return tree.end();
	}
	const_iterator end() const
	{
		return tree.end();
	}

	reverse_iterator rbegin()
	{
		return tree.rbegin();
	}
	const_reverse_iterator rbegin() const
	{
		return tree.rbegin();
	}

	reverse_iterator rend()
	{
		return tree.rend();
	}
	const_reverse_iterator rend() const
	{
		return tree.rend();
	}

	bool empty() const
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

	void clear()
	{
		tree.clear();
	}

	pair<iterator, bool> insert(const value_type& value)
	{
		return tree.insert_unique(value);
	}

	template< class InputIt >
	void insert(InputIt first, InputIt last)
	{
		for (; first != last; ++last)
			tree.insert_unique(*first);
	}

	void erase(iterator pos)
	{
		tree.erase(pos);
	}

	void erase(iterator first, iterator last)
	{
		while(first != last)
		{
			iterator temp = first++;
			erase(temp);
		}
	}

	void swap(my_type& other)
	{
		tree.swap(other.tree);
	}

	size_type count(const key_type& key) const
	{
		return tree.count(value_type(key, mapped_type()));
	}

	iterator find(const key_type& key)
	{
		return tree.find(value_type(key, mapped_type()));
	}
	const_iterator find(const key_type& key) const
	{
		return tree.find(value_type(key, mapped_type()));
	}

	pair<iterator, iterator> equal_range(const key_type& key)
	{
		return tree.equal_range(value_type(key, mapped_type()));
	}

	pair<const_iterator, const_iterator> equal_range(const key_type& key) const
	{
		return tree.equal_range(value_type(key, mapped_type()));
	}

	iterator lower_bound(const key_type& key)
	{
		return tree.lower_bound(value_type(key, mapped_type()));
	}

	const_iterator lower_bound(const key_type& key) const
	{
		return tree.lower_bound(value_type(key, mapped_type()));
	}

	iterator upper_bound(const key_type& key)
	{
		return tree.upper_bound(value_type(key, mapped_type()));
	}

	const_iterator upper_bound(const key_type& key) const
	{
		return tree.upper_bound(value_type(key, mapped_type()));
	}

	key_compare key_comp() const
	{
		return tree.compare;
	}

private:
	search_tree tree;
};

template< class Key, class Value, class Compare, class Alloc >
void swap(map<Key, Value, Compare, Alloc>& lhs,
	map<Key, Value, Compare, Alloc>& rhs)
{
	lhs.swap(rhs);
}


template< class Key,
class Value,
class Compare = less<Key>,
class Allocator = allocator<pair<const Key, Value> > >
class multimap
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
	typedef multimap<Key, Value, Compare, Allocator> my_type;

	struct comp_pair
	{
		Compare compare;
		comp_pair(Compare comp = Compare()) : compare(comp) {}
		bool operator()(const value_type& lhs, const value_type& rhs) const
		{
			return comp(lhs.first, rhs.first);
		}
	};

public:
	explicit multimap(const Compare &comp = Compare()) : tree(comp_pair(comp)) {}

	template< class InputIt >
	multimap(InputIt first, InputIt last, const Compare &comp = Compare())
		: tree(comp)
	{
		for (; first != last; ++first)
			tree.insert(*first);
	}

	multimap(const my_type& other) : tree(other.tree) {}

	~multimap() { tree.clear(); }

	my_type& operator=(const my_type& other)
	{
		tree = other.tree;
		return *this;
	}

	allocator_type get_allocator() const
	{
		return Allocator();
	}

	iterator begin()
	{
		return tree.begin();
	}

	const_iterator begin() const
	{
		return tree.begin();
	}

	iterator end()
	{
		return tree.end();
	}
	const_iterator end() const
	{
		return tree.end();
	}

	reverse_iterator rbegin()
	{
		return tree.rbegin();
	}
	const_reverse_iterator rbegin() const
	{
		return tree.rbegin();
	}

	reverse_iterator rend()
	{
		return tree.end();
	}
	const_reverse_iterator rend() const
	{
		return tree.end();
	}

	bool empty() const
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

	void clear()
	{
		tree.clear();
	}

	pair<iterator, bool> insert(const value_type& value)
	{
		return tree.insert_equal(value);
	}

	template< class InputIt >
	void insert(InputIt first, InputIt last)
	{
		for (; first != last; ++last)
			tree.insert_equal(*first);
	}

	void erase(iterator pos)
	{
		tree.erase(pos);
	}

	void swap(my_type& other)
	{
		tree.swap(other.tree);
	}

	size_type count(const Key& key) const
	{
		return tree.count(key);
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

	key_compare key_comp() const
	{
		return tree.compare;
	}

private:
	search_tree tree;
};


}

#endif
