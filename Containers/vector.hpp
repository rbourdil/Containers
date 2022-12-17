#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>

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
			typedef typename Allocator::pointer			pointer;
			typedef typename Allocator::const_pointer	const_pointer;
			typedef T			value_type;
			typedef T&			reference;
			typedef const T&	const_reference;
			typedef ft::rand_access_iterator<pointer, vector>	iterator;
			typedef ft::rand_access_iterator<const_pointer, vector>	const_iterator;
			typedef	typename ft::iterator_traits<iterator>::difference_type	difference_type; 
			typedef size_t		size_type;
			typedef ft::reverse_iterator<iterator>	reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		
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

			// Copy assignment operator
			vector&	operator=(const vector& orig)
			{
				if (&orig != this)
				{
					const size_type	orig_len = orig.size();
					// if the range to copy is greater than the capacity of our vector
					if (orig_len > capacity())
					{
						pointer	tmp = _alloc.allocate(orig_len);
						ft::destroy(_markers._start, _markers._end, _alloc);
						_alloc.deallocate(_markers._start, _markers._last - _markers._start);
						_markers._start = tmp;
						_markers._end = std::uninitialized_copy(orig.begin(), orig.end(), _markers._start);
						_markers._last = _markers._start + orig_len;
					}
					// if the size of our vector is greater than the range to copy, copy the smaller part and destroy what's left
					else if (size() >= orig_len)
					{
						iterator	tmp = std::copy(orig.begin(), orig.end(), begin());
						ft::destroy(tmp, end(), _alloc);
						_markers._end = _markers._start + orig_len;
					}
					// the size of the vector is smaller, but the capacity is enough
					else
					{
						std::copy(orig.begin(), orig.begin() + size(), _markers._start);
						std::uninitialized_copy(orig.begin() + size(), orig.end(), _markers._end);
					} 
				}
				return (*this);
			}

			// size & value constructor
			vector(size_type n, const value_type& t)
			{
				_markers._start = _alloc.allocate(n);
				_markers._last = _markers._start + n;
				_markers._end = std::uninitialized_fill(_markers._start, _markers._start + n, t);
			}

			// range constructor
			template <typename _Iter>
			vector(_Iter first, _Iter last)
			{
				const difference_type	n = last - first;

				_markers._start = _alloc.allocate(n);
				_markers._last = _markers._start + n;
				_markers._end = std::uninitialized_copy(first, last, _markers._start);
			}

			// Destructor
			~vector(void)
			{
				ft::destroy(_markers._start, _markers._end, _alloc);
				_alloc.deallocate(_markers._start, _markers._last - _markers._start);
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
				return (reverse_iterator(end()));
			}

			const_reverse_iterator	rbegin(void) const
			{
				return (reverse_iterator(end()));
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

			void	swap(vector& v)
			{
				Markers<pointer>	tmp;

				tmp.copy_markers(_markers);
				_markers.copy_markers(v._markers);
				v._markers.copy_markers(tmp);
				std::swap(_alloc, v._alloc);
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

		private:
			Allocator			_alloc;
			Markers<pointer>	_markers;
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

#endif
