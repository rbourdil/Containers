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

}

#endif
