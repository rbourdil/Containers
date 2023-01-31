#ifndef MAP_HPP
#define MAP_HPP

#include <memory>
#include <fuctional>

#include "rb_tree.hpp"

namespace ft {

template <class Key, class T, class Compare = less<Key>,
		class Allocator = allocator<pair<const Key, T> > >
class map {

	private:
		typedef rb_tree<Key, T, Compare, Allocator>	_tree_type;

		tree_type	_tree_base;

	public:
		typedef Key						key_type;
		typedef T						mapped_type;
		typedef pair<const Key, T>		value_type;
		typedef Compare					key_compare;
		typedef Allocator				allocator_type;
		typedef value_type&				reference;
		typedef const value_type&		const_reference;
		typedef typename _tree_type::iterator		iterator;
		typedef typename _tree_type::const_iterator	const_iterator;
		typedef typename _tree_type::size_type		size_type;
		typedef typename _tree_type::difference_type	difference_type;
		typedef typename std::allocator_traits<Allocator>::pointer	pointer;
		typedef typename std::allocator_traits<Allocator>::const_pointer	const_pointer;
		typedef typename _tree_type::reverse_iterator	reverse_iterator;
		typedef typename _tree_type::const_reverse_iterator	const_reverse_iterator;

		class	value_compare
			: public binary_function<value_type, value_type, bool> {

			friend class	map;

			protected:
				Compare	comp;
				value_compare(Compare c) : comp(c) {}

			public:
				bool	operator()(const value_type& x, const value_type& y) const {
					return comp(x.first, y.first);
				}
			};
		

		// construct/copy/destroy

		explicit map(const Compare& comp = Compare(), const Allocator& alloc = Allocator()) :
			_tree_base(comp, alloc)
			{ }

		template <class InputIterator>>
		map(InputIterator first, InputIterator last,
			const Compare& comp = Compare(), const Allocator& = Allocator()) :
			_tree_base(first, last)
			{ }

		map(const map& x) :
			_tree_base(map._tree_base)
			{ }

		~map();

		map&	operator=(const map& x)
		{
			_tree_base = x._tree_base;
			return (*this);
		}
		
		allocator_type	get_allocator(void) const
		{
			return (_tree_base.get_allocator());
		}

		//iterators

		iterator	begin()
		{
			return (_tree_base.begin());
		}

		const_iterator	begin() const
		{
			return (_tree_base.begin());
		}

		iterator	end()
		{
			return (_tree_base.end());
		}

		const_iterator	end() const
		{
			return (_tree_base.end());
		}

		reverse_iterator	rbegin()
		{
			return (_tree_base.rbegin());
		}

		const_reverse_iterator	rbegin() const
		{
			return (_tree_base.rbegin());
		}

		reverse_iterator	rend()
		{
			return (_tree_base.rend());
		}

		const_reverse_iterator	rend() const
		{
			return (_tree_base.rend());
		}


		// capacity

		bool	empty() const
		{
			return (_tree_base.empty());
		}

		size_type	size() const
		{
			return (_tree_base.size());
		}

		size_type	max_size()	const
		{
			return (_tree_base.max_size());
		}


		// element access

		T&	operator[](const key_type& x)
		{
			return (_tree_base.find(x)->second);
		}

		T&	at(const key_type& x)
		{
			return (_tree_base.find(x)->second);
		}


		// modifiers

		pair<iterator, bool>	insert(const value_type& x)
		{
			return (_tree_base._insert_pair(x));
		}
		
		iterator	insert(iterator position, const value_type& x)
		{
			return (
			//HHHHHEHRHEHHREKJLFJDSJFDSKJHFJDSHJFDSH

		template <class InputIterator>
			void	insert(InputIterator first, InputIterator last);

		void	erase(iterator position);

		size_type	erase(const key_type& x);

		void	erase(iterator first, iterator last);

		void	swap(map<Key, T, Compare, Allocator>&);

		void	clear();


		// observers

		key_compare	key_comp() const;

		value_compare	value_comp() const;


		// map operations

		iterator	find(const key_type& x);

		const_iterator	find(const key_type& x) const;

		size_type	count(const key_type& x) const;

		iterator	lower_bound(const key_type& x);

		const_iterator	lower_bound(const key_type& x) const;

		iterator	upper_bound(const key_type& x);

		const_iterator	upper_bound(const key_type& x) const;

		pair<iterator, iterator>
		equal_range(const key_type& x);

		pair<const_iterator, const_iterator>
		equal_range(const key_type& x) const;

};

template <class Key, class T, class Compare, class Allocator>
bool	operator==(const map<Key, T, Compare, Allocator>& x,
				const map<Key, T, Compare, Allocator>& y);

template <class Key, class T, class Compare, class Allocator>
bool	operator<(const map<Key, T, Compare, Allocator>& x,
				const map<Key, T, Compare, Allocator>& y);

template <class key, class t, class compare, class allocator>
bool	operator!=(const map<key, t, compare, allocator>& x,
				const map<key, t, compare, allocator>& y);

template <class key, class t, class compare, class allocator>
bool	operator>(const map<key, t, compare, allocator>& x,
				const map<key, t, compare, allocator>& y);

template <class key, class t, class compare, class allocator>
bool	operator>=(const map<key, t, compare, allocator>& x,
				const map<key, t, compare, allocator>& y);

template <class key, class t, class compare, class allocator>
bool	operator<=(const map<key, t, compare, allocator>& x,
				const map<key, t, compare, allocator>& y);

template <class Key, class T, class Compare, class Allocator>
void	swap(map<Key, T, Compare, Allocator>& x,
			map<Key, T, Compare, Allocator>& y);

} // namespace ft

#endif
