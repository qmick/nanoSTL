#ifndef __NANO_RB_TREE_HPP__
#define __NANO_RB_TREE_HPP__

#include "../algorithm.hpp"

namespace nano {

const bool color_red = false;
const bool color_black = true;

template< class Value >
struct rb_tree_node
{
	typedef rb_tree_node<Value>* node_ptr;
	bool color;
	node_ptr parent;
	node_ptr left;
	node_ptr right;
	Value value;
};

template< class Value, class Ref, class Ptr >
struct rb_tree_iterator
{
	typedef bidirectional_iterator_tag iterator_category;
	typedef Value value_type;
	typedef Ref reference;
	typedef Ptr pointer;
	typedef ptrdiff_t difference_type;
	typedef rb_tree_node<Value>* node_ptr;
	typedef rb_tree_iterator<Value, Value&, Value*> iterator;
	typedef rb_tree_iterator<Value, const Value&, const Value*> const_iterator;
	typedef rb_tree_iterator<Value, Ref, Ptr> my_type;
	
	node_ptr node;

	rb_tree_iterator() {}
	rb_tree_iterator(node_ptr x) { node = x; }
	rb_tree_iterator(const iterator &other) { node = other.node; }

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

template< class Key, class Compare, class Allocator >
class rb_tree
{
public:
	typedef rb_tree_node<Key> tree_node;
	typedef tree_node* node_ptr;
	typedef typename Allocator::template rebind<tree_node>::other node_allocator;
	typedef simple_allocator<tree_node, node_allocator> tree_allocator;
	typedef Key value_type;
	typedef Key* pointer;
	typedef const Key* const_pointer;
	typedef Key& reference;
	typedef const Key& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef rb_tree_iterator<value_type, reference, pointer> iterator;
	typedef rb_tree_iterator<value_type, const_reference, const_pointer> const_iterator;
	typedef nano::reverse_iterator<iterator> reverse_iterator;
	typedef nano::reverse_iterator<const_iterator> const_reverse_iterator;
	typedef rb_tree<Key, Compare, Allocator> my_type;
	
protected:
	node_ptr get_node() { return tree_allocator::allocate(); }
	void put_node(node_ptr p) { tree_allocator::deallocate(p); }
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
		temp->color = x->color;
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

private:
	void init()
	{
		header = get_node();
		header->color = color_red;
		root() = 0;
		leftmost() = header;
		rightmost() = header;
	}

	node_ptr copy(node_ptr x, node_ptr p)
	{
		node_ptr top = clone_node(x);
		top->parent = p;

		try
		{
			if (x->right)
				top->right = copy(x->right, top);
			p = top;
			x = x->left;

			while (x != 0)
			{
				node_ptr y = clone_node(x);
				p->left = y;
				y->parent = p;
				if (x->right)
					y->right = copy(x->right, y);
				p = y;
				x = x->left;
			}
		}
		catch (...)
		{
			simple_erase_all(top);
		}
	}

	iterator insert(node_ptr x, node_ptr y, const value_type& v)
	{
		node_ptr z;
		if (y == header || x != 0 || compare(v, y->value))
		{
			z = create_node(v);
			y->left = z;
			if (y == header)
			{
				root() = z;
				rightmost() = z;
			}
			else if (y == leftmost())
				leftmost() = z;
		}
		else
		{
			z = create_node(v);
			y->right = z;
			if (y == rightmost())
				rightmost() = z;
		}

		z->parent = y;
		z->left = 0;
		z->right = 0;

		insert_rebalance(z);
		++node_count;
		return iterator(z);
	}

	//simply remove node x and all its children without rebalancing
	void simple_erase_all(node_ptr x)
	{
		while (x != 0)
		{
			simple_erase_all(x->right);
			node_ptr y = x->left;
			destroy_node(x);
			x = y;
		}
	}

	//remove a node x and rebalance if neccessary
	void delete_node(node_ptr z)
	{
		node_ptr y = z;
		bool y_color = y->color;
		node_ptr x;

		if (z->left == header)
		{
			x = z->right;
			transplant(z, z->right);
		}
		else if (z->right == header)
		{
			x = z->left;
			transplant(z, z->left);
		}
		else
		{
			y = minimun(z->right);
			y_color = y->color;
			x = y->right;
			if (y->parent == z)
				x->parent = y;
			else
			{
				transplant(y, y->right);
				y->right = z->right;
				y->right->parent = y;
			}
			transplant(z, y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
		if (y_color == color_black)
			delete_rebalance(x);
		--node_count;
	}
	
	void rotate_left(node_ptr x)
	{
		node_ptr y = x->right;
		x->right = y->left;
		if (y->left != 0)
			y->left->parent = x;
		y->parent = x->parent;

		if (x == root())
			root() = y;
		else if (x == x->parent->left)
			x->parent->left = y;
		else
			x->parent->right = y;
		y->left = x;
		x->parent = y;
	}

	void rotate_right(node_ptr x)
	{
		node_ptr y = x->left;
		x->left = y->right;
		if (y->right != 0)
			y->right->parent = x;
		y->parent = x->parent;

		if (x == root())
			root() = y;
		else if (x == x->parent->right)
			x->parent->right = y;
		else
			x->parent->left = y;
		y->right = x;
		x->parent = y;
	}

	void transplant(node_ptr u, node_ptr v)
	{
		if (u->parent == 0)
			root() = v;
		else if (u == u->parent->left)
			u->parent->left = v;
		else u->parent->right = v;
		v->parent = u->parent;
	}
	 
	void insert_rebalance(node_ptr x)
	{
		x->color = color_red;
		while (x != root() && x->parent->color == color_red)
		{
			if (x->parent == x->parent->parent->left)
			{
				node_ptr y = x->parent->parent->right;
				if (y && y->color == color_red)
				{
					x->parent->color = color_black;
					y->color = color_black;
					x->parent->parent->color = color_red;
					x = x->parent->parent;
				}
				else
				{
					if (x == x->parent->right)
					{
						x = x->parent;
						rotate_left(x);
					}
					x->parent->color = color_black;
					x->parent->parent->color = color_red;
					rotate_right(x->parent->parent);
				}
			}
			else
			{
				node_ptr y = x->parent->parent->left;
				if (y && y->color == color_red)
				{
					x->parent->color = color_black;
					y->color = color_black;
					x->parent->parent->color = color_red;
					x = x->parent->parent;
				}
				else
				{
					if (x == x->parent->left)
					{
						x = x->parent;
						rotate_right(x);
					}
					x->parent->color = color_black;
					x->parent->parent->color = color_red;
					rotate_left(x->parent->parent);
				}
			}
		}

		root()->color = color_black;
	}

	void delete_rebalance(node_ptr x)
	{
		while (x != root() && x->color == color_black)
		{
			if (x == x->parent->left)
			{
				node_ptr w = x->parent->right;
				if (w->color == color_red)
				{
					w->color = color_black;
					x->parent->color = color_red;
					rotate_left(x->parent);
					w = x->right;
				}
				if (w->left->color == color_black && w->right->color == color_black)
				{
					w->color = color_red;
					x = x->parent;
				}
				else
				{
					if (w->right->color == color_black)
					{
						w->left->color = color_black;
						w->color = color_red;
						rotate_right(w);
						w = x->parent->right;
					}
					w->color = x->parent->color;
					x->parent->color = color_black;
					w->right->color = color_black;
					rotate_left(x->parent);
					x = root();
				}
			}
			else
			{
				if (x == x->parent->right)
				{
					node_ptr w = x->parent->left;
					if (w->color == color_red)
					{
						w->color = color_black;
						x->parent->color = color_red;
						rotate_right(x->parent);
						w = x->left;
					}
					if (w->right->color == color_black && w->left->color == color_black)
					{
						w->color = color_red;
						x = x->parent;
					}
					else
					{
						if (w->left->color == color_black)
						{
							w->right->color = color_black;
							w->color = color_red;
							rotate_left(w);
							w = x->parent->left;
						}
						w->color = x->parent->color;
						x->parent->color = color_black;
						w->left->color = color_black;
						rotate_right(x->parent);
						x = root();
					}
				}
			}
		}
		x->color = color_black;
	}

public:
	explicit rb_tree(const Compare& comp = Compare())
		: node_count(0), compare(comp) 
	{
		init();
	}

	rb_tree(const my_type& x)
		: node_count(0), compare(x.compare)
	{
		if (x.root() == 0)
			init();
		else
		{
			header->color = color_red;
			root() = copy(x.root(), header);
			leftmost() = minimun(root());
			rightmost() = maximum(root());
		}
		node_count = x.node_count;
	}

	~rb_tree()
	{
		clear();
		put_node(header);
	}

	my_type& operator=(const my_type& x)
	{
		if (this != &x)
		{
			clear();
			compare = x.compare;
			if (x.root() != 0)
			{
				root() = copy(x.root(), x.header);
				leftmost() = minimun(root());
				rightmost() = maximum(root());
				node_count = x.node_count;
			}
		}
		return *this;
	}

public:
	Compare value_comp() const 
	{ return compare; }

	iterator begin()
	{ return leftmost(); }

	const_iterator begin() const 
	{ return leftmost(); }

	iterator end()
	{ return header; }

	const_iterator end() const 
	{ return header; }

	reverse_iterator rbegin() 
	{ return reverse_iterator(end()); }

	const_reverse_iterator rbegin() const 
	{ return const_reverse_iterator(end()); }

	reverse_iterator rend() 
	{ return reverse_iterator(begin()); }

	const_reverse_iterator rend() const 
	{ return const_reverse_iterator(begin()); }

	iterator empty() const 
	{ return node_count == 0; }

	size_type size() const 
	{ return node_count; }

	size_type max_size() const 
	{ return size_type(-1); }

	void swap(my_type& other)
	{
		nano::swap(header, other.header);
		nano::swap(node_count, other.node_count);
		nano::swap(compare, other.compare);
	}

public:
	pair<iterator, bool> insert_unique(const value_type& v)
	{
		node_ptr y = header;
		node_ptr x = root();
		bool comp = true;

		while (x != 0)
		{
			y = x;
			comp = compare(v, x->value);
			x = comp ? x->left : x->right;
		}

		iterator j = iterator(y);
		if (comp)
		{
			if (j == begin())
				return pair<iterator, bool>(insert(x, y, v), true);
			else
				--j;
		}
		if (compare(y->value, v))
			return pair<iterator, bool>(insert(x, y, v), true);
		return pair<iterator, bool>(j, false);		
	}
	
	iterator insert_equal(const value_type& v)
	{
		node_ptr y = header;
		node_ptr x = root();
		while (x != 0)
		{
			y = x;
			x = compare(v, x->value) ? x->left : x->right;
		}
		return insert(x, y, v);
	}
	
	void erase(iterator pos)
	{
		delete_node(pos->node);
	}

	void erase(iterator first, iterator last)
	{
		if (first == begin() && last == end())
			clear();
		else
		{
			for (iterator i = begin(); i != end(); ++i)
				delete_node(i->node);
		}
	}

	size_type erase(const value_type &x)
	{
		pair<iterator, iterator> range = equal_range(x);
		size_t pass = distance(range.first, range.second);

		if (pass == node_count)
			clear();
		else
		{
			for (size_t i = 0; i < pass; ++i, ++range.first)
				delete_node(range.first->node);
		}

		return pass;
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
		return (size_t)distance(p.first, p.second);
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
		if (node_count != 0)
		{
			simple_erase_all(root());
			leftmost() = header;
			rightmost() = header;
			root() = 0;
			node_count = 0;
		}
	}
};

}

#endif
