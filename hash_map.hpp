#ifndef __HASH_MAP_HPP__
#define __HASH_MAP_HPP__

#include "nano/hashtable.hpp"
#include "functional.hpp"
#include "nano/hash_function.hpp"

namespace nano {

template< class Key, 
          class Value, 
          class KeyEqual = equal_to<Key>, 
          class Hash = hash<Key>, 
          class Allocator = allocator<pair<const Key, value> > >
class hash_map
{
public:
	typedef pair<const Key, Value> value_type;
	typedef size_t size_type;
	typedef Hash hasher;
	typedef KeyEqual key_equal;

	struct pair_equal
	{
		bool operator()(const value_type& lhs, const value_type& rhs) const
		{
			return KeyEqual(lhs.first, rhs.first);
		}
	};

	typedef hashtable<value_type, pair_equal, Hash, Allocator> table;
	typedef table::reference reference;
	typedef table::const_reference const_reference;
	typedef table::pointer pointer;
	typedef table::const_pointer const_pointer;
	typedef table::iterator iterator;
	typedef table::const_iterator const_iterator;
	typedef hash_map<Key, Value, KeyEqual, Hash, Allocator> my_type;

public:
	hash_map() {}

	explicit hash_map(size_type buckets_count,
		const Hash& hash = Hash(),
		const KeyEqual& equal = KeyEqual())
		: ht(buckets_count, hash, equal) {}

	hash_map(const my_type& other)
		: ht(other.ht) {}

	my_type& operator=(const my_type& other)
	{
		ht = other.ht;
	}

public:
	iterator begin()
	{
		return ht.begin();
	}

	const_iterator begin() const
	{
		return ht.begin();
	}

	iterator end()
	{
		return ht.end();
	}

	const_iterator end() const
	{
		return ht.end();
	}

	bool empty() const
	{
		return elements_count == 0;
	}

	size_type size() const
	{
		return ht.size();
	}

	size_type max_size() const
	{
		return ht.max_size();
	}

	size_type buckets_count() const
	{
		return ht.buckets_count();
	}

	size_type max_buckets_count() const
	{
		return ht.max_buckets_count();
	}

	void clear()
	{
		ht.clear();
	}

	pair<iterator, bool> insert(const value_type& value)
	{
		return ht.insert_unique(value);
	}

	template< class InputIt >
	void insert(InputIt first, InputIt last)
	{
		ht.insert_unique(first, last);
	}

	iterator erase(iterator pos)
	{
		return ht.erase(pos);
	}

	iterator erase(iterator first, iterator last)
	{
		return ht.erase(first, last);
	}

	size_type erase(const value_type& value)
	{
		return ht.erase(value);
	}

	void swap(const my_type& other)
	{
		ht.swap(other.ht);
	}

	pair<iterator, iterator> equal_range(const value_type& value)
	{
		return ht.equal_range(value);
	}

	pair<const_iterator, const_iterator> equal_range(const value_type& value) const
	{
		return ht.equal_range(value);
	}

	iterator find(const value_type& value)
	{
		return ht.find(value);
	}

	const_iterator find(const value_type& value) const
	{
		return ht.find(value);
	}

	size_type count(const value_type& value) const
	{
		return ht.count;
	}

	float load_factor() const
	{
		return ht.load_factor();
	}

	float max_load_factor() const
	{
		return ht.max_load_factor();
	}

	void max_load_factor(float factor)
	{
		ht.max_load_factor(factor);
	}

	void rehash(size_type count)
	{
		ht.rehash(count);
	}

	void reserve(size_type count)
	{
		ht.reserve(count);
	}

	key_equal key_eq() const
	{
		return ht.key_eq();
	}

	hasher hash_function() const
	{
		return ht.hash_function();
	}


private:
	hashtable ht;
};

}

#endif
