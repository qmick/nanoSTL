#ifndef __NANO_RB_TREE_HPP__
#define __NANO_RB_TREE_HPP__

namespace nano {

const bool color_red = false;
const bool color_black = true;

template< class Value >
struct rb_tree_node
{
	typedef rb_tree_node<T>* node_ptr;
	bool color;
	node_ptr parent;
	node_ptr left;
	node_ptr right;
	Value value;
};

template< class Value, class Ref, class Ptr >
struct rb_tree_iterator
{
	typedef rb_tree_node<Value>* node_ptr;
	typedef bidirectional_iterator_tag iterator_catagory;
	typedef ptrdiff_t difference_type;
	typedef Ref reference;
	typedef Ptr pointer;
	typedef rb_tree_iterator<Value, Value&, Value*> iterator;
	typedef rb_tree_iterator<Value, const Value&, const Value*> const_iterator;
	typedef rb_tree_iterator<Value, Ref, Ptr> my_type;
	
	node_ptr node;

	rb_tree_iterator() {}
	rb_tree_iterator(node_ptr x) { node = x; }
	rb_tree_iterator(const iterator &other) { node = other.node; }

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
			node_ptr temp = node->parent;
			while (node == y->right)
			{
				node = temp;
				temp = temp->parent;
			}
			if (node->right != temp)
				node = temp;
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
			node_ptr temp = node->parent;
			while (temp->right == node)
			{
				node = temp;
				temp = temp->parent;
			}
			node = temp;
		}
		
	}
};

template< class Value, class Compare, class Allocator = allocator<Value> >
class rb_tree
{
public:
	typedef rb_tree_node<Value> tree_node;
	typedef tree_node* node_ptr;
	typedef simple_allocator<tree_node, Allocator> tree_allocator;
	typedef Value value_type;
	typedef Value* pointer;
	typedef const Value* const_pointer;
	typedef Value& reference;
	typedef const Value& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef rb_tree_iterator<value_type, reference, pointer> iterator;
	typedef rb_tree<Value, Compare, Allocator> my_type;
	
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

	static maximum(node_ptr x)
	{
		while (x->right != 0)
			x = x->right;
		return x;
	}

	node_ptr& root() const
	{
		return (node_ptr&) header->parent;
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

	iterator insert(node_ptr x, node_ptr y, const value_type& v)
	{
		node_ptr z;
		if (y == header || x != 0 || compare(v, y))
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

		z->parent = z;
		z->left = 0;
		z->right = 0;

		rebalance(z);
		++node_count;
		return iterator(z);
	}

	node_ptr copy(node_ptr x, node_ptr p)
	{

	}

	void erase(node_ptr x)
	{

	}
	
	void rebalance(node_ptr x)
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

	void rotate_left(node_ptr x)
	{
		node_ptr y = x->right;
		x->right = y->left;
		if (y > left != 0)
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

public:
	rb_tree(const Compare& comp = Compare())
		: node_count(0), compare(comp) 
	{
		init();
	}

	~rb_tree()
	{
		clear();
		put_node(header);
	}

	my_type& operator=(const my_type& x);

public:
	Compare value_comp() const { return compare; }
	iterator begin(){ return leftmost(); }
	iterator end(){ return header; }
	iterator empty() const { return node_count == 0; }
	size_type size() const { return node_count; }
	size_type max_size() const { return size_type(-1); }

public:
	pair<iterator, bool> insert_unique(const value_type& v)
	{
		node_ptr y = header;
		node_ptr x = root();
		bool comp = true;

		while (x != 0)
		{
			y = x;
			comp = compare(v, x);
			x = comp ? x->left : x->right;
		}

		iterator j = iterator(y);
		if (comp)
		{
			if (j == begin())
				return pair<iterator, bool>(insert(x, y, v), true);
			else
				--j;
			if (compare(j.node, v))
				return pair<iterator, bool>(insert(x, y, v), true);
			return pair<iterator, bool>(j, false);
		}
	}
	iterator insert_equal(const value_type& v)
	{
		node_ptr y = header;
		node_ptr x = root();
		while (x != 0)
		{
			y = x;
			x = compare(v, x) ? x->left : x->right;
		}
		return insert(x, y, v);
	}
	void clear();
};

}

#endif