#pragma once
#include <limits>

namespace nano{
	template<class T>
	class allocator
	{
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef void* void_pointer;
		typedef const void* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t size_type;	
		typedef ptrdiff_t diffrence_type;

		allocator() {}
		~allocator() {}

		allocator<T>::pointer allocate(size_type count)
		{

		}

		void deallocate(pointer ptr)
		{

		}

		void construct(pointer ptr, const_reference val)
		{

		}

		void destroy(pointer ptr)
		{

		}
	};
}