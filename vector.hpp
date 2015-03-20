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
    typedef T             value_type;
    typedef Allocator     allocator_type;
    typedef size_t        size_type;
    typedef ptrdiff_t     difference_type;
    typedef T&            reference;
    typedef const T&      const_reference;
    typedef T*            pointer;
    typedef const T*      const_pointer;
    typedef pointer       iterator;
    typedef const_pointer const_iterator;
    typedef nano::reverse_iterator<iterator>       reverse_iterator;
    typedef nano::reverse_iterator<const_iterator> const_reverse_iterator;
	typedef vector<T, allocator<T> >               my_type;

	//Member functions
    vector()
		: my_first(0), my_last(0), my_end(0) {}

	explicit vector(size_type count, 
		            const T& value = T(),
		            const Allocator& alloc = Allocator())	//May be removed	
					: my_first(0), my_last(0), my_end(0)
	{
		this->vector_init(count, value, true_type()); //Call 
	}

    template< class InputIt >
    vector(InputIt first, InputIt last)
		: my_first(0), my_last(0), my_end(0)
    {
		this->vector_init(first, last, is_integral(InputIt()));
    }

	vector(const my_type& other)
		: my_first(0), my_last(0), my_end(0)
	{
		size_type count = other.size();
		if (count > 0)
		{
			this->reserve(count);
			memcpy(my_first, other.my_first, count * sizeof(T));
			my_last = my_first + count;
		}
	}

    ~vector()
    {
		destroy(my_first, my_last);
		Allocator::deallocate(my_first, capacity());
    }

	vector& operator=(const my_type& other)
	{
		size_type count = other.size();
		if (count > 0)
		{
			this->reserve(count);
			memcpy(my_first, other.my_first, count * sizeof(T));
			my_last = my_first + count;
		}
	}

    void assign(size_type count, const_reference value)
    {
		this->reserve(count);
		my_last = uninitialized_fill_n(my_first, count, value);
    }

    template < class InputIt >
    void assign(InputIt first, InputIt last)
    {
		
    }

	allocator_type get_allocator() const
	{
		return Allocator();
	}

    //Element access
    reference at(size_type pos)
    {
		if (pos < size() && pos >= my_first)
			return (*this)[pos];
		else
			throw std::out_of_range;
    }

    const_reference at(size_type pos) const
    {
		if (pos < size() && pos >= my_first)
			return (*this)[pos];
		else
			throw std::out_of_range;
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
		return size_type(my_last - my_first);
	}

    size_type max_size() const
    {
		return size_type(-1) / sizeof(T);
    }

    void reserve(size_type new_cap)
    {
		if (new_cap > this->capacity())
		{
			pointer temp_first = Allocator::allocate(new_cap);
			try
			{
				pointer temp_last = uninitialized_copy(my_first, my_last, temp_first);
				destroy(begin(), end());
				Allocator::deallocate(my_first, capacity());
				my_first = temp_first;
				my_last  = temp_last;
				
			}
			catch (...)
			{
				//If copy operation fails, memory must be deallocated
				Allocator::deallocate(temp_first, new_cap);
			}
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
		//pos should be within range
		assert(pos - my_first <= size() && pos >= my_first);

		if (size() + 1 <= capacity())
		{			
			copy_backward(my_first, my_last, my_last + 1);
			::new((void *) pos) T(value);
			return pos;
		}
		else
		{
			pointer temp_first = Allocator::allocate(2 * size());
			pointer mid, temp_last;
			try
			{
				mid = uninitialized_copy(my_first, pos, temp_first);
				temp_last = uninitialized_copy(pos, my_last, mid + 1);
			}
			catch (...)
			{
				//If copy operation fails, memory must be deallocated
				Allocator::deallocate(temp_first, 2 * size());
				return pos;
			}

			::new((void *) mid) T(value);
			destroy(begin(), end());
			Allocator::deallocate(my_first, capacity());
			my_first = temp_first;
			my_last = temp_last;
			return mid;
		}
    }


    iterator insert(iterator pos, size_type count, const T& value)
    {
		assert(pos - my_first <= size() && pos > my_first);

		if (count == 0)
			return pos;

		if (size() + count <= capacity())
		{
			copy_backward(my_first, my_last, my_last + count);
			uninitialized_fill_n(pos, count, value);
		}
		else
		{
			size_t expected_size = max(capacity() + count, 2 * capacity());
			pointer temp_first = Allocator::allocate(expected_size);
			pointer mid, temp_last;
			try
			{
				mid = uninitialized_copy(my_first, pos, temp_first);
				temp_last = uninitialized_copy(pos, my_last, mid + count);
				uninitialized_fill_n(mid, mid + count, value);
			}
			catch (...)
			{
				//If copy operation fails, memory must be deallocated
				Allocator::deallocate(temp_first, expected_size);
				return pos;
			}

			destroy(begin(), end());
			Allocator::deallocate(my_first, capacity());
			my_first = temp_first;
			my_last = temp_last;
			return mid;
		}
    }

    template <class InputIt>
    iterator insert(iterator pos, InputIt first, InputIt last)
    {		
		assert(pos - my_first <= size() && pos > my_first);

		size_t count = distance(first, last);

		if (count == 0)
			return pos;

		if (size() + count <= capacity())
		{
			copy_backward(my_first, my_last, my_last + count);
			uninitialized_copy(first, last, pos);
		}
		else
		{
			size_t expected_size = max(capacity() + count, 2 * capacity());
			pointer temp_first = Allocator::allocate(expected_size);
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
				Allocator::deallocate(temp_first, expected_size);
				return pos;
			}
			
			destroy(begin(), end());
			Allocator::deallocate(my_first, capacity());

			my_first = temp_first;
			my_last = temp_last;
			return mid;
		}
    }

    iterator erase(iterator pos)
    {
		if (pos >= my_last && pos < my_last)
		{
			pos->~T();
			copy(pos + 1, my_last, pos);
			--my_last;
		}
		return pos;
    }

    iterator erase(iterator first, iterator last)
    {
		if (first < last && first >= my_first && last < my_last)
		{
			destroy(first, last);
			copy(last, my_last, first);
			my_last -= last - first;
		}
		return first;
    }

    void push_back(const T& value)
    {
		insert(my_last, value);
    }

    void pop_back()
    {
		--my_last;
		destroy(my_last);
    }

	void resize(size_type count, T value = T())
    {
		if (count > size())
		{
			temp_last = my_last;
			reserve(count);
			uninitialized_fill_n(temp_last, count - (temp_last - my_last), value);
		}
    }

    void swap(my_type& other)
    {
		nano::swap(my_first, other.my_first);
		nano::swap(my_last, other.my_last);
		nano::swap(my_end, other.my_end);
	}

	private:
		pointer my_first; //First of array
		pointer my_last; //Last of array
		pointer my_end; //End of space

		template< class InputIt >
		void vector_init(InputIt count, InputIt value, true_type)
		{
			this->reserve(count);
			my_last = uninitialized_fill_n(my_first, count, value);
		}

		template< class InputIt >
		void vector_init(InputIt first, InputIt last, false_type)
		{
			this->fill_from_range(first, last, iterator_category(InputIt()));
		}
		
		template< class InputIt >
		void fill_from_range(InputIt first, InputIt last, input_iterator_tag)
		{
			for (; first != last; ++first)
				this->push_back(first);
		}

		template< class InputIt >
		void fill_from_range(InputIt first, InputIt last, forward_iterator_tag)
		{
			size_type count = static_cast<size_type>(distance(first, last));
			my_first        = Allocator::allocate(count);
			my_end          = my_first + count;
			my_last         = uninitialized_copy(first, last, begin());
		}

};

template< class Allocator >
//Bit vector of high space efficiency
class vector< bool, Allocator >
{

};

}



#endif
