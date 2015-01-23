#ifndef _VECTOR_HPP_
#define _VECTOR_HPP_

#include "memory.hpp"
#include "iterator.hpp"

namespace nano{

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


    vector()
    {
        //TODO
    }
    explicit vector(size_type count)
    {
        //TODO
    }

    template< class InputIt >
    vector(InputIt first, InputIt last)
    {
        //TODO
    }


    ~vector()
    {
        //TODO
    }

    void assign(size_type count, const_reference value)
    {
        //TODO
    }

    template < class InputIt >
    void assign(InputIt first, InputIt last)
    {
        //TODO
    }

    //Element access
    reference at(size_type pos)
    {
        //TODO
    }

    const_reference at(size_type pos) const
    {
        //TODO
    }

    reference operator[](size_type pos)
    {
        //TODO
    }

    const_reference operator[](size_type pos) const
    {
        //TODO
    }

    reference front()
    {
        //TODO
    }

    const_reference front()  const
    {
        //TODO
    }

    reference back()
    {
        //TODO
    }

    const_reference back() const
    {
        //TODO
    }

    //Iterators
    iterator begin()
    {
        //TODO
    }

    const_iterator begin() const
    {
        //TODO
    }

    iterator end()
    {
        //TODO
    }

    const_iterator end() const
    {
        //TODO
    }

    reverse_iterator rbegin()
    {
        //TODO
    }    

    const_reverse_iterator rbegin() const
    {
        //TODO
    }

    reverse_iterator rend()
    {
        //TODO
    }

    const_reverse_iterator rend() const
    {
        //TODO
    }

    //Capacity
    bool empty() const
    {
        //TODO
    }

    size_type size() const
    {
        //TODO
    }

    size_type max_size() const
    {
        //TODO
    }

    void reserve(size_type new_cap)
    {
        //TODO
    }

    size_type capacity() const
    {
        //TODO
    }

    //Modifiers
    void clear()
    {
        //TODO
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

    void swap(vector<T>& other)
    {
        //TODO
    }
};

}

#endif
