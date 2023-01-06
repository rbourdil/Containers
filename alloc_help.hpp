#ifndef ALLOC_HELP_HPP
#define ALLOC_HELP_HPP

#include <memory>

namespace ft {

	template <typename ForwardIter, typename Allocator>
	void	destroy(ForwardIter first, ForwardIter last, Allocator alloc)
	{
		while (first != last)
		{
			alloc.destroy(__builtin_addressof(*first));
			first++;
		}
	}

	template <typename InputIt, typename FwdIt, typename Allocator>
	FwdIt	_my_uninitialized_copy(InputIt first, InputIt last, FwdIt p, Allocator alloc)
	{
		while (first != last)
		{
			alloc.construct(__builtin_addressof(*p), *first);
			first++;
			p++;
		}
		return (p);
	}

	template <typename InputIt, typename T, typename Allocator>
	void	_my_uninitialized_fill(InputIt first, InputIt last, const T& val, Allocator alloc)
	{
		while (first != last)
		{
			alloc.construct(__builtin_addressof(*first), val);
			first++;
		}
	}

}

#endif
