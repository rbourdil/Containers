#ifndef VECTOR_TCC
#define VECTOR_TCC

#include "vector.hpp"

namespace ft {

template <typename T, typename Allocator>
vector<T, Allocator>&
vector<T, Allocator>::operator=(const vector& orig)
{
	if (&orig != this)
	{
		const size_type	orig_len = orig.size();
		// if the range to copy is greater than the capacity of our vector
		if (orig_len > capacity())
		{
			pointer	new_start = _alloc.allocate(orig_len);
			ft::destroy(begin(), end(), _alloc);
			safe_deallocate(_markers._start, _markers._last - _markers._start);
			_markers._start = new_start;
			pointer	new_end = ft::_my_uninitialized_copy(orig.begin(), orig.end(), _markers._start, _alloc);
			_markers._end = _markers._start + (new_end - new_start);
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
			ft::_my_uninitialized_copy(orig.begin() + size(), orig.end(), _markers._end, _alloc);
			_markers._end = _markers._start + orig_len;
		} 
	}
	return (*this);
}

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::insert(iterator p, const value_type& t)
{
	size_type	n = ft::distance(begin(), p);

	// check if there is enough room in current allocation
	if (_markers._end != _markers._last)
	{
		value_type	current = t;
		value_type	forward;
		while (p != end()) // insert inside the vector
		{
			forward = *p;
			*p = current;
			current = forward;
			p++;
		}
		_alloc.construct(_markers._end, current); // append
		_markers._end++;
	}
	else // need to allocate more room
	{
		size_type	len = check_len(1);
		pointer	new_start = _alloc.allocate(len);
		iterator	new_end = ft::_my_uninitialized_copy(begin(), p, iterator(new_start), _alloc);
		_alloc.construct(new_start + (new_end - iterator(new_start)), t);
		new_end++;
		if (p != end())
			new_end = ft::_my_uninitialized_copy(p, end(), new_end, _alloc);
		ft::destroy(begin(), end(), _alloc);
		safe_deallocate(_markers._start, _markers._last - _markers._start);
		_markers._start = new_start;
		_markers._end = _markers._start + (new_end - iterator(new_start));
		_markers._last = _markers._start + len;
	}
	return (begin() + n);
}

template <typename T, typename Allocator>
void vector<T, Allocator>::fill_insert(iterator p, size_type n, const value_type& t)
{
	size_type	i;
	// check if there is enough room in current allocation
	if (static_cast<size_type>(_markers._last - _markers._end) >= n)
	{
		// insertion inside the vector
		if (p != end())
		{
			size_type	block_len = ft::distance(p, end());
			pointer		tmp = _alloc.allocate(block_len);
			iterator	tmp_start = iterator(tmp);
			iterator	tmp_end = ft::_my_uninitialized_copy(p, end(), tmp_start, _alloc);
			for (i = 0; i < n && p != end(); i++)
				*p++ = t;
			for (; i < n; i++, p++)
				_alloc.construct(_markers._start + (p - begin()), t);
			for (; p != end(); p++, tmp_start++)
				*p = *tmp_start;
			ft::_my_uninitialized_copy(tmp_start, tmp_end, p, _alloc);
			ft::destroy(iterator(tmp), tmp_end, _alloc);
			safe_deallocate(tmp, block_len);
			_markers._end += n;
		}
		else // copy at the end of the vector
		{
			for (i = 0; i < n; i++, p++)
				_alloc.construct(_markers._start + (p - begin()), t);
			_markers._end += n;
		}
	}
	else // need to allocate more room
	{
		size_type	len = check_len(n);	
		pointer		pstart = _alloc.allocate(len);
		iterator	new_start = iterator(pstart);
		iterator	new_end = ft::_my_uninitialized_copy(begin(), p, new_start, _alloc);
		for (i = 0; i < n; i++, new_end++)
			_alloc.construct(pstart + (new_end - new_start), t);
		new_end = ft::_my_uninitialized_copy(p, end(), new_end, _alloc);
		size_type	end_pos = new_end - new_start;
		ft::destroy(begin(), end(), _alloc);
		safe_deallocate(_markers._start, _markers._last - _markers._start);
		_markers._start = pstart;
		_markers._end = _markers._start + end_pos;
		_markers._last = _markers._start + len;
	}
}

template <typename T, typename Allocator>
template <typename _Iter>
void	vector<T, Allocator>::range_insert(iterator p, _Iter i, _Iter j, std::input_iterator_tag)
{
	if (p == end())
	{
		while (i != j)
		{
			insert(end(), *i);
			++i;
		}
	}
	else if (i != j)
	{
		vector	tmp(i, j);
		insert(p, tmp.begin(), tmp.end());
	}
}

template <typename T, typename Allocator>
template <typename _Iter>
void vector<T, Allocator>::range_insert(iterator p, _Iter i, _Iter j, std::forward_iterator_tag)
{
	size_type	n = ft::distance(i, j);
	size_type	k;
	// check if there is enough room in current allocation
	if ((_markers._end + n) <= _markers._last)
	{
		// insertion inside the vector
		if (p != end())
		{
			pointer		tmp = _alloc.allocate(n);
			iterator	tmp_start = iterator(tmp);
			iterator	tmp_end = ft::_my_uninitialized_copy(p, p + n, tmp_start, _alloc);
			for (k = 0; k < n && p != end(); k++)
				*p++ = *i++;
			for (; k < n; k++, p++, i++)
				_alloc.construct(_markers._start + (p - begin()), *i);
			ft::_my_uninitialized_copy(tmp_start, tmp_end, p + n, _alloc);
			ft::destroy(tmp_start, tmp_end, _alloc);
			safe_deallocate(tmp, n);
			_markers._end += n;
		}
		else // copy at the end of the vector
		{
			for (k = 0; k < n; k++, p++, i++)
				_alloc.construct(_markers._start + (p - begin()), *i);
			_markers._end += n;
		}
	}
	else // need to allocate more room
	{
		size_type	len = check_len(n);	
		pointer		pstart = _alloc.allocate(len);
		iterator	new_start = iterator(pstart);
		iterator	new_end = ft::_my_uninitialized_copy(begin(), p, new_start, _alloc);
		new_end = ft::_my_uninitialized_copy(i, j, new_end, _alloc);
		new_end = ft::_my_uninitialized_copy(p, end(), new_end, _alloc);
		size_type	end_pos = new_end - new_start;
		ft::destroy(begin(), end(), _alloc);
		safe_deallocate(_markers._start, _markers._last - _markers._start);
		_markers._start = pstart;
		_markers._end = _markers._start + end_pos;
		_markers._last = _markers._start + len;
	}
}	

template <typename T, typename Allocator>
void	vector<T, Allocator>::reserve(size_type n)
{
	if (n > max_size())
		throw std::length_error("Tried to reserve in excess of maximum capacity");
	if (n > capacity())
	{
		pointer	new_start = _alloc.allocate(n);
		iterator	i_start = iterator(new_start);
		iterator	i_end = ft::_my_uninitialized_copy(begin(), end(), i_start, _alloc);
		ft::destroy(begin(), end(), _alloc);
		safe_deallocate(_markers._start, _markers._last - _markers._start);
		_markers._start = new_start;
		_markers._end = new_start + (i_end - i_start);
		_markers._last = new_start + n;
	}
}

} // namespace ft

#endif
