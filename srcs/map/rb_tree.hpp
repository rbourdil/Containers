#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <memory>
#include <iostream>
#include <stdexcept>
#include <cstddef>
#include <algorithm>

#include "../alloc_help.hpp"

namespace ft {

enum rb_tree_color { red = false, black = true };

// node struct used as base type for the tree
template <typename Key, typename T>
struct rb_node {

	typedef rb_node*	node_ptr;

	rb_node() :
		_color(),
		_key(Key()),
		_val(T()),
		_left(NULL),
		_right(NULL),
		_p(NULL)
		{ }
	
	rb_node(const Key& key, const T& val) :
		_color(),
		_key(key),
		_val(val),
		_left(NULL),
		_right(NULL),
		_p(NULL)
		{ }
	
	rb_node(const rb_node& from) :
		_color(from._color),
		_key(from._key),
		_val(from._val),
		_left(from._left),
		_right(from._right),
		_p(from._p)
		{ }
	
	rb_tree_color	_color;
	Key				_key;
	T				_val;
	node_ptr		_left;
	node_ptr		_right;
	node_ptr		_p;
};

template <typename Key, typename T>
struct	rb_tree_iterator
{
	typedef T			value_type;
	typedef T&			reference;
	typedef T*			pointer;
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
		return (_node->_val);
	}

	self&	operator++(void)
	{
		_node = _rb_tree_successor(_node);
		return (*this);
	}

	// input iterator requirements

	pointer	operator->(void) const
	{
		return (&_node->_val);
	}

	self	operator++(int)
	{
		self	tmp = *this;
		_node = _rb_tree_successor(_node);
		return (tmp);
	}

	bool	operator==(const self& comp) const
	{
		return (_node == comp._node);
	}

	bool	operator!=(const self& comp) const
	{
		return (_node != comp._node);
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
		_node = rb_tree_predecessor(_node);
		return (tmp);
	}

	node_ptr	_node;

};

template <typename Key, typename T>
struct	const_rb_tree_iterator
{
	typedef const T			value_type;
	typedef const T&			reference;
	typedef const T*			pointer;
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


	// iterator requirements

	reference	operator*(void) const
	{
		return (_node->_val);
	}

	self&	operator++(void)
	{
		_node = _rb_tree_successor(_node);
		return (*this);
	}

	// input iterator requirements

	pointer	operator->(void) const
	{
		return (&_node->_val);
	}

	self	operator++(int)
	{
		self	tmp = *this;
		_node = _rb_tree_successor(_node);
		return (tmp);
	}

	bool	operator==(const self& comp) const
	{
		return (_node == comp._node);
	}

	bool	operator!=(const self& comp) const
	{
		return (_node != comp._node);
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
		_node = rb_tree_predecessor(_node);
		return (tmp);
	}

	const_node_ptr	_node;

};


template <typename Key, typename T>
bool	_is_null_node(rb_node<Key, T>* node)
{
	if (node->_p == node)
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
		_begin(NULL),
		_size(0)
	{
		_null = Allocator().allocate(1);
		Allocator().construct(_null, rb_node<Key, T>());
		_null->_color = black;
		_null->_left = _null;
		_null->_right = _null;
		_null->_p = _null;
		_root = _null;
	}

	~rb_tree_header(void) 
	{
		Allocator().destroy(__builtin_addressof(*_null));
		Allocator().deallocate(__builtin_addressof(*_null), 1);
	}

	void	reset(void)
	{
		_root = _null;
		_begin = NULL;
		_size = 0;
	}

	node_ptr	_root;
	node_ptr	_begin;
	node_ptr	_null;
	typename Allocator::size_type	_size;
};

template <typename Key, typename T,
	typename Compare, typename Allocator = std::allocator<rb_node<Key, T> > >
class rb_tree
{
	typedef	rb_node<Key, T>*				node_ptr;
	typedef typename Allocator::size_type	size_type;

	public:

	typedef rb_tree_iterator<Key, T>		iterator;
	typedef const_rb_tree_iterator<Key, T>	const_iterator;

	// constructors/destructor

	rb_tree(void) { }

	rb_tree(const rb_tree& from) :
		_comp(from._comp),
		_alloc(from._alloc)
	{
		_rb_tree_copy(from.get_root(), from._head._null);
	}

	// rb tree modifiers

	void	clear(void)
	{
		_delete_all_nodes(_head._root);
		_head.reset();
	}

	iterator	find(const Key& key)
	{
		node_ptr	x = _head._root;

		while (x != _head._null && x->_key != key)
		{
			if (_comp(x->_key, key))
				x = x->_right;
			else
				x = x->_left;
		}
		return (x);
	}

	iterator	insert(const Key& key, const T& val)
	{
		node_ptr	in_node;

		in_node = _get_node(key, val);
		_rb_tree_insert(in_node);
		if (_head._begin == NULL || in_node == _rb_tree_predecessor(_head._begin))
			_head._begin = in_node;
		_head._size++;
		return (in_node);
	}

	void	erase(iterator pos)
	{
		node_ptr	pos_node = pos._node;
		if (pos_node == _head._begin)
			_head._begin = _rb_tree_successor(_head._begin);
		_rb_tree_delete(pos_node);
		_delete_node(pos_node);
		_head._size--;
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


	// helper functions 

	size_type	check_len(size_type n) const
	{
		if (max_size() - size() < n)
			throw std::length_error("Tried to allocate over maximum size");
		const size_type	len = size() + std::max(size(), n);
		if (len > max_size() || len < size())
			return (max_size());
		return (len);
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

	// insert helper functions

	// actual insert function
	void	_rb_tree_insert(node_ptr z)
	{
		node_ptr	y = _head._null;
		node_ptr	x = _head._root;

		while (x != _head._null)
		{
			y = x;
			if (_comp(z->_key, x->_key))
				x = x->_left;
			else
				x = x->_right;
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
		if (v != _head._null)
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
			_head._root = y;
		else if (x == x->_p->_left)
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
		_alloc.construct(__builtin_addressof(*ret), rb_node<Key, T>(key, val));
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

	/*
	// struct that contains current allocation of nodes
	struct	node_pool
	{
		node_pool(rb_tree& orig_tree) :
			_start(NULL),
			_current(NULL),
			_last(NULL),
			_tree(orig_tree)
			{ }

		~node_pool(void)
		{
			destroy(_start, _current, _alloc);
			_alloc.deallocate(_start, _last - _start);
		}

		node_ptr	get_node(const Key& key, const T& val)
		{
			if (_start == NULL) // first allocation
			{
				_start = _alloc.allocate(1);
				_current = _start;
				_last = _start + 1;
				_alloc.construct(_current, rb_node<Key, T>(key, val));
			}
			else if (_current != _last) // enough room, just construct
				_alloc.construct(_current, rb_node<Key, T>(key, val));
			else // need to reallocate
			{
				size_type	n = _last - _start;
				size_type	new_size = _tree.check_len(1);
				node_ptr	new_start = _alloc.allocate(new_size);
				node_ptr	new_last = new_start + new_size;
				node_ptr	new_current = new_start;

				_tree._head.reset();
				for (node_ptr p = _start; p != _current; p++, new_current++)
				{
					_alloc.construct(__builtin_addressof(*new_current), *p);
					_tree._rb_tree_insert(new_current);
					_alloc.destroy(__builtin_addressof(*p));
				}
				_alloc.construct(__builtin_addressof(*new_current), rb_node<Key, T>(key, val));
				// reset the begin pointer "manually"
				_tree._head._begin = _tree_minimum(_tree._head._root);

				_alloc.deallocate(_start, n);

				_start = new_start;
				_current = new_current;
				_last = new_last;
			}
			return (_current++);
		}

		node_ptr	_start;
		node_ptr	_current;
		node_ptr	_last;
		Allocator	_alloc;
		rb_tree&	_tree;
	};
	*/

	// attributes
	rb_tree_header<Key, T, Allocator>	_head;
	Compare			_comp;
	Allocator		_alloc;

};

template <typename mapL, typename mapR>
bool	operator==(const mapL& left, const mapR& right)
{
	if (left.size() != right.size())
		return (false);
	return (std::equal(left.begin(), left.end(), right.begin()));
}
	
} // namespace ft

#endif
