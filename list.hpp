#pragma once
#include "memory.hpp"
#include "iterator.hpp"

namespace nano{

template < class T, class Allocator = allocator<T> >
class list
{
public:
	typedef T value_type;
	typedef Allocator allocator_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef typename Allocator::reference reference;
	typedef typename Allocator::const_reference const_reference;
	typedef typename Allocator::pointer pointer;
	typedef typename Allocator::const_pointer const_pointer;
	typedef nano::iterator<bidirectional_iterator_tag, T> iterator;
	typedef nano::iterator<bidirectional_iterator_tag, T, const T*, const T&> const_iterator;
	typedef nano::reverse_iterator<iterator> reverse_iterator;
	typedef nano::reverse_iterator<const_iterator> const_reverse_iterator;

	list()
	{
		//TODO:list constructor
	}

	~list()
	{
		//TODO:list destructor
	}

	list& operator=(const list& other)
	{
		//TODO:list operator=
	}

	void assign(size_type count, const T& value)
	{
		//TODO:list assign1
	}
	
	template<class InputIt>
	void assign(InputIt first, InputIt lase)
	{
		//TODO:list assign2
	}

	allocator_type get_allocator() const
	{
		//TODO:list get_allocator
	}

	reference front()
	{
		//TODO:list front
	}

	reference back()
	{
		//TODO:list back
	}

	iterator begin()
	{
		//TODO:list begin
	}

	const_iterator begin() const
	{
		//TODO:list begin const
	}

	iterator end()
	{
		//TODO:list end
	}

	const_iterator end() const
	{
		//TODO:list end const
	}

	reverse_iterator rbegin()
	{
		//TODO:list rbegin	
	}

	const_reverse_iterator rbegin() const
	{
		//TODO:list rbegin const
	}

	reverse_iterator rend()
	{
		//TODO:list rend()
	}
	
	const_reverse_iterator rend() const
	{
		//TODO:list rend() const
	}

	bool empty() const
	{
		//TODO:list empty
	}

	size_type size() const
	{
		//TODO:list size
	}

	size_type max_size() const
	{
		//TODO:list max_size const
	}
	void clear()
	{
		//TODO:list clear
	}

	iterator insert(iterator pos, const T& value)
	{
		//TODO:list insert1
	}

	void insert(iterator pos, size_type count, const T& value)
	{
		//TODO:list insert2
	}

	template< class InputIt >
	void insert(iterator pos, InputIt first, InputIt last)
	{
		//TODO:list insert3
	}

	iterator erase(iterator pos)
	{
		//TODO:list erase1
	}

	iterator erase(iterator first, iterator last)
	{
		//TODO:list erase2
	}

	void push_back(const T& value)
	{
		//TODO:list push_back
	}

	void pop_back()
	{
		//TODO:list pop_back
	}

	void push_front(const T& value)
	{
		//TODO:list push_front
	}

	void pop_front()
	{
		//TODO:list pop_front
	}
	
	void resize(size_type count, T value = T())
	{
		//TODO:list resize
	}

	void swap(list& other)
	{
		//TODO:list swap
	}
};

}
