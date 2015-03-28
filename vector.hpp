#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include "memory.hpp"
#include "iterator.hpp"
#include "algorithm.hpp"
#include <stdexcept>
#include <cassert>

namespace nano {

template< class T, class Allocator = allocator<T> >
class vector
{
public:
    //Member types
    typedef T value_type;
    typedef Allocator allocator_type;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T* pointer;
    typedef const T* const_pointer;
    typedef pointer iterator;
    typedef const_pointer const_iterator;
    typedef nano::reverse_iterator<iterator> reverse_iterator;
    typedef nano::reverse_iterator<const_iterator> const_reverse_iterator;
	typedef vector<T, allocator<T> > my_type;
	typedef simple_allocator<T, Allocator> vector_allocator;

	//Member functions
	vector() : my_first(0), my_last(0), my_end(0), element_count(0) {}

	explicit vector(size_type count, const T& value = T())	//May be removed	
		: my_first(0), my_last(0), my_end(0), element_count(0)
	{
		assign(count, value);
	}

    template< class InputIt >
    vector(InputIt first, InputIt last)
		: my_first(0), my_last(0), my_end(0), element_count(0)
    {
		assign(first, last);
    }

	vector(const my_type& other)
		: my_first(0), my_last(0), my_end(0), element_count(0)
	{
		*this = other;
	}

    ~vector()
    {
		destroy(my_first, my_last);
		vector_allocator::deallocate(my_first);
    }

	vector& operator=(const my_type& other)
	{
		assign(other.begin(), other.end());
		return *this;
	}


    void assign(size_type count, const_reference value)
    {
		fill_assign(count, value);
    }

    template < class InputIt >
    void assign(InputIt first, InputIt last)
    {
		assign_dispatch(first, last, is_integral(first));
    }



	allocator_type get_allocator() const
	{
		return Allocator();
	}

    //Element access
    reference at(size_type pos)
    {
		if (pos < element_count)
			return (*this)[pos];
		else
			throw std::out_of_range("pos out of bound");
    }

    const_reference at(size_type pos) const
    {
		if (pos < element_count)
			return (*this)[pos];
		else
			throw std::out_of_range("pos out of bound");
    }

    reference operator[](size_type pos)
    {
		return *(my_first + pos);
    }

    const_reference operator[](size_type pos) const
    {
		return *(my_first + pos);
    }

    reference front()
    {
		return *my_first;
    }

    const_reference front()  const
    {
		return *my_first;
    }

    reference back()
    {
		return *(my_last - 1);
    }

    const_reference back() const
    {
		return *(my_last - 1);
	}

    //Iterators

    iterator begin() { return my_first; }
    const_iterator begin() const { return my_first; }
	iterator end() { return my_last; }
	const_iterator end() const { return my_last; }

	reverse_iterator rbegin()
	{ return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const 
	{ return const_reverse_iterator(end()); }
	reverse_iterator rend() 
	{ return reverse_iterator(begin()); }
	const_reverse_iterator rend() const 
	{ return const_reverse_iterator(begin()); }

    //Capacity

    bool empty() const
    {
		return my_first == my_last;
    }

    size_type size() const
	{
		return element_count;
	}

    size_type max_size() const
    {
		return size_type(-1) / sizeof(T);
    }

    void reserve(size_type new_cap)
    {
		if (new_cap > capacity())
		{
			pointer temp_first = vector_allocator::allocate(new_cap);
			pointer temp_end = temp_first + new_cap;
			pointer temp_last;
			try
			{
				temp_last = uninitialized_copy(my_first, my_last, temp_first);			
			}
			catch (...)
			{
				//If copy operation fails, memory must be deallocated
				vector_allocator::deallocate(temp_first);
				return;
			}
			destroy(begin(), end());
			vector_allocator::deallocate(my_first);
			my_first = temp_first;
			my_last = temp_last;
			my_end = temp_end;
		}
    }

    size_type capacity() const
    {
		return my_end - my_first;
    }

    //Modifiers
    void clear()
    {
		erase(my_first, my_last);
    }

    iterator insert(iterator pos, const T& value)
    {
		if (element_count + 1 <= capacity())
		{			
			copy_backward(my_first, my_last, my_last + 1);
			construct(pos, value);
			++my_last;
			++element_count;
			return pos;
		}
		else
		{
			pointer temp_first = vector_allocator::allocate(2 * capacity() + 1);  
			pointer mid, temp_last;
			try
			{
				mid = uninitialized_copy(my_first, pos, temp_first);
				temp_last = uninitialized_copy(pos, my_last, mid + 1);
			}
			catch (...)
			{
				//If copy operation fails, memory must be deallocated
				vector_allocator::deallocate(temp_first);
				return pos;
			}

			construct(mid, value);
			destroy(begin(), end());
			vector_allocator::deallocate(my_first);
			my_first = temp_first;
			my_last = temp_last;
			++element_count;
			return mid;
		}		
    }


    iterator insert(iterator pos, size_type count, const T& value)
    {
		return fill_insert(pos, count, value);
    }

    template <class InputIt>
    iterator insert(iterator pos, InputIt first, InputIt last)
    {		
		return insert_dispatch(pos, first, last, is_integral(first));
    }

    iterator erase(iterator pos)
    {
		if (pos >= my_last && pos < my_last)
		{
			destroy(pos);
			copy(pos + 1, my_last, pos);
			--my_last;
			--element_count;
		}
		return pos;
    }

    iterator erase(iterator first, iterator last)
    {
		if (first < last && first >= my_first && last <= my_last)
		{
			destroy(first, last);
			copy(last, my_last, first);
			my_last -= last - first;
			element_count = my_last - my_first;
		}
		return first;
    }

    void push_back(const T& value)
    {
		if (element_count + 1 > capacity())
			reserve(max(element_count + 1, 2 * element_count));			
		construct(my_last, value);
		++my_last;
		++element_count;
    }

    void pop_back()
    {
		--my_last;
		destroy(my_last);
		--element_count;
    }

	void resize(size_type count, T value = T())
    {
		reserve(count);
		if (count > element_count)
		{
			temp_last = my_last;		
			uninitialized_fill_n(temp_last, my_first + count, value);
		}
		else
		{
			destroy(my_first + count + 1, my_last);
			my_last = my_first + count;
		}
		element_count = count;
    }

    void swap(my_type& other)
    {
		nano::swap(my_first, other.my_first);
		nano::swap(my_last, other.my_last);
		nano::swap(my_end, other.my_end);
		nano::swap(element_count);
	}

	private:
		pointer my_first; //First of array
		pointer my_last; //Last of array
		pointer my_end; //End of space
		size_type element_count;

		void fill_assign(size_type count, const_reference value)
		{
			if (count > capacity())
			{
				size_t prev_cap = capacity();

				int new_cap = max(2 * prev_cap, count);
				pointer temp_first = vector_allocator::allocate(new_cap);
				pointer temp_last;
				try
				{
					uninitialized_fill_n(temp_first, count, value);				
				}
				catch (...)
				{
					vector_allocator::deallocate(temp_first);
					return;
				}
				temp_last = temp_first + count;
				destroy(my_first, my_last);
				vector_allocator::deallocate(my_first);
				my_first = temp_first;
				my_last = my_first + count;
				my_end = my_first + new_cap;
			}
			else
			{
				destroy(my_first, my_last);
				uninitialized_fill_n(my_first, count, value);
				my_last = my_first + count;
			}
			element_count = count;
		}

		template< class InputIt >
		void copy_assign(InputIt first, InputIt last)
		{
			size_t count = distance(first, last);

			if (count > capacity())
			{
				size_t prev_cap = capacity();

				int new_cap = max(2 * prev_cap, count);
				pointer temp_first = vector_allocator::allocate(new_cap);
				pointer temp_last;
				try
				{
					temp_last = uninitialized_copy(first, last, temp_first);
				}
				catch (...)
				{
					vector_allocator::deallocate(temp_first);
					return;
				}
				destroy(my_first, my_last);
				vector_allocator::deallocate(my_first);
				my_first = temp_first;
				my_last = my_first + count;
				my_end = my_first + new_cap;
			}
			else
			{
				destroy(my_first, my_last);
				my_last = uninitialized_copy(first, last, my_first);
			}
			element_count = my_last - my_first;
		}


		template< class InputIt >
		void assign_dispatch(InputIt first, InputIt last, true_type)
		{
			fill_assign(first, last);
		}

		template< class InputIt >
		void assign_dispatch(InputIt first, InputIt last, false_type)
		{
			copy_assign(first, last);
		}

		iterator fill_insert(iterator pos, size_type count, const_reference value)
		{
			if (count == 0)
				return pos;
			else if (element_count + count <= capacity())
			{
				copy_backward(my_first, my_last, my_last + count);
				uninitialized_fill_n(pos, count, value);
				element_count += count;
				return pos;
			}
			else
			{
				size_t expected_size = max(capacity() + count, 2 * capacity());
				pointer temp_first = vector_allocator::allocate(expected_size);
				pointer mid, temp_last;
				try
				{
					mid = uninitialized_copy(my_first, pos, temp_first);
					temp_last = uninitialized_copy(pos, my_last, mid + count);
					uninitialized_fill_n(mid, count, value);
				}
				catch (...)
				{
					//If copy operation fails, memory must be deallocated
					vector_allocator::deallocate(temp_first);
					return pos;
				}
				destroy(begin(), end());
				vector_allocator::deallocate(my_first);
				my_first = temp_first;
				my_last = temp_last;
				element_count += count;
				return mid;
			}
		}

		template< class InputIt >
		iterator copy_insert(iterator pos, InputIt first, InputIt last)
		{
			size_t count = distance(first, last);

			if (count == 0)
				return pos;
			else if (element_count + count <= capacity())
			{
				copy_backward(my_first, my_last, my_last + count);
				uninitialized_copy(first, last, pos);
				element_count += count;
				return pos;
			}
			else
			{
				size_t expected_size = max(capacity() + count, 2 * capacity());
				pointer temp_first = vector_allocator::allocate(expected_size);
				pointer mid, temp_last;

				try
				{
					mid = uninitialized_copy(my_first, pos, temp_first);
					temp_last = uninitialized_copy(pos, my_last, mid + count);
					uninitialized_copy(first, last, mid);
				}
				catch (...)
				{
					//If copy operation fails, memory must be deallocated
					vector_allocator::deallocate(temp_first);
					return pos;
				}

				destroy(begin(), end());
				vector_allocator::deallocate(my_first);
				my_first = temp_first;
				my_last = temp_last;
				element_count += count;
				return mid;
			}
		}

		template< class InputIt >
		iterator insert_dispatch(iterator pos, InputIt first, InputIt last, true_type)
		{
			return fill_insert(pos, first, last);
		}

		template< class InputIt >
		iterator insert_dispatch(iterator pos, InputIt first, InputIt last, false_type)
		{
			return copy_insert(pos, first, last);
		}
};

template< class Allocator >
//Bit vector of high space efficiency
class vector< bool, Allocator >
{

};

}



#endif
