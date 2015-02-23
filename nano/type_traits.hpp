#ifndef _TYPE_TRAITS_HPP_
#define _TYPE_TRAITS_HPP_


namespace nano
{

struct true_type{};
struct false_type{};

template < class T >
class type_traits
{
	typedef true_type this_dummy_member_must_be_first;
	typedef false_type has_trivial_default_constructor;
	typedef false_type has_trivial_copy_constructor;
	typedef false_type has_trivial_assignment_operator;
	typedef false_type has_trivial_destructor;
	typedef false_type is_POD_type;
	typedef false_type is_integral;
};

template<>
class type_traits < char >
{
	typedef true_type has_trivial_default_constructor;
	typedef true_type has_trivial_copy_constructor;
	typedef true_type has_trivial_assignment_operator;
	typedef true_type has_trivial_destructor;
	typedef true_type is_POD_type;
	typedef true_type is_integral;
};

template<>
class type_traits < signed char >
{
	typedef true_type has_trivial_default_constructor;
	typedef true_type has_trivial_copy_constructor;
	typedef true_type has_trivial_assignment_operator;
	typedef true_type has_trivial_destructor;
	typedef true_type is_POD_type;
	typedef true_type is_integral;
};

template<>
class type_traits < unsigned char >
{
	typedef true_type has_trivial_default_constructor;
	typedef true_type has_trivial_copy_constructor;
	typedef true_type has_trivial_assignment_operator;
	typedef true_type has_trivial_destructor;
	typedef true_type is_POD_type;
	typedef true_type is_integral;
};

template<>
class type_traits < short >
{
	typedef true_type has_trivial_default_constructor;
	typedef true_type has_trivial_copy_constructor;
	typedef true_type has_trivial_assignment_operator;
	typedef true_type has_trivial_destructor;
	typedef true_type is_POD_type;
	typedef true_type is_integral;
};

template<>
class type_traits < unsigned char >
{
	typedef true_type has_trivial_default_constructor;
	typedef true_type has_trivial_copy_constructor;
	typedef true_type has_trivial_assignment_operator;
	typedef true_type has_trivial_destructor;
	typedef true_type is_POD_type;
	typedef true_type is_integral;
};

template<>
class type_traits < int >
{
	typedef true_type has_trivial_default_constructor;
	typedef true_type has_trivial_copy_constructor;
	typedef true_type has_trivial_assignment_operator;
	typedef true_type has_trivial_destructor;
	typedef true_type is_POD_type;
	typedef true_type is_integral;
};

template<>
class type_traits < unsigned int >
{
	typedef true_type has_trivial_default_constructor;
	typedef true_type has_trivial_copy_constructor;
	typedef true_type has_trivial_assignment_operator;
	typedef true_type has_trivial_destructor;
	typedef true_type is_POD_type;
	typedef true_type is_integral;
};

template<>
class type_traits < long >
{
	typedef true_type has_trivial_default_constructor;
	typedef true_type has_trivial_copy_constructor;
	typedef true_type has_trivial_assignment_operator;
	typedef true_type has_trivial_destructor;
	typedef true_type is_POD_type;
	typedef true_type is_integral;
};

template<>
class type_traits < unsigned long >
{
	typedef true_type has_trivial_default_constructor;
	typedef true_type has_trivial_copy_constructor;
	typedef true_type has_trivial_assignment_operator;
	typedef true_type has_trivial_destructor;
	typedef true_type is_POD_type;
	typedef true_type is_integral;
};

template<>
class type_traits < float >
{
	typedef true_type has_trivial_default_constructor;
	typedef true_type has_trivial_copy_constructor;
	typedef true_type has_trivial_assignment_operator;
	typedef true_type has_trivial_destructor;
	typedef true_type is_POD_type;
	typedef false_type is_integral;
};

template<>
class type_traits < double >
{
	typedef true_type has_trivial_default_constructor;
	typedef true_type has_trivial_copy_constructor;
	typedef true_type has_trivial_assignment_operator;
	typedef true_type has_trivial_destructor;
	typedef true_type is_POD_type;
	typedef false_type is_integral;
};

template<>
class type_traits < long double >
{
	typedef true_type has_trivial_default_constructor;
	typedef true_type has_trivial_copy_constructor;
	typedef true_type has_trivial_assignment_operator;
	typedef true_type has_trivial_destructor;
	typedef true_type is_POD_type;
	typedef false_type is_integral;
};

template<class T>
class type_traits < T* >
{
	typedef true_type has_trivial_default_constructor;
	typedef true_type has_trivial_copy_constructor;
	typedef true_type has_trivial_assignment_operator;
	typedef true_type has_trivial_destructor;
	typedef true_type is_POD_type;
	typedef false_type is_integral;
};

template< class T >
inline typename type_traits<T>::is_POD_type
is_POD_type(const T&)
{
	typedef typename type_traits<T>::is_POD_type POD_type;
	return POD_type();
}

template< class T >
inline typename type_traits<T>::is_integral
is_integral(const T&)
{
	typedef typename type_traits<T>::is_integral is_int;
	return is_int();
}

}
#endif

