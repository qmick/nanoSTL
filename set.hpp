#ifndef __SET_HPP__
#define __SET_HPP__

#include "memory.hpp"
#include "iterator.hpp"
#include "utility.hpp"

namespace nano
{
//TODO:default parameter of Compare
template < class Key, class Compare, class Allocator = nano::allocator<Key> >
class set
{
public:
	typedef Key key_type;
	typedef Key value_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef Compare key_compare;
    typedef Compare value_compare;	
	typedef Allocator allocator_type;
	typedef typename Allocator::reference reference;
	typedef typename Allocator::const_reference const_reference;
	typedef typename Allocator::pointer pointer;
	typedef typename Allocator::const_pointer const_pointer;
	typedef nano::iterator<nano::bidirectional_iterator_tag, Key> iterator;
	typedef nano::iterator<nano::bidirectional_iterator_tag, Key, const Key*, const Key&> const_iterator;
	typedef nano::reverse_iterator<iterator> reverse_iterator;
	typedef nano::reverse_iterator<const_iterator> const_reverse_iterator;	

	set()
	{
		//TODO:set constructor
	}

	~set()
	{
		//TODO:set destructor
	}

	set& operator=(const set& other)
	{
		//TODO:set operator=
	}

	allocator_type get_allocator() const
	{
		//TODO:set get_allocator const
	}

	iterator begin()
	{
		//TODO:set begin 
	}

	const_iterator begin() const
	{
		//TODO:set begin const
	}

	iterator end()
	{
		//TODO:set end
	}

	const_iterator end() const
	{
		//TODO:set end const
	}

	reverse_iterator rbegin()
	{
		//TODO:set rbegin
	}	

	const_reverse_iterator rbegin() const
	{
		//TODO:set rend const
	}

	reverse_iterator rend()
	{
		//TODO:set rend
	}

	const_reverse_iterator rend() const
	{
		//TODO:set rend const
	}

	//Capacity
	void empty() const
	{
		//TODO:set empty const
	}
	
	size_type size() const
	{
		//TOD:set size const
	}

	size_type max_size() const
	{
		//TODO:set max_size
	}

	//Modifiers
	void clear()
	{
		//TODO:set clear
	}

	nano::pair<iterator, bool> insert(const value_type& value)
	{
		//TODO:set insert1
	}

	iterator insert(iterator hint, const value_type& value)
	{
		//TODO:set insert2
	}

	template< class InputIt>
	void insert(InputIt first, InputIt last)
	{
		//TODO:set insert3
	}

	void erase(iterator pos)
	{
		//TODO:set erase1
	}

	void erase(iterator first, iterator last)
	{
		//TODO:set erase2
	}

	size_type erase(const key_type& key)
	{
		//TODO:set erase3
	}
	
	void swap(set& other)
	{
		//TODO:set swap
	}
	
	//Lookup
	size_type count(const Key& key) const
	{
		//TODO:set count
	}

	iterator find(const Key& key)
	{
		//TODO:set find1
	}

	const_iterator find(const Key& key) const
	{
		//TODO:set find2
	}

	nano::pair<iterator, iterator> equal_range(const Key& key)
	{
		//TODO:set equal_range
	}

	nano::pair<const_iterator, const_iterator> equal_range(const Key& key) const
	{
		//TODO:set equal_range const
	}

	iterator lower_bound(const Key& key)
	{
		//TODO:lower_bound
	}

	const_iterator lower_bound(const Key& key) const
	{
		//TODO:lower_bound const
	}

	iterator upper_bound(const Key& key)
	{
		//TODO:set upper_bound
	}

	const_iterator upper_bound(const Key& key) const
	{
		//TODO:set upper_bound const
	}

	//Observers
	key_compare key_comp() const
	{
		//TODO:set key_comp const
	}

	value_compare value_comp() const
	{
		//TODO:set value_comp
	}
};

template< class Key, class Compare, class Allocator = nano::allocator<Key> >
class multiset
{
public:
	//Member types
	typedef Key key_type;
	typedef Key value_type;
	typedef size_t size_type;
	typedef ptrdiff_t difference_type;
	typedef Compare key_compare;
	typedef Compare value_compare;
	typedef Allocator allocator_type;
	typedef typename Allocator::reference reference;
	typedef typename Allocator::const_reference const_reference;
	typedef typename Allocator::pointer pointer;
	typedef typename Allocator::const_pointer pointer;
	typedef nano::iterator<nano::bidirectional_iterator_tag, Key> iterator;
	typedef nano::iterator<nano::bidirectional_iterator_tag, Key, Key*, Key&> const_iterator;
	typedef nano::reverse_iterator<iterator> reverse_iterator;
	typedef nano::reverse_iterator<const_iterator> const_reverse_iterator;
	
	//Member functions
	explicit multiset(const Compare& comp = Compare(), 
					  const Allocator& alloc = Allocator())	
	{
		//TODO:multiset constructor1
	}

	template< class InputIt >
	multiset(InputIt first, InputIt last,
			 const Compare& comp = Compare(),
			 const Allocator& alloc = Allocator())
	{
		//TODO:multiset constructor2
	}

	multiset(const multiset& other)
	{
		//TODO:multiset constructor3
	}

	~multiset()
	{
		//TODO:multiset destructor
	}

	multiset& operator=(const multiset& other)
	{
		//TODO:multiset operator=
	}

	allocator_type get_allocator() const
	{
		//TODO:multiset get_allocator const
	}

	//Iterators
	iterator begin()
	{
		//TODO:multiset begin
	}

	const_iterator begin() const
	{
		//TODO:multiset begin const
	}
	
	iterator end()
	{
		//TODO:multiset end
	}

	const_iterator end() const
	{
		//TODO:multiset end const
	}

	reverse_iterator rbegin()
	{
		//TODO
	}

	const_reverse_iterator rbegin() const
	{
		//TODO
	}

	reverse_iterator rend()
	{
		//TODO
	}

	const_reverse_iterator rend() const
	{
		//TODO
	}

	//Capacity
	bool empty() const
	{
		//TODO
	}

	size_type size() const
	{
		//TODO
	}

	size_type max_size() const
	{
		//TODO
	}

	iterator insert(const value_type& value)
	{
		//TODO
	}

	iterator insert(iterator hint, const value_type& value)
	{
		//TODO
	}
	
	template< class InputIt >
	void insert(InputIt first, InputIt last)	
	{
		//TODO
	}

	void clear()
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

	size_type erase(const key_type& key)
	{
		//TODO
	}

	void swap(multiset& other)
	{
		//TODO
	}

	size_type count( const Key& key ) const
	{
		//TODO
	}

	iterator find( const Key& key )
	{
		//TODO
	}

	const_iterator find( const Key& key ) const
	{
		//TODO
	}

	std::pair<iterator,iterator> equal_range( const Key& key )
	{
		//TODO
	}

	iterator lower_bound( const Key& key )
	{
		//TODO
	}

	const_iterator lower_bound( const Key& key ) const
	{
		//TODO
	}

	iterator upper_bound( const Key& key )
	{
		//TODO
	}

	const_iterator upper_bound( const Key& key ) const
	{
		//TODO
	}

	std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const
	{
		//TODO
	}

	key_compare key_comp() const
	{
		//TODO
	}

	std::multiset::value_compare value_comp() const
	{
		//TODO
	}
};

}

#endif