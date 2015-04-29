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
class hashtable
{
public:
	enum{INIT_SIZE = 7};
	typedef Value value_type;
	typedef size_t size_type;
	typedef Hash hasher;
	typedef KeyEqual key_equal;
	typedef list_node<Value> node;
	typedef node* node_ptr;
	typedef hashtable_iterator<Value, KeyEqual, Hash, Allocator> iterator;
	typedef hashtable_const_iterator<Value, KeyEqual, Hash, Allocator> const_iterator;
	typedef typename Allocator::template rebind<node>::other node_allocator;
	typedef typename simple_allocator<node, node_allocator> hash_allocator;
	typedef hashtable<Value, KeyEqual, Hash, Allocator> my_type;

	friend class iterator;
	friend class const_iterator;

private:
	key_equal equals;
	hasher hash_func;
	vector<node_ptr> buckets;
	float max_factor;
	size_type elements_count;
	node_ptr first;
	node_ptr last;

public:
	explicit hashtable(size_type buckets_count = INIT_SIZE,
		const Hash& hash = Hash(),
		const KeyEqual& equal = KeyEqual())
		: hash_func(hash),
		equals(key_equal),
		max_factor(1.0), 
		elements_count(0),
		first(0), 
		last(0)
	{
		buckets.assign(buckets_count, 0);
	}

	hashtable(const my_type& other)
		: hash_func(other.hash_func),
		equals(other.equals),
		max_factor(other.max_factor),
		buckets(other.buckets),
		elements_count(other.elements_count),
		first(other.start),
		last(other.end)
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
		first = other.first;
		end = other.end;

		buckets.resize(other.buckets.size());
		copy_from(other);
	}


public:
	iterator begin()
	{
		return iterator(first, this);
	}

	const_iterator begin() const
	{
		return const_iterator(first, this);
	}

	iterator end()
	{
		return iterator(end, this);
	}

	const_iterator end() const
	{
		return const_iterator(end, this);
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
		int i = hash_func(first->value);
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
		first = 0;
		last = 0;
	}

	pair<iterator, bool> insert_unique(const value_type& value)
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
		size_type code = hashcode(pos.list_ptr->value);
		node_ptr target = buckets[code];
		iterator next(pos);

		++next;
		if (target == pos.list_ptr)
		{
			buckets[code] = target->next;
			delete_node(target);
		}
		else
		{
			while (target->next != pos.list_ptr)
				target = target->next;
			target->next = target->next->next;
			delete_node(pos.list_ptr);
		}
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
		nano::swap(first, other.first);
		nano::swap(end, other.end);
		buckets.swap(other.buckets);
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

	void reserve(size_type count)
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
	static unsigned long next_prime(unsigned long value)
	{
		return *nano::lower_bound(prime_list, prime_list + num_primes, value);
	}

	node_ptr new_node(const value_type& value)
	{
		node_ptr block = (node_ptr)hash_allocator::allocate();
		construct(block->value, value);
	}

	void delete_node(node_ptr ptr)
	{
		destroy(ptr->value);
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
	pair<iterator, bool> direct_insert_unique(const value_type& value)
	{
		size_type n = hashcode(value);
		node_ptr i = buckets[hashcode(value)];
		node_ptr temp = i;
		while (i)
		{
			if (equals(i->value, value))
				return pair<iterator, bool>(i, false);
			else
				i = i->next;
		}
		buckets[n] = new_node(value);
		buckets[n]->next = temp;
		++elements_count;
		return pair<iterator, bool>(iterator(buckets[n], this), true);
	}

	//insert_unique without considering load factor
	pair<iterator, bool> direct_insert_equal(const value_type& value)
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
		return pair<iterator, bool>(iterator(buckets[n], this), true);
	}
};


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
	typedef hashtable_iterator<Value, KeyEqual, Hash, Allocator> iterator;

public:
	hashtable_iterator() {}
	hashtable_iterator(const node_ptr list_ptr, const hashtable* table)
		: list_ptr(list_ptr), table(table) {}

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

	iterator& operator++()
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

	iterator operator++(int)
	{
		my_type self = *this;
		++(*this);
		return self;
	}

public:
	node_ptr list_ptr;
	const hashtable* table;
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
	typedef hashtable_const_iterator<Value, KeyEqual, Hash, Allocator> iterator;

public:
	hashtable_const_iterator() {}
	hashtable_const_iterator(const node_ptr list_ptr, const hashtable* table)
		: list_ptr(list_ptr), table(table) {}

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

	iterator& operator++()
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

	iterator operator++(int)
	{
		my_type self = *this;
		++(*this);
		return self;
	}

public:
	const node_ptr list_ptr;
	const hashtable* table;
};

}

#endif
