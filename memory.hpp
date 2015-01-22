#pragma once
#include <stddef.h>

namespace nano{

template<class T>
class allocator
{
public:
	typedef T value_type;
	typedef T* pointer;
	typedef const T* const_pointer;
	typedef void* void_pointer;
	typedef const void* const_void_pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t diffrence_type;

	template< class U > 
	struct rebind 
	{ 
		typedef allocator<U> other; 
	};

	allocator() 
	{

	}

	allocator(const allocator& other)
	{

	}

	template<class U>
	allocator(const allocator<U>& other)
	{

	}
	~allocator() {}

	pointer address(reference x) const
	{

	}
	const_pointer address(const_reference x) const
	{

	}

	pointer allocate(size_type n, const void* = 0)
	{

	}

	void deallocate(pointer ptr, size_type n)
	{

	}

	size_type max_size() const
	{

	}

	void construct(pointer p, const_reference val)
	{

	}

	void destroy(pointer p)
	{

	}



};
template< class InputIt, class ForwardIt >
ForwardIt uninitialized_copy(InputIt first, InputIt last, ForwardIt d_first)
{

}

template< class ForwardIt, class T >
void uninitialized_fill(ForwardIt first, ForwardIt last, const T& value)
{

}

}
