#pragma once
#include <limits>
namespace nano{
	struct input_iterator_tag{};
	struct output_iterator_tag{};
	struct forward_iterator_tag : public input_iterator_tag{};
	struct bidirectional_iterator_tag : public forward_iterator_tag{};
	struct random_access_iterator_tag : public bidirectional_iterator_tag{};

	template<class Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::iterator_category iterator_category;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::different_type different_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
	};

	template<class T>
	struct iterator_traits < T* >
	{
		typedef ptrdiff_t difference_type;
		typedef T value_type;
		typedef T* pointer;
		typedef T& reference;
		typedef random_access_iterator_tag iterator_category;
	};

	template<class T>
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
		class Distance = std::ptrdiff_t,
		class Pointer = T*,
		class Reference = T&
	>
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
	public:
		typedef typename Iterator iterator_type;
		typedef	typename iterator_traits<Iterator>::difference_type difference_type;
		typedef	typename iterator_traits<Iterator>::pointer pointer;
		typedef	typename iterator_traits<Iterator>::reference reference;

		reverse_iterator()
		{

		}
	};
}

