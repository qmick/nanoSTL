#ifndef __NANO_RB_TREE_HPP__
#define __NANO_RB_TREE_HPP__

namespace nano {

const bool color_red = false;
const bool color_black = true;

template< class T >
struct rb_tree_node
{
	typedef rb_tree_node<T>* node_ptr;
	bool color;
	node_ptr parent;
	node_ptr left;
	node_ptr right;
	T value;
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

template< class Key, class Value, class Compare, class Allocator = allocator<Key> >
class rb_tree
{
public:
	typedef rb_tree_node<Key> tree_node;
	typedef tree_node* node_ptr;
	typedef simple_allocator<tree_node, Allocator> tree_allocator;
	typedef Key key_type;
	typedef Value value_type;
	typedef Value* pointer;
	typedef const Value* const_pointer;
	typedef Value& reference;
	typedef const Value& const_reference;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef rb_tree_iterator<value_type, reference, pointer> iterator;
	
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
	Compare key_compare;

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


};

}

#endif