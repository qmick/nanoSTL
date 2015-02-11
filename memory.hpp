#ifndef _MEMORY_HPP_
#define _MEMORY_HPP_
#include "iterator.hpp"
#include <new>
#include <stddef.h>

namespace nano{

	enum{__Align = 8};  
	enum{__UpperBound = 128};  //Memory required larger than this
							   //upperbound would be allocated by operator new
	enum{__NFreeLists = __UpperBound / __Align}; //Number of free lists
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

	static pointer address(reference x) const
	{
		return addressof(x);
	}
	static const_pointer address(const_reference x) const
	{
		return addressof(x);
	}

	static pointer allocate(size_type n, const void* = 0)
	{
		mem_block * volatile *local_list;
		mem_block *result;
		size_type total_size = n * sizeof(T);
		if(total_size <= max_size())
		{
			if(n * sizeof(T) > __UpperBound)
				return static_cast<T*>(::operator new(n * sizeof(T)));
			else
			{
				local_list = free_list + list_index(total_size);
				result = *local_list;
				if (result != 0)
				{
					*local_list = result->next_block;					
				}
				else
				{
					result = refill(total_size);
				}
				return (pointer *) result;
			}
		}
		else throw std::bad_alloc();
	}

	static void deallocate(pointer ptr, size_type)
	{
		::operator delete(ptr);
	}

	static size_type max_size() const
	{
		return size_t(-1) / sizeof(T);
	}

	static void construct(pointer p, const_reference val)
	{
		::new((void *)p) T(val);
	}

	static void destroy(pointer p)
	{
		p->~T();
	}

private:
	struct mem_block
	{
		mem_block *next_block;
	};
	static size_t pool_size = 0;
	static char *pool_start = 0;
	static char *pool_end = 0;
	static mem_block *free_list[__NFreeLists] = { 0 };

	static size_t round_up(size_t n)
	{
		return (n + __Align - 1) & ~(__Align - 1);
	}

	static size_t list_index(size_t n)
	{
		return (n + __Align - 1) / __Align - 1;
	}
	
	static void* refill(size_t n)
	{
		//TODO
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
