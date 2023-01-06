#ifndef ITERATOR_ADAPTORS_HPP
#define ITERATOR_ADAPTORS_HPP

#include <cstddef>
#include <iterator>

#include "iterator_primitives.hpp"

namespace ft {

	// Predefined iterators

	// reverse_iterator class definition
	template <typename Iterator>
	class reverse_iterator :
		public iterator<
			typename iterator_traits<Iterator>::iterator_category,
			typename iterator_traits<Iterator>::value_type,
			typename iterator_traits<Iterator>::difference_type,
			typename iterator_traits<Iterator>::pointer,
			typename iterator_traits<Iterator>::reference> {

	protected:
		Iterator	current;

	public:
		typedef Iterator
			iterator_type;
		typedef typename iterator_traits<Iterator>::difference_type
			difference_type;
		typedef typename iterator_traits<Iterator>::reference
			reference;
		typedef typename iterator_traits<Iterator>::pointer
			pointer;

		reverse_iterator() : current() { }
		explicit reverse_iterator(Iterator x) : current(x) { }
		template <typename U>
		reverse_iterator(const reverse_iterator<U>& u) : current(u.base()) { }

		Iterator	base() const
		{
			return (current);
		}

		reference	operator*() const
		{
			Iterator	tmp = current;
			return (*--tmp);
		}
		pointer		operator->() const
		{
			return (&(operator*()));
		}

		reverse_iterator&	operator++()
		{
			--current;
			return (*this);
		}

		reverse_iterator	operator++(int)
		{
			reverse_iterator	tmp = *this;
			--current;
			return (tmp);
		}

		reverse_iterator&	operator--()
		{
			++current;
			return (*this);
		}

		reverse_iterator	operator--(int)
		{
			reverse_iterator	tmp = *this;
			++current;
			return (tmp);
		}

		reverse_iterator	operator+(difference_type n) const
		{
			return (reverse_iterator(current - n));
		}

		reverse_iterator&	operator+=(difference_type n)
		{
			current -= n;
			return (*this);
		}

		reverse_iterator	operator-(difference_type n) const
		{
			return (reverse_iterator(current + n));
		}

		reverse_iterator&	operator-=(difference_type n)
		{
			current += n;
			return (*this);
		}
		
		reference			operator[](difference_type n) const
		{
			return (current[-n - 1]);
		}
	};

	template <typename Iterator>
	bool	operator==(
		const reverse_iterator<Iterator>& x,
		const reverse_iterator<Iterator>& y)
	{
		return (x.base() == y.base());
	}

	// necessary for const to normal comparison
	template <typename IteratorL, typename IteratorR>
	bool	operator==(
		const reverse_iterator<IteratorL>& x,
		const reverse_iterator<IteratorR>& y)
	{
		return (x.base() == y.base());
	}

	template <typename Iterator>
	bool	operator<(
		const reverse_iterator<Iterator>& x,
		const reverse_iterator<Iterator>& y)
	{
		return (x.base() > y.base());
	}

	// necessary for const to normal comparison
	template <typename IteratorL, typename IteratorR>
	bool	operator<(
		const reverse_iterator<IteratorL>& x,
		const reverse_iterator<IteratorR>& y)
	{
		return (x.base() > y.base());
	}

	template <typename Iterator>
	bool	operator!=(
		const reverse_iterator<Iterator>& x,
		const reverse_iterator<Iterator>& y)
	{
		return (x.base() != y.base());
	}

	// necessary for const to normal comparison
	template <typename IteratorL, typename IteratorR>
	bool	operator!=(
		const reverse_iterator<IteratorL>& x,
		const reverse_iterator<IteratorR>& y)
	{
		return (x.base() != y.base());
	}

	template <typename Iterator>
	bool	operator>(
		const reverse_iterator<Iterator>& x,
		const reverse_iterator<Iterator>& y)
	{
		return (x.base() < y.base());
	}

	// necessary for const to normal comparison
	template <typename IteratorL, typename IteratorR>
	bool	operator>(
		const reverse_iterator<IteratorL>& x,
		const reverse_iterator<IteratorR>& y)
	{
		return (x.base() < y.base());
	}

	template <typename Iterator>
	bool	operator>=(
		const reverse_iterator<Iterator>& x,
		const reverse_iterator<Iterator>& y)
	{
		return (x.base() <= y.base());
	}

	// necessary for const to normal comparison
	template <typename IteratorL, typename IteratorR>
	bool	operator>=(
		const reverse_iterator<IteratorL>& x,
		const reverse_iterator<IteratorR>& y)
	{
		return (x.base() <= y.base());
	}

	template <typename Iterator>
	bool	operator<=(
		const reverse_iterator<Iterator>& x,
		const reverse_iterator<Iterator>& y)
	{
		return (x.base() >= y.base());
	}

	// necessary for const to normal comparison
	template <typename IteratorL, typename IteratorR>
	bool	operator<=(
		const reverse_iterator<IteratorL>& x,
		const reverse_iterator<IteratorR>& y)
	{
		return (x.base() >= y.base());
	}

	template <typename Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(
		const reverse_iterator<Iterator>& x,
		const reverse_iterator<Iterator>& y)
	{
		return (y.base() - x.base());
	}

	// necessary for const to normal comparison
	template <typename IteratorL, typename IteratorR>
	typename reverse_iterator<IteratorL>::difference_type operator-(
		const reverse_iterator<IteratorL>& x,
		const reverse_iterator<IteratorR>& y)
	{
		return (y.base() - x.base());
	}

	template <typename Iterator>
	reverse_iterator<Iterator>	operator+(
		typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator>& x)
	{
		return (reverse_iterator<Iterator>(x.base() - n));
	}
	

	// back_insert_iterator class definition
	template <typename Container>
	class back_insert_iterator :
		public iterator<std::output_iterator_tag, void, void, void, void> {

	protected:
		Container*	container;		

	public:
		typedef Container	container_type;

		explicit back_insert_iterator(Container& x) : container(&x) { }
		back_insert_iterator<Container>&
			operator=(typename Container::const_reference value)
		{
			container->push_back(value);
			return (*this);
		}

		back_insert_iterator<Container>&	operator*()
		{
			return (*this);
		}
		back_insert_iterator<Container>&	operator++()
		{
			return (*this);
		}
		back_insert_iterator<Container>		operator++(int)
		{
			return (*this);
		}
	};

	template <typename Container>
	back_insert_iterator<Container>	back_inserter(Container& x)
	{
		return (back_insert_iterator<Container>(x));
	}
	
	//front_insert_iterator class definition
	template <typename Container>
	class front_insert_iterator :
		public iterator<std::output_iterator_tag, void, void, void, void> {

	protected:
		Container*	container;		

	public:
		typedef Container	container_type;

		explicit front_insert_iterator(Container& x) : container(&x) { }
		front_insert_iterator<Container>&
			operator=(typename Container::const_reference value)
		{
			container->push_front(value);
			return (*this);
		}

		back_insert_iterator<Container>&	operator*()
		{
			return (*this);
		}
		back_insert_iterator<Container>&	operator++()
		{
			return (*this);
		}
		back_insert_iterator<Container>		operator++(int)
		{
			return (*this);
		}
	};

	template <typename Container>
	front_insert_iterator<Container>	front_inserter(Container& x)
	{
		return (front_insert_iterator<Container>(x));
	}
	
	//insert_iterator class definition
	template <typename Container>
	class insert_iterator :
		public iterator<std::output_iterator_tag, void, void, void, void> {

	protected:
		Container*						container;
		typename Container::iterator	iter;

	public:
		typedef Container	container_type;

		insert_iterator(Container& x, typename Container::iterator i) :
			container(x), iter(i) { }
		insert_iterator<Container>&
			operator=(typename Container::const_reference value)
		{
			iter = container->insert(iter, value);
			++iter;
			return (*this);
		}

		insert_iterator<Container>&	operator*()
		{
			return (*this);
		}
		insert_iterator<Container>&	operator++()
		{
			return (*this);
		}
		insert_iterator<Container>&	operator++(int)
		{
			return (*this);
		}
	};

	template <typename Container, typename Iterator>
		insert_iterator<Container>	inserter(Container& x, Iterator i)
	{
		return (insert_iterator<Container>(x, typename Container::iterator(i)));
	}

}

#endif
