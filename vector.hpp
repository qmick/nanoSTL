#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include "memory.hpp"
#include "iterator.hpp"
#include "algorithm.hpp"
#include <stdexcept>

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
		range_destroy(begin(), end());
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
		if (pos < size())
			return (*this)[pos];
		else
			throw std::out_of_range;
    }

    const_reference at(size_type pos) const
    {
		if (pos < size())
			return (*this)[pos];
		else
			throw std::out_of_range;
    }

    reference operator[](size_type pos)
    {
		return *(begin() + pos);
    }

    const_reference operator[](size_type pos) const
    {
		return *(begin() + pos);
    }

    reference front()
    {
		return *begin();
    }

    const_reference front()  const
    {
		return *begin();
    }

    reference back()
    {
		return *(end() - 1);
    }

    const_reference back() const
    {
		return *(end() - 1);
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
		return begin() == end();
    }

    size_type size() const
	{
		return size_type(end() - begin());
	}

    size_type max_size() const
    {
		return size_type(-1) / sizeof(T);
    }

    void reserve(size_type new_cap)
    {
		//TODO
		if (new_cap > this->capacity())
		{
			pointer temp_first = Allocator::allocate(new_cap);
			try
			{
				iterator temp_last = uninitialized_copy(begin(), end(), temp);
				range_destroy(begin(), end());
				my_first = temp_first;
				my_last  = temp_last;
			}
			catch (...)
			{
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
		range_destroy(begin(), end());
    }

    iterator insert(const_iterator pos, const T& value)
    {
        //TODO
    }

    iterator insert(const_iterator pos, size_type count, const T& value)
    {
        //TODO
    }

    template <class InputIt>
    iterator insert(const_iterator pos, InputIt first, InputIt last)
    {
        //TODO
    }

    iterator erase(const_iterator pos)
    {
        //TODO
    }

    iterator erase(const_iterator first, const_iterator last)
    {
        //TODO
    }

    void push_back(const T& value)
    {
        //TODO
    }

    void pop_back()
    {
        //TODO
    }

    void resize(size_type count)
    {
        //TODO
    }

    void resize(size_type count, const value_type& value)
    {
        //TODO
    }

    void swap(my_type& other)
    {
        //TODO
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
class vector< bool, Allocator >
{

};

}



#endif
