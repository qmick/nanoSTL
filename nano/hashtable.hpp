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

template< class Value, class Ref, class Ptr >
struct hashtable_iterator;

template< class Value, class Compare, class HashFunc, class Allocator >
class hashtable
{
	friend struct hashtable_iterator<Value, Value&, Value*>;
public:
	typedef Value value_type;
	typedef size_t size_type;
	typedef list_node<Value> node;
	typedef node* node_ptr;
	typedef typename Allocator::template rebind<node>::other node_allocator;
	typedef typename simple_allocator<node, node_allocator> hash_allocator;

private:
	Compare equals;
	HashFunc hasher;
	vector<node_ptr> buckets;

public:
	size_type hashcode(const value_type& value) const
	{
		return hasher(value);
	}
};

template< class Value, class Ref, class Ptr >
struct hashtable_iterator
{
	typedef forward_iterator_tag iterator_category;
	typedef Value value_type;
	typedef Ref reference;
	typedef Ptr pointer;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef list_node<Value>* node_ptr;
	typedef hashtable_iterator<Value, Value&, Value*> iterator;
	typedef hashtable_iterator<Value, const Value&, const Value*> const_iterator;
	typedef hashtable_iterator<Value, Ref, Ptr> my_type;

	node_ptr list_ptr;
	hashtable* table;

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
		increment();
		return *this;
	}

	my_type operator++(int)
	{
		my_type self = *this;
		increment();
		return self;
	}

	void increment()
	{
		if (!list_ptr->next)
		{
			size_type code = table->hashcode(list_ptr->value);
			while (!list_ptr && ++code < table->buckets[code])
				list_ptr = table->buckets[code];
		}
		else
			list_ptr = list_ptr->next;
	}
};

}

#endif
