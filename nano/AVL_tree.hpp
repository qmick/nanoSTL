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

template< class Value, class Ref, class Ptr>
struct AVL_tree_iterator
{	
	typedef bidirectional_iterator_tag iterator_category;
	typedef Value value_type;
	typedef Ref reference;
	typedef Ptr pointer;
	typedef ptrdiff_t difference_type;
	typedef AVL_tree_node<Value>* node_ptr;
	typedef AVL_tree_iterator<Value, Value&, Value*> iterator;
	typedef AVL_tree_iterator<Value, const Value&, const Value*> const_iterator;
	typedef AVL_tree_iterator<Value, Ref, Ptr> my_type;

	node_ptr node;

	AVL_tree_iterator() {}
	AVL_tree_iterator(node_ptr x) 
	{ 
		node = x; 
	}

	AVL_tree_iterator(const iterator &other) 
	{ 
		node = other.node; 
	}

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
		if (node->right != 0) //find minimum of the right
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

		return *this;
	}

	my_type operator++(int)
	{
		my_type self = *this;
		++(*this);

		return self;
	}

	my_type& operator--()
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

		return *this;
	}

	my_type operator--(int)
	{
		my_type self = *this;
		--(*this);

		return self;
	}


};

template< class Key, class Value, class Compare, class Allocator = allocator<Value> >
class AVL_tree
{
public:
	//data type
	typedef AVL_tree_node<Key> tree_node;
	typedef tree_node* node_ptr;
	typedef Key key_type;
	typedef Value value_type;
	typedef value_type* pointer;
	typedef const value_type* const_pointer;
	typedef value_type& reference;
	typedef const value_type& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;

	//iterator
	typedef AVL_tree_iterator<value_type, reference, pointer> iterator;
	typedef AVL_tree_iterator<value_type, const_reference, const_pointer> const_iterator;
	typedef nano::reverse_iterator<iterator> reverse_iterator;
	typedef nano::reverse_iterator<const_iterator> const_reverse_iterator;

	//rebind allocator to tree_node
	typedef typename Allocator::template rebind<tree_node>::other node_allocator;
	typedef typename simple_allocator<tree_node, node_allocator> tree_allocator;

	typedef AVL_tree<Key, Compare, Allocator> my_type;

public:
	explicit AVL_tree(const Compare& comp = Compare())
		: node_count(0), compare(comp)
	{
		init();
	}

	AVL_tree(const my_type& other)
		: node_count(0), compare(other.compare)
	{
		init();
	}

	~AVL_tree()
	{
		clear();
		put_node(header);
	}

	my_type& operator=(const my_type& other)
	{
		clone_tree(root(), other.root());
		compare = other.compare;
		node_count = compare.node_count;
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

	iterator insert_equal(const value_type& v)
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
		return pair<iterator, iterator>(lower_bound(key), upper_bound(key));
	}

	pair<iterator, iterator> equal_range(const Key& key) const
	{
		pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key));
	}

	iterator lower_bound(const Key& key)
	{
		node_ptr y = header;
		node_ptr x = root();

		while (x != 0)
		{
			if (!compare(x->value, key))
			{
				y = x;
				x = x->left;
			}
			else
				x = x->right;
		}
		return iterator(y);
	}

	const_iterator lower_bound(const Key& key) const
	{
		node_ptr y = header;
		node_ptr x = root();

		while (x != 0)
		{
			if (!compare(x->value, key))
			{
				y = x;
				x = x->left;
			}
			else
				x = x->right;
		}
		return const_iterator(y);
	}

	iterator upper_bound(const Key& key)
	{
		node_ptr y = header;
		node_ptr x = root();

		while (x != 0)
		{
			if (compare(x->value, key))
			{
				y = x;
				x = x->left;
			}
			else
				x = x->right;
		}
		return iterator(y);
	}

	const_iterator upper_bound(const Key& key) const
	{
		node_ptr y = header;
		node_ptr x = root();

		while (x != 0)
		{
			if (compare(x->value, key))
			{
				y = x;
				x = x->left;
			}
			else
				x = x->right;
		}
		return const_iterator(y);
	}

	size_type count(const Key& key) const
	{
		pair<const_iterator, const_iterator> p = equal_range(key);
		return (size_t) distance(p.first, p.second);
	}

	iterator find(const Key& key)
	{
		iterator j = lower_bound(key);
		return (j == end() || compare(key, j.node->value)) ? end() : j;
	}

	const_iterator find(const Key& key) const
	{
		const_iterator j = lower_bound(key);
		return (j == end() || compare(key, j.node->value)) ? end() : j;
	}

	void clear()
	{
		destroy_tree(root());		
		root() = 0;
		leftmost() = 0;
		rightmost() = 0;
		node_count = 0;
	}

protected:
	size_type node_count;
	node_ptr header;
	Compare compare;

	node_ptr& root() const 
	{ 
		return (node_ptr&) header->parent; 
	}

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
	

private:
	node_ptr get_node()
	{
		return tree_allocator::allocate();
	}

	void put_node(node_ptr p)
	{
		tree_allocator::deallocate(p);
	}

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
			temp = 0;
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



	//initialize header
	void init()
	{
		header = get_node();
		root() = 0;
		leftmost() = header;
		rightmost() = header;
	}

	//copy a tree whose root is 'src' to 'dst'
	void clone_tree(node_ptr dst, const node_ptr src)
	{
		if (dst)
		{
			destroy_tree(dst);
		}

		while (src)
		{
			dst = create_node(dst->value);
			clone_tree(dst->right, src->right);
			dst = dst->left;
			src = src->left;
		}
	}

	//destroy a tree whose root is 'target'
	void destroy_tree(node_ptr target)
	{
		if (target)
		{
			destroy_tree(target->left);
			destroy_tree(target->right);
			destroy_node(target);
		}
	}
};



}

#endif
