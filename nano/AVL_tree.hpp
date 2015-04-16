#ifndef __NANO_AVL_TREE_HPP__
#define __NANO_AVL_TREE_HPP__

#include "../memory.hpp"
#include "../algorithm.hpp"

namespace nano {

template< class Value >
struct AVL_tree_node
{
	typedef rb_tree_node<Value>* node_ptr;
	node_ptr parent;
	node_ptr left;
	node_ptr right;
	Value value;
};

template< class Value, class Ref, class Ptr >
struct AVL_tree_iterator
{
	typedef AVL_tree_node<Value>* node_ptr;
	typedef bidirectional_iterator_tag iterator_category;
	typedef Value value_type;
	typedef Ref reference;
	typedef Ptr pointer;
	typedef ptrdiff_t difference_type;
	typedef AVL_tree_iterator<Value, Value&, Value*> iterator;
	typedef AVL_tree_iterator<Value, const Value&, const Value*> const_iterator;
	typedef AVL_tree_iterator<Value, Ref, Ptr> my_type;

	node_ptr node;

	AVL_tree_iterator() {}
	AVL_tree_iterator(node_ptr x) { node = x; }
	AVL_tree_iterator(const iterator &other) { node = other.node; }

	bool operator==(const my_type& other) const
	{
		return node == other.node;
	}

	bool operator!=(const my_type& other) const
	{
		return node != other.node;
	}

	reference operator*()const
	{
		return node->value;
	}

	pointer operator->() const
	{
		return &(operator*());
	}

	my_type& operator++()
	{
		increment();
		return *this;
	}

	my_type operator++(int)
	{
		my_type self = *this;
		increment();
		return self;
	}

	my_type& operator--()
	{
		decrement();
		return *this;
	}

	my_type operator--(int)
	{
		my_type self = *this;
		decrement();
		return self;
	}

	void increment()
	{
		if (node->right != 0)
		{
			node = node->right;
			while (node->left != 0)
				node = node->left;
		}
		else
		{
			node_ptr y = node->parent;
			while (node == y->right)
			{
				node = y;
				y = y->parent;
			}
			if (node->right != y)
				node = y;
		}
	}

	void decrement()
	{
		if (node->color == color_red &&
			node->parent->parent == node)
			node = node->right;
		else if (node->left != 0)
		{
			node = node->left;
			while (node->right != 0)
				node = node->right;
		}
		else
		{
			node_ptr y = node->parent;
			while (y->left == node)
			{
				node = y;
				y = y->parent;
			}
			node = y;
		}

	}
};

template< class Key, class Compare, class Allocator = allocator<Key> >
class AVL_tree
{
public:
	typedef AVL_tree_node<Key> tree_node;
	typedef tree_node* node_ptr;
	typedef typename Allocator::template rebind<tree_node>::other node_allocator;
	typedef typename simple_allocator<tree_node, node_allocator> tree_allocator;
	typedef Key value_type;
	typedef Key* pointer;
	typedef const Key* const_pointer;
	typedef Key& reference;
	typedef const Key& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef AVL_tree_iterator<value_type, reference, pointer> iterator;
	typedef AVL_tree_iterator<value_type, const_reference, const_pointer> const_iterator;
	typedef nano::reverse_iterator<iterator> reverse_iterator;
	typedef nano::reverse_iterator<const_iterator> const_reverse_iterator;
	typedef AVL_tree<Key, Compare, Allocator> my_type;

public:
	explicit AVL_tree(const Compare& comp = Compare())
		: node_count(0), compare(comp)
	{
		//TODO
	}

	AVL_tree(const my_type& x)
		: node_count(0), compare(x.compare)
	{
		//TODO
	}

	~AVL_tree()
	{
		clear();
		put_node(header);
	}

	my_type& operator=(const my_type& x)
	{
		//TODO
	}

//public interface
public:
	Compare value_comp() const
	{
		return compare;
	}

	iterator begin()
	{
		return leftmost();
	}

	const_iterator begin() const
	{
		return leftmost();
	}

	iterator end()
	{
		return header;
	}

	const_iterator end() const
	{
		return header;
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

	iterator empty() const
	{
		return node_count == 0;
	}

	size_type size() const
	{
		return node_count;
	}

	size_type max_size() const
	{
		return size_type(-1);
	}

	void swap(my_type& other)
	{
		nano::swap(header, other.header);
		nano::swap(node_count, other.node_count);
		nano::swap(compare, other.compare);
	}

public:
	pair<iterator, bool> insert_unique(const value_type& v)
	{
		//TODO
	}

	terator insert_equal(const value_type& v)
	{
		//TODO
	}

	void erase(iterator pos)
	{
		//TODO
	}

	void erase(iterator first, iterator last)
	{
		//TODO
	}

	size_type erase(const value_type &x)
	{
		//TODO
	}

	pair<iterator, iterator> equal_range(const Key& key)
	{
		//TODO
	}

	pair<iterator, iterator> equal_range(const Key& key) const
	{
		//TODO
	}

	iterator lower_bound(const Key& key)
	{
		//TODO
	}

	const_iterator lower_bound(const Key& key) const
	{
		//TODO
	}

	iterator upper_bound(const Key& key)
	{
		//TODO
	}

	const_iterator upper_bound(const Key& key) const
	{
		//TODO
	}

	size_type count(const Key& key) const
	{
		//TODO
	}

	iterator find(const Key& key)
	{
		//TODO
	}

	const_iterator find(const Key& key) const
	{
		//TODO
	}

	void clear()
	{
		//TODO
	}

protected:
	node_ptr get_node() 
	{ return tree_allocator::allocate(); }
	void put_node(node_ptr p) 
	{ tree_allocator::deallocate(p); }
	node_ptr create_node(const value_type & x)
	{
		node_ptr temp = get_node();
		try
		{
			construct(&temp->value, x);
		}
		catch (...)
		{
			put_node(temp);
		}
		return temp;
	}

	node_ptr clone_node(node_ptr x)
	{
		node_ptr temp = create_node(x->value);
		temp->left = 0;
		temp->right = 0;
		return temp;
	}

	void destroy_node(node_ptr p)
	{
		destroy(&p->value);
		put_node(p);
	}

protected:
	size_type node_count;
	node_ptr header;
	Compare compare;

	node_ptr& root() const { return (node_ptr&) header->parent; }

	static node_ptr minimun(node_ptr x)
	{
		while (x->left != 0)
			x = x->left;
		return x;
	}

	static node_ptr maximum(node_ptr x)
	{
		while (x->right != 0)
			x = x->right;
		return x;
	}

	node_ptr& leftmost() const
	{
		return (node_ptr&) header->left;
	}

	node_ptr& rightmost() const
	{
		return (node_ptr&) header->right;
	}
};

}

#endif