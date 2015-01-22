#pragma once
#include "memory.hpp"
#include "iterator.hpp"

namespace nano
{

template< class T, class Allocator = nano::allocator<T> >
class deque
{
public:
	typedef T value_type;
	typedef Allocator allocator_type;
	typedef size_t size_type;
	typedef ptrdiff_t diffrence_type;
	typedef typename Allocator::reference reference;
	typedef typename Allocator::const_reference const_reference;
	typedef typename Allocator::pointer pointer;
	typedef typename Allocator::const_pointer const_pointer;
	typedef nano::iterator<nano::random_access_iterator_tag, T> iterator;
	typedef nano::iterator<nano::random_access_iterator_tag, T, const T*, const T&> const_iterator;
	typedef nano::reverse_iterator<iterator> reverse_iterator;
	typedef nano::reverse_iterator<const_iterator> const_reverse_iterator;

	deque()
	{
		//TODO:deque constructor
	}

	~deque()
	{
		//TODO:deque destructor
	}

	deque& operator=(const deque& other)
	{
		//TODO:deque operator=
	}

	void assign(size_type count, const T& value)
	{
		//TODO:deque assign1
	}

	template< class InputIt >
	void assign(InputIt first, InputIt last)
	{
		//TODO:deque assign12
	}

	allocator_type get_allocator() const
	{
		//TODO:deque get_allocator const
	}

	reference at(size_type pos)
	{
		//TODO:deque at
	}

	const_reference at(size_type pos) const
	{
		//TODO:deque at const
	}

	reference operator[](size_type pos)
	{
		//TODO:deque operator[] 
	}

	const_reference operator[](size_type pos) const
	{
		//TODO:deque operator[] const
	}

	reference front()
	{
		//TODO:deque front
	}

	const_reference front() const
	{
		//TODO:deque front const
	}

	reference back()
	{
		//TODO:deque back
	}

	const_reference back() const
	{
		//TODO:deque back
	}

	//iterators
	iterator begin()
	{
		//TODO:deque begin
	}	
	
	const_iterator begin() const
	{
		//TODO:deque begin const
	}

	iterator end()
	{
		//TODO:deque end
	}

	const_iterator end() const
	{
		//TODO:deque end const
	}

	reverse_iterator rbegin()
	{
		//TODO:deque rbegin
	}

	const_reverse_iterator rbegin() const
	{
		//TODO:deque rbegin const
	}

	reverse_iterator rend()
	{
		//TODO:deque rend
	}

	const_reverse_iterator rend() const
	{
		//TODO:deque rend const
	}

	//Capacity
	bool empty() const
	{
		//TODO:deque empty const
	}
	
	size_type size() const
	{
		//TODO:deque size const
	}

	size_type max_size() const
	{
		//TODO:deque max_size const
	}

	void clear()
	{
		//TODO:deque clear
	}

	iterator insert(iterator pos, const T& value)
	{
		//TODO:deque insert1
	}

	void insert(iterator pos, size_type count, const T& value)
	{
		//TODO:deque insert2
	}

	template< class InputIt >
	void insert(iterator pos, InputIt first, InputIt last)
	{
		//TODO:deque insert3
	}

	iterator erase(iterator pos)
	{
		//TODO:deque erase1
	}

	iterator erase(iterator first, iterator last)
	{
		//TODO:deque erase2
	}

	void push_back(const T& value)
	{
		//TODO:deque push_back
	}

	void pop_back()
	{
		//TODO:deque pop_back
	}

	void push_front(const T& value)
	{
		//TODO:deque push_front
	}

	void pop_front()
	{
		//TODO:deque pop_front
	}

	void resize(size_type count, T value = T())
	{
		//TODO:deque resize
	}

	void swap(deque &other)
	{
		//TODO:deque swap
	}


};

}
