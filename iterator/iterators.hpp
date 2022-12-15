#ifndef ITERATORS_HPP
#define ITERATORS_HPP

#include <stddef.h>

#include "../type_traits.hpp"
#include "iterator_primitives.hpp"

namespace ft {

	template <typename Iterator, typename Container>
	class rand_access_iterator {

		protected:
			Iterator	_current;
			typedef ft::iterator_traits<Iterator>	traits_type;

		public:
			typedef Iterator								iterator_type;
			typedef typename traits_type::iterator_category	iterator_category;
			typedef typename traits_type::value_type		value_type;
			typedef typename traits_type::difference_type	difference_type;
			typedef typename traits_type::reference			reference;
			typedef typename traits_type::pointer			pointer;

			/*******************************/
			/* Basic iterator requirements */
			/*******************************/

			// Copy constructible
			template <typename Iter>
			rand_access_iterator(const rand_access_iterator<
			Iter,
			typename ft::enable_if<
				(ft::are_same<Iter, typename Container::pointer>::value),
				Container>::type>& orig) : _current(orig.base()) { }

			rand_access_iterator(const Iterator& orig) : _current(orig) { }
			
			// Copy Assignable
			rand_access_iterator&	operator=(const Iterator& orig)
			{
				_current = orig;
				return (*this);
			}

			// Destructible
			~rand_access_iterator(void) { }

			reference	operator*(void) const
			{
				return (*_current);
			}

			rand_access_iterator&	operator++(void)
			{
				++_current;
				return (*this);
			}

			/*******************************/
			/* Input iterator requirements */
			/*******************************/

			pointer	operator->(void) const
			{
				return (_current);
			}

			/*********************************/
			/* Forward iterator requirements */
			/*********************************/

			//Default constructible
			rand_access_iterator(void) : _current(Iterator()) { }

			const rand_access_iterator&	operator++(int)
			{
				rand_access_iterator	tmp(*this);
				_current++;
				return (tmp);
			}

			/***************************************/
			/* BiDirectional iterator requirements */
			/***************************************/

			rand_access_iterator&	operator--(void)
			{
				--_current;
				return (*this);
			}
			
			const rand_access_iterator&	operator--(int)
			{
				rand_access_iterator	tmp(*this);
				_current--;
				return (tmp);
			}

			/***************************************/
			/* Random Access iterator requirements */
			/***************************************/

			rand_access_iterator&	operator+=(difference_type n)
			{
				_current += n;
				return (*this);
			}
			
			rand_access_iterator	operator+(difference_type n) const
			{
				rand_access_iterator	tmp(_current + n);
				return (tmp);
			}
			
			rand_access_iterator&	operator-=(difference_type n)
			{
				_current -= n;
				return (*this);
			}

			rand_access_iterator	operator-(difference_type n) const
			{
				rand_access_iterator	tmp(_current - n);
				return (tmp);
			}

			difference_type	operator-(const rand_access_iterator comp) const
			{
				return (_current - comp._current);
			}

			reference	operator[](difference_type n) const
			{
				return (*(_current + n));
			}

			/* 	this function is used to access the _current protected member
				for copy construction.
				Since the object constructed from might be instantiated
				differently from the object being constructed, _current
				cannot be accessed directly
			*/
			const Iterator&	base(void) const
			{
				return (_current);
			}
	};

	/*******************************/
	/* Input iterator requirements */
	/*******************************/

	template <typename IteratorL, typename IteratorR, typename Container>
	inline bool	operator==(const rand_access_iterator<IteratorL, Container>& l,
			const rand_access_iterator<IteratorR, Container>& r)
	{
		return (l._current == r._current);
	}

	template <typename Iterator, typename Container>
	inline bool	operator==(const rand_access_iterator<Iterator, Container>& l,
			const rand_access_iterator<Iterator, Container>& r)
	{
		return (l._current == r._current);
	}

	template <typename IteratorL, typename IteratorR, typename Container>
	inline bool	operator!=(const rand_access_iterator<IteratorL, Container>& l,
			const rand_access_iterator<IteratorR, Container>& r)
	{
		return (l._current != r._current);
	}

	template <typename Iterator, typename Container>
	inline bool	operator!=(const rand_access_iterator<Iterator, Container>& l,
			const rand_access_iterator<Iterator, Container>& r)
	{
		return (l._current != r._current);
	}

	/***************************************/
	/* Random Access iterator requirements */
	/***************************************/

	template <typename IteratorL, typename IteratorR, typename Container>
	inline bool	operator<(const rand_access_iterator<IteratorL, Container>& l,
			const rand_access_iterator<IteratorR, Container>& r)
	{
		return (l._current < r._current);
	}

	template <typename Iterator, typename Container>
	inline bool	operator<(const rand_access_iterator<Iterator, Container>& l,
			const rand_access_iterator<Iterator, Container>& r)
	{
		return (l._current < r._current);
	}

	template <typename IteratorL, typename IteratorR, typename Container>
	inline bool	operator>(const rand_access_iterator<IteratorL, Container>& l,
			const rand_access_iterator<IteratorR, Container>& r)
	{
		return (l._current > r._current);
	}

	template <typename Iterator, typename Container>
	inline bool	operator>(const rand_access_iterator<Iterator, Container>& l,
			const rand_access_iterator<Iterator, Container>& r)
	{
		return (l._current > r._current);
	}

	template <typename IteratorL, typename IteratorR, typename Container>
	inline bool	operator<=(const rand_access_iterator<IteratorL, Container>& l,
			const rand_access_iterator<IteratorR, Container>& r)
	{
		return (l._current <= r._current);
	}

	template <typename Iterator, typename Container>
	inline bool	operator<=(const rand_access_iterator<Iterator, Container>& l,
			const rand_access_iterator<Iterator, Container>& r)
	{
		return (l._current <= r._current);
	}

	template <typename IteratorL, typename IteratorR, typename Container>
	inline bool	operator>=(const rand_access_iterator<IteratorL, Container>& l,
			const rand_access_iterator<IteratorR, Container>& r)
	{
		return (l._current >= r._current);
	}

	template <typename Iterator, typename Container>
	inline bool	operator>=(const rand_access_iterator<Iterator, Container>& l,
			const rand_access_iterator<Iterator, Container>& r)
	{
		return (l._current >= r._current);
	}

}

#endif
