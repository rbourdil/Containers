#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <memory>
#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <algorithm>

#include "../alloc_help.hpp"
#include "../algorithm.hpp"
#include "../iterator/iterator_adaptors.hpp"
#include "pair.hpp"

namespace ft {

enum rb_tree_color { red = false, black = true };
enum null_marker { not_null = false, null = true };

// node struct used as base type for the tree
template <typename Key, typename T>
struct rb_node {

	typedef rb_node*	node_ptr;

	rb_node() :
		_color(),
		_is_null(),
		_key(Key()),
		_val(T()),
		_left(NULL),
		_right(NULL),
		_p(NULL)
		{ }
	
	rb_node(const Key& key, const T& val, node_ptr null_node) :
		_color(),
		_is_null(not_null),
		_key(key),
		_val(val),
		_left(null_node),
		_right(null_node),
		_p(null_node),
		_key_val(key, val)
		{ }
	
	rb_node(const rb_node& from) :
		_color(from._color),
		_is_null(from._is_null),
		_key(from._key),
		_val(from._val),
		_left(from._left),
		_right(from._right),
		_p(from._p),
		_key_val(from._key_val)
		{ }
	
	rb_tree_color	_color;
	null_marker		_is_null;
	Key				_key;
	T				_val;
	node_ptr		_left;
	node_ptr		_right;
	node_ptr		_p;
	ft::pair<Key, T>	_key_val;
};

template <typename Key, typename T>
struct	rb_tree_iterator
{
	typedef ft::pair<Key, T>	value_type;
	typedef value_type&			reference;
	typedef value_type*			pointer;
	typedef std::bidirectional_iterator_tag	iterator_category;
	typedef ptrdiff_t	difference_type;

	typedef	rb_node<Key, T>*	node_ptr;
	typedef rb_tree_iterator<Key, T>	self;

	public:

	// constructors/destructor

	rb_tree_iterator() :
		_node()
		{ }

	rb_tree_iterator(node_ptr node) :
		_node(node)
		{ }
	
	rb_tree_iterator(const rb_tree_iterator& from) :
		_node(from._node)
		{ }

	rb_tree_iterator&	operator=(const rb_tree_iterator& from)
	{
		_node = from._node;
		return (*this);
	}
	
	~rb_tree_iterator(void) { }


	// iterator requirements

	reference	operator*(void) const
	{
		return (_node->_key_val);
	}

	self&	operator++(void)
	{
		_node = _rb_tree_successor(_node);
		return (*this);
	}

	// input iterator requirements

	pointer	operator->(void) const
	{
		return (&_node->_key_val);
	}

	self	operator++(int)
	{
		self	tmp = *this;
		_node = _rb_tree_successor(_node);
		return (tmp);
	}

	friend bool	operator==(const self& x, const self& y)
	{
		return (x._node == y._node);
	}

	friend bool	operator!=(const self& x, const self& y)
	{
		return (x._node != y._node);
	}

	// bidirectional iterator requirements

	self&	operator--(void)
	{
		_node = _rb_tree_predecessor(_node);
		return (*this);
	}

	self	operator--(int)
	{
		self	tmp = *this;
		_node = _rb_tree_predecessor(_node);
		return (tmp);
	}

	node_ptr	_node;
};

template <typename Key, typename T>
struct	const_rb_tree_iterator
{
	typedef const ft::pair<Key, T>	value_type;
	typedef const value_type&		reference;
	typedef const value_type*		pointer;
	typedef std::bidirectional_iterator_tag	iterator_category;
	typedef ptrdiff_t	difference_type;

	typedef	const rb_node<Key, T>*	const_node_ptr;
	typedef const_rb_tree_iterator<Key, T>	self;
	typedef rb_tree_iterator<Key, T>	iterator;

	public:

	// constructors/destructor

	const_rb_tree_iterator() :
		_node()
		{ }

	const_rb_tree_iterator(const_node_ptr node) :
		_node(node)
		{ }
	
	const_rb_tree_iterator(const iterator& from) :
		_node(from._node)
		{ }

	~const_rb_tree_iterator(void) { }

	const_rb_tree_iterator&	operator=(const const_rb_tree_iterator& from)
	{
		_node = from._node;
		return (*this);
	}

	// iterator requirements

	reference	operator*(void) const
	{
		return (_node->_key_val);
	}

	self&	operator++(void)
	{
		_node = _rb_tree_successor(_node);
		return (*this);
	}

	// input iterator requirements

	pointer	operator->(void) const
	{
		return (&_node->_key_val);
	}

	self	operator++(int)
	{
		self	tmp = *this;
		_node = _rb_tree_successor(_node);
		return (tmp);
	}

	friend bool	operator==(const self& x, const self& y)
	{
		return (x._node == y._node);
	}

	friend bool	operator!=(const self& x, const self& y)
	{
		return (x._node != y._node);
	}

	// bidirectional iterator requirements

	self&	operator--(void)
	{
		_node = _rb_tree_predecessor(_node);
		return (*this);
	}

	self	operator--(int)
	{
		self	tmp = *this;
		_node = _rb_tree_predecessor(_node);
		return (tmp);
	}

	private:
	const_node_ptr	_node;
};

template <typename Key, typename T>
bool	_is_null_node(rb_node<Key, T>* x)
{
	if (x->_is_null == null)
		return (true);
	return (false);
}

template <typename Key, typename T>
rb_node<Key, T>*	_tree_minimum(rb_node<Key, T>* x)
{
	while (!_is_null_node(x->_left))
		x = x->_left;
	return (x);
}

template <typename Key, typename T>
rb_node<Key, T>*	_tree_maximum(rb_node<Key, T>* x)
{
	while (!_is_null_node(x->_right))
		x = x->_right;
	return (x);
}

template <typename Key, typename T>
rb_node<Key, T>*	_rb_tree_successor(rb_node<Key, T>* x)
{
	if (!_is_null_node(x->_right))
		return (_tree_minimum(x->_right));
	rb_node<Key, T>*	y = x->_p;
	while (!_is_null_node(y) && x == y->_right)
	{
		x = y;
		y = y->_p;
	}
	return (y);
}

template <typename Key, typename T>
const rb_node<Key, T>*	_rb_tree_successor(const rb_node<Key, T>* x)
{
	if (!_is_null_node(x->_right))
		return (_tree_minimum(x->_right));
	rb_node<Key, T>*	y = x->_p;
	while (!_is_null_node(y) && x == y->_right)
	{
		x = y;
		y = y->_p;
	}
	return (y);
}

template <typename Key, typename T>
rb_node<Key, T>*	_rb_tree_predecessor(rb_node<Key, T>* x)
{
	if (!_is_null_node(x->_left))
		return (_tree_maximum(x->_left));
	rb_node<Key, T>*	y = x->_p;
	while (!_is_null_node(y) && x == y->_left)
	{
		x = y;
		y = y->_p;
	}
	return (y);
}

template <typename Key, typename T>
const rb_node<Key, T>*	_rb_tree_predecessor(const rb_node<Key, T>* x)
{
	if (!_is_null_node(x->_left))
		return (_tree_maximum(x->_left));
	rb_node<Key, T>*	y = x->_p;
	while (!_is_null_node(y) && x == y->_left)
	{
		x = y;
		y = y->_p;
	}
	return (y);
}

// struct that keeps track of the root, the begin, end, the size and the null node
template <typename Key, typename T, typename Allocator>
struct rb_tree_header
{
	typedef rb_node<Key, T>*	node_ptr;

	rb_tree_header(void) :
		_size(0)
	{
		_null = Allocator().allocate(1);
		Allocator().construct(_null, rb_node<Key, T>());
		_null->_color = black;
		_null->_is_null = null;
		_null->_left = _null;
		_null->_right = _null;
		_null->_p = _null;
		_root = _null;
		_begin = _null;
	}

	~rb_tree_header(void) 
	{
		Allocator().destroy(__builtin_addressof(*_null));
		Allocator().deallocate(__builtin_addressof(*_null), 1);
	}

	void	reset(void)
	{
		_root = _null;
		_begin = _null;
		_size = 0;
		_null->_left = _null;
	}

	node_ptr	_root;
	node_ptr	_begin;
	node_ptr	_null;
	typename Allocator::size_type	_size;
};

template <typename Key, typename T,
	typename Compare, typename Allocator>
class rb_tree
{
	public:
	typedef	rb_node<Key, T>*				node_ptr;
	typedef typename Allocator::size_type	size_type;
	typedef ptrdiff_t						difference_type;
	typedef ft::pair<Key, T>				pair_type;
	typedef rb_tree_iterator<Key, T>		iterator;
	typedef const_rb_tree_iterator<Key, T>	const_iterator;
	typedef ft::reverse_iterator<iterator>		reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
	typedef typename Allocator::template rebind<rb_node<Key, T> >::other	node_allocator;

	// constructors/destructor

	rb_tree(void) { }

	rb_tree(const rb_tree& from) :
		_comp(from._comp),
		_alloc(from._alloc)
	{
		_rb_tree_copy(from.get_root(), from._head._null);
	}

	explicit rb_tree(const Compare& comp, const Allocator& alloc) :
		_comp(comp),
		_alloc(alloc)
		{ }
	
	template <typename InputIterator>
	rb_tree(InputIterator first, InputIterator last, const Compare& comp, const Allocator& alloc) :
		_comp(comp),
		_alloc(alloc)
	{
		_rb_tree_copy_range(first, last);
	}

	~rb_tree(void)
	{
		_delete_all_nodes(_head._root);
	}

	rb_tree&	operator=(const rb_tree& from)
	{
		clear();
		if (from.size() != 0)
			_rb_tree_copy_range(from.begin(), from.end());
		return (*this);
	}

	Allocator	get_allocator(void) const
	{
		return (_alloc);
	}


	// lookup

	size_type	count(const Key& key) const
	{
		node_ptr	x = _head._begin;
		size_type	count = 0;

		while (x != _head._null && _comp(x->_key, key))
			x = _rb_tree_successor(x);
		while (x != _head._null && !_comp(key, x->_key))
		{
			x = _rb_tree_successor(x);
			count++;
		}
		return (count);
	}
	
	iterator	find(const Key& key)
	{
		return (_find_node(key));
	}

	const_iterator	find(const Key& key) const
	{
		return (_find_node(key));
	}

	iterator	find_throw(const Key& key)
	{
		node_ptr	found = _find_node(key);

		if (found == _head._null)
			throw std::out_of_range("Key not found");
		return (found);
	}

	const_iterator	find_throw(const Key& key) const
	{
		node_ptr	found = _find_node(key);

		if (found == _head._null)
			throw std::out_of_range("Key not found");
		return (found);
	}

	iterator	lower_bound(const Key& key)
	{
		node_ptr	x = _head._begin;

		while (x != _head._null && _comp(x->_key, key))
			x = _rb_tree_successor(x);
		return (x);
	}

	const iterator	lower_bound(const Key& key) const
	{
		node_ptr	x = _head._begin;

		while (x != _head._null && _comp(x->_key, key))
			x = _rb_tree_successor(x);
		return (x);
	}

	iterator	upper_bound(const Key& key)
	{
		node_ptr	x = _head._begin;

		while (x != _head._null && !_comp(key, x->_key))
			x = _rb_tree_successor(x);
		return (x);
	}

	const iterator	upper_bound(const Key& key) const
	{
		node_ptr	x = _head._begin;

		while (x != _head._null && !_comp(key, x->_key))
			x = _rb_tree_successor(x);
		return (x);
	}

	ft::pair<iterator, iterator>	equal_range(const Key& key)
	{
		node_ptr	x = _head._begin;

		while (x != _head._null && _comp(x->_key, key))
			x = _rb_tree_successor(x);
		iterator	low(x);
		while (x != _head._null && !_comp(key, x->_key))
			x = _rb_tree_successor(x);
		iterator	up(x);
		return (ft::make_pair(low, up));
	}

	ft::pair<const_iterator, const_iterator>	equal_range(const Key& key) const
	{
		node_ptr	x = _head._begin;

		while (x != _head._null && _comp(x->_key, key))
			x = _rb_tree_successor(x);
		const_iterator	low(x);
		while (x != _head._null && !_comp(key, x->_key))
			x = _rb_tree_successor(x);
		const_iterator	up(x);
		return (ft::make_pair(low, up));
	}


	// rb tree modifiers

	void	clear(void)
	{
		_delete_all_nodes(_head._root);
		_head.reset();
	}

	ft::pair<iterator, bool>	insert(const Key& key, const T& val)
	{
		node_ptr	in_node;
		node_ptr	tmp_node;

		in_node = _get_node(key, val);
		if ((tmp_node = _rb_tree_insert(in_node, _head._root)) != in_node)
		{
			_delete_node(in_node);
			return (ft::make_pair(iterator(tmp_node), false));
		}
		if (_head._begin == _head._null || in_node == _rb_tree_predecessor(_head._begin))
			_head._begin = in_node;
		if (_head._null->_left == _head._null || in_node == _rb_tree_successor(_head._null->_left))
			_head._null->_left = in_node;
		_head._size++;
		return (ft::make_pair(iterator(in_node), true));
	}

	iterator	insert(iterator pos, const Key& key, const T& val)
	{
		node_ptr	pos_node = pos._node;
		node_ptr	in_node = _get_node(key, val);
		node_ptr	tmp_node;

		if (pos_node == _head._null) // map is empty
			tmp_node = _rb_tree_insert(in_node, _head._root);
		else
		{
			if (pos_node != _head._root)
				tmp_node = _rb_tree_insert(in_node, pos_node->_p);
			else
				tmp_node = _rb_tree_insert(in_node, pos_node);
			if (tmp_node != in_node)
			{
				_delete_node(in_node);
				return (tmp_node);
			}
		}
		if (_head._begin == _head._null || in_node == _rb_tree_predecessor(_head._begin))
			_head._begin = in_node;
		if (_head._null->_left == _head._null || in_node == _rb_tree_successor(_head._null->_left))
			_head._null->_left = in_node;
		_head._size++;
		return (in_node);
	}

	// the two _insert functions are just here to simplify
	// the interface by deconstructing the pairs in two elements

	pair<iterator, bool>	_insert_pair(const pair_type& pair)
	{
		return (insert(pair.first, pair.second));
	}

	iterator	_insert_pos(iterator pos, const pair_type& pair)
	{
		return (insert(pos, pair.first, pair.second));
	}

	void	erase(iterator pos)
	{
		node_ptr	pos_node = pos._node;

		if (pos_node == _head._null)
			return ;
		if (pos_node == _head._begin)
			_head._begin = _rb_tree_successor(_head._begin);
		if (pos_node == _head._null->_left)
			_head._null->_left = _rb_tree_predecessor(_head._null->_left);
		_rb_tree_delete(pos_node);
		_delete_node(pos_node);
		_head._size--;
	}

	size_type	erase(const Key& key)
	{
		node_ptr	pos_node = _find_node(key);

		if (pos_node == _head._null)
			return (0);
		if (pos_node == _head._begin)
			_head._begin = _rb_tree_successor(_head._begin);
		if (pos_node == _head._null->_left)
			_head._null->_left = _rb_tree_predecessor(_head._null->_left);
		_rb_tree_delete(pos_node);
		_delete_node(pos_node);
		_head._size--;
		return (1);
	}

	void	swap(rb_tree& other)
	{
		std::swap(_head._root, other._head._root);
		std::swap(_head._begin, other._head._begin);
		std::swap(_head._null, other._head._null);
		size_type	tmp_size = _head._size;
		_head._size = other._head._size;
		other._head._size = tmp_size;
	}

	// capacity

	size_type	size(void) const
	{
		return (_head._size);
	}

	bool	empty(void) const
	{
		return (_head._size == 0);
	}

	size_type	max_size(void) const
	{
		return (_alloc.max_size());
	}

	// iterators

	iterator	begin(void)
	{
		return (_head._begin);
	}

	const_iterator	begin(void) const
	{
		return (_head._begin);
	}

	iterator	end(void)
	{
		return (_head._null);
	}

	const_iterator	end(void) const
	{
		return (_head._null);
	}

	reverse_iterator	rbegin(void)
	{
		return (reverse_iterator(_head._null));
	}

	const_reverse_iterator	rbegin(void) const
	{
		return (const_reverse_iterator(_head._null));
	}

	reverse_iterator	rend(void)
	{
		return (reverse_iterator(_head._begin));
	}

	const_reverse_iterator	rend(void) const
	{
		return (const_reverse_iterator(_head._begin));
	}

	// debug
	node_ptr	get_root(void) const
	{
		return (_head._root);
	}

	void	print(node_ptr root) const
	{
		if (root != _head._null)
		{
			print(root->_left);
			std::cout << root->_key << "::" << root->_val << std::endl;
			print(root->_right);
		}
	}


	private:

	node_ptr	_find_node(const Key& key) const
	{
		node_ptr	x = _head._root;

		while (x != _head._null && x->_key != key)
		{
			if (_comp(x->_key, key))
				x = x->_right;
			else if (_comp(key, x->_key))
				x = x->_left;
		}
		return (x);
	}

	// insert helper functions

	// actual insert function
	node_ptr	_rb_tree_insert(node_ptr z, node_ptr start)
	{
		node_ptr	y = _head._null;
		node_ptr	x = start;

		while (x != _head._null)
		{
			y = x;
			if (_comp(z->_key, x->_key))
				x = x->_left;
			else if (_comp(x->_key, z->_key))
				x = x->_right;
			else
				return (x);
		}
		z->_p = y;
		if (y == _head._null)
			_head._root = z;
		else if (_comp(z->_key, y->_key))
			y->_left = z;
		else
			y->_right = z;
		z->_left = _head._null;
		z->_right = _head._null;
		z->_color = red;
		_rb_tree_color_fixup(z);
		return (z);
	}

	void	_rb_tree_color_fixup(node_ptr z)
	{
		node_ptr	y;

		while (z->_p->_color == red)
		{
			if (z->_p == z->_p->_p->_left)
			{
				y = z->_p->_p->_right;		
				if (y->_color == red)
				{
					z->_p->_color = black;
					y->_color = black;
					z->_p->_p->_color = red;
					z = z->_p->_p;
				}
				else
				{
					if (z == z->_p->_right)
					{
						z = z->_p;
						_left_rotate(z);
					}
					z->_p->_color = black;
					z->_p->_p->_color = red;
					_right_rotate(z->_p->_p);
				}
			}
			else
			{
				y = z->_p->_p->_left;
				if (y->_color == red)
				{
					z->_p->_color = black;
					y->_color = black;
					z->_p->_p->_color = red;
					z = z->_p->_p;
				}
				else
				{
					if (z == z->_p->_left)
					{
						z = z->_p;
						_right_rotate(z);
					}
					z->_p->_color = black;
					z->_p->_p->_color = red;
					_left_rotate(z->_p->_p);
				}
			}
		}
		_head._root->_color = black;
	}

		// delete helper functions

	void	_rb_tree_delete(node_ptr z)
	{
		node_ptr	x;
		node_ptr	y = z;
		enum rb_tree_color	y_orig_color = y->_color;

		if (z->_left == _head._null)
		{
			x = z->_right;
			_transplant(z, z->_right);
		}
		else if (z->_right == _head._null)
		{
			x = z->_left;
			_transplant(z, z->_left);
		}
		else
		{
			y = _tree_minimum(z->_right);
			y_orig_color = y->_color;
			x = y->_right;
			if (y->_p == z)
				x->_p = y;
			else
			{
				_transplant(y, y->_right);
				y->_right = z->_right;
				y->_right->_p = y;
			}
			_transplant(z, y);
			y->_left = z->_left;
			y->_left->_p = y;
			y->_color = z->_color;
		}
		if (y_orig_color == black)
			_rb_delete_fixup(x);
	}

	void	_rb_delete_fixup(node_ptr x)
	{
		node_ptr	w;

		while (x != _head._root && x->_color == black)
		{
			if (x == x->_p->_left)
			{
				w = x->_p->_right;
				if (w->_color == red)
				{
					w->_color = black;
					x->_p->_color = red;
					_left_rotate(x->_p);
					w = x->_p->_right;
				}
				if (w->_left->_color == black && w->_right->_color == black)
				{
					w->_color = red;
					x = x->_p;
				}
				else
				{
					if (w->_right->_color == black)
					{
						w->_left->_color = black;
						w->_color = red;
						_right_rotate(w);
						w = x->_p->_right;
					}
					w->_color = x->_p->_color;
					x->_p->_color = black;
					w->_right->_color = black;
					_left_rotate(x->_p);
					x = _head._root;
				}
			}
			else
			{
				w = x->_p->_left;
				if (w->_color == red)
				{
					w->_color = black;
					x->_p->_color = red;
					_right_rotate(x->_p);
					w = x->_p->_left;
				}
				if (w->_right->_color == black && w->_left->_color == black)
				{
					w->_color = red;
					x = x->_p;
				}
				else
				{
					if (w->_left->_color == black)
					{
						w->_right->_color = black;
						w->_color = red;
						_left_rotate(w);
						w = x->_p->_left;
					}
					w->_color = x->_p->_color;
					x->_p->_color = black;
					w->_left->_color = black;
					_right_rotate(x->_p);
					x = _head._root;
				}
			}
		}
		x->_color = black;
	}
				

	void	_transplant(node_ptr u, node_ptr v)
	{
		if (u->_p == _head._null)
			_head._root = v;
		else if (u == u->_p->_left)
			u->_p->_left = v;
		else
			u->_p->_right = v;
		v->_p = u->_p;
	}

	void	_left_rotate(node_ptr x)
	{
		node_ptr	y = x->_right;

		x->_right = y->_left;
		if (y->_left != _head._null)
			y->_left->_p = x;
		y->_p = x->_p;
		// these 3 conditions replace x by y in x's former parent
		if (x->_p == _head._null)
			_head._root = y;		else if (x == x->_p->_left)
			x->_p->_left = y;
		else
			x->_p->_right = y;
		y->_left = x;
		x->_p = y;
	}

	void	_right_rotate(node_ptr y)
	{
		node_ptr	x = y->_left;

		y->_left = x->_right;
		if (x->_right != _head._null)
			x->_right->_p = y;
		x->_p = y->_p;
		if (y->_p == _head._null)
			_head._root = x;
		else if (y == y->_p->_left)
			y->_p->_left = x;
		else
			y->_p->_right = x;
		x->_right = y;
		y->_p = x;
	}

	// allocate/deallocate

	node_ptr	_get_node(const Key& key, const T& val)
	{
		node_ptr	ret = _alloc.allocate(1);
		_alloc.construct(__builtin_addressof(*ret), rb_node<Key, T>(key, val, _head._null));
		return (ret);
	}

	void	_delete_node(node_ptr x)
	{
		if (x != _head._null)
		{
			_alloc.destroy(__builtin_addressof(*x));
			_alloc.deallocate(__builtin_addressof(*x), 1);
		}
	}

	void	_delete_all_nodes(node_ptr x)
	{
		if (x != _head._null)
		{
			_delete_all_nodes(x->_left);
			_delete_all_nodes(x->_right);
			_delete_node(x);
		}
	}

	void	_rb_tree_copy(node_ptr x, node_ptr null)
	{
		if (x != null)
		{
			insert(x->_key, x->_val);
			_rb_tree_copy(x->_right, null);
			_rb_tree_copy(x->_left, null);
		}
	}

	template <typename Iter>
	void	_rb_tree_copy_range(Iter first, Iter last)
	{
		while (first != last)
		{
			_insert_pair(*first);
			++first;
		}
	}

	// attributes
	rb_tree_header<Key, T, node_allocator>	_head;
	Compare			_comp;
	node_allocator	_alloc;

};

// Comparison operators 

template <typename Key, typename T, typename Compare, typename Allocator>
bool	operator==(const rb_tree<Key, T, Compare, Allocator>& left, const rb_tree<Key, T, Compare, Allocator>& right)
{
	if (left.size() != right.size())
		return (false);
	return (std::equal(left.begin(), left.end(), right.begin()));
}

template <typename Key, typename T, typename Compare, typename Allocator>
bool	operator!=(const rb_tree<Key, T, Compare, Allocator>& left, const rb_tree<Key, T, Compare, Allocator>& right)
{
	return (!(left == right));
}

template <typename Key, typename T, typename Compare, typename Allocator>
bool	operator<(const rb_tree<Key, T, Compare, Allocator>& left, const rb_tree<Key, T, Compare, Allocator>& right)
{
	return (ft::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end()));
}

template <typename Key, typename T, typename Compare, typename Allocator>
bool	operator>=(const rb_tree<Key, T, Compare, Allocator>& left, const rb_tree<Key, T, Compare, Allocator>& right)
{
	return (!ft::lexicographical_compare(left.begin(), left.end(), right.begin(), right.end()));
}

template <typename Key, typename T, typename Compare, typename Allocator>
bool	operator>(const rb_tree<Key, T, Compare, Allocator>& left, const rb_tree<Key, T, Compare, Allocator>& right)
{
	return (ft::lexicographical_compare(right.begin(), right.end(), left.begin(), left.end()));
}

template <typename Key, typename T, typename Compare, typename Allocator>
bool	operator<=(const rb_tree<Key, T, Compare, Allocator>& left, const rb_tree<Key, T, Compare, Allocator>& right)
{
	return (!ft::lexicographical_compare(right.begin(), right.end(), left.begin(), left.end()));
}

} // namespace ft

#endif
