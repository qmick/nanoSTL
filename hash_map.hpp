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
          class Allocator = allocator<pair<const Key, Value> > >
class hash_map
{
public:
	typedef Key key_type;
	typedef Value mapped_type;
	typedef pair<const Key, Value> value_type;
	typedef size_t size_type;
	typedef Hash hasher;
	typedef KeyEqual key_equal;

	struct pair_equal
	{
		bool operator()(const value_type& lhs, const value_type& rhs) const
		{
			return key_equal()(lhs.first, rhs.first);
		}
	};

	struct key_hash
	{
		size_type operator()(const value_type& value) const
		{
			return hasher()(value.first);
		}
	};

	typedef hashtable<value_type, pair_equal, key_hash, Allocator> table;
	typedef typename table::reference reference;
	typedef typename table::const_reference const_reference;
	typedef typename table::pointer pointer;
	typedef typename table::const_pointer const_pointer;
	typedef typename table::iterator iterator;
	typedef typename table::const_iterator const_iterator;
	typedef hash_map<Key, Value, KeyEqual, Hash, Allocator> my_type;

public:
	explicit hash_map(size_type buckets_count = 7,
		const key_hash& hash = key_hash(),
		const pair_equal& equal = pair_equal())
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

	size_type erase(const key_type& key)
	{
		return ht.erase(value_type(key, mapped_type()));
	}

	void swap(const my_type& other)
	{
		ht.swap(other.ht);
	}

	mapped_type& at(const key_type& key)
	{
		return ht.at(value_type(key, mapped_type()));
	}

	mapped_type& operator[](const key_type& key)
	{
		return (*(ht.insert_unique(value_type(key, mapped_type())).first)).second;
	}

	pair<iterator, iterator> equal_range(const key_type& key)
	{
		return ht.equal_range(value_type(key, mapped_type()));
	}

	pair<const_iterator, const_iterator> equal_range(const key_type& key) const
	{
		return ht.equal_range(value_type(key, mapped_type()));
	}

	iterator find(const key_type& key)
	{
		return ht.find(value_type(key, value_type()));
	}

	const_iterator find(const key_type& key) const
	{
		return ht.find(value_type(key, value_type()));
	}

	size_type count(const key_type& key) const
	{
		return ht.count(value_type(key, value_type()));
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
	table ht;
};

}

#endif
