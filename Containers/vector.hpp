#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>
#include <stdexcept>

#include "../iterator/iterators.hpp"
#include "../iterator/iterator_adaptors.hpp"
#include "../algorithm.hpp"
#include "../alloc_help.hpp"

namespace ft {

	template <typename Pointer>
	struct Markers {
		Pointer	_start;
		Pointer	_end;
		Pointer	_last;

		Markers() : _start(), _end(), _last()
		{ }

		void	copy_markers(const Markers& orig)
		{
			_start = orig._start;
			_end = orig._end;
			_last = orig._last;
		}
	};

	template <typename T, typename Allocator = std::allocator<T> >
	class vector {

		
		public:
			typedef typename Allocator::pointer								pointer;
			typedef typename Allocator::const_pointer						const_pointer;
			typedef T														value_type;
			typedef typename Allocator::reference							reference;
			typedef typename Allocator::const_reference						const_reference;
			typedef ft::rand_access_iterator<pointer, vector>				iterator;
			typedef ft::rand_access_iterator<const_pointer, vector>			const_iterator;
			typedef	typename ft::iterator_traits<iterator>::difference_type	difference_type; 
			typedef size_t													size_type;
			typedef ft::reverse_iterator<iterator>							reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
		
			// Default: empty vector
			vector(void) { }

			// Copy constructor
			vector(const vector& orig)
			{
				_alloc = orig._alloc;
				_markers._start = _alloc.allocate(orig.size());
				_markers._last = _markers._start + orig.size();
				_markers._end = std::uninitialized_copy(orig.begin(), orig.end(), _markers._start);
			}

			// Copy assignment operator (defined in .tcc)
			vector&	operator=(const vector& orig);

			// size & value constructor
			explicit
			vector(size_type n, const value_type& t = value_type())
			{
				fill_initialize(n, t);
			}

			// range constructor
			template <typename _Iter>
			vector(_Iter first, _Iter last)
			{
				typedef typename ft::is_integral<_Iter>::type	isInt;
				copy_initialize(first, last, isInt());
			}

			// Destructor
			~vector(void)
			{
				ft::destroy(_markers._start, _markers._end, _alloc);
				safe_deallocate(_markers._start, _markers._last - _markers._start);
			}

			template <typename InputIterator>
			void	assign(InputIterator first, InputIterator last)
			{
				typename is_integral<InputIterator>::type	isInt;	
				__assign(first, last, isInt);
			}

			void	assign(size_type n, const value_type& t)
			{
				erase(begin(), end());
				insert(begin(), n, t);
			}

			iterator	begin(void)
			{
				return (_markers._start);
			}

			const_iterator	begin(void) const
			{
				return (_markers._start);
			}

			reverse_iterator	rbegin(void)
			{
				return (reverse_iterator(_markers._end));
			}

			const_reverse_iterator	rbegin(void) const
			{
				return (const_reverse_iterator(_markers._end));
			}

			iterator	end(void)
			{
				return (_markers._end);
			}

			const_iterator	end(void) const
			{
				return (_markers._end);
			}

			reverse_iterator	rend(void)
			{
				return (reverse_iterator(begin()));
			}

			const_reverse_iterator	rend(void) const
			{
				return (reverse_iterator(begin()));
			}
			
			size_type	size(void) const
			{
				return (_markers._end - _markers._start);
			}

			size_type	max_size(void) const
			{
				return (_alloc.max_size());
			}

			bool	empty(void) const
			{
				return (size() == 0);
			}

			size_type	capacity(void) const
			{
				return (_markers._last - _markers._start);
			}

			void	reserve(size_type n);

			void	resize(size_type sz, value_type c = value_type())
			{
				if (sz > size())
					insert(end(), sz - size(), c);
				else if (sz < size())
					erase(begin() + sz, end());
			}

			// Modifiers

			void	push_back(const value_type& t)
			{
				if (_markers._end != _markers._last)
				{
					_alloc.construct(_markers._end, t);
					_markers._end++;
				}
				else
					insert(end(), t);
			}

			void	pop_back(void)
			{
				_markers._end--;
				ft::destroy(end(), end() + 1, _alloc);
			}

			// insert a value at pos p (defined in .tcc)
			iterator	insert(iterator p, const value_type& t);

			// insert n values at pos p (defined in .tcc)
			void	insert(iterator p, size_type n, const value_type& t)
			{
				fill_insert(p, n, t);
			}

			// inserts the range [i, j) at pos p (defined in .tcc)
			template <typename _Iter>
			void	insert(iterator p, _Iter i, _Iter j)
			{
				typedef typename is_integral<_Iter>::type	isInt;
				// select_insert calls either fill_insert or range_insert
				// depending on whether _Iter is an integral type
				select_insert(p, i, j, isInt());
			}

			// erases one element in the vector
			iterator	erase(iterator pos)
			{
				// if the element to erase is not at the end
				if (pos + 1 != end())
					std::copy(pos + 1, end(), pos);
				else
					ft::destroy(pos, pos + 1, _alloc);
				_markers._end--;
				return (pos);
			}

			// erases a range of elements in the vector
			iterator	erase(iterator first, iterator last)
			{
				if (first != last)
				{
					// if the range to erase does not reach the end
					if (last != end())
						std::copy(last, end(), first);
					ft::destroy(first + (end() - last), end(), _alloc);
					_markers._end -= (last - first);
				}
				return (first);
			}

			void	swap(vector& v)
			{
				Markers<pointer>	tmp;

				tmp.copy_markers(_markers);
				_markers.copy_markers(v._markers);
				v._markers.copy_markers(tmp);
				std::swap(_alloc, v._alloc);
			}

			void	clear(void)
			{
				erase(begin(), end());
			}


			// Element Access
			
			reference	operator[](size_type n)
			{
				return (*(begin() + n));
			}

			const_reference	operator[](size_type n) const
			{
				return (*(begin() + n));
			}

			const_reference	at(size_type n) const
			{
				if (n >= size())
					throw std::out_of_range("Subscript out of range");
				return (*(begin() + n));
			}

			reference	at(size_type n)
			{
				if (n >= size())
					throw std::out_of_range("Subscript out of range");
				return (*(begin() + n));
			}

			reference	front(void)
			{
				return (*begin());
			}

			const_reference	front(void) const
			{
				return (*begin());
			}

			reference	back(void)
			{
				return (*--end());
			}

			const_reference	back(void) const
			{
				return (*--end());
			}


		private:
			Allocator			_alloc;
			Markers<pointer>	_markers;

			void	fill_initialize(size_type n, const value_type& t)
			{
				if (n > max_size())
					throw std::length_error("Tried to allocate over max size");
				_markers._start = _alloc.allocate(n);
				_markers._last = _markers._start + n;
				_markers._end = _markers._start + n;
				std::uninitialized_fill(_markers._start, _markers._start + n, t);
			}

			template <typename Integer>
			void	copy_initialize(Integer n, Integer t, ft::true_type)
			{
				if (static_cast<size_type>(n) > max_size())
					throw std::length_error("Tried to allocate over max size");
				fill_initialize(n, t);
			}

			template <typename InputIt>
			void	copy_initialize(InputIt first, InputIt last, ft::false_type)
			{
				const size_type	n = ft::distance(first, last);

				if (n > max_size())
					throw std::length_error("Tried to allocate over max size");
				_markers._start = _alloc.allocate(n);
				_markers._last = _markers._start + n;
				_markers._end = std::uninitialized_copy(first, last, _markers._start);
			}	

			size_type	check_len(size_type n)
			{
				if (max_size() - size() < n)
					throw std::length_error("Tried to allocate over the maximum size");
				const size_type	len = size() + std::max(size(), n);
				if (len > max_size() || len < size())
					return (max_size());
				return (len);
			}

			/* 	the select_insert overloads are necessary to avoid
				calling range insert on integral type arguments */	
			template <typename _Int>
			void	select_insert(iterator p, _Int n, _Int t, true_type)
			{
				fill_insert(p, n, t);
			}

			template <typename _Iter>
			void	select_insert(iterator p, _Iter i, _Iter j, false_type)
			{
				range_insert(p, i, j);
			}
			
			void	fill_insert(iterator p, size_type n, const value_type& t);
			template <typename _Iter>

			void	range_insert(iterator p, _Iter i, _Iter j);

			template <typename _Iter>
			void __assign(_Iter first, _Iter last, false_type)
			{
				erase(begin(), end());
				insert(begin(), first, last);
			}

			template <typename _Int>
			void __assign(_Int n, _Int t, true_type)
			{
				erase(begin(), end());
				insert(begin(), n, t);
			}

			void	safe_deallocate(pointer p, size_type n)
			{
				if (p)
					_alloc.deallocate(p, n);
			}
	};

	template <typename T, typename Alloc>
	bool	operator==(const vector<T, Alloc>& op1, const vector<T, Alloc>& op2)
	{
		if (op1.size() == op2.size()
			&& ft::equal(op1.begin(), op1.end(), op2.begin()))
			return (true);
		return (false);
	}

	template <typename T, typename Alloc>
	bool	operator!=(const vector<T, Alloc>& op1, const vector<T, Alloc>& op2)
	{
		if (op1.size() != op2.size()
			|| !ft::equal(op1.begin(), op1.end(), op2.begin()))
			return (true);
		return (false);
	}

	template <typename T, typename Alloc>
	bool	operator<(const vector<T, Alloc>& op1, const vector<T, Alloc>& op2)
	{
		return (ft::lexicographical_compare(op1.begin(), op1.end(), op2.begin(), op2.end()));
	}

	template <typename T, typename Alloc>
	bool	operator>(const vector<T, Alloc>& op1, const vector<T, Alloc>& op2)
	{
		return (ft::lexicographical_compare(op2.begin(), op2.end(), op1.begin(), op1.end()));
	}

	template <typename T, typename Alloc>
	bool	operator<=(const vector<T, Alloc>& op1, const vector<T, Alloc>& op2)
	{
		return (!ft::lexicographical_compare(op2.begin(), op2.end(), op1.begin(), op1.end()));
	}
	
	template <typename T, typename Alloc>
	bool	operator>=(const vector<T, Alloc>& op1, const vector<T, Alloc>& op2)
	{
		return (!ft::lexicographical_compare(op1.begin(), op1.end(), op2.begin(), op2.end()));
	}

}

#include "vector.tcc"

#endif
