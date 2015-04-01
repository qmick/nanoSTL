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
	typedef typename Iterator::difference_type difference_type;
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
	typename iterator_traits<Iterator>::pointer,
	typename iterator_traits<Iterator>::reference,
	typename iterator_traits<Iterator>::difference_type >
{
protected:
	Iterator current;

public:
	typedef Iterator iterator_type;
	typedef reverse_iterator<Iterator> my_type;

	reverse_iterator() {}

	explicit reverse_iterator(Iterator x) : current(x) {}

	//Copy constructor
	template< class U >
	reverse_iterator(const reverse_iterator<U>& other)
		: current(other.base()) {}

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
		return *(--tmp);
	}

	pointer operator->() const
	{
		return &(operator*());
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

	reference operator[](difference_type n) const
	{
		return (*(*this + n));
	}

	bool operator<(const my_type& other) const
	{
		return current < other.base();
	}

	bool operator<=(const my_type& other) const
	{
		return !(other.base() < current);
	}

	bool operator>(const my_type& other) const
	{
		return other.base() < current;
	}

	bool operator>=(const my_type& other) const
	{
		return !(current < other.base());
	}

	bool operator==(const my_type& other) const
	{
		return current == other.base();
	}

	bool operator!=(const my_type& other) const
	{
		return !(current == other.base());
	}
};

template< class It >
inline typename iterator_traits<It>::value_type
value_type(const It&)
{
	typedef typename iterator_traits<It>::value_type value_type;
	return value_type();
}

template< class It >
inline typename iterator_traits<It>::iterator_category
iterator_category(const It&)
{
	typedef typename iterator_traits<It>::iterator_category category;
	return category();
}

template< class It >
inline typename iterator_traits<It>::difference_type
difference_type(const It&)
{
	typedef typename iterator_traits<It>::difference_type difference_type;
	return difference_type();
}

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
	while (n--) ++it;
}

template< class InputIt >
inline typename iterator_traits<InputIt>::difference_type
distance(InputIt first, InputIt last)
{
	return __distance(first, last, iterator_category(first));
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
	typename iterator_traits<InputIt>::difference_type dist = 0;
	while (first != last)
	{
		++first;
		++dist;
	}
	return dist;
}



}

