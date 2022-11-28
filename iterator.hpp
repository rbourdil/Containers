#ifndef ITERATOR_HPP
#define ITERATOR_HPP

#include <cstddef>

namespace ft {

	// primitives

	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	template <typename Iterator>
	struct iterator_traits {
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <typename T>
	struct iterator_traits<T*> {
		typedef ptrdiff_t					difference_type;
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template <typename T>
	struct iterator_traits<const T*> {
		typedef ptrdiff_t					difference_type;
		typedef T							value_type;
		typedef const T*					pointer;
		typedef const T&					reference;
		typedef random_access_iterator_tag	iterator_category;
	};

	template <
		typename Category,
		typename T,
		typename Distance = ptrdiff_t,
		typename Pointer = T*,
		typename Reference = T&
		>
	struct iterator {
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef Category	iterator_category;
	};

	// iterator operations
	template <typename InputIterator, typename Distance>
		void	_advance(InputIterator& i, Distance n, input_iterator_tag)
	{
		while (n-- > 0)
			i++;
	}
	template <typename BiDirIterator, typename Distance>
	inline void	_advance(BiDirIterator& i, Distance n, bidirectional_iterator_tag)
	{
		if (n > 0)
		{
			while (n-- > 0)
				i++;
		}
		else
			while (n++ < 0)
				i--;
	}
	template <typename RandAccessIterator, typename Distance>
	inline void	_advance(RandAccessIterator& i, Distance n, random_access_iterator_tag)
	{
		i += n;
	}
	template <typename InputIterator, typename Distance>
	inline void	advance(InputIterator& i, Distance n)
	{
		typename iterator_traits<InputIterator>::difference_type	d = n;
		_advance(i, d, typename iterator_traits<InputIterator>::iterator_category());
	}

	template <typename InputIterator>
	inline typename iterator_traits<InputIterator>::difference_type
		_distance(InputIterator first, InputIterator last, input_iterator_tag)
	{
		typename iterator_traits<InputIterator>::difference_type	d = 0;
		while (first != last)
		{
			first++;
			d++;
		}
		return (d);
	}
	template <typename RandAccessIterator>
	inline typename iterator_traits<RandAccessIterator>::difference_type
		_distance(RandAccessIterator first, RandAccessIterator last, random_access_iterator_tag)
	{
		return (last - first);
	}
	template <typename InputIterator>
	inline typename iterator_traits<InputIterator>::difference_type
		distance(InputIterator first, InputIterator last)
	{
		return (_distance(first, last, typename iterator_traits<InputIterator>::iterator_category()));
	}

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
		reverse_iterator(const reverse_iterator<U>& u) : current(u.current) { }

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
		return (x.current == y.current);
	}
	template <typename Iterator>
	bool	operator<(
		const reverse_iterator<Iterator>& x,
		const reverse_iterator<Iterator>& y)
	{
		return (x.current < y.current);
	}
	template <typename Iterator>
	bool	operator!=(
		const reverse_iterator<Iterator>& x,
		const reverse_iterator<Iterator>& y)
	{
		return (x.current != y.current);
	}
	template <typename Iterator>
	bool	operator>(
		const reverse_iterator<Iterator>& x,
		const reverse_iterator<Iterator>& y)
	{
		return (x.current > y.current);
	}
	template <typename Iterator>
	bool	operator>=(
		const reverse_iterator<Iterator>& x,
		const reverse_iterator<Iterator>& y)
	{
		return (x.current >= y.current);
	}
	template <typename Iterator>
	bool	operator<=(
		const reverse_iterator<Iterator>& x,
		const reverse_iterator<Iterator>& y)
	{
		return (x. current <= y.current);
	}

	template <typename Iterator>
	typename reverse_iterator<Iterator>::difference_type operator-(
		const reverse_iterator<Iterator>& x,
		const reverse_iterator<Iterator>& y)
	{
		return (y.current - x.current);
	}
	template <typename Iterator>
	reverse_iterator<Iterator>	operator+(
		typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator>& x)
	{
		return (reverse_iterator<Iterator>(x.current - n));
	}
	
	// back_insert_iterator class definition
	template <typename Container>
	class back_insert_iterator :
		public iterator<output_iterator_tag, void, void, void, void> {

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
		public iterator<output_iterator_tag, void, void, void, void> {

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
		public iterator<output_iterator_tag, void, void, void, void> {

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
