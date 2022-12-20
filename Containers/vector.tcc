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

template <typename T, typename Allocator>
typename vector<T, Allocator>::iterator
vector<T, Allocator>::insert(iterator p, const value_type& t)
{
	size_type	n = p - begin();

	// check if there is enough room in current allocation
	if (_markers._end != _markers._last)
	{
		if (p != end()) // insert inside the vector
		{
			value_type	current = t;
			value_type	forward;
			while (p != end())
			{
				forward = *p;
				*p = current;
				current = forward;
				p++;
			}
		}
		_alloc.construct(_markers._end, t); // append
		_markers._end++;
	}
	else // need to allocate more room
	{
		size_type	len = check_len(1);
		pointer	new_start = _alloc.allocate(len);
		iterator	new_end = std::uninitialized_copy(begin(), p, iterator(new_start));
		*new_end = t;
		new_end++;
		new_end = std::uninitialized_copy(p, end(), new_end);
		size_type	end_pos = new_end - iterator(new_start);
		ft::destroy(begin(), end(), _alloc);
		_alloc.deallocate(_markers._start, _markers._last - _markers._start);
		_markers._start = new_start;
		_markers._end = _markers._start + end_pos;
		_markers._last = _markers._start + len;
	}
	return (begin() + n);
}

template <typename T, typename Allocator>
void vector<T, Allocator>::fill_insert(iterator p, size_type n, const value_type& t)
{
	size_type	i;
	// check if there is enough room in current allocation
	if ((_markers._end + n) <= _markers._last)
	{
		// insertion inside the vector
		if (p != end())
		{
			pointer		tmp = _alloc.allocate(n);
			iterator	tmp_start = iterator(tmp);
			iterator	tmp_end = std::uninitialized_copy(p, p + n, tmp_start);
			for (i = 0; i < n && p != end(); i++)
				*p++ = t;
			for (; i < n; i++, p++)
				_alloc.construct(_markers._start + (p - begin()), t);
			std::uninitialized_copy(tmp_start, tmp_end, p + n);
			ft::destroy(tmp_start, tmp_end, _alloc);
			_alloc.deallocate(tmp, n);
		}
		else // copy at the end of the vector
		{
			for (i = 0; i < n; i++, p++)
				_alloc.construct(_markers._start + (p - begin()), t);
		}
	}
	else // need to allocate more room
	{
		size_type	len = check_len(n);	
		pointer		pstart = _alloc.allocate(len);
		iterator	new_start = iterator(pstart);
		iterator	new_end = std::uninitialized_copy(begin(), p, new_start);
		for (i = 0; i < n; i++, new_end++)
			_alloc.construct(pstart + (new_end - new_start), t);
		new_end = std::uninitialized_copy(p, end(), new_end);
		size_type	end_pos = new_end - new_start;
		ft::destroy(begin(), end(), _alloc);
		_alloc.deallocate(_markers._start, _markers._last - _markers._start);
		_markers._start = pstart;
		_markers._end = _markers._start + end_pos;
		_markers._last = _markers._start + len;
	}
}

template <typename T, typename Allocator>
template <typename _Iter>
void vector<T, Allocator>::range_insert(iterator p, _Iter i, _Iter j)
{
	size_type	n = j - i;
	size_type	k;
	// check if there is enough room in current allocation
	if ((_markers._end + n) <= _markers._last)
	{
		// insertion inside the vector
		if (p != end())
		{
			pointer		tmp = _alloc.allocate(n);
			iterator	tmp_start = iterator(tmp);
			iterator	tmp_end = std::uninitialized_copy(p, p + n, tmp_start);
			for (k = 0; k < n && p != end(); k++)
				*p++ = *i++;
			for (; k < n; k++, p++, i++)
				_alloc.construct(_markers._start + (p - begin()), *i);
			std::uninitialized_copy(tmp_start, tmp_end, p + n);
			ft::destroy(tmp_start, tmp_end, _alloc);
			_alloc.deallocate(tmp, n);
		}
		else // copy at the end of the vector
		{
			for (k = 0; k < n; k++, p++, i++)
				_alloc.construct(_markers._start + (p - begin()), *i);
		}
	}
	else // need to allocate more room
	{
		size_type	len = check_len(n);	
		pointer		pstart = _alloc.allocate(len);
		iterator	new_start = iterator(pstart);
		iterator	new_end = std::uninitialized_copy(begin(), p, new_start);
		for (k = 0; k < n; k++, new_end++, i++)
			_alloc.construct(pstart + (new_end - new_start), *i);
		new_end = std::uninitialized_copy(p, end(), new_end);
		size_type	end_pos = new_end - new_start;
		ft::destroy(begin(), end(), _alloc);
		_alloc.deallocate(_markers._start, _markers._last - _markers._start);
		_markers._start = pstart;
		_markers._end = _markers._start + end_pos;
		_markers._last = _markers._start + len;
	}
}	

}

#endif
