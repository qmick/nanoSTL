#ifndef __NANO_RB_TREE_HPP__
#define __NANO_RB_TREE_HPP__

namespace nano {

const bool color_red = false;
const bool color_black = true;

template< class T >
struct rb_tree_node
{
	typedef rb_tree_node* node_ptr;
	bool color;
	node_ptr parent;
	node_ptr left;
	node_ptr right;
};

template< class Key, class Compare, class Allocator = allocator<Key> >
class rb_tree
{
	typedef rb_tree_node<Key> tree_node;
	typedef tree_node* node_ptr;

};

}

#endif