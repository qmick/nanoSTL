#ifndef __NANO_AVL_TREE_HPP__
#define __NANO_AVL_TREE_HPP__

#include "../memory.hpp"

namespace nano {

template< class Value >
struct AVL_tree_node
{
	typedef AVL_tree_node<Value>* node_ptr;
	node_ptr parent;
	node_ptr left;
	node_ptr right;
	Value value;
};
template< class Key, class Compare, class Allocator = allocator<Key> >
class AVL_tree
{

};

}

#endif