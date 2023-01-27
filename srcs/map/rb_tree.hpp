#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#include <memory>
#include <iostream>
#include <stdexcept>

#include "../alloc_help.hpp"

namespace ft {

enum rb_tree_color { red = false, black = true };

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

template <typename Key, typename T,
	typename Compare, typename Allocator = std::allocator<rb_node<Key, T> > >
class rb_tree
{
	typedef	rb_node<Key, T>*				node_ptr;
	typedef typename Allocator::size_type	size_type;

	public:

	// constructors/destructor

	rb_tree(void) :
		_pool(*this) { }
	

	// rb tree operations

	void	insert(const Key& key, const T& val)
	{
		node_ptr	in_node;

		in_node = _pool.get_node(key, val);
		_rb_tree_insert(in_node);
	}

	size_type	size(void) const
	{
		return (_head._size);
	}

	size_type	max_size(void) const
	{
		return (_pool._alloc.max_size());
	}

	// helper functions 

	size_type	check_len(size_type n)
	{
		if (max_size() - size() < n)
			throw std::length_error("Tried to allocate over maximum size");
		const size_type	len = size() + std::max(size(), n);
		if (len > max_size() || len < size())
			return (max_size());
		return (len);
	}

	// debug
	node_ptr	get_root(void)
	{
		return (_head._root);
	}

	void	print(node_ptr root)
	{
		if (root != _head._null)
		{
			print(root->_left);
			std::cout << root->_key << "::" << root->_val << std::endl;
			print(root->_right);
		}
	}


	private:

	void	_rb_tree_insert(node_ptr z)
	{
		node_ptr	y = _head._null;
		node_ptr	x = _head._root;

		_head._size++;
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

	struct rb_tree_header
	{
		rb_tree_header(void) :
			_begin(NULL),
			_end(NULL),
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
			_end = NULL;
			_size = 0;
		}

		node_ptr	_root;
		node_ptr	_begin;
		node_ptr	_end;
		node_ptr	_null;
		size_type	_size;
	};

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
				_alloc.construct(_current, rb_node(key, val));
			}
			else if (_current != _last) // enough room, just construct
				_alloc.construct(_current, rb_node(key, val));
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
				_alloc.construct(__builtin_addressof(*new_current), rb_node(key, val));

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

	// attributes
	rb_tree_header	_head;
	node_pool		_pool;
	Compare			_comp;

};

} // namespace ft

#endif
