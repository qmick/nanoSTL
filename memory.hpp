#ifndef _MEMORY_HPP_
#define _MEMORY_HPP_
#include "iterator.hpp"
#include <new>
#include <stddef.h>

namespace nano{

template<class T>
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

	template< class U > 
	struct rebind 
	{ 
		typedef allocator<U> other; 
	};

	allocator() 
	{
		//do nothing
	}

	allocator(const allocator&)
	{

	}

	template< class U >
	allocator(const allocator<U>&)
	{

	}
	~allocator() {}

	pointer address(reference x) const
	{
		return addressof(x);
	}
	const_pointer address(const_reference x) const
	{
		return addressof(x);
	}

	pointer allocate(size_type n, const void* = 0)
	{
		if(n * sizeof(T) <= this->max_size())
		{
			if(n * sizeof(T) > 128)
				return static_cast<T*>(::operator new(n * sizeof(T)));
			else
			{

			}
		}
		else throw std::bad_alloc();
	}

	void deallocate(pointer ptr, size_type)
	{
		::operator delete(ptr);
	}

	size_type max_size() const
	{
		return size_t(-1) / sizeof(T);
	}

	void construct(pointer p, const_reference val)
	{
		::new((void *)p) T(val);
	}

	void destroy(pointer p)
	{
		p->~T();
	}
};

//C++11 standard function, get address of an object even it overloads "&" operator
template< class T >
T* addressof(T& arg)
{
	return reinterpret_cast<T*>(&const_cast<char&>(reinterpret_cast<const volatile char&>(arg)));
}

//Tow allocator are always equal because class allocator is stateless
template< class T1, class T2 >
bool operator==(const allocator<T1>&, const allocator<T2>&) {return true;}
template< class T1, class T2 >
bool operator<=(const allocator<T1>&, const allocator<T2>&) {return true;}
template< class T1, class T2 >
bool operator>=(const allocator<T1>&, const allocator<T2>&) {return true;}
template< class T1, class T2 >
bool operator!=(const allocator<T1>&, const allocator<T2>&) {return false;}
template< class T1, class T2 >
bool operator<(const allocator<T1>&, const allocator<T2>&) {return false;}
template< class T1, class T2 >
bool operator>(const allocator<T1>&, const allocator<T2>&) {return false;}

	
template< class InputIt, class ForwardIt >
ForwardIt uninitialized_copy(InputIt first, InputIt last, ForwardIt d_first)
{
	typedef typename nano::iterator_traits<ForwardIt>::value_type Value;
	ForwardIt current = d_first;
	try
	{
		for(; first != last; first++, current++)
		{
			::new((void *)(&*current)) Value(*first);
		}
		return current;
	}
	catch(...)
	{
		for(; d_first != current; d_first++)
		{
			d_first->~Value();
		}
		throw;
	}
}

template< class ForwardIt, class T >
void uninitialized_fill(ForwardIt first, ForwardIt last, const T& value)
{
	typedef typename nano::iterator_traits<ForwardIt>::value_type Value;
	ForwardIt current = first;
	try
	{
		for(; current != last; current++)
		{
			::new((void*)(&*current)) Value(value);
		}
	}
	catch(...)
	{
		for(; first != last; first++)
		{
			first->~Value();
		}
		throw;
	}
}

template< class ForwardIt, class Size, class T >
void uninitialized_fill_n(ForwardIt first, Size count, const T& value)
{
	typedef typename nano::iterator_traits<ForwardIt>::value_type Value;
	ForwardIt current = first;
	try
	{
		for(; count > 0; count--, current++)
		{
			::new ((void*)(&*current)) Value(value);
		}
	}
	catch(...)
	{
		for(; first != current; first++)
		{
			first->~Value();
		}
		throw;
	}
}

}

#endif
