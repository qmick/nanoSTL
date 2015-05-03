#ifndef __NANO_HASHTABLE_HPP__
#define __NANO_HASHTABLE_HPP__

#include <cstddef>
#include <cmath>
#include "../memory.hpp"
#include "../iterator.hpp"
#include "../vector.hpp"
#include "../algorithm.hpp"

namespace nano
{

template< class Value >
struct list_node
{
	typedef list_node<Value>* node_ptr;
	node_ptr next;
	Value value;
};



enum { num_primes = 28 };

static const unsigned long prime_list[num_primes] =
{
	53ul, 97ul, 193ul, 389ul, 769ul,
	1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
	49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
	1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
	50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
	1610612741ul, 3221225473ul, 4294967291ul
};

template< class Value, class KeyEqual, class Hash, class Allocator >
class hashtable;

template< class Value, class KeyEqual, class Hash, class Allocator >
class hashtable_iterator
{
public:
	typedef forward_iterator_tag iterator_category;
	typedef Value value_type;
	typedef Value& reference;
	typedef Value* pointer;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef list_node<Value>* node_ptr;
	typedef hashtable<Value, KeyEqual, Hash, Allocator> table;
	typedef hashtable_iterator<Value, KeyEqual, Hash, Allocator> iterator;

public:
	hashtable_iterator() {}
	hashtable_iterator(const node_ptr list_ptr, const table* ht)
		: list_ptr(list_ptr), ht(ht) {}

	bool operator==(const iterator& other) const
	{
		return list_ptr == other.list_ptr;
	}

	bool operator!=(const iterator& other) const
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

	iterator& operator++();

	iterator operator++(int)
	{
		my_type self = *this;
		++(*this);
		return self;
	}

public:
	node_ptr list_ptr;
	const table* ht;
};

template< class Value, class KeyEqual, class Hash, class Allocator >
class hashtable_const_iterator
{
public:
	typedef forward_iterator_tag iterator_category;
	typedef Value value_type;
	typedef const Value& reference;
	typedef const Value* pointer;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef list_node<Value>* node_ptr;
	typedef hashtable_iterator<Value, KeyEqual, Hash, Allocator> non_const_iterator;
	typedef hashtable<Value, KeyEqual, Hash, Allocator> table;
	typedef hashtable_const_iterator<Value, KeyEqual, Hash, Allocator> iterator;

public:
	hashtable_const_iterator() {}
	hashtable_const_iterator(non_const_iterator it)
		: list_ptr(it.list_ptr), ht(it.ht) {}
	hashtable_const_iterator(const node_ptr list_ptr, const table* table)
		: list_ptr(list_ptr), ht(table) {}

	bool operator==(const iterator& other) const
	{
		return list_ptr == other.list_ptr;
	}

	bool operator!=(const iterator& other) const
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

	iterator& operator++();

	iterator operator++(int)
	{
		my_type self = *this;
		++(*this);
		return self;
	}

public:
	const node_ptr list_ptr;
	const table* ht;
};


template< class Value, class KeyEqual, class Hash, class Allocator >
class hashtable
{
public:
	typedef Value value_type;
	typedef size_t size_type;
	typedef Hash hasher;
	typedef KeyEqual key_equal;
	typedef list_node<Value> node;
	typedef node* node_ptr;
	typedef Value& reference;
	typedef const Value& const_reference;
	typedef Value* pointer;
	typedef const Value* const_pointer;
	typedef hashtable_iterator<Value, KeyEqual, Hash, Allocator> iterator;
	typedef hashtable_const_iterator<Value, KeyEqual, Hash, Allocator> const_iterator;
	typedef typename Allocator::template rebind<node>::other node_allocator;
	typedef typename simple_allocator<node, node_allocator> hash_allocator;
	typedef hashtable<Value, KeyEqual, Hash, Allocator> my_type;
	typedef pair<iterator, iterator> Pii;
	typedef pair<iterator, bool> Pib;
	typedef pair<const_iterator, const_iterator> Pcc;
	friend class iterator;
	friend class const_iterator;

private:
	key_equal equals;
	hasher hash_func;
	vector<node_ptr> buckets;
	float max_factor;
	size_type elements_count;

public:
	hashtable()
		: equals(key_equal()), hash_func(hasher()), max_factor(1.0), elements_count(0) {}

	hashtable(size_type buckets_count, const Hash& hash, const KeyEqual& equal)
		: hash_func(hash), equals(key_equal()), max_factor(1.0), elements_count(0)
	{
		buckets.assign(buckets_count, 0);
	}

	hashtable(const my_type& other)
		: hash_func(other.hash_func),
		equals(other.equals),
		max_factor(other.max_factor),
		buckets(other.buckets),
		elements_count(other.elements_count),
	{
		copy_from(other);
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
		max_factor = other.max_factor;	
		elements_count = other.elements_count;		

		buckets.resize(other.buckets.size());
		copy_from(other);
	}


public:
	iterator begin()
	{
		for (size_type i = 0; i < buckets.size(); ++i)
			if (buckets[i])
				return iterator(buckets[i], this);
		return end();
	}

	const_iterator begin() const
	{
		for (int i = 0; i < buckets.size(); ++i)
			if (buckets[i])
				return const_iterator(buckets[i], this);
		return end();
	}

	iterator end()
	{
		return iterator(0, this);
	}

	const_iterator end() const
	{
		return const_iterator(0, this);
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
		size_type i = hashcode(*begin());
		for (; i < buckets.size(); ++i)
		{
			node_ptr cur = buckets[i];
			while (cur)
			{
				node_ptr temp = cur;
				cur = cur->next;
				delete_node(temp);
			}
		}
		buckets.clear();
		elements_count = 0;
	}

	Pib insert_unique(const value_type& value)
	{
		int code = hashcode(value);
		node_ptr cur = buckets[code];
		if (elements_count / buckets.size() > max_factor)
			rehash(next_prime(buckets_count() + 1));

		return direct_insert_unique(value);
	}

	template< class InputIt >
	void insert_unique(InputIt first, InputIt last)
	{
		size_type d = distance(first, last);
		size_type new_size = size() + d;
		if (new_size / buckets.size() > max_factor)
			rehash(next_prime(new_size));
		for (; first != last; ++first)
			direct_insert_unique(*first);
	}

	iterator insert_equal(const value_type& value)
	{
		int code = hashcode(value);
		node_ptr cur = buckets[code];
		if (elements_count / buckets.size() > max_factor)
			rehash(next_prime(buckets_count() + 1));

		return direct_insert_equal(value);
	}

	template< class InputIt >
	void insert_equal(InputIt first, InputIt last)
	{
		size_type d = distance(first, last);
		size_type new_size = size() + d;
		if (new_size / buckets.size() > max_factor)
			rehash(next_prime(new_size));
		for (; first != last; ++first)
			direct_insert_equal(*first);
	}

	iterator erase(iterator pos)
	{
		const size_type n = hashcode(pos.list_ptr->value);
		node_ptr target = buckets[n];
		iterator next(pos);

		++next;
		if (target == pos.list_ptr)
		{
			buckets[n] = target->next;
			delete_node(target);
		}
		else
		{
			while (target->next != pos.list_ptr)
				target = target->next;
			target->next = target->next->next;
			delete_node(pos.list_ptr);
		}
		if (buckets[n])
		return next;
	}

	iterator erase(iterator first, iterator last)
	{
		for (; first != last; ++first)
			erase(first);
		return last;
	}

	size_type erase(const value_type& value)
	{
		iterator result = find(value);
		size_type n = 0;
		if (result != end())
		{
			do
			{
				erase(result++);
				++n;
			} while (equals(result, value));
		}

		return n;
	}

	void swap(my_type& other)
	{
		nano::swap(hash_func, other.hash_func);
		nano::swap(equals, other.equals);
		nano::swap(max_factor, other.max_factor);
		nano::swap(elements_count, other.elements_count);
		buckets.swap(other.buckets);
	}

	value_type& at(const value_type& value)
	{
		size_type n = hashcode(value);
		node_ptr cur = buckets[n];

		while (cur)
		{
			if (equals(cur->value, value))
				break;
		}
		if (!cur)
			throw std::out_of_range;
		else
			return cur->value;
	}


	Pii equal_range(const value_type& value)
	{
		const size_type n = hashcode(value);
		node_ptr first = buckets[n];
		for (; first; first = first->next)
		{
			if (equals(value, first->value))
			{
				for (node_ptr second = first->next; second; second = second->next)
				{
					if (!equals(second->value, value))
						return Pii(iterator(first, this), iterator(second, this));
				}

				for (size_type i = n + 1; i < buckets.size(); ++i)
				{
					if (buckets[i])
						return Pii(iterator(first, this), iterator(buckets[i], this));
				}
			}
		}
		return Pii(end(), end());
	}

	Pcc equal_range(const Value& key) const
	{
		const size_type n = hashcode(value);
		node_ptr first = buckets[n];
		for (; first; first = first->next)
		{
			if (equals(value, first->value))
			{
				for (node_ptr second = first->next; second; second = second->next)
				{
					if (!equals(second->value, value))
						return Pcc(const_iterator(first, this), const_iterator(second, this));
				}

				for (size_type i = n + 1; i < buckets.size(); ++i)
				{
					if (buckets[i])
						return Pcc(const_iterator(first, this), const_iterator(buckets[i], this));
				}
			}
		}
		return Pcc(end(), end());
	}

	iterator find(const value_type& value)
	{
		const size_type n = hashcode(value);
		for (node_ptr cur = buckets[n]; cur; cur = cur->next)
		{
			if (equals(cur->value, value))
				return iterator(cur, this);
		}
		return iterator(0, this);
	}

	const_iterator find(const value_type& value) const
	{
		const size_type n = hashcode(value);
		for (node_ptr cur = buckets[n]; cur; cur = cur->next)
		{
			if (equals(cur->value, value))
				return const_iterator(cur, this);
		}
		return const_iterator(0, this);
	}

	size_type count(const value_type& value) const
	{
		const size_type n = hashcode(value);
		size_type cnt = 0;
		for (node_ptr cur = buckets[n]; cur; cur = cur->next)
		{
			if (equals(cur->value, value))
				++cnt;
			if (cnt)
				break;
		}
		return cnt;
	}

	float load_factor() const
	{
		return size() / buckets.size();
	}

	float max_load_factor() const
	{
		return max_factor;
	}

	void max_load_factor(float factor)
	{
		max_load_factor = factor;
	}

	void rehash(size_type count)
	{
		if ((float) size() / max_factor > count )
			count = (size_type) ceil((float) size() / max_factor);
		
		my_type temp(count, hash_func, equals);
		for (iterator i = begin(); i != end(); ++i)
		{
			temp.insert_equal(*i);
		}
		swap(temp);
	}

	void reserve(size_type count)
	{
		rehash(ceil(count / max_load_factor()));
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
		return hash_func(value) % buckets.size();
	}

private:
	static unsigned long next_prime(unsigned long value)
	{
		return *nano::lower_bound(prime_list, prime_list + num_primes, value);
	}

	node_ptr new_node(const value_type& value)
	{
		node_ptr block = (node_ptr)hash_allocator::allocate();
		construct(&block->value, value);
		return block;
	}

	void delete_node(node_ptr ptr)
	{
		destroy(ptr);
		hash_allocator::deallocate(ptr);
	}

	void copy_from(const my_type& other)
	{
		for (int i = 0; i < other.buckets.size(); ++i)
		{
			node_ptr cur = other.buckets[i];
			node_ptr *this_cur = &buckets[i];
			while (cur)
			{
				(*this_cur) = new_node(cur->value);
				cur = cur->next;
				this_cur = &(*this_cur)->next;
			}
			(*this_cur)->next = 0;
		}

	}

	void clear_bucket(node_ptr pos)
	{
		if (pos)
		{
			clear_bucket(pos->next);
			delete_node(pos);
		}
	}

	//insert_unique without considering load factor
	Pib direct_insert_unique(const value_type& value)
	{
		size_type n = hashcode(value);
		node_ptr i = buckets[hashcode(value)];
		node_ptr temp = i;
		while (i)
		{
			if (equals(i->value, value))
				return Pib(iterator(i, this), false);
			else
				i = i->next;
		}
		buckets[n] = new_node(value);
		buckets[n]->next = temp;
		++elements_count;
		return Pib(iterator(buckets[n], this), true);
	}

	//insert_unique without considering load factor
	iterator direct_insert_equal(const value_type& value)
	{
		size_type n = hashcode(value);
		node_ptr i = buckets[hashcode(value)];
		node_ptr temp = i;
		while (i)
		{
			if (equals(i->value, value))
			{
				temp = i->next;
				i->next = new_node(value);
				i->next->next = temp;
				++elements_count;
				return iterator(i->next, this);
			}
			else
				i = i->next;
		}
		buckets[n] = new_node(value);
		buckets[n]->next = temp;
		++elements_count;
		return iterator(buckets[n], this);
	}
};

template< class Value, class KeyEqual, class Hash, class Allocator >
hashtable_iterator<Value, KeyEqual, Hash, Allocator>& 
hashtable_iterator<Value, KeyEqual, Hash, Allocator>::operator++()
{
	if (!list_ptr->next)
	{
		size_type code = ht->hashcode(list_ptr->value);
		list_ptr = list_ptr->next;
		while (!list_ptr && ++code < ht->buckets.size())
			list_ptr = ht->buckets[code];
	}
	else
		list_ptr = list_ptr->next;
	return *this;
}

template< class Value, class KeyEqual, class Hash, class Allocator >
hashtable_const_iterator<Value, KeyEqual, Hash, Allocator>&
hashtable_const_iterator<Value, KeyEqual, Hash, Allocator>::operator++()
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

}

#endif
