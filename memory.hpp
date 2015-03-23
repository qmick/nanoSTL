#ifndef _MEMORY_HPP_
#define _MEMORY_HPP_
#include "iterator.hpp"
#include "nano\type_traits.hpp"
#include "nano\uninitialized.hpp"
#include <new>
#include <cstddef>


namespace nano {

template< class T >
class allocator
{
public:
	typedef T           value_type;
	typedef T*          pointer;
	typedef const T*    const_pointer;
	typedef void*       void_pointer;
	typedef const void* const_void_pointer;
	typedef T&          reference;
	typedef const T&    const_reference;
	typedef size_t      size_type;
	typedef ptrdiff_t   diffrence_type;


	static size_type max_size()
	{
		return size_t(-1) / sizeof(T);
	}

	static void* allocate(size_type bytes)
	{		
		if (bytes <= max_size())
			return malloc(bytes);
		else 
			throw std::bad_alloc();
	}

	static void deallocate(pointer ptr, size_type = 0)
	{
		free(ptr);
	}
};

template< class T, class Alloc >
class simple_allocator
{
public:
	static T* allocate()
	{
		return (T*) Alloc::allocate(sizeof(T));
	}

	static T* allocate(size_t n)
	{
		return n == 0 ? 0 : (T*) Alloc::allocate(n * sizeof(T));
	}

	static void deallocate(T *p)
	{
		Alloc::deallocate(p);
	}

	static void deallocate(T *p, size_t n)
	{
		return n == 0 ? 0 : Alloc::deallocate(p, n * sizeof(T));
	}
};


template< class T >
T* __addressof(T& arg)
{
	return reinterpret_cast<T*>(
		&const_cast<char&>(
		reinterpret_cast<const volatile char&>(arg)));
}


template< class InputIt, class ForwardIt >
ForwardIt uninitialized_copy(InputIt first, InputIt last, ForwardIt d_first)
{
	return __uninitialized_copy(first, last, d_first, is_POD_type(first));
}

template< class ForwardIt, class T >
void uninitialized_fill(ForwardIt first, ForwardIt last, const T& value)
{
	__uninitialized_fill(first, last, value, is_POD_type(value));
}

template< class ForwardIt, class Size, class T >
void uninitialized_fill_n(ForwardIt first, Size count, const T& value)
{
	__uninitialized_fill_n(first, count, value, is_POD_type(value));
}

template< class OutputIt, class T >
class raw_storage_iterator
	: public iterator< output_iterator_tag, void, void, void, void >
{
	explicit raw_storage_iterator(OutputIt it)
	{
		//TODO
	}

	raw_storage_iterator& operator=(const T& el)
	{
		//TODO
	}

	raw_storage_iterator& operator*()
	{
		//TODO
	}

	raw_storage_iterator& operator++()
	{
		//TODO
	}

	raw_storage_iterator operator++(int)
	{
		//TODO
	}
};

}

#endif
