#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace ft {

	// primitives

	struct input_iterator_tag { };
	struct output_operator_tag { };
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
		void	advance(InputIterator& i, Distance n);
	template <typename InputIterator>
		typename iterator_traits<InputIterator>::difference_type
		distance(InputIterator first, InputIterator last);
	
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

		reverse_iterator() : current(x) { }
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
		reverse_iterator	operator-(difference_type n); const
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
	
	template <typename Container> class front_insert_iterator;
	template <typename Container>
		front_insert_iterator<Container>	front_inserter(Container& x);
	
	template <typename Container> class insert_iterator;
	template <typename Container, typename Iterator>
		insert_iterator<Container>	inserter(Container& x, Iterator& i);
}

#endif
