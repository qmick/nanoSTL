#ifndef __LIST_HPP__
#define __LIST_HPP__
#include "memory.hpp"
#include "iterator.hpp"

namespace nano{

template< class Value >
struct list_node
{
	typedef list_node<Value>* node_ptr;
	node_ptr prev;
	node_ptr next;
	Value value;
};

template< class Value, class Ref, class Ptr >
class list_iterator
{
public:
	typedef bidirectional_iterator_tag iterator_category;
	typedef Value value_type;
	typedef Ref reference;
	typedef Ptr pointer;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef list_node<Value>* node_ptr; node_ptr;
	typedef list_iterator<Value, Value&, Value*> iterator;
	typedef list_iterator<Value, Ref, Ptr> my_type;

public:
	list_iterator() {}
	list_iterator(const node_ptr node)
		: current(node) {}
	list_iterator(const my_type& other)
		: current(other.current) {}

	bool operator==(const my_type& other) const
	{
		return current == other.current;
	}

	bool operator!=(const my_type& other) const
	{
		return current != other.current;
	}

	reference operator*() const
	{
		return (*current).value;
	}

	pointer operator->() const
	{
		return &(operator*());
	}

	my_type& operator++()
	{
		current = current->next;
		return *this;
	}

	my_type& operator++(int)
	{
		my_type temp = *this;
		++*this;
		return temp;
	}

	my_type& operator--()
	{
		current = current->prev;
		return *this;
	}

	my_type& operator++(int)
	{
		my_type temp = *this;
		--*this;
		return temp;
	}

private:
	node_ptr current;
};

template < class T, class Allocator = allocator<T> >
class list
{
public:
	typedef list_node<T> node;
	typedef list_node<T>* node_ptr;
	typedef T value_type;
	typedef T& reference;
	typedef const T& const_reference;
	typedef T* const_pointer;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	typedef list_iterator<T, T&, T*>  iterator;
	typedef list_iterator<T, const T&, const T*> const_iterator;
	typedef nano::reverse_iterator<iterator> reverse_iterator;
	typedef nano::reverse_iterator<const_iterator> const_reverse_iterator;

	typedef typename Allocator::template rebind<list_node>::other node_allocator;
	typedef simple_allocator<list_node, node_allocator> list_allocator;

	list()
	{
		empty_init();
	}

	explicit list(size_type count, value_type value = value_type())
	{
		if (count == 0)
		{
			empty_init();
			return;
		}

		header = get_node(count, value);
		tail = header + count - 1;
	}

	~list()
	{
		clear();
	}

	list& operator=(const list& other)
	{
		//TODO:list operator=
	}

	void assign(size_type count, const T& value)
	{
		fill_assign(count, value);
	}
	
	//If type of InputIt is integer, it should not be treat as iterator
	//and assign(size_type, const T&) should be called
	template<class InputIt>
	void assign(InputIt first, InputIt last)
	{
		assign_dispatch(first, last, is_integral(*first));
	}

	reference front()
	{
		return *header;
	}

	reference back()
	{
		return *tail;
	}

	iterator begin()
	{
		return iterator(header);
	}

	const_iterator begin() const
	{
		return const_iterator(header);
	}

	iterator end()
	{
		return iterator(tail);
	}

	const_iterator end() const
	{
		return const_iterator(tail);
	}

	reverse_iterator rbegin()
	{
		return reverse_iterator(end());
	}

	const_reverse_iterator rbegin() const
	{
		return const_reverse_iterator(end());
	}

	reverse_iterator rend()
	{
		return reverse_iterator(begin());
	}
	
	const_reverse_iterator rend() const
	{
		return const_reverse_iterator(begin());
	}

	bool empty() const
	{
		return header == tail;
	}

	size_type size() const
	{
		return element_count;
	}

	size_type max_size() const
	{
		return size_type(-1) / sizeof(list_node<T>);
	}
	void clear()
	{
		while (header)
		{
			node_ptr temp = header;
			header = header->next;
			delete_node(temp);
		}
		element_count = 0;
		tail = 0;
		end_node->prev = 0;
		end_node->next = 0;
	}

	iterator insert(iterator pos, const T& value)
	{
		//TODO
		node_ptr temp = pos.current->prev;
		node_ptr cur = get_node(1, value);
		
		cur->next = pos->current;
		if (temp)
			temp->next = cur;
		else
			header = cur;

		++element_count;
	}

	void insert(iterator pos, size_type count, const T& value)
	{
		//TODO
		if (count == 0) return;

		node_ptr temp = pos.current->prev;
		node_ptr cur = get_node(count, value);

		for (int i = 0; i < count - 1; ++i)
		{
			cur->next = cur + 1;
			++cur;
		}
		(cur + count)->next = pos->current;
		if (temp)
			temp->next = cur;
		else
			header = cur;

		element_count += count;
		if (pos.current == tail)
			tail += count;
	}

	template< class InputIt >
	void insert(iterator pos, InputIt first, InputIt last)
	{
		//TODO
		for (; first != last; ++first)
		{
			node_ptr cur = get_node(1, *first);
			
		}
		
	}

	iterator erase(iterator pos)
	{
		//TODO:list erase1
	}

	iterator erase(iterator first, iterator last)
	{
		//TODO:list erase2
	}

	void push_back(const T& value)
	{
		//TODO:list push_back
	}

	void pop_back()
	{
		//TODO:list pop_back
	}

	void push_front(const T& value)
	{
		//TODO:list push_front
	}

	void pop_front()
	{
		//TODO:list pop_front
	}
	
	void resize(size_type count, T value = T())
	{
		//TODO:list resize
	}

	void swap(list& other)
	{
		//TODO:list swap
	}

private:
	void empty_init()
	{
		header = 0;
		tail = 0;
		element_count = 0;
		end_node.next = 0;
		end_node.prev = 0;
	}

	node_ptr get_node(size_type count = 1, value_type value = value_type())
	{
		node_ptr cur = (node_ptr)list_allocator::allocate(count);
		construct(&(cur->value), &((cur + count - 1)->value), value);
	}

	void delete_node(node_ptr ptr)
	{
		destroy(ptr);
		return list_allocator::deallocate(ptr);
	}

	void assign_dispatch(size_type count, const T& value, true_type)
	{
		fill_assign(count, value);
	}

	template< class InputIt >
	void assign_dispatch(InputIt first, InputIt last, false_type)
	{
		copy_assign(first, last);
	}

	void fill_assign(size_type count, const T& value)
	{
		uninitialized_fill_n(header, count, value);
	}

	template< class InputIt >
	void copy_assign(InputIt first, InputIt last)
	{
		uninitialized_copy(first, last, header);
	}

private:
	node_ptr header;
	node_ptr tail;
	node end_node;
	size_type element_count;
};

}

#endif
