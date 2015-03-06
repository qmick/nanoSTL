#ifndef __FUNCTIONAL_HPP__
#define __FUNCTIONAL_HPP__

namespace nano {

//Arithmetic operations
template< class T >
struct plus
{
	T operator()(const T& lhs, const T& rhs) const
	{
		return lhs + rhs;
	}
};

template< class T >
struct minus
{
	T operator()(const T& lhs, const T& rhs) const
	{
		return lhs - rhs;
	}
};

template< class T >
struct multiplies
{
	T operator()(const T& lhs, const T& rhs) const
	{
		return lhs * rhs;
	}
};

template< class T >
struct divides
{
	T operator()(const T& lhs, const T& rhs) const
	{
		return lhs / rhs;
	}
};

template< class T >
struct modulus
{
	T operator()(const T& lhs, const T& rhs) const
	{
		return lhs % rhs;
	}
};

template< class T >
struct negate
{
	T operator()(const T& arg) const
	{
		return -arg;
	}
};

//Comparisons
template< class T >
struct equal_to
{
	bool operator()(const T& lhs, const T& rhs) const
	{
		return lhs == rhs;
	}
};

template< class T >
struct not_equal_to
{
	bool operator()(const T& lhs, const T& rhs) const
	{
		return lhs != rhs;
	}
};

template< class T >
struct greater
{
	bool operator()(const T& lhs, const T& rhs) const
	{
		return lhs > rhs;
	}
};

template< class T >
struct less
{
	bool operator()(const T& lhs, const T& rhs) const
	{
		return lhs < rhs;
	}
};

template< class T >
struct greater_equal
{
	bool operator()(const T& lhs, const T& rhs) const
	{
		return lhs >= rhs;
	}
};

template< class T >
struct less_equal
{
	bool operator()(const T& lhs, const T& rhs) const
	{
		return lhs <= rhs;
	}
};

//Logical operations
template< class T >
struct logical_and
{
	bool operator()(const T& lhs, const T& rhs) const
	{
		return lhs && rhs;
	}
};

template< class T >
struct logical_or
{
	bool operator()(const T& lhs, const T& rhs) const
	{
		return lhs || rhs;
	}
};

template< class T >
struct logical_not
{
	bool operator()(const T& arg) const
	{
		return !arg;
	}
};

//Bitwise operations
template< class T >
struct bit_and
{
	T operator()(const T& lhs, const T& rhs) const
	{
		return lhs & rhs;
	}
};

template< class T >
struct bit_or
{
	T operator()(const T& lhs, const T& rhs) const
	{
		return lhs | rhs;
	}
};

template< class T >
struct bit_xor
{
	T operator()(const T& lhs, const T& rhs) const
	{
		return lhs ^ rhs;
	}
};


//Negators
template< class Predicate >
struct unary_negate : public unary_function < Predicate::argument_type, bool >
{
public:
	explicit unary_negate(Predicate const& pred)
		: my_pred(pred){}

	bool operator()(argument_type const& x) const
	{
		return !my_pred(x);
	}

protected:
	Predicate my_pred;
};

template< class Predicate >
struct binary_negate :
	public binary_function <
	Predicate::first_argument_type,
	Predicate::second_argument_type,
	bool >
{
public:
	explicit binary_negate(Predicate const& pred)
		: my_pred(pred){}
	bool operator()(first_argument_type const& x,
		second_argument_type const& y) const
	{
		return !my_pred(x, y);
	}

protected:
	my_pred;
};

template< class Predicate >
unary_negate<Predicate> not1(const Predicate& pred)
{
	return unary_negate<Predicate>(pred);
}

template< class Predicate >
binary_negate<Predicate> not2(const Predicate& pred)
{
	return binary_negate<Predicate>(pred);
}

//Deprecated in C++11
template <typename ArgumentType, typename ResultType>
struct unary_function
{
public:
	typedef ArgumentType argument_type;
	typedef ResultType result_type;
};

template< class Arg1, class Arg2, class Result > 
struct binary_function
{
public:
	typedef Arg1 first_argument_type;
	typedef	Arg2 second_argument_type;
	typedef	Result result_type;
};

}

#endif