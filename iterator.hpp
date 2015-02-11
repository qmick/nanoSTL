#pragma once
#include <stddef.h>
namespace nano{

struct input_iterator_tag{};
struct output_iterator_tag{};
struct forward_iterator_tag : public input_iterator_tag{};
struct bidirectional_iterator_tag : public forward_iterator_tag{};
struct random_access_iterator_tag : public bidirectional_iterator_tag{};

template< class Iterator >
struct iterator_traits
{
	typedef typename Iterator::iterator_category iterator_category;
	typedef typename Iterator::value_type value_type;
	typedef typename Iterator::different_type different_type;
	typedef typename Iterator::pointer pointer;
	typedef typename Iterator::reference reference;
};

template< class T >
struct iterator_traits < T* >
{
	typedef ptrdiff_t difference_type;
	typedef T value_type;
	typedef T* pointer;
	typedef T& reference;
	typedef random_access_iterator_tag iterator_category;
};

template< class T >
struct iterator_traits < const T* >
{
	typedef ptrdiff_t difference_type;
	typedef T value_type;
	typedef const T* pointer;
	typedef const T& reference;
	typedef random_access_iterator_tag iterator_category;
};

template<
	class Category,
	class T,
	class Pointer = T*,
	class Reference = T&,
	class Distance = ptrdiff_t >
struct iterator
{
	typedef T value_type;
	typedef Distance difference_type;
	typedef Pointer	pointer;
	typedef Reference reference;
	typedef Category iterator_category;

};

template< class Iterator >
class reverse_iterator : public iterator <
	typename iterator_traits<Iterator>::iterator_category,
	typename iterator_traits<Iterator>::value_type,
	typename iterator_traits<Iterator>::difference_type,
	typename iterator_traits<Iterator>::pointer,
	typename iterator_traits<Iterator>::reference >
{
protected:
	Iterator current;

public:
	typedef Iterator iterator_type;
	typedef reverse_iterator<Iterator> My_type;

	reverse_iterator()
	{

	}

	explicit reverse_iterator(Iterator x)
		: current(x)
	{

	}

	//Copy constructor
	template< class U >
	reverse_iterator(const reverse_iterator<U>& other)
		: current(other.base())
	{

	}

	template< class U >
	reverse_iterator& operator=(const reverse_iterator<U>& other)
	{
		this->current = other.base();
		return (*this);
	}

	//Return the underlying base iterator
	Iterator base() const
	{
		return current;
	}

	reference operator*() const
	{
		Iterator tmp = current;
		return *--tmp;
	}

	pointer operator->() const
	{
		return nano::addressof(operator*());
	}

	//Preincrement
	reverse_iterator& operator++()
	{
		current--;
		return (*this);
	}

	//Predecrement
	reverse_iterator& operator--()
	{
		current++;
		return (*this);
	}

	//Postincrement
	reverse_iterator operator++(int)
	{
		My_type tmp = *this;
		current--;
		return tmp;
	}

	//Postdecrement
	reverse_iterator operator--(int)
	{
		My_type tmp = *this;
		current++;
		return tmp;
	}

	reverse_iterator operator+(difference_type n) const
	{
		return My_type(current - n);
	}

	reverse_iterator operator-(difference_type n) const
	{
		return My_type(current + n);
	}
	reverse_iterator& operator+=(difference_type n)
	{
		current -= n;
		return (*this);
	}
	reverse_iterator& operator-=(difference_type n)
	{
		current += n;
		return (*this);
	}

	reference operator[](different_type n) const
	{
		return (*(*this + n));
	}
};

}

