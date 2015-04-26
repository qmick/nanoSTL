#ifndef __NANO_HASHTABLE_HPP__
#define __NANO_HASHTABLE_HPP__

#include <cstddef>
#include "../memory.hpp"
#include "../iterator.hpp"
#include "../vector.hpp"

namespace nano
{

template< class Value >
struct list_node
{
	typedef list_node<Value>* node_ptr;
	node_ptr next;
	Value value;
};

template< class Value, class KeyEqual, class Hash, class Allocator >
class hashtable
{
	friend class hashtable_iterator<Value, Value&, Value*>;
	friend class hashtable_const_iterator<Value, Value&, Value*>;
public:
	enum{INIT_SIZE = 7};
	typedef Value value_type;
	typedef size_t size_type;
	typedef Hash hasher;
	typedef KeyEqual key_equal;
	typedef list_node<Value> node;
	typedef node* node_ptr;
	typedef hashtable_iterator<Value, Value&, Value*> iterator;
	typedef hashtable_const_iterator<Value, Value&, Value*> const_iterator;
	typedef typename Allocator::template rebind<node>::other node_allocator;
	typedef typename simple_allocator<node, node_allocator> hash_allocator;
	typedef hashtable<Value, KeyEqual, Hash, Allocator> my_type;


private:
	key_equal equals;
	hasher hash_func;
	vector<node_ptr> buckets;
	float factor;
	float max_factor;
	size_type elements_count;

public:
	explicit hashtable(size_type buckets_count = INIT_SIZE,
		const Hash& hash = Hash(), 
		const KeyEqual& equal = KeyEqual())
		: hash_func(hash), equals(key_equal), max_factor(1.0)
	{
		buckets.reserve(buckets_count);
	}

	hashtable(const my_type& other)
	{
		//TODO
	}

	~hashtable()
	{
		clear();
	}

	my_type& operator=(const my_type& other)
	{
		clear();
		hash_func = other.hash_func;
		equals = other.equals;
		factor = other.factor;
		max_factor = other.max_factor;	
		//TODO
	}


public:
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

	bool empty() const
	{
		return elements_count == 0;
	}

	size_type size() const
	{
		return elements_count;
	}

	size_type max_size() const
	{
		return size_type(-1) / sizeof(Value);
	}

	size_type buckets_count() const
	{
		return buckets.size();
	}

	size_type max_buckets_count() const
	{
		return buckets.max_size();
	}

	void clear()
	{
		for (int i = 0; i < buckets.size(); ++i)
		{
			clear_bucket(i);
		}		
		elements_count = 0;
	}

	pair<iterator, bool> insert_unique(const value_type& value)
	{
		//TODO
	}

	template< class InputIt >
	void insert_unique(InputIt first, InputIt last)
	{
		//TODO
	}

	iterator insert_equal(const value_type& value)
	{
		//TODO
	}

	template< class InputIt >
	void insert_equal(InputIt first, InputIt last)
	{
		//TODO
	}

	iterator erase(iterator pos)
	{
		//TODO
	}

	iterator erase(iterator first, iterator last)
	{
		for (; first != end; ++first)
			erase(first);
	}

	size_type erase(const value_type& value)
	{
		//TODO
	}

	void swap(my_type& other)
	{
		nano::swap(hash_func, other.hash_func);
		nano::swap(equals, other.equals);
		//TODO
	}

	value_type& at(const value_type& value)
	{
		//TODO
	}

	const value_type& at(const value_type& value)
	{
		//TODO
	}

	value_type& operator[](const value_type& value)
	{
		//TODO
	}

	pair<iterator, iterator> equal_range(const value_type& value)
	{
		//TODO
	}

	pair<const_iterator, const_iterator> equal_range(const Value& key) const
	{
		//TODO
	}

	iterator find(const value_type& value)
	{
		//TODO
	}

	const_iterator find(const value_type& value) const
	{
		//TODO
	}

	size_type count(const value_type& value) const
	{
		//TODO
	}

	float load_factor() const
	{
		//TODO
	}

	float max_load_factor() const
	{
		//TODO
	}

	void max_load_factor(float factor)
	{
		//TODO
	}

	void rehash(size_type count)
	{
		//TODO
	}

	hasher hash_function() const
	{
		return hash_func;
	}

	key_equal key_eq() const
	{
		return equals;
	}

	size_type hashcode(const value_type& value) const
	{
		return hasher(value);
	}

private:
	void clear_bucket(size_type pos)
	{
		//TODO
	}
};


template< class Value, class Ref, class Ptr >
class hashtable_iterator
{
public:
	typedef forward_iterator_tag iterator_category;
	typedef Value value_type;
	typedef Ref reference;
	typedef Ptr pointer;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef list_node<Value>* node_ptr;
	typedef hashtable_iterator<Value, Value&, Value*> iterator;
	typedef hashtable_iterator<Value, Ref, Ptr> my_type;

public:
	hashtable_iterator() {}
	hashtable_iterator(const node_ptr list_ptr, const hashtable* table)
		: list_ptr(list_ptr), table(table) {}

	bool operator==(const my_type& other) const
	{
		return list_ptr == other.list_ptr;
	}

	bool operator!=(const my_type& other) const
	{
		return list_ptr != other.list_ptr;
	}

	reference operator*()const
	{
		return list_ptr->value;
	}

	pointer operator->() const
	{
		return &(operator*());
	}

	my_type& operator++()
	{
		if (!list_ptr->next)
		{
			size_type code = table->hashcode(list_ptr->value);
			while (!list_ptr && ++code < table->buckets[code])
				list_ptr = table->buckets[code];
		}
		else
			list_ptr = list_ptr->next;
		return *this;
	}

	my_type operator++(int)
	{
		my_type self = *this;
		++(*this);
		return self;
	}

private:
	node_ptr list_ptr;
	hashtable* table;
};

template< class Value, class Ref, class Ptr >
class hashtable_const_iterator
	: public hashtable_iterator< Value, Ref, Ptr >
{
public:
	typedef const Ref reference;
	typedef const Ptr pointer;
	typedef hashtable_const_iterator<Value, Value&, Value*> iterator;
	typedef hashtable_const_iterator<Value, Ref, Ptr> my_type;

public:
	hashtable_const_iterator() {}
	hashtable_const_iterator(const node_ptr list_ptr, const hashtable* table)
		: list_ptr(list_ptr), table(table) {}
};

}

#endif
