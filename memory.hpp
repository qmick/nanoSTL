#ifndef _MEMORY_HPP_
#define _MEMORY_HPP_
#include "iterator.hpp"
#include "nano\type_traits.hpp"
#include "nano\uninitialized.hpp"
#include <new>
#include <cstddef>


namespace nano {

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

	pointer address(reference x)
	{
		return __addressof(x);
	}
	const_pointer address(const_reference x)
	{
		return __addressof(x);
	}

	pointer allocate(size_type n, const void* = 0)
	{
		if (total_size <= max_size())
		{
			return static_cast<T*>(::operator new(n * sizeof(T)));
		}
		else throw std::bad_alloc();
	}

	void deallocate(pointer ptr, size_type)
	{
		::operator delete(ptr);
	}

	size_type max_size()
	{
		return size_t(-1) / sizeof(T);
	}

	void construct(pointer p, const_reference val)
	{
		::new((void *) p) T(val);
	}

	void destroy(pointer p)
	{
		p->~T();
	}
};



template<class T>
class default_allocator
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

	static pointer allocate(size_type n, const void* = 0)
	{
		block * volatile *local_list;
		block *result;
		size_type total_size = n * sizeof(T);
		if(total_size <= max_size())
		{
			if(n * sizeof(T) > UPPERBOUND)
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

	static void deallocate(pointer ptr, size_type n)
	{
		block *q = (block*) ptr;
		obj * volatile * local_list;
		int total_size = n * sizeof(T);
		if (total_size > UPPERBOUND)
		{
			::operator delete(ptr);
			return;
		}
		
		local_list = free_list + list_index(total_size);
		q->next_block = *local_list;
		*local_list = q;
	}

	static size_type max_size()
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
	enum{ ALIGN = 8 };
	enum{ UPPERBOUND = 128 };  //Memory required larger than this would be allocated by operator new
	enum{ NFREELISTS = UPPERBOUND / ALIGN }; //Number of free lists

	//Memory block
	struct block 
	{
		block *next_block;
	};
	static size_t pool_size;
	static char *pool_start;
	static char *pool_end;
	static block * volatile free_list[NFREELISTS];

	static size_t round_up(size_t n)
	{
		return (n + ALIGN - 1) & ~(ALIGN - 1);
	}

	static size_t list_index(size_t n)
	{
		return (n + ALIGN - 1) / ALIGN - 1;
	}
	
	static void* refill(size_t n)
	{
		//Try to get 20 memory blocks
		int nblocks = 20;
		char * chunk = chunk_alloc(n, nblocks);	
		block * volatile * local_list;
		block * result;
		block * current_block, * next_block;
		int i;

		if(1 == nblocks) return chunk;

		local_list = free_list + list_index(n);
		result = (block*)chunk;

		*local_list = next_block = (block*)(chunk + n);
		for(i = 1;; i++)
		{
			current_block = next_block;
			next_block = (block *)((char*)next_block + n);
			if(nblocks - 1 == i)
			{
				current_block->next_block = 0;
				break;
			}
			else
			{
				current_block->next_block = next_block;
			}
		}

		return result;
	}

	static char *chunk_alloc(size_t size, int &nblocks)
	{
		char * result;
		size_t total_bytes = size * nblocks;	
		size_t bytes_left  = pool_end - pool_end;

		//If memory pool is large enough
		if(bytes_left >= total_bytes)
		{
			result = pool_start;
			pool_start += total_bytes;
			return result;
		} else if(bytes_left >= size)
		{
			nblocks     = bytes_left / size;
			total_bytes = size * nblocks;
			result      = pool_start;
			pool_start += total_bytes;
			return result;
		} else //If memory is too small for one block
		{
			size_t bytes_to_get = 2 * total_bytes + round_up(pool_size >> 4);
			if(bytes_left > 0)	
			{
				block * volatile * local_list    = free_list + list_index(bytes_left);
				((block*)pool_start)->next_block = *local_list;
				*local_list                      = (block*)pool_start;
			}

			pool_start = static_cast<char*>(::operator new(bytes_to_get));
			pool_size += bytes_to_get;
			pool_end   = pool_start + bytes_to_get;
			return chunk_alloc(size, nblocks);
		}
	}
};

//Initilization of static member of class allocator
template< class T >
size_t allocator<T>::pool_size = 0;
template< class T >
char* allocator<T>::pool_start = 0;
template< class T >
char* allocator<T>::pool_end = 0;
template< class T >
typename allocator<T>::block* volatile allocator<T>::free_list[NFREELISTS] = {0};

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
	typedef typename nano::type_traits<T>::is_POD_type POD_type;
	return __uninitialized_copy(first, last, d_first, POD_type);
}

template< class ForwardIt, class T >
void uninitialized_fill(ForwardIt first, ForwardIt last, const T& value)
{
	typedef typename nano::type_traits<T>::is_POD_type POD_type;
	__uninitialized_fill(first, last, value, POD_type);
}

template< class ForwardIt, class Size, class T >
void uninitialized_fill_n(ForwardIt first, Size count, const T& value)
{
	typedef typename nano::type_traits<T>::is_POD_type POD_type;
	__uninitialized_fill_n(first, count, value, POD_type);
}

template< class OutputIt, class T >
class raw_storage_iterator
	: public iterator< output_iterator_tag, void, void, void, void >
{
	explicit raw_storage_iterator(OutputIt it)
	{

	}

	raw_storage_iterator& operator=(const T& el)
	{

	}

	raw_storage_iterator& operator*()
	{

	}

	raw_storage_iterator& operator++()
	{

	}

	raw_storage_iterator operator++(int)
	{

	}
};

}

#endif
