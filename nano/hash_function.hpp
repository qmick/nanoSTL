#ifndef __HASH_FUNCTION_HPP__
#define __HASH_FUNCTION_HPP__

#include "../string.hpp"

namespace nano {

size_t BKDRHash(const char* str)
{
	size_t seed = 131; // 31 131 1313 13131 131313 etc..
	size_t hash = 0;

	while (*str)
	{
		hash = hash * seed + (*str++);
	}

	return (hash & 0x7FFFFFFF);
}

// AP Hash Function
size_t APHash(const char *str)
{
	size_t hash = 0;
	int i;

	for (i = 0; *str; i++)
	{
		if ((i & 1) == 0)
		{
			hash ^= ((hash << 7) ^ (*str++) ^ (hash >> 3));
		}
		else
		{
			hash ^= (~((hash << 11) ^ (*str++) ^ (hash >> 5)));
		}
	}

	return (hash & 0x7FFFFFFF);
}

template< class Key >
struct hash
{

};

template<>
struct hash< string >
{
	size_t operator()(const string& str)
	{
		return BKDRHash(str.c_str());
	}
};

template<>
struct hash< char* >
{
	size_t operator()(const char* str)
	{
		return BKDRHash(str);
	}
};


template<>
struct hash< long >
{
	long operator()(const long x) const
	{
		return x;
	}
};

template<>
struct hash< unsigned long >
{
	unsigned long operator()(const unsigned long x) const
	{
		return x;
	}
};

template<>
struct hash< int >
{
	int operator()(const int x) const
	{
		return x;
	}
};

template<>
struct hash< unsigned int >
{
	unsigned int operator()(const unsigned int x)
	{
		return x;
	}
};

template<>
struct hash< short >
{
	short operator()(const short x) const
	{
		return x;
	}
};

template<>
struct hash< unsigned short >
{
	unsigned short operator()(const unsigned short x) const
	{
		return x;
	}
};

template<>
struct hash< char >
{
	char operator()(const char x) const
	{
		return x;
	}
};

template<>
struct hash< unsigned char >
{
	temp;
	unsigned char operator()(const unsigned char x) const
	{
		return x;
	}
};

}

#endif