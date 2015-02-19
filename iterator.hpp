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
	typedef reverse_iterator<Iterator> my_type;

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
		--current;
		return (*this);
	}

	//Predecrement
	reverse_iterator& operator--()
	{
		++current;
		return (*this);
	}

	//Postincrement
	reverse_iterator operator++(int)
	{
		my_type tmp = *this;
		--current;
		return tmp;
	}

	//Postdecrement
	reverse_iterator operator--(int)
	{
		my_type tmp = *this;
		++current;
		return tmp;
	}

	reverse_iterator operator+(difference_type n) const
	{
		return my_type(current - n);
	}

	reverse_iterator operator-(difference_type n) const
	{
		return my_type(current + n);
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

template< class InputIt, class Distance >
inline void advance(InputIt& it, Distance n)
{
	typedef typename iterator_traits<InputIt>::iterator_category category;
	__advance(it, n, category);
}

template< class RanIt, class Distance >
inline void __advance(RanIt& it, Distance n, random_access_iterator_tag)
{
	it += n;
}

template< class BidIt, class Distance >
inline void __advance(BidIt& it, Distance n, bidirectional_iterator_tag)
{
	if (n > 0)
		while (n--) ++it;
	else
		while (n++) --it;
	
}

template< class InputIt, class Distance >
inline void __advance(InputIt& it, Distance n, output_iterator_tag)
{

}

template< class InputIt >
inline typename iterator_traits<InputIt>::difference_type
distance(InputIt first, InputIt last)
{
	typedef typename iterator_traits<InputIt>::iterator_category category;
	return __distance(first, last, category);
}

template< class RanIt >
inline typename iterator_traits<RanIt>::difference_type
__distance(RanIt first, RanIt last, random_access_iterator_tag)
{
	return last - first;
}

template< class InputIt >
inline typename iterator_traits<InputIt>::difference_type
__distance(InputIt first, InputIt last, input_iterator_tag)
{
	typename iterator_traits<InputIt>::difference_type return_type;
	return_type dist = 0;
	while (first != last)
	{
		++first;
		++dist;
	}
	return distance;
}

}

