#pragma once
#include "memory.hpp"
#include "iterator.hpp"

namespace nano{
	template<class T, class Alloc = allocator<T>>
	class vector
	{
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef pointer iterator;
		typedef const_pointer const_iterator;
		typedef size_t size_type;


		vector()
		{

		}
		explicit vector(size_type count)
		{

		}

		template<class InputIt>
		vector(InputIt first, InputIt last)
		{

		}


		~vector()
		{

		}

		void assign(szie_type count, const_reference value)
		{

		}

		template <class InputIt>
		void assign(InputIt first, InputIt last)
		{

		}

		reference at(size_type pos)
		{

		}

		const_reference at(size_type pos) const
		{

		}

		reference operator[](size_type pos)
		{

		}

		const_reference operator[](size_type pos) const
		{

		}

		reference front()
		{

		}

		const_reference front()  const
		{

		}

		reference back()
		{

		}

		const_reference back() const
		{

		}

		iterator begin()
		{

		}

		const_iterator begin() const
		{

		}

		iterator end()
		{

		}

		const_iterator end() const
		{

		}

		bool empty() const
		{

		}

		size_type size() const
		{

		}

		size_type max_size() const
		{

		}

		void reserve(size_type new_cap)
		{

		}

		size_type capacity() const
		{

		}

		void clear()
		{

		}

		iterator insert(const_iterator pos, const T& value)
		{

		}

		iterator insert(const_iterator pos, size_type count, const T& value)
		{

		}

		template <class InputIt>
		iterator insert(const_iterator pos, InputIt first, InputIt last)
		{

		}

		iterator erase(const_iterator pos)
		{

		}

		iterator erase(const_iterator first, const_iterator last)
		{

		}

		void push_back(const T& value)
		{

		}

		void pop_back()
		{

		}

		void resize(size_type count)
		{

		}

		void resize(size_type count, const value_type& value)
		{

		}

		void swap(vector<T>& other)
		{

		}
	};
}

