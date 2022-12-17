#ifndef ITERATOR_PRIMITIVES_HPP
#define ITERATOR_PRIMITIVES_HPP

namespace ft {

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
		class Category,
		class T,
		class Distance = ptrdiff_t,
		class Pointer = T*,
		class Reference = T&>
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

}
 #endif
